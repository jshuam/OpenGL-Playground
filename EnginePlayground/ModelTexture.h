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
	void setTransparency( const GLboolean& transparency );
	void setFakeLighting( const GLboolean& fake_lighting );
	const GLboolean& hasTransparency() const;
	const GLboolean& hasFakeLighting() const;
	const GLfloat& getShineDamper() const;
	const GLfloat& getReflectivity() const;

private:
	GLboolean has_transparency = false;
	GLboolean use_fake_lighting = false;
	GLuint texture_id;
	GLfloat shine_damper = 1;
	GLfloat reflectivity = 0;
};

