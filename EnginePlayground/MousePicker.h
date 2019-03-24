#pragma once

#include "Camera.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class MousePicker
{
public:
	MousePicker( const Camera& camera, const glm::mat4& projection_matrix, Terrain* terrain );
	~MousePicker() = default;

	const glm::vec3& getCurrentRay() const;
	const glm::vec3& getCurrentTerrainPoint() const;

	void update();
	const bool& endPointFound() const;
	const bool& currentTerrainPointFound() const;

private:
	glm::vec3 calculateMouseRay();
	glm::vec2 getNormalizedDeviceCoords( GLfloat mouse_x, GLfloat mouse_y );
	glm::vec4 toEyeCoords( glm::vec4 clip_coords );
	glm::vec3 toWorldCoords( glm::vec4 eye_coords );
	glm::vec3 getPointOnRay( glm::vec3 ray, GLfloat distance );
	glm::vec3 binarySearch( GLuint count, GLfloat start, GLfloat finish, glm::vec3& ray );
	bool intersectionInRange( GLfloat start, GLfloat finish, glm::vec3& ray );
	bool isUnderGround( glm::vec3 test_point );
	Terrain* getTerrain( GLfloat world_x, GLfloat world_z );

private:
	static constexpr const GLuint RECURSION_COUNT = 200;
	static constexpr const GLfloat RAY_RANGE = 600;

	glm::vec3 current_ray;
	glm::mat4 projection_matrix;
	glm::mat4 view_matrix;
	Camera camera;
	Terrain* terrain;
	glm::vec3 current_terrain_point;
	bool current_terrain_point_found;
	bool end_point_found;
};

