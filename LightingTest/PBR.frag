#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

in vec3 vViewPosition;
in vec3 vNormal;

// uniforms
float metallic = 0.01;
float roughness = 0.85;
vec3 albedo = vec3(1.0,1.0,1.0);

// defines
#define PI 3.14159265359
#define PI2 6.28318530718
#define RECIPROCAL_PI 0.31830988618
#define RECIPROCAL_PI2 0.15915494
#define LOG2 1.442695
#define EPSILON 1e-6

//�|���S���֘A�̃f�[�^
struct Geometry{
	vec3 position;
	vec3 normal;
	vec3 viewDir;
};

//�����̃f�[�^
struct IncidentLight{
	vec3 direction;	//���˕���
	vec3 color;		//�F
	bool visible;	//�����͂��Ă邩�ǂ���
};

//�ގ��̃p�����[�^
struct Material{
	vec3 diffuseColor;
	float specularRoughness;
	vec3 specularColor;
};

//���z��
struct DirectionalLight{
	vec3 direction;	//���Е���
	vec3 color;
};

//�_����
struct PointLight {
  vec3 position;	//�ʒu
  vec3 color;	//�F
  float distance;	//�����͂�����
  float decay;	//������
};

//�X�|�b�g���C�g
struct SpotLight {
  vec3 position;
  vec3 direction;
  vec3 color;
  float distance;
  float decay;
  float coneCos;	//���[���cos�l�V�F�[�_�[�Ŏg�p����cos�l
  float penumbraCos;	//���e��cos�l(�V�F�[�_�[�Ŏg�p����)
};

//����
struct ReflectedLight {
  vec3 directDiffuse;
  vec3 directSpecular;
  vec3 indirectDiffuse;
  vec3 indirectSpecular;
};

//�����n�Ńv���O��������n�����f�[�^
#define LIGHT_MAX 1
DirectionalLight directionalLights[LIGHT_MAX];
PointLight pointLights[LIGHT_MAX];
uniform SpotLight spotLights[LIGHT_MAX];
int numDirectionalLights = 0;
int numPointLights = 1;
uniform int numSpotLights;

//�����������Ă邩�ǂ����͈͎̔擾
bool LightInRange(const in float lightDistance,const in float cutoffDistance){
	return any(bvec2(cutoffDistance == 0.0,lightDistance < cutoffDistance));
}

//���������l���������ˏƓx�擾
float PunctualLightIntensityToIrradianceFactor(const in float lightDistance,const in float cutoffDistance,const in float decayExponent){
	//�������v�Z http://hiyoko1986.web.fc2.com/program/pages/WebGL/PointLight.html
	if(decayExponent > 0.0){
		return pow(clamp((-lightDistance / cutoffDistance+1.0),0,1),decayExponent);
	}
	return 1.0;
}

//directLight�̕��ˏƓx
void GetDirectionalLightIrradiance(const in DirectionalLight directionalLight, const in Geometry geometry, out IncidentLight directLight){
	directLight.color = directionalLight.color;
	directLight.direction = directionalLight.direction;
	directLight.visible = true;
}

//PointLight�̕��ˏƓx
void GetPointLightIrradiance(const in PointLight pointLight, const in Geometry geometry, out IncidentLight directLight){
	//�����܂ł̋���,�����̐��K��
	vec3 L = pointLight.position - geometry.position;
	directLight.direction = normalize(L);
	float lightDistance = length(L);

	//�����͂����͂��Ȃ����ŐF�t���𕪂���
	bool visible = LightInRange(lightDistance,pointLight.distance);
	directLight.color = (visible) ? pointLight.color : vec3(0.0);
	directLight.color *= PunctualLightIntensityToIrradianceFactor(lightDistance, pointLight.distance, pointLight.decay); 
	directLight.visible = (visible) ? true : false;
}

//�X�|�b�g���C�g�̕��ˏƓx
void GetSpotDirectLightIrradiance(const in SpotLight spotLight,const in Geometry geometry, out IncidentLight directLight){
	//�����܂ł̋���,�����̐��K��
	vec3 L = spotLight.position - geometry.position;
	directLight.direction = normalize(L);
	float lightDistance = length(L);
	float angleCos = dot(directLight.direction,spotLight.direction);
	
	//�����������Ă��邩�ǂ���(�~�����������͂������Ȃ�)
	bool visible = all(bvec2(angleCos > spotLight.coneCos, LightInRange(lightDistance, spotLight.distance)));
	
	float spotEffect = (visible) ? smoothstep(spotLight.coneCos,spotLight.penumbraCos,angleCos) : 0;
	directLight.color = (visible) ? spotLight.color : vec3(0.0);
	directLight.visible = (visible) ? true : false;

	directLight.color *= spotEffect * PunctualLightIntensityToIrradianceFactor(lightDistance, spotLight.distance, spotLight.decay); 
}

//�g�U����BRDF(Lambert)
vec3 DiffuseBRDF(vec3 diffuseColor){
	return diffuseColor/PI;
}

//�t���l����(F�V�����b�N)
vec3 F_Schlick(vec3 specularColor, vec3 H, vec3 V){
	return (specularColor + (1.0 - specularColor) * pow(1.0 - clamp(dot(V,H),0.0,1.0),5.0));
}

//D��(D_ggx)
float D_GGX(float a, float dotNH){
	float a2 = a*a;
	float dotNH2 = dotNH*dotNH;
	float d = dotNH2 * (a2 - 1.0) + 1.0;
	return a2 / (PI * d * d);
}

//G��(G_smith)
float G_Smith_Schlick_GGX(float a, float dotNV, float dotNL) {
  float k = a*a*0.5 + EPSILON;
  float gl = dotNL / (dotNL * (1.0 - k) + k);
  float gv = dotNV / (dotNV * (1.0 - k) + k);
  return gl*gv;
}

//���ʔ���(CookTorrance) D_ggx,�􉽌���,�t���l�� / 4(n�El)(n�Ev)
vec3 SpecularBRDF(const in IncidentLight directLight, const in Geometry geometry, vec3 specularColor,float roughnessFactor){
	vec3 N = geometry.normal;
	vec3 V = geometry.viewDir;
	vec3 L = directLight.direction;

	float dotNL = clamp(dot(N,L),0.0,1.0);
	float dotNV = clamp(dot(N,V),0.0,1.0);
	vec3 H = normalize(L+V);
	float dotNH = clamp(dot(N,H),0.0,1.0);
	float dotVH = clamp(dot(V,H),0.0,1.0);
	float dotLV = clamp(dot(L,V),0.0,1.0);
	float a = roughnessFactor * roughnessFactor;

	float D = D_GGX(a,dotNH);
	float G = G_Smith_Schlick_GGX(a,dotNV,dotNL);
	vec3 F = F_Schlick(specularColor,V,H);

	return (F*(G*D))/(4.0*dotNL*dotNV+EPSILON);
}

//���ˌ��̌v�Z
void RE_Direct(const in IncidentLight directLight, const in Geometry geometry, const in Material material, inout ReflectedLight reflectedLight) {
	//cos��
	float dotNL = clamp(dot(geometry.normal, directLight.direction),0,1);
	vec3 irradiance = dotNL * directLight.color;

	// punctual light
	irradiance *= PI;
	  
	reflectedLight.directDiffuse += irradiance * DiffuseBRDF(material.diffuseColor);
	reflectedLight.directSpecular += irradiance * SpecularBRDF(directLight, geometry, material.specularColor, material.specularRoughness);
}

// ���X�^���C�U����󂯎�钸�_�����̕�Ԓl
in vec4 iamb;                                       // �����̔��ˌ����x
in vec4 idiff;                                      // �g�U���ˌ����x
in vec4 ispec;                                      // ���ʔ��ˌ����x

float sum = 0;

// �t���[���o�b�t�@�ɏo�͂���f�[�^
layout (location = 0) out vec4 fc;                  // �t���O�����g�̐F

void main(void)
{
	//�|���S���֘A�̃f�[�^�ݒ�
	Geometry geometry;
	geometry.position = -vViewPosition;
	geometry.normal = normalize(vNormal);
	geometry.viewDir = normalize(vViewPosition);

	Material material;
	material.diffuseColor = mix(albedo,vec3(0.0),metallic);
	material.specularColor = mix(vec3(0.04),albedo,metallic);
	material.specularRoughness = roughness;

	directionalLights[0].color = vec3(0.015,0.2,0.02);
	directionalLights[0].direction = vec3(-3.0,1.0,5.0);

	pointLights[0].color = vec3(0.85);
	pointLights[0].position = vec3(5.0,3.0,0.0);
	pointLights[0].distance = 50.0;
	pointLights[0].decay = 0.2;

	//Lighting
	ReflectedLight reflectedLight = ReflectedLight(vec3(0.0),vec3(0.0),vec3(0.0),vec3(0.0));
	vec3 emissive = vec3(0.0);
	float opacity = 1.0;

	IncidentLight directLight;

	//PointLight
	for (int i=0; i<LIGHT_MAX; ++i) {
		if (i >= numPointLights) break;
		GetPointLightIrradiance(pointLights[i], geometry, directLight);
		if (directLight.visible) {
		  RE_Direct(directLight, geometry, material, reflectedLight);
		}
	}

	 // spot light
	 for (int i=0; i<LIGHT_MAX; ++i) {
	 if (i >= numSpotLights) break;
	 GetSpotDirectLightIrradiance(spotLights[i], geometry, directLight);
		if (directLight.visible) {
		 RE_Direct(directLight, geometry, material, reflectedLight);
		}
	 }
  
	  // directional light
	 for (int i=0; i<LIGHT_MAX; ++i) {
	 if (i >= numDirectionalLights) break;
	 GetDirectionalLightIrradiance(directionalLights[i], geometry, directLight);
		RE_Direct(directLight, geometry, material, reflectedLight);
	 }
	 //vec3 outgoingLight = directLight.color;
	 vec3 outgoingLight = emissive + reflectedLight.directDiffuse + reflectedLight.directSpecular + reflectedLight.indirectDiffuse + reflectedLight.indirectSpecular;
  
	fc = vec4(outgoingLight, opacity);

	//fc = idiff + iamb + ispec;
}