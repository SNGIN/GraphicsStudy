#pragma once
#include "Commonheader.h"

//入力を管理するマネージャー
static class InputManager
{
public:
	static bool CheckInputSpace();
	static bool CheckInputP();
	static bool CheckInputR();
	static bool CheckInputT();
	static bool CheckInputB();
	static bool CheckInputUpArrow();

	static void SetMyWindow(GLFWwindow* w);

private:
	static GLFWwindow* myWindow;
	InputManager(){
	};
	~InputManager(){
	};

	static unsigned int mInputFlag;
};