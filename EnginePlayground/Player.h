#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player() = default;
	~Player() = default;
	Player( TexturedModel model, glm::vec3 position, GLfloat rot_x, GLfloat rot_y, GLfloat rot_z, GLfloat scale );
	void move( const GLfloat& dt );

private:
	void checkInputs();
	void jump();

private:
	GLfloat current_speed = 0;
	GLfloat current_turn_speed = 0;
	GLfloat upwards_speed = 0;

	GLboolean in_air = false;

	static constexpr GLfloat RUN_SPEED = 20;
	static constexpr GLfloat BOOST_SPEED = 1000;
	static constexpr GLfloat TURN_SPEED = 160;
	static constexpr GLfloat GRAVITY = -50;
	static constexpr GLfloat JUMP_POWER = 30;
	static constexpr GLfloat TERRAIN_HEIGHT = 0;
};

