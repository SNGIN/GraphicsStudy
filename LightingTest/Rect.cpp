#include "Rect.h"
#include "Window.h"

Rect::Rect()
{
}

Rect::Rect(GLfloat width, GLfloat height){
	// 基準となる形状
	static const GLfloat p[][2] =
	{
		{ -0.5f, -0.5f },
		{ 0.5f, -0.5f },
		{ 0.5f, 0.5f },
		{ -0.5f, 0.5f },
	};

	GLfloat tmpuv[4][2] = {
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 1.0f },
	};

	// 作業用のメモリ
	GLfloat pos[4][3];
	GLfloat norm[4][3];

	// 頂点位置と法線ベクトルを求める
	for (int v = 0; v < 4; ++v)
	{
		uv[v][0] = tmpuv[v][0];
		uv[v][1] = tmpuv[v][1];

		pos[v][0] = p[v][0] * width;
		pos[v][1] = p[v][1] * height;
		pos[v][2] = 0.0f;

		norm[v][0] = 0.0f;
		norm[v][1] = 0.0f;
		norm[v][2] = 1.0f;
	}

	mtriangle = new ShapeTriangle(4, pos, norm, GL_TRIANGLE_FAN);
}

Rect::~Rect()
{
	Common::Delete(mtriangle);
}

void Rect::SetMaterial(Material* mat){
	mMaterial = mat;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 頂点の座標値 tv 用のバッファオブジェクト
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof uv, uv, GL_STATIC_DRAW);

	//uvやテクスチャの位置をin変数から参照できるようにセットする
	mMaterial->SetTexLoc();
}

void Rect::Draw(){
	if (mtriangle != NULL && mMaterial != NULL){
		//使う頂点バッファオブジェクトの指定
		mtriangle->Use();
		//使うシェーダとテクスチャの指定
		mMaterial->m_shader->Use();
		mMaterial->UseTexture();
		//配置
		mMaterial->m_shader->loadMatrix(Window::getMp(), Window::ReturnMV()*Translate(0.0f, 0.0f, 0.0f));
		//描く
		mtriangle->Draw();
	}
}