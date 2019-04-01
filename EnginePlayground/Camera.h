#pragma once

#include "DisplayManager.h"
#include "Player.h"

#include <glm/vec3.hpp>

class Camera
{
public:
	Camera( std::shared_ptr<Player> player );
	void move( const GLfloat& dt );

	const glm::vec3& getPosition() const;
	const GLfloat& getPitch() const;
	const GLfloat& getYaw() const;
	const GLfloat& getRoll() const; void setPosX( const GLfloat& x );

	void setPosY( const GLfloat& y );
	void setPosZ( const GLfloat& z );
	void setPosition( const glm::vec3& position );
	void setPosition( const GLfloat& x, const GLfloat& y, const GLfloat& z );

	void invertPitch();

private:
	void calculateZoom();
	void calculatePitch();
	void calculateAngleAroundPlayer();
	void calculateCameraPosition( const GLfloat& horizontal_distance, const GLfloat& vertical_distance );

	const GLfloat& calculateHorizontalDistance() const;
	const GLfloat& calculateVerticalDistance() const;

private:
	glm::vec3 position;
	GLfloat pitch = 20;
	GLfloat yaw = 0;
	GLfloat roll;
	static GLfloat speed;
	static GLfloat boost_speed;

	std::shared_ptr<Player> player;
	GLfloat distance_from_player = 50;
	GLfloat angle_around_player = 0;
};

