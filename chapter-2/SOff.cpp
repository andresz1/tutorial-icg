#include "SOff.h"

CSOff::CSOff()
{
}

CSOff::~CSOff()
{
}

bool CSOff::load(string path)
{
	fstream file;
	string token;

	file.open(path, std::ios::in);

	file >> token;

	if (token != "SOFF")
	{
		file.close();
		return false;
	}
	else
	{
		file >> token;
		mNumOfVertices = 3 * atoi(token.c_str());
	
		mVertices = new float[mNumOfVertices];

		for (int i = 0; i < mNumOfVertices; i++)
		{
			file >> token;
			mVertices[i] = atof(token.c_str());
		}
	
		file.close();
		return true;
	}
}