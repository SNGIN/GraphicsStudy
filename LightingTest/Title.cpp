#include "Title.h"
#include "InputManager.h"
#include "SeaquenceController.h"
#include "GameSeaquenceController.h"
#include "SimpleImageMaterial.h"

Title::Title()
{
	//ウィンドウサイズのRectオブジェクト用意
	GLfloat aspect = (GLfloat)Window::Get_h() / (GLfloat)Window::Get_w();
	mrect = new Rect(15.0f, 15.0f*aspect, Vector3(0.0f, 0.0f, 20.0f), true);
	//シェーダー使用定義
	Shader* titleShader = new Shader("simpleTex.vert","simpleTex.frag");

	//テクスチャ定義
	Texture* tex = new Texture("texture1.tga", GL_RGBA);

	//マテリアル定義
	SimpleImageMaterial* mat = new SimpleImageMaterial(titleShader,tex);
	mrect->SetMaterial(mat);

	std::cout << "Title" << std::endl;
}


Title::~Title()
{
	//タイトルで使ってるリソースの解放
	Common::Delete(mrect);
}

Boot* Title::Update(SeaquenceController* controller){
	Boot* next = this;

	mrect->Draw();
	if (InputManager::CheckInputSpace()){
		next = new GameSeaquenceController();
	}
	return next;
}