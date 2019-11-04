#include "Input.h"

Input::Input()
{
}

//setters
void Input::setKeyDown(int key)
{
	keys[key] = true;
}
void Input::setKeyUp(int key)
{
	keys[key] = false;
}

//getters
bool Input::isKeyDown(int key)
{
	return keys[key];
}
