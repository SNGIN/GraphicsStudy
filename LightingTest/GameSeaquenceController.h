#pragma once
#include "Seaquence.h"
class State;
class SeaquenceController;
class GameSeaquence;

class GameSeaquenceController:public Seaquence
{
public:
	typedef SeaquenceController GrandController;

	enum NextSeaquence{
		NEXT_ENDING,
		NEXT_GAMEOVER,
		NEXT_TITLE,

		NEXT_NONE,
	};

	GameSeaquenceController();
	~GameSeaquenceController();

	Boot* Update(GrandController*);
	State* GetState();
	void DrawState()const;//�Q�[����`�悷��
	bool HasFinalStageCleard()const;
	void StartLoading();
	void GotoNextStage();
	int LifeNumber();
	void ReduceLife();
private:
	State* mState;
	int mStageID;
	int mLife;
	//�ŏI�X�e�[�W�ʒ�`
	static const int FINALSTAGE = 2;

	NextSeaquence mNextSeaquence;

	GameSeaquence* mGameSeaquence;
};