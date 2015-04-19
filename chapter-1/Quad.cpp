#include "Quad.h"

CQuad::CQuad()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = QUAD;
}

CQuad::~CQuad()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CQuad::display()
{
	glColor3fv(mColor);

	glBegin(GL_POLYGON);
		glVertex2fv(mVertices[0]);
		glVertex2f(mVertices[0][0], mVertices[1][1]);
		glVertex2fv(mVertices[1]);
		glVertex2f(mVertices[1][0], mVertices[0][1]);
	glEnd();
}