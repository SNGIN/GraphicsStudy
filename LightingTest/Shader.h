#pragma once
#include "Commonheader.h"
#include "BufferBase.h"
#include "Texture.h"

//材質情報のシェーダーソースでの場所
struct MaterialLoc
{
	GLint kamb;       // 環境光の反射係数の uniform 変数の場所
	GLint kdiff;      // 拡散反射係数の uniform 変数の場所
	GLint kspec;      // 鏡面反射係数の uniform 変数の場所
	GLint kshi;       // 輝き係数の uniform 変数の場所
};

//変換行列のシェーダーソースでの場所
struct MatrixLoc
{
	GLint mc;
	GLint mw;
	GLint mg;         // モデルビュー変換の法線変換行列の uniform 変数の場所
};

static GLchar *ReadShaderSource(const char *name);

extern GLuint LoadShader(const char *vert, const char *frag = NULL, const char *geom = NULL,
	int nvarying = 0, const char *varyings[] = NULL);

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

public:

	MaterialLoc loc_material;
	MatrixLoc loc_matrix;

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
		int nvarying = 0, const char **varyings = 0) :program(LoadShader(vert, frag, geom, nvarying, varyings)){
		
		// 変換行列の uniform 変数の場所
		loc_matrix.mc = glGetUniformLocation(program, "mc");
		loc_matrix.mw = glGetUniformLocation(program, "mw");
		// 変換行列の uniform 変数の場所
		loc_matrix.mg = glGetUniformLocation(program, "mg");
	}

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

	//シェーダプログラムを登録
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

	//変換行列,mp=投影変換行列 mw モデルビュー変換行列
	virtual void loadMatrix(Matrix mp, Matrix mw);

	virtual void UseSimpleShader(Texture tex){};
};