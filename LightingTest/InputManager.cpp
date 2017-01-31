#pragma once
#include "InputManager.h"

GLFWwindow* InputManager::myWindow = 0;
unsigned int InputManager::mInputButtonFlag = 0;
unsigned int InputManager::mInputMoveFlag = 0;

bool InputManager::PressSpace = false;
bool InputManager::PressB = false;
bool InputManager::PressR = false;
bool InputManager::PressT = false;
bool InputManager::PressP = false;

//�E�B���h�E�A�L�[�{�[�h�̓o�^
void InputManager::SetMyWindow(GLFWwindow* w){
	myWindow = w;
	// �L�[���͂���������R�[���o�b�N�֐���ݒ�B
	glfwSetKeyCallback(w, keyCallback);
}

//�r�b�g���Z�Ńt���O�Ǘ�
bool InputManager::CheckInputSpace(){
	bool r = ((mInputButtonFlag & FLAG_SPACE) != 0) ? true:false;
	if (r){
		//�t���O���I�t�ɂ���(�A���Ŕ��肳���Ȃ�����)
		mInputButtonFlag &= ~FLAG_SPACE;
	}
	return r;
}

bool InputManager::CheckInputP(){
	bool r = ((mInputButtonFlag & FLAG_P) != 0) ? true : false;
	if (r){
		//�t���O���I�t�ɂ���(�A���Ŕ��肳���Ȃ�����)
		mInputButtonFlag &= ~FLAG_P;
	}
	return r;
}

bool InputManager::CheckInputR(){
	bool r =  ((mInputButtonFlag & FLAG_R) != 0) ? true : false;
	if (r){
		//�t���O���I�t�ɂ���(�A���Ŕ��肳���Ȃ�����)
		mInputButtonFlag &= ~FLAG_R;
	}
	return r;
}

bool InputManager::CheckInputT(){
	bool r = ((mInputButtonFlag & FLAG_T) != 0) ? true : false;
	if (r){
		//�t���O���I�t�ɂ���(�A���Ŕ��肳���Ȃ�����)
		mInputButtonFlag &= ~FLAG_T;
	}
	return r;
}

bool InputManager::CheckInputB(){
	bool r = ((mInputButtonFlag & FLAG_B) != 0) ? true : false;
	if (r){
		//�t���O���I�t�ɂ���(�A���Ŕ��肳���Ȃ�����)
		mInputButtonFlag &= ~FLAG_B;
	}
	return r;
}

//�r�b�g���Z�Ńt���O�Ǘ�
bool InputManager::CheckInputMoveUp(){
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

//�ړ����͂𔻒�
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

//�L�[�{�[�h�̏�Ԃ����ă{�^�����͂��t���O����
void InputManager::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
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