#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// ����
const vec4 pl = vec4(3.0, 4.0, 5.0, 1.0);           // �ʒu
const vec3 ldiff  = vec3(1.0, 1.0, 1.0);            // �g�U���ː����̋��x

// �ގ�
const vec3 kdiff  = vec3(0.8, 0.8, 0.8);            // �g�U���ˌW��

// ���_����
layout (location = 0) in vec4 pv;                   // ���[�J�����W�n�̒��_�ʒu
layout (location = 1) in vec4 nv;                   // ���_�̖@���x�N�g��

// �ϊ��s��
uniform mat4 mw;                                    // ���_���W�n�ւ̕ϊ��s��
uniform mat4 mc;                                    // �N���b�s���O���W�n�ւ̕ϊ��s��
uniform mat4 mg;                                    // �@���x�N�g���̕ϊ��s��

// ���X�^���C�U�ɑ��钸�_����
out vec3 idiff;                                     // �g�U���ˌ����x

void main(void)
{
  vec4 p = mw * pv;                                 // ���_���W�n�̒��_�̈ʒu
  vec3 l = normalize((pl * p.w - p * pl.w).xyz);    // �����x�N�g��
  vec3 n = normalize((mg * nv).xyz);                // �@���x�N�g��

  idiff = max(dot(n, l), 0.0) * kdiff * ldiff;

  gl_Position = mc * pv;
}