#pragma once

#include <glad/glad.h>

class ModelTexture
{
public:
	ModelTexture() = default;
	ModelTexture(GLuint texture_id);
	const GLuint& getID() const;
	void setShineDamper( const GLfloat& shine_damper );
	void setReflectivity( const GLfloat& reflectivity );
	const GLfloat& getShineDamper() const;
	const GLfloat& getReflectivity() const;

private:
	GLuint texture_id;
	GLfloat shine_damper = 1;
	GLfloat reflectivity = 0;
};

