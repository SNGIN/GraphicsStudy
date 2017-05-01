#pragma once
#include "Commonheader.h"
#include "Quaternion.h"

/*
** トラックボール処理
*/
class TrackBall
{
	int cx, cy;                             // ドラッグ開始位置
	bool drag;                              // ドラッグ中か否か
	float sx, sy;                           // マウスの絶対位置→ウィンドウ内での相対位置の換算係数
	const float rotateSpeed = 0.1;
	Quaternion cq;                        // 回転の初期値 (四元数)
	Quaternion tq;                        // ドラッグ中の回転 (四元数)
	GLfloat rt[16];                         // 回転の変換行列

public:

	// デストラクタ
	virtual ~TrackBall(void) {}

	// コンストラクタ
	TrackBall(void);

	// トラックボール処理の範囲指定
	//    ウィンドウのリサイズ時に呼び出す
	void Region(int w, int h);

	// トラックボール処理の開始
	//    マウスのドラッグ開始時（マウスボタンを押したとき）に呼び出す
	void Start(int x, int y);

	// 回転の変換行列の計算
	//    マウスのドラッグ中に呼び出す
	void Motion(int x, int y);

	// トラックボール処理の停止
	//    マウスのドラッグ終了時（マウスボタンを離したとき）に呼び出す
	void Stop(int x, int y);

	// 現在の回転の変換行列を取り出す
	const GLfloat *Get(void) const
	{
		return rt;
	}
};

