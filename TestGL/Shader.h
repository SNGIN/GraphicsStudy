#pragma once
#include "Commonheader.h"


#ifdef DEBUG
	// シェーダオブジェクトのコンパイル結果を表示する
	extern GLboolean printShaderInfoLog(GLuint shader, const char *str);
	
	// シェーダオブジェクトのリンク結果を表示
	extern GLboolean printProgramInfoLog(GLuint program);
#endif // DEBUG

	// プログラムオブジェクトの作成
	extern GLuint createProgram(const char *vsrc, const char *pv, const char *fsrc, const char *fc,
		const char *vert = "vertex shader", const char *frag = "fragment shader");

	// シェーダのソースファイルの読み込み
	extern GLuint loadProgram(const char *vert, const char *pv, const char *frag, const char *fc);

