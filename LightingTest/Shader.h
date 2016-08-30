#pragma once
#include "Commonheader.h"
#include "BufferBase.h"

//光源特性
struct Light
{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat position[4];

	// シェーダーソースでの場所
	GLint pl;         // 光源位置の uniform 変数の場所
	GLint lamb;       // 光源強度の環境光成分の uniform 変数の場所
	GLint ldiff;      // 光源強度の拡散反射光成分の uniform 変数の場所
	GLint lspec;      // 光源強度の鏡面反射光成分の uniform 変数の場所
};

//材質情報のシェーダーソースでの場所
struct MaterialLoc
{
	GLint kamb;       // 環境光の反射係数の uniform 変数の場所
	GLint kdiff;      // 拡散反射係数の uniform 変数の場所
	GLint kspec;      // 鏡面反射係数の uniform 変数の場所
	GLint kshi;       // 輝き係数の uniform 変数の場所
	GLint mg;         // モデルビュー変換の法線変換行列の uniform 変数の場所
};


static GLchar *ReadShaderSource(const char *name);

extern GLuint LoadShader(const char *vert, const char *frag, const char *geom,
	GLint nvarying, const char **varyings);

#ifdef DEBUG
// シェーダオブジェクトのコンパイル結果を表示する
extern GLboolean printShaderInfoLog(GLuint shader, const char *str);

// シェーダオブジェクトのリンク結果を表示
extern GLboolean printProgramInfoLog(GLuint program);
#endif // DEBUG

// シェーダオブジェクトの作成
extern GLuint CreateShader(const char *vsrc, const char *fsrc, const char *gsrc,
	GLint nvarying, const char **varyings, const char *vtext, const char *ftext, const char *gtext);

//シェーダークラス(メインでインスタンス化され、使用するマテリアルと紐づけられる(マテリアルクラスのメンバ変数として))
class Shader :public BufferBase{

	//シェーダープログラム名
	GLuint program;

	//光源情報(複数あるかも)

	//材質情報(一つでいい)

public:

	//デストラクタ
	~Shader(){
		//参照してるオブジェクトが一つならシェーダを削除
		if (program != 0 && last()){
			glUseProgram(0);
			glDeleteProgram(program);
		}
	}
	Shader(){}

	//引数ありのコンストラクタ
	Shader(const char *vert, const char *frag = 0, const char *geom = 0,
		int nvarying = 0, const char **varyings = 0) :program(LoadShader(vert, frag, geom, nvarying, varyings)){}

	//コピーコンストラクタ
	Shader(const Shader &o) :BufferBase(o), program(o.program){}

	//代入演算子
	Shader &operator=(const Shader &o){
		if (&o != this){
			BufferBase::operator=(o);
			program = o.program;
		}
		return *this;
	}

	//別のシェーダプログラムを登録
	void SetProgram(GLuint newProgram){
		if (program != 0 && newCounter()){
			glUseProgram(0);
			glDeleteProgram(program);
		}
		program = newProgram;
	}

	//シェーダのソースを読んでプログラムオブジェクトと紐づけ
	void load(const char *vert, const char *frag = 0, const char *geom = 0,
		GLint nvarying = 0, const char **varyings = 0)
	{
		SetProgram(LoadShader(vert, frag, geom, nvarying, varyings));
	}

	void Use()const{
		glUseProgram(program);
	}

	void EndUse()const{
		glUseProgram(0);
	}

	GLuint GetProgramName()const{
		return program;
	}
};