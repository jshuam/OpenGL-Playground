#include "DisplayManager.h"
#include "Maths.h"
#include "MousePicker.h"

MousePicker::MousePicker( const Camera& camera, const glm::mat4& projection_matrix, Terrain* terrain )
	:
	camera( camera ),
	projection_matrix( projection_matrix ),
	view_matrix( Maths::createViewMatrix( camera ) ),
	terrain( terrain )
{}

const glm::vec3& MousePicker::getCurrentRay() const
{
	return current_ray;
}

const glm::vec3& MousePicker::getCurrentTerrainPoint() const
{
	return current_terrain_point;
}

void MousePicker::update()
{
	view_matrix = Maths::createViewMatrix( camera );
	current_ray = calculateMouseRay();
	if( intersectionInRange( 0, RAY_RANGE, current_ray ) )
	{
		current_terrain_point = binarySearch( 0, 0, RAY_RANGE, current_ray );
		current_terrain_point_found = end_point_found;
	}
	else
	{
		current_terrain_point = glm::vec3( -1, -1, -1 );
		current_terrain_point_found = false;
	}
}

glm::vec3 MousePicker::calculateMouseRay()
{
	GLfloat mouse_x = DisplayManager::getMouseXPos();
	GLfloat mouse_y = DisplayManager::getMouseYPos();
	glm::vec2 normalized_coords = getNormalizedDeviceCoords( mouse_x, mouse_y );
	glm::vec4 clip_coords = glm::vec4( normalized_coords.x, normalized_coords.y, -1.0f, 1.0f );
	glm::vec4 eye_coords = toEyeCoords( clip_coords );
	glm::vec3 world_ray = toWorldCoords( eye_coords );
	return world_ray;
}

glm::vec2 MousePicker::getNormalizedDeviceCoords( GLfloat mouse_x, GLfloat mouse_y )
{
	GLfloat x = ( 2.0f * mouse_x ) / DisplayManager::getWidth() - 1.0f;
	GLfloat y = ( 2.0f * mouse_y ) / DisplayManager::getHeight() - 1.0f;
	return glm::vec2( x, -y );
}

glm::vec4 MousePicker::toEyeCoords( glm::vec4 clip_coords )
{
	glm::mat4 inverted_projection = glm::inverse( projection_matrix );
	glm::vec4 eye_coords = inverted_projection * clip_coords;
	return glm::vec4( eye_coords.x, eye_coords.y, -1.0f, 0.0f );
}

glm::vec3 MousePicker::toWorldCoords( glm::vec4 eye_coords )
{
	glm::mat4 inverted_view = glm::inverse( view_matrix );
	glm::vec4 ray_world = inverted_view * eye_coords;
	glm::vec3 mouse_ray = glm::vec3( ray_world.x, ray_world.y, ray_world.z );
	mouse_ray = glm::normalize( mouse_ray );
	return mouse_ray;
}

glm::vec3 MousePicker::getPointOnRay( glm::vec3 ray, GLfloat distance )
{
	glm::vec3 start = camera.getPosition();
	glm::vec3 scaled_ray = glm::vec3( ray.x * distance, ray.y * distance, ray.z * distance );
	return glm::vec3( start.x + scaled_ray.x, start.y + scaled_ray.y, start.z + scaled_ray.z );
}

glm::vec3 MousePicker::binarySearch( GLuint count, GLfloat start, GLfloat finish, glm::vec3& ray )
{
	GLfloat half = start + ( ( finish - start ) / 2.0f );
	if( count >= RECURSION_COUNT )
	{
		glm::vec3 end_point = getPointOnRay( ray, half );
		Terrain* terrain = getTerrain( end_point.x, end_point.z );
		if( terrain != nullptr )
		{
			end_point_found = true;
		}
		else
		{
			end_point_found = false;
		}
		return end_point;
	}
	if( intersectionInRange( start, half, ray ) )
	{
		glm::vec3 temp = binarySearch( count + 1, start, half, ray );
		return temp;
	}
	else
	{
		glm::vec3 temp = binarySearch( count + 1, half, finish, ray );
		return temp;
	}
}

bool MousePicker::intersectionInRange( GLfloat start, GLfloat finish, glm::vec3& ray )
{
	glm::vec3 start_point = getPointOnRay( ray, start );
	glm::vec3 end_point = getPointOnRay( ray, finish );
	if( !isUnderGround( start_point ) && isUnderGround( end_point ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MousePicker::isUnderGround( glm::vec3 test_point )
{
	Terrain* terrain = getTerrain( test_point.x, test_point.z );
	GLfloat height = 0;
	if( terrain != nullptr )
	{
		height = terrain->getTerrainHeight( test_point.x, test_point.z );
	}
	if( test_point.y < height )
	{
		return true;
	}
	else
	{
		return false;
	}
}

Terrain* MousePicker::getTerrain( GLfloat world_x, GLfloat world_z )
{
	return terrain;
}

const bool& MousePicker::endPointFound() const
{
	return end_point_found;
}

const bool& MousePicker::currentTerrainPointFound() const
{
	return current_terrain_point_found;
}
