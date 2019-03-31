#pragma once

#include <glad/glad.h>

class WaterFrameBuffer
{
public:
	WaterFrameBuffer();

	const GLuint& getReflectionTexture() const;
	const GLuint& getRefractionDepthTexture() const;
	const GLuint& getRefractionTexture() const;

	void bindReflectionFrameBuffer();
	void bindRefractionFrameBuffer();
	void cleanUp();
	void unbindCurrentFrameBuffer();

private:
	GLuint createDepthTextureAttachment( GLuint width, GLuint height );
	GLuint createDepthBufferAttachment( GLuint width, GLuint height );
	GLuint createFrameBuffer();
	GLuint createTextureAttachment( GLuint width, GLuint height );

	void bindFrameBuffer( GLuint frame_buffer, GLuint width, GLuint height );
	void initialiseReflectionFrameBuffer();
	void initialiseRefractionFrameBuffer();

protected:
	static constexpr const GLuint reflection_width = 320;
	static constexpr const GLuint refraction_width = 1280;

private:
	static constexpr const GLuint reflection_height = 180;
	static constexpr const GLuint refraction_height = 720;

	GLuint reflection_frame_buffer;
	GLuint reflection_texture;
	GLuint reflection_depth_buffer;

	GLuint refraction_frame_buffer;
	GLuint refraction_texture;
	GLuint refraction_depth_texture;
};

