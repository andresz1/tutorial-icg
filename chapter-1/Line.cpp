#include "Line.h"

CLine::CLine()
{
	mVertices = new float*[2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = LINE;
}

CLine::~CLine()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CLine::display()
{
	glColor3fv(mColor);

	glBegin(GL_LINES);
		glVertex2fv(mVertices[0]);
		glVertex2fv(mVertices[1]);
	glEnd();
}