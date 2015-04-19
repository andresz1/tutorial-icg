#pragma once

#include "../headers/AntTweakBar.h"
#include "../headers/glm/glm.hpp"
#include <iostream>
#include <string>

using std::string;

class CUserInterface
{
	TwBar *mUserInterface;
	glm::vec3 mModelTranslation;

public:
	CUserInterface();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setModelTranslation(glm::vec3 modelTranslation);
	glm::vec3 getModelTranslation();
};