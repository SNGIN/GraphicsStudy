#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// ����
uniform vec4 lamb = vec4(0.2, 0.2, 0.2, 1.0);       // ��������
uniform vec4 ldiff = vec4(1.0, 1.0, 1.0,1.0);       // �g�U���ˌ�����
uniform vec4 lspec = vec4(1.0f, 1.0f, 1.0f, 1.0f);                                 // ���ʔ��ˌ�����
uniform vec4 pl= vec4(3.0, 4.0, 5.0, 1.0);          // �ʒu

// �ގ�
uniform vec4 kamb;                                  // �����̔��ˌW��
uniform vec4 kdiff;                                 // �g�U���ˌW��
uniform vec4 kspec;                                 // ���ʔ��ˌW��
uniform float kshi;                                 // �P���W��

// �ϊ��s��
uniform mat4 mw;                                    // ���_���W�n�ւ̕ϊ��s��
uniform mat4 mc;                                    // �N���b�s���O���W�n�ւ̕ϊ��s��
uniform mat4 mg;                                    // �@���x�N�g���̕ϊ��s��

// ���_����
layout (location = 0) in vec4 pv;                   // ���[�J�����W�n�̒��_�ʒu
layout (location = 1) in vec4 nv;                   // ���_�̖@���x�N�g��

// ���X�^���C�U�ɑ��钸�_����
out vec4 iamb;                                      // �����̔��ˌ����x
out vec4 idiff;                                     // �g�U���ˌ����x
out vec4 ispec;                                     // ���ʔ��ˌ����x

//�f�v�X�}�b�v�̃e�N�X�`�����W
out vec4 dtc; 

void main(void)
{

  vec4 p = mw * pv;                                 // ���_���W�n�̒��_�̈ʒu
  vec3 v = -normalize(p.xyz / p.w);                 // �����x�N�g��
  vec3 l = normalize((pl * p.w - p * pl.w).xyz);    // �����x�N�g��
  vec3 n = normalize((mg * nv).xyz);                // �@���x�N�g��
  vec3 h = normalize(l + v);                        // ���ԃx�N�g��

  iamb = kamb * lamb;
  idiff = max(dot(n, l), 0.0) * kdiff * ldiff;
  ispec = pow(max(dot(n, h), 0.0), kshi) * kspec * lspec;

  gl_Position = mc * pv;
}