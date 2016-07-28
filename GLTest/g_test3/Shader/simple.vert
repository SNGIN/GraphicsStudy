// バーテックスシェーダのソースプログラム
#version 150 core

in vec4 pv;
uniform vec2 scale;
uniform vec2 posi;
uniform vec2 texposi;

in vec2 texCoord;

out vec2 texCoordV;

uniform float aspect;

void main(void)
{
	texCoordV = texCoord + texposi;
	gl_Position = pv * vec4(scale,1.0,1.0) + vec4(posi,0.0f,0.0f);
}