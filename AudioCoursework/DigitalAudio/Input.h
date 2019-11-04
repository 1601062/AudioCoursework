#pragma once

class Input
{
	
public:
	Input();

	//setters
	void setKeyDown(int key);
	void setKeyUp(int key);

	//getters
	bool isKeyDown(int key);

protected:
	bool keys[256]{ false };
};