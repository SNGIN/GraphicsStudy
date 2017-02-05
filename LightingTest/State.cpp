#include "State.h"
#include "GoalObj.h"
#include "Player.h"
#include "InputManager.h"

//マップの広さ
static const int WIDTH = 20;
static const int HEIGHT = 15;

//適当なステージデータ(拡張予定)
struct StageData
{
	int mBlockNumber;
	int enemyNumber;
};

static StageData gStageData[] = {
	{5},
	{0},
};

State::State(int stageID) :mDynamicObjects(0), mDynamicObjectNumber(0), mstageID(stageID)
{
	//Widthとheightを利用して地面を作る

	//ステージパラメータの読み込み
	const StageData& stageData = gStageData[mstageID];
	//ブロックを作ってセットしていく
	
	//ゴールオブジェクトを作る
	mGoalObj = new GoalObj();
	mGoalObj->SetFlag(StaticObj::FLAG_GOAL);

	DynamicObj* p = new Player();
	//プレイヤーの配置

	//敵の数とプレイヤーの数
	mDynamicObjectNumber = 1 + stageData.enemyNumber;
	mDynamicObjects = new DynamicObj*[mDynamicObjectNumber];
	
	//プレイヤー
	mDynamicObjects[0] = p;
	//配置
	mDynamicObjects[0]->Set(0,2);

	//敵
	for (int i = 0; i < mDynamicObjectNumber; i++){
		if (i>0){

			//配置
		}
	}
}

State::~State()
{
	Common::Delete(*mDynamicObjects);
	Common::Delete(mDynamicObjects);
}

//各オブジェクトの描画
void State::Draw(){
	for (int i = 0; i < mDynamicObjectNumber; i++){
		mDynamicObjects[i]->Draw();
	}
}

//各オブジェクトの更新
void State::Update(){
	for (int i = 0; i < mDynamicObjectNumber; i++){
		mDynamicObjects[i]->Update();
	}

	if (mDynamicObjects[0]->Get().x() < -2.5 || mDynamicObjects[0]->Get().x() > 2.5){
		//TODO:本来はゴールオブジェクトに触れたら
		miss = true;
	}

	if (mDynamicObjects[0]->Get().z() < -2.5){
		//TODO:本来はゴールオブジェクトに触れたら
		clear = true;
	}

}

//クリアしたかどうかのチェック
bool State::hasCleared()const{
	return clear;
}

//ミスしたかどうか
bool State::hasMissed()const{
	//落ちたらミスの判定を入れる
	return miss;
}