#include "DisplayManager.h"
#include "WaterFrameBuffer.h"

WaterFrameBuffer::WaterFrameBuffer()
{
	initialiseReflectionFrameBuffer();
	initialiseRefractionFrameBuffer();
}

const GLuint& WaterFrameBuffer::getReflectionTexture() const
{
	return reflection_texture;
}

const GLuint& WaterFrameBuffer::getRefractionDepthTexture() const
{
	return refraction_depth_texture;
}

const GLuint& WaterFrameBuffer::getRefractionTexture() const
{
	return refraction_texture;
}

void WaterFrameBuffer::bindReflectionFrameBuffer()
{
	bindFrameBuffer( reflection_frame_buffer, reflection_width, reflection_height );
}

void WaterFrameBuffer::bindRefractionFrameBuffer()
{
	bindFrameBuffer( refraction_frame_buffer, refraction_width, refraction_height );
}

void WaterFrameBuffer::cleanUp()
{
	glDeleteFramebuffers( 1, &reflection_frame_buffer );
	glDeleteTextures( 1, &reflection_texture );
	glDeleteRenderbuffers( 1, &reflection_depth_buffer );
	glDeleteFramebuffers( 1, &refraction_frame_buffer );
	glDeleteTextures( 1, &refraction_texture );
	glDeleteTextures( 1, &refraction_depth_texture );
}

void WaterFrameBuffer::unbindCurrentFrameBuffer()
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	glViewport( 0, 0, DisplayManager::getWidth(), DisplayManager::getHeight() );
}

void WaterFrameBuffer::bindFrameBuffer( GLuint frame_buffer, GLuint width, GLuint height )
{
	glBindTexture( GL_TEXTURE_2D, 0 );
	glBindFramebuffer( GL_FRAMEBUFFER, frame_buffer );
	glViewport( 0, 0, width, height );
}

GLuint WaterFrameBuffer::createDepthTextureAttachment( GLuint width, GLuint height )
{
	GLuint texture;
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glFramebufferTexture( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0 );
	return texture;
}

GLuint WaterFrameBuffer::createDepthBufferAttachment( GLuint width, GLuint height )
{
	GLuint depth_buffer;
	glGenRenderbuffers( 1, &depth_buffer );
	glBindRenderbuffer( GL_RENDERBUFFER, depth_buffer );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height );
	glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer );
	return depth_buffer;
}

GLuint WaterFrameBuffer::createFrameBuffer()
{
	GLuint frame_buffer;
	glGenFramebuffers( 1, &frame_buffer );
	glBindFramebuffer( GL_FRAMEBUFFER, frame_buffer );
	glDrawBuffer( GL_COLOR_ATTACHMENT0 );
	return frame_buffer;
}

GLuint WaterFrameBuffer::createTextureAttachment( GLuint width, GLuint height )
{
	GLuint texture;
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glFramebufferTexture( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0 );
	return texture;
}

void WaterFrameBuffer::initialiseReflectionFrameBuffer()
{
	reflection_frame_buffer = createFrameBuffer();
	reflection_texture = createTextureAttachment( reflection_width, reflection_height );
	reflection_depth_buffer = createDepthBufferAttachment( reflection_width, reflection_height );
	unbindCurrentFrameBuffer();
}

void WaterFrameBuffer::initialiseRefractionFrameBuffer()
{
	refraction_frame_buffer = createFrameBuffer();
	refraction_texture = createTextureAttachment( refraction_width, refraction_height );
	refraction_depth_texture = createDepthTextureAttachment( refraction_width, refraction_height );
	unbindCurrentFrameBuffer();
}