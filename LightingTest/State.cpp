#include "State.h"
#include "GoalObj.h"
#include "DynamicObj.h"

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

	//敵の数とプレイヤーの数
	mDynamicObjectNumber = 1 + stageData.enemyNumber;
	mDynamicObjects = new DynamicObj[mDynamicObjectNumber];

	//プレイヤーの取得（？）

	//プレイヤーの配置
	mDynamicObjects[0].Set(0, 0);
}

State::~State()
{
	Common::Delete(mDynamicObjects);
}

//各オブジェクトの描画
void State::Draw()const{

}

//各オブジェクトの更新
void State::Update(){

}

//クリアしたかどうかのチェック
bool State::hasCleared()const{
	return mGoalObj->CheckGoal();
}

//ミスしたかどうか
bool State::hasMissed()const{
	//落ちたらミスの判定を入れる
	return false;
}