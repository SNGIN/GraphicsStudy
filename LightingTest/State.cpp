#include "State.h"
#include "GoalObj.h"
#include "Player.h"
#include "InputManager.h"
#include "Ground.h"

//マップの広さ
static const GLfloat WIDTH = 10.0f;
static const GLfloat HEIGHT = 10.0f;

//適当なステージデータ(拡張予定)
struct StageData
{
	int mBlockNumber;
	int enemyNumber;
};

static StageData gStageData[] = {
	{0},
	{0},
};


Physics* State::GetPhysics(){
	return m_Physics;
}

Ground* g;

State::State(int stageID) :mDynamicObjects(0), mDynamicObjectNumber(0), mstageID(stageID)
{

	Common::Delete(m_Physics);
	m_Physics = new Physics();

	//ステージパラメータの読み込み
	const StageData& stageData = gStageData[mstageID];
	//ブロックを作ってセットしていく

	//オブジェクトの数(地面+ゴール+ブロック数)だけ箱を用意
	mStaticObjectNumber = 1 + 1 + stageData.mBlockNumber;
	mStaticObjects = new StaticObj*[mStaticObjectNumber];

	//Widthとheightを利用して地面を作る
	g = new Ground(WIDTH,HEIGHT,m_Physics);
	g->Set(0, 0);
	mStaticObjects[0] = g;
	
	//ゴールオブジェクトを作る
	GoalObj* goal = new GoalObj();
	goal->SetFlag(StaticObj::FLAG_GOAL);
	mStaticObjects[1] = goal;

	//ブロック数
	for (int i = 0; i < mStaticObjectNumber; i++){
		if (i>1){

			//配置
		}
	}

	DynamicObj* p = new Player(m_Physics);
	//プレイヤーの配置

	//敵の数とプレイヤーの数
	mDynamicObjectNumber = 1 + stageData.enemyNumber;
	mDynamicObjects = new DynamicObj*[mDynamicObjectNumber];
	
	//プレイヤー
	mDynamicObjects[0] = p;
	//配置
	//mDynamicObjects[0]->Set(0,1.0,0.5);

	//敵
	for (int i = 0; i < mDynamicObjectNumber; i++){
		if (i>0){

			//配置
		}
	}
}

State::~State()
{
	Common::Delete(*mStaticObjects);
	Common::Delete(mStaticObjects);

	Common::Delete(*mDynamicObjects);
	Common::Delete(mDynamicObjects);
}

//各オブジェクトの描画
void State::Draw(){
	for (int i = 0; i < mStaticObjectNumber; i++){
		mStaticObjects[i]->Draw();
	}
	for (int i = 0; i < mDynamicObjectNumber; i++){
		mDynamicObjects[i]->Draw();
	}
}

//物理シミュレーションを動かす
void State::PhysicsUpdate(){
	Vector3 force = Vector3(0);
	Vector3 torque = Vector3(0);
	if (InputManager::CheckInputMoveUp()){
		/*Matrix3 forwardRotate = Matrix3::rotationX(-0.01f);
		m_Physics->PlusRigidBodyOrientation(g->GetRigidbodyIndex(), forwardRotate);
		g->xRotate-=0.01f;*/
		force.setZ(-5.0f);
		//torque.setZ(-8.0f);
		torque.setX(-2.0f);
	}
	if (InputManager::CheckInputMoveDown()){
		/*Matrix3 forwardRotate = Matrix3::rotationX(0.01f);
		m_Physics->PlusRigidBodyOrientation(g->GetRigidbodyIndex(), forwardRotate);
		g->xRotate += 0.01f;*/
		force.setZ(5.0f);
		torque.setZ(2.0f);
	}
	if (InputManager::CheckInputMoveLeft()){
		/*Matrix3 leftrightRotate = Matrix3::rotationZ(0.01f);
		m_Physics->PlusRigidBodyOrientation(g->GetRigidbodyIndex(), leftrightRotate);
		g->zRotate -= 0.01f;*/
		force.setX(-5.0f);
		torque.setX(-2.0f);
	}
	if (InputManager::CheckInputMoveRight()){
		/*Matrix3 leftrightRotate = Matrix3::rotationZ(-0.01f);
		m_Physics->PlusRigidBodyOrientation(g->GetRigidbodyIndex(), leftrightRotate);
		g->zRotate += 0.01f;*/
		force.setX(5.0f);
		torque.setX(2.0f);
	}

	m_Physics->PhysicsUpdate(force,torque);
}

//各オブジェクトの更新
void State::Update(){

	for (int i = 0; i < mStaticObjectNumber; i++){
		mStaticObjects[i]->Update();
	}

	for (int i = 0; i < mDynamicObjectNumber; i++){
		mDynamicObjects[i]->Update();
	}

	if (mDynamicObjects[0]->miss){
		//TODO:本来はゴールオブジェクトに触れたら
		miss = true;
	}

	//std::cout << mDynamicObjects[0]->GetPos().y() << std::endl;

	/*if (mDynamicObjects[0]->GetPos().z() < -2.5){
		std::cout << mDynamicObjects[0]->GetPos().z() << std::endl;
		//TODO:本来はゴールオブジェクトに触れたら
		clear = true;
	}*/

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