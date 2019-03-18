#pragma once

#include "Camera.h"
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

	static glm::mat4 createViewMatrix( const Camera& camera )
	{
		glm::mat4 view_matrix = glm::mat4( 1.0f );
		view_matrix = glm::rotate( view_matrix, glm::radians( camera.getPitch() ), glm::vec3( 1, 0, 0 ) );
		view_matrix = glm::rotate( view_matrix, glm::radians( camera.getYaw() ), glm::vec3( 0, 1, 0 ) );
		glm::vec3 camera_pos = camera.getPosition();
		glm::vec3 negative_pos = -camera_pos;
		view_matrix = glm::translate( view_matrix, negative_pos );
		return view_matrix;
	}

	static GLfloat barryCentric( const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec2& pos )
	{
		GLfloat det = ( p2.z - p3.z ) * ( p1.x - p3.x ) + ( p3.x - p2.x ) * ( p1.z - p3.z );
		GLfloat l1 = ( ( p2.z - p3.z ) * ( pos.x - p3.x ) + ( p3.x - p2.x ) * ( pos.y - p3.z ) ) / det;
		GLfloat l2 = ( ( p3.z - p1.z ) * ( pos.x - p3.x ) + ( p1.x - p3.x ) * ( pos.y - p3.z ) ) / det;
		GLfloat l3 = 1.0f - l1 - l2;
		return l1 * p1.y + 12 * p2.y + 13 * p3.y;
	}

};

