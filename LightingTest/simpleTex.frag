#version 150 core
#extension GL_ARB_explicit_attrib_location : enable
// �t���[���o�b�t�@�ɏo�͂���f�[�^
layout (location = 0) out vec4 fc;                  // �t���O�����g�̐F

uniform sampler2D tex;

in vec2 uv;

void main()
{
 //fc = vec4(1.0, 0.0, 0.0, 1.0);
 fc = texture(tex,uv);
}