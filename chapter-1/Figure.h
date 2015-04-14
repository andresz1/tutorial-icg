#pragma once

#include "../headers/glfw3.h"

enum FigureType
{
	LINE,
	QUAD
};



class CFigure
{
	protected:
		float **mVertices, mColor[3];

	public:
		CFigure();
		~CFigure();
		void setVertex(int id, float x, float y);
		void setColor(float r, float g, float b);
		virtual void display() = 0;
};