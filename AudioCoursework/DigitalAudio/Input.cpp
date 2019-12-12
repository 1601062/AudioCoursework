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
void Input::setMouseX(int lx)
{
	mouse.x = lx;
}
void Input::setMouseY(int ly)
{
	mouse.y = ly;
}
void Input::setMouseLeft(bool l)
{
	mouse.left = l;
}
void Input::setMousePosition(int lx, int ly)
{
	setMouseX(lx);
	setMouseY(ly);
}

//getters
bool Input::isKeyDown(int key)
{
	return keys[key];
}
int Input::getMouseX()
{
	return mouse.x;
}
int Input::getMouseY()
{
	return mouse.y;
}

bool Input::getMouseLeft()
{
	return mouse.left;
}
