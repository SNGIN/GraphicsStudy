#pragma once
#include "Commonheader.h"
#include "Window.h"
#include "TrackBall.h"

//���͂��Ǘ�����}�l�[�W���[
static class InputManager
{
public:

	enum ButtonFlag{
		FLAG_SPACE = 1,
		FLAG_P = 1 << 1,
		FLAG_R = 1 << 2,
		FLAG_T = 1 << 3,
		FLAG_B = 1 << 4
	};
	enum MoveFlag{
		FLAG_UP = 1,
		FLAG_RIGHT = 1 << 1,
		FLAG_DOWN = 1 << 2,
		FLAG_LEFT = 1 << 3
	};

	static bool CheckInputSpace(); static bool PressSpace;
	static bool CheckInputP(); static bool PressP;
	static bool CheckInputR(); static bool PressR;
	static bool CheckInputT(); static bool PressT;
	static bool CheckInputB(); static bool PressB;

	static bool CheckInputMoveUp();
	static bool CheckInputMoveRight();
	static bool CheckInputMoveDown();
	static bool CheckInputMoveLeft();

	static void SetMyWindow(GLFWwindow* w);
	static void CheckInputMove();
	static void CheckInputMouseDrag(GLFWwindow *window);

	static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void MouseCallback(GLFWwindow *window, int button, int action, int mods);

	static TrackBall* GetTrackBall(){
		CheckInputMouseDrag(myWindow);
		return m_trackBall;
	}

private:
	static GLFWwindow* myWindow;
	InputManager(){
	};
	~InputManager(){
	};

	static unsigned int mInputButtonFlag;
	static unsigned int mInputMoveFlag;
	static TrackBall* m_trackBall;
};