#pragma once
#include "Commonheader.h"

static class Shader
{
private:
	Shader();
	~Shader();
public:
#ifdef DEBUG
	// シェーダオブジェクトのコンパイル結果を表示する
	GLboolean printShaderInfoLog(GLuint shader, const char *str);
	
	// シェーダオブジェクトのリンク結果を表示
	GLboolean printProgramInfoLog(GLuint program);
#endif // DEBUG

	// 読み込んだメモリを返す
	GLchar *readShaderSource(const char *name);

	// プログラムオブジェクトの作成
	GLuint createProgram(const char *vsrc, const char *pv, const char *fsrc, const char *fc,
		const char *vert = "vertex shader", const char *frag = "fragment shader");

	// シェーダのソースファイルの読み込み
	GLuint loadProgram(const char *vert, const char *pv, const char *frag, const char *fc);
};

