#pragma once
#include "Shader.h"

//材質情報と使用するシェーダを保持するクラス
class Material
{
	//環境光の反射係数
	GLfloat(*m_amb);
	//拡散反射係数
	GLfloat(*m_diff);
	//鏡面反射係数
	GLfloat(*m_spec);
	//輝き係数
	GLfloat*m_shi;


public:
	Material(){};
	~Material();

	//使用するシェーダ
	Shader *m_shader;

	//引数ありのコンストラクタで材質の設定とシェーダーの選択をさせたい
	//(ついでにメンバのシェーダクラスに情報を渡す)
	Material(Shader* shader);

	void attachShader(Shader &shader){
		this->m_shader = &shader;
	}

	void attachShader(Shader *shader){
		this->m_shader = shader;
	}

	Shader* GetShader();

	virtual void SetMaterial();
	virtual void UseTexture(){};
	virtual void SetTexLoc(){};

};

