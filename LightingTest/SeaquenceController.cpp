#include "SeaquenceController.h"
#include "Title.h"

SeaquenceController* SeaquenceController::mInstance = 0;

SeaquenceController::SeaquenceController() :mSeaquence(0)
{
	//最初にタイトルを作る
	mSeaquence = new Title();
}


SeaquenceController::~SeaquenceController()
{
	//シーケンスのポインタ終了処理
	Common::Delete(mSeaquence);
}

void SeaquenceController::Create(){
	//実体を作る
	mInstance = new SeaquenceController();
}

void SeaquenceController::Destroy(){
	//自身のポインタ終了処理
	Common::Delete(mInstance);
}

SeaquenceController* SeaquenceController::instance(){
	return mInstance;
}

void SeaquenceController::Update(){
	//派生クラスのUpdateを実行する
	Boot* nextSeaquence = mSeaquence->Update(this);
	if (nextSeaquence != mSeaquence){
		//遷移判定
		Seaquence* casted = dynamic_cast<Seaquence*>(nextSeaquence);
		//現在のシーケンスを捨てて次へ
		Common::Delete(mSeaquence);
		mSeaquence = casted;
	}
	nextSeaquence = 0;
}

