#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// �ϊ��s��
uniform mat4 mc;                                    // �N���b�s���O���W�n�ւ̕ϊ��s��

// ���_����
layout (location = 0) in vec4 pv;                   // ���[�J�����W�n�̒��_�ʒu

in vec2 tv;
out vec2 uv;

void main(){
	gl_Position = pv * mc;
	uv = tv;
}