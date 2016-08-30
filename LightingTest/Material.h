#pragma once
#include "Shader.h"

//材質情報と使用するシェーダを保持するクラス
class Material
{
	//環境光の反射係数
	GLfloat(*amb)[4];
	//拡散反射係数
	GLfloat(*diff)[4];
	//鏡面反射係数
	GLfloat(*spec)[4];
	//輝き係数
	GLfloat*shi;
	//使用するシェーダ
	Shader *m_shader;

public:
	Material(){};
	~Material(){};

	//引数ありのコンストラクタで材質の設定とシェーダーの選択をさせたい
	//(ついでにメンバのシェーダクラスに情報を渡す)

	void attachShader(Shader &shader){
		this->m_shader = &shader;
	}

	void attachShader(Shader *shader){
		this->m_shader = shader;
	}

};

