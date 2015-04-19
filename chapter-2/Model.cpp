#include "Model.h"

CModel::CModel()
{
	mTranslation[0] = mTranslation[1] = mTranslation[2] = 0.0f;
}

CModel::~CModel()
{
	delete[] mVertices;
}

void CModel::display()
{

}

void CModel::setTranslation(float *translation)
{
	mTranslation[0] = translation[0];
	mTranslation[1] = translation[1];
	mTranslation[2] = translation[2];
}

float* CModel::getTranslation()
{
	return mTranslation;
}