// フラグメントシェーダのソースプログラム
#version 150 core

in vec2 texCoordV;
out vec4 fc;
uniform sampler2D texture1;

void main(void)
{
  fc = texture(texture1,texCoordV);
  //fc = vec4(1.0,0.0,0.0,1.0);
}