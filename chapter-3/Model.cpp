#include "Model.h"

CModel::CModel()
{
	mTranslation[0] = mTranslation[1] = mTranslation[2] = 0.0f;
}

CModel::~CModel()
{
	if (glIsVertexArray(mVao))
		glDeleteVertexArrays(1, &mVao);
}

void CModel::display()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(mVao);
		glDrawArrays(GL_TRIANGLES, 0, mNumOfVertices);
	glBindVertexArray(0);
}

void CModel::setTranslation(glm::vec3 translation)
{
	mTranslation[0] = translation[0];
	mTranslation[1] = translation[1];
	mTranslation[2] = translation[2];
}

glm::vec3 CModel::getTranslation()
{
	return mTranslation;
}