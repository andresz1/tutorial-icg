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
	
		float *vertices = new float[mNumOfVertices];

		for (int i = 0; i < mNumOfVertices; i++)
		{
			file >> token;
			vertices[i] = float(atof(token.c_str()));
		}
	
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glGenVertexArrays(1, &mVao);

		glBindVertexArray(mVao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, mNumOfVertices * sizeof(float), vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		delete[] vertices;

		file.close();
		return true;
	}
}