#pragma once

#include "../headers/AntTweakBar.h"
#include <iostream>
#include <string>

using std::string;

class CUserInterface
{
	TwBar *mUserInterface;
	float mModelTranslation[3];

public:
	CUserInterface();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setModelTranslation(float *modelTranslation);
	float* getModelTranslation();
};