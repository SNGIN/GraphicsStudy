#include "Title.h"
#include "InputManager.h"
#include "SeaquenceController.h"
#include "GameSeaquenceController.h"
#include "SimpleImageMaterial.h"

Title::Title()
{
	//ウィンドウサイズのRectオブジェクト用意
	mrect = new Rect(1, 1);
	//シェーダー使用定義
	Shader* titleShader = new Shader("simpleTex.vert","simpleTex.frag");

	//テクスチャ定義
	Texture* tex = new Texture("texture1.tga", GL_RGBA);

	//マテリアル定義
	SimpleImageMaterial* mat = new SimpleImageMaterial(titleShader,tex);
	mrect->SetMaterial(mat);
}


Title::~Title()
{
	//タイトルで使ってるリソースの解放
	Common::Delete(mrect);
}

Boot* Title::Update(SeaquenceController* controller){
	Boot* next = this;

	std::cout << "Title" << std::endl;
	mrect->Draw();
	if (InputManager::CheckInputSpace()){
		next = new GameSeaquenceController();
	}
	return next;
}