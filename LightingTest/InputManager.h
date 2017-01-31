#pragma once
#include "Commonheader.h"

//入力を管理するマネージャー
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

	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

private:
	static GLFWwindow* myWindow;
	InputManager(){
	};
	~InputManager(){
	};

	static unsigned int mInputButtonFlag;
	static unsigned int mInputMoveFlag;
};