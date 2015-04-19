#pragma once

#include "../headers/glfw3.h"
#include <string>

using std::string;

class CModel
{
	protected:
		float *mVertices, mTranslation[3];
		int mNumOfVertices;

	public:
		CModel();
		~CModel();
		virtual bool load(string path) = 0;
		virtual void display();
		void setTranslation(float *translation);
		float* getTranslation();
};