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
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (int i = 0; i < mNumOfVertices; i += 9)
	{
		glBegin(GL_TRIANGLES);
			glVertex3f(mVertices[i], mVertices[i + 1], mVertices[i + 2]);
			glVertex3f(mVertices[i + 3], mVertices[i + 4], mVertices[i + 5]);
			glVertex3f(mVertices[i + 6], mVertices[i + 7], mVertices[i + 8]);
		glEnd();
	}
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