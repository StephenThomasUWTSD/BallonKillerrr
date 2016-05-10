#pragma once
class Controller
{
public:
	
	void Controls(unsigned int key);
	void pressKey();
	void releaseKey(int, int, int);
	void keyboardread(unsigned char key, int x, int y);
	Controller();
	~Controller();
};

