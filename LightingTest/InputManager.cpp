#pragma once
#include "InputManager.h"

GLFWwindow* InputManager::myWindow = 0;
TrackBall* InputManager::m_trackBall = 0;
unsigned int InputManager::mInputButtonFlag = 0;
unsigned int InputManager::mInputMoveFlag = 0;

bool InputManager::PressSpace = false;
bool InputManager::PressB = false;
bool InputManager::PressR = false;
bool InputManager::PressT = false;
bool InputManager::PressP = false;

//ウィンドウ、キーボードの登録
void InputManager::SetMyWindow(GLFWwindow* w){
	myWindow = w;
	m_trackBall = new TrackBall();
	// キー入力を処理するコールバック関数を設定
	glfwSetKeyCallback(w, KeyCallback);
	//マウス入力を処理するコールバック関数を設定
	glfwSetMouseButtonCallback(w, MouseCallback);
}

//ビット演算でフラグ管理
bool InputManager::CheckInputSpace(){
	bool r = ((mInputButtonFlag & FLAG_SPACE) != 0) ? true:false;
	if (r){
		//フラグをオフにする(連続で判定させないため)
		mInputButtonFlag &= ~FLAG_SPACE;
	}
	return r;
}

bool InputManager::CheckInputP(){
	bool r = ((mInputButtonFlag & FLAG_P) != 0) ? true : false;
	if (r){
		//フラグをオフにする(連続で判定させないため)
		mInputButtonFlag &= ~FLAG_P;
	}
	return r;
}

bool InputManager::CheckInputR(){
	bool r =  ((mInputButtonFlag & FLAG_R) != 0) ? true : false;
	if (r){
		//フラグをオフにする(連続で判定させないため)
		mInputButtonFlag &= ~FLAG_R;
	}
	return r;
}

bool InputManager::CheckInputT(){
	bool r = ((mInputButtonFlag & FLAG_T) != 0) ? true : false;
	if (r){
		//フラグをオフにする(連続で判定させないため)
		mInputButtonFlag &= ~FLAG_T;
	}
	return r;
}

bool InputManager::CheckInputB(){
	bool r = ((mInputButtonFlag & FLAG_B) != 0) ? true : false;
	if (r){
		//フラグをオフにする(連続で判定させないため)
		mInputButtonFlag &= ~FLAG_B;
	}
	return r;
}

//ビット演算でフラグ管理
bool InputManager::CheckInputMoveUp(){
	bool test = (mInputMoveFlag & FLAG_UP);
	return ((mInputMoveFlag & FLAG_UP) != 0) ? true : false;
}

bool InputManager::CheckInputMoveRight(){
	return ((mInputMoveFlag & FLAG_RIGHT) != 0) ? true : false;
}

bool InputManager::CheckInputMoveDown(){
	return ((mInputMoveFlag & FLAG_DOWN) != 0) ? true : false;
}

bool InputManager::CheckInputMoveLeft(){
	return ((mInputMoveFlag & FLAG_LEFT) != 0) ? true : false;
}

//移動入力を判定
void InputManager::CheckInputMove(){
	if (glfwGetKey(myWindow, GLFW_KEY_UP)){
		mInputMoveFlag |= FLAG_UP;
	}
	else{
		mInputMoveFlag &= ~FLAG_UP;
	}

	if (glfwGetKey(myWindow, GLFW_KEY_RIGHT)){
		mInputMoveFlag |= FLAG_RIGHT;
	}
	else{
		mInputMoveFlag &= ~FLAG_RIGHT;
	}

	if (glfwGetKey(myWindow, GLFW_KEY_DOWN)){
		mInputMoveFlag |= FLAG_DOWN;
	}
	else{
		mInputMoveFlag &= ~FLAG_DOWN;
	}

	if (glfwGetKey(myWindow, GLFW_KEY_LEFT)){
		mInputMoveFlag |= FLAG_LEFT;
	}
	else{
		mInputMoveFlag &= ~FLAG_LEFT;
	}
}

//キーボードの状態を見てボタン入力をフラグ判定
void InputManager::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_B){
		if (action == GLFW_PRESS && !PressB){
			mInputButtonFlag = FLAG_B;
			PressB = true;
		}
		else if (action == GLFW_RELEASE){
			PressB = false;
		}
	}
	
	if (key == GLFW_KEY_T){
		if (action == GLFW_PRESS && !PressT){
			mInputButtonFlag = FLAG_T;
			PressT = true;
		}
		else if (action == GLFW_RELEASE){
			PressT = false;
		}
	}

	if (key == GLFW_KEY_R){
		if (action == GLFW_PRESS && !PressR){
			mInputButtonFlag = FLAG_R;
			PressR = true;
		}
		else if (action == GLFW_RELEASE){
			PressR = false;
		}
	}

	if (key == GLFW_KEY_P){
		if (action == GLFW_PRESS && !PressP){
			mInputButtonFlag = FLAG_P;
			PressP = true;
		}
		else if (action == GLFW_RELEASE){
			PressP = false;
		}
	}

	if (key == GLFW_KEY_SPACE){
		if (action == GLFW_PRESS && !PressSpace){
			mInputButtonFlag = FLAG_SPACE;
			PressSpace = true;
		}
		else if (action == GLFW_RELEASE){
			PressSpace = false;
		}
	}
}

//
// マウスボタン操作時の処理
//
void InputManager::MouseCallback(GLFWwindow *window, int button, int action, int mods)
{
	// マウスの現在位置を取得する
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		if (action != GLFW_RELEASE)
		{
			// ボタン押下
			m_trackBall->Start(x, y);
		}
		else
		{
			// ボタン開放
			m_trackBall->Stop(x, y);
		}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		break;
	default:
		break;
	}
}

void InputManager::CheckInputMouseDrag(GLFWwindow *window){
	// マウスの現在位置を取得する
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	m_trackBall->Motion(x,y);
}