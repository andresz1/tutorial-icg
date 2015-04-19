#pragma once

#include "../headers/glew.h"
#include "../headers/glfw3.h"
#include "../headers/glm/glm.hpp"
#include "../headers/glm/gtc/matrix_transform.hpp"
#include "../headers/glm/gtx/transform2.hpp"
#include "../headers/glm/gtc/type_ptr.hpp"
#include <string>

using std::string;

class CModel
{
	protected:
		GLuint mVao;
		glm::vec3 mTranslation;
		int mNumOfVertices;

	public:
		CModel();
		~CModel();
		virtual bool load(string path) = 0;
		virtual void display();
		void setTranslation(glm::vec3 translation);
		glm::vec3 getTranslation();
};