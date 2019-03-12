#pragma once

#include <glad/glad.h>

class ModelTexture
{
public:
	ModelTexture() = default;
	ModelTexture(GLuint texture_id);
	GLuint getID();
	void setShineDamper( const GLfloat& shine_damper );
	void setReflectivity( const GLfloat& reflectivity );
	const GLfloat& getShineDamper() const;
	const GLfloat& getReflectivity() const;

private:
	GLuint texture_id;
	GLfloat shine_damper;
	GLfloat reflectivity;
};

