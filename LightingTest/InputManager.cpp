#pragma once
#include "InputManager.h"

GLFWwindow* InputManager::myWindow = 0;
unsigned int InputManager::mInputFlag = 0;

void InputManager::SetMyWindow(GLFWwindow* w){
	myWindow = w;
}

//TODO:�r�b�g���Z�Ńt���O�Ǘ�
bool InputManager::CheckInputSpace(){
	return glfwGetKey(myWindow, GLFW_KEY_SPACE);
}

bool InputManager::CheckInputP(){
	return glfwGetKey(myWindow, GLFW_KEY_SPACE);
}

bool InputManager::CheckInputSpace(){
	return glfwGetKey(myWindow, GLFW_KEY_SPACE);
}

bool InputManager::CheckInputSpace(){
	return glfwGetKey(myWindow, GLFW_KEY_SPACE);
}

bool InputManager::CheckInputSpace(){
	return glfwGetKey(myWindow, GLFW_KEY_SPACE);
}