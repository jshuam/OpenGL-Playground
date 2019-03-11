#pragma once

//#include "Camera.h"
#include "glm/matrix.hpp"
#include "glm/vec3.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

class Maths
{
public:
	static glm::mat4 createTransformationMatrix( glm::vec3 translation, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale )
	{
		glm::mat4 matrix = glm::translate( glm::mat4( 1.0f ), translation );
		matrix = glm::rotate( matrix, glm::radians( rx ), glm::vec3( 1, 0, 0 ) );
		matrix = glm::rotate( matrix, glm::radians( ry ), glm::vec3( 0, 1, 0 ) );
		matrix = glm::rotate( matrix, glm::radians( rz ), glm::vec3( 0, 0, 1 ) );
		matrix = glm::scale( matrix, glm::vec3( scale, scale, scale ) );

		return matrix;
	}

	/*static glm::mat4 createViewMatrix( const Camera& camera )
	{
		glm::mat4 matrix( 1.0f );
		matrix = glm::rotate( matrix, glm::radians( camera.getPitch() ), glm::vec3( 1, 0, 0 ) );
		matrix = glm::rotate( matrix, glm::radians( camera.getYaw() ), glm::vec3( 0, 1, 0 ) );
		glm::vec3 camera_pos = camera.getPosition();
		glm::vec3 negative_camera_pos = glm::vec3( -camera_pos.x, -camera_pos.y, -camera_pos.z );
		matrix = glm::translate( matrix, negative_camera_pos );

		return matrix;
	}*/

};

