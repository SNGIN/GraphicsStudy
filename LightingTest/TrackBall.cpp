#include "TrackBall.h"


TrackBall::TrackBall(void)
{
	// ドラッグ中ではない
	drag = false;

	// 単位クォーターニオン
	cq.loadIdentity();

	// 回転行列の初期化
	cq.getMatrix(rt);
}

/*
** 簡易トラックボール処理：トラックボールする領域の設定
**
**    Reshape コールバック (resize) の中で実行する
**    (w, h): ウィンドウサイズ
*/
void TrackBall::Region(int w, int h)
{
	// マウスポインタ位置のウィンドウ内の相対的位置への換算用
	sx = 1.0f / static_cast<float>(w);
	sy = 1.0f / static_cast<float>(h);
}

/*
** 簡易トラックボール処理：ドラッグ開始時の処理
**
**    マウスボタンを押したときに実行する
**    (x, y): 現在のマウス位置
*/
void TrackBall::Start(int x, int y)
{
	// ドラッグ開始
	drag = true;

	// ドラッグ開始点を記録する
	cx = x;
	cy = y;
}

/*
** 簡易トラックボール処理：ドラッグ中の処理
**
**    マウスのドラッグ中に実行する
**    (x, y): 現在のマウス位置
*/
void TrackBall::Motion(int x, int y)
{
	if (drag)
	{
		float dx, dy, a;

		// マウスポインタの位置のドラッグ開始位置からの変位
		dx = ((x - cx) * sx)/1000;
		dy = ((y - cy) * sy)/1000;

		// マウスポインタの位置のドラッグ開始位置からの距離
		a = sqrt(dx * dx + dy * dy)*rotateSpeed;

		if (a != 0.0)
		{
			// 現在の回転の四元数に作った四元数を掛けて合成する
			tq = RotateQuaternion(dy, dx, 0.0f, 0.01) * cq;
			// 合成した四元数から回転の変換行列を求める
			tq.getMatrix(rt);
		}
		// 現在の回転を表す四元数を正規化して保存する
		cq = tq.normalize();
	}
}

/*
** 簡易トラックボール処理：停止時の処理
**
**    マウスボタンを離したときに実行する
**    (x, y): 現在のマウス位置
*/
void TrackBall::Stop(int x, int y)
{
	// ドラッグ終了点における回転を求める
	Motion(x, y);

	// 現在の回転を表す四元数を正規化して保存する
	cq = tq.normalize();

	// ドラッグ終了
	drag = false;
}