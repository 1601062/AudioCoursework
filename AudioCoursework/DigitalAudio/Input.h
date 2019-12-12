#pragma once

class Input
{
	

	struct Mouse
	{
		int x, y;
		bool left;
	};
public:
	Input();

	//setters
	void setKeyDown(int key);
	void setKeyUp(int key);
	void setMouseX(int lx);
	void setMouseY(int ly);
	void setMouseLeft(bool l);
	void setMousePosition(int lx, int ly);
	//getters
	int getMouseX();
	int getMouseY();
	bool getMouseLeft();
	bool isKeyDown(int key);

protected:
	bool keys[256]{ false };
	bool mouseLeft{ false };
	Mouse mouse;
};