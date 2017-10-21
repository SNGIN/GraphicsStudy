#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// ����
uniform vec4 lamb;       // ��������
uniform vec4 ldiff;       // �g�U���ˌ�����
uniform vec4 lspec;                                 // ���ʔ��ˌ�����
uniform vec4 pl;          // �ʒu

// �ގ�
uniform vec4 kamb;                                  // �����̔��ˌW��
uniform vec4 kdiff;                                 // �g�U���ˌW��
uniform vec4 kspec;                                 // ���ʔ��ˌW��
uniform float kshi;                                 // �P���W��

// �ϊ��s��
uniform mat4 modelMatrix; 			//���f���s��(ModelMatrix)
uniform mat4 modelViewMatrix;		// ���f���r���[�s��
uniform mat4 modelViewprojectionMatrix;	   // �N���b�s���O���W�n�ւ̕ϊ��s��
uniform mat4 viewMatrix;			//�r���[�s��
uniform mat4 normalMatrix;			//�@���x�N�g���̍s��

// ���_����
layout (location = 0) in vec4 pv;                   // ���[�J�����W�n�̒��_�ʒu
layout (location = 1) in vec4 nv;                   // ���_�̖@���x�N�g��

// ���X�^���C�U�ɑ��钸�_����
out vec4 iamb;                                      // �����̔��ˌ����x
out vec4 idiff;                                     // �g�U���ˌ����x
out vec4 ispec;                                     // ���ʔ��ˌ����x

out vec3 vViewPosition;	//���_�ʒu���王�_�ʒu�܂ł̃x�N�g��
out vec3 vNormal;			//�@���x�N�g���̍s��Ŗ@���ϊ���������

void main(){
	vViewPosition = -1.0*(modelViewMatrix * pv).xyz;
	vNormal = (normalMatrix * nv).xyz;
	gl_Position = modelViewprojectionMatrix * pv;

}