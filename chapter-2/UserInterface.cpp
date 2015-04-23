#include "UserInterface.h"

extern int gWidth, gHeight;

CUserInterface::CUserInterface()
{
	mUserInterface = TwNewBar("Model");

	TwDefine("Model refresh = '0.0001f'");
	TwDefine("Model resizable = false");
	TwDefine("Model fontresizable = false");
	TwDefine("Model movable = false");
	TwDefine("Model position = '20 20'");
	TwDefine("Model size = '220 320'");

	mModelTranslation[0] = 0.0f;
	mModelTranslation[1] = 0.0f;
	mModelTranslation[2] = 0.0f;

	TwAddVarRW(mUserInterface, "X", TW_TYPE_FLOAT, &mModelTranslation[0], " group='Translation' step=0.1 ");
	TwAddVarRW(mUserInterface, "Y", TW_TYPE_FLOAT, &mModelTranslation[1], " group='Translation' step=0.1 ");
	TwAddVarRW(mUserInterface, "Z", TW_TYPE_FLOAT, &mModelTranslation[2], " group='Translation' step=0.1 ");
}

CUserInterface::~CUserInterface()
{
}

void CUserInterface::reshape()
{
	TwWindowSize(gWidth, gHeight);
}

void CUserInterface::show()
{
	TwDefine("Figure visible = true");
}

void CUserInterface::hide()
{
	TwDefine("Figure visible = false");
}

void CUserInterface::setModelTranslation(float *modelTranslation)
{
	mModelTranslation[0] = modelTranslation[0];
	mModelTranslation[1] = modelTranslation[1];
	mModelTranslation[2] = modelTranslation[2];
}

float* CUserInterface::getModelTranslation()
{
	return mModelTranslation;
}