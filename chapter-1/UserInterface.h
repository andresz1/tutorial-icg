#pragma once

#include "../headers/AntTweakBar.h"
#include <iostream>
#include <string>

using std::string;

class CUserInterface
{
	TwBar *mUserInterface;
	float mFigureColor[3];
	string mFigureType;

public:
	CUserInterface();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setFigureColor(float *color);
	void setFigureType(string type);
	float* getFigureColor();
};