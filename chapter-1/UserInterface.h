#pragma once

#include "Headers\AntTweakBar\AntTweakBar.h"
#include <iostream>
#include <string>

using std::string;

class CUserInterface
{
	TwBar *mUserInterface;
	float mFigureColor[3];
	string mFigureType;
	bool mShow;

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

