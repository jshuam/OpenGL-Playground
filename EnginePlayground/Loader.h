#pragma once

#include <glad/glad.h>
#include <vector>
#include "RawModel.h"

class Loader
{
public:
	RawModel loadToVAO( const std::vector<GLfloat>& positions );
	void cleanUp();

private:
	GLuint createVAO();
	void storeDataInAttributeList( GLuint attribute_number, const std::vector<GLfloat>& data );
	void unbindVAO();
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
};

