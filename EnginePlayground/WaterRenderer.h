#pragma once

#include "Loader.h"
#include "RawModel.h"
#include "WaterFrameBuffer.h"
#include "WaterShader.h"
#include "WaterTile.h"

class WaterRenderer
{
public:
	WaterRenderer( Loader& loader, WaterShader& shader, const glm::mat4& projection_matrix, WaterFrameBuffer& water_fbos );

	void render(const std::vector<WaterTile>& water, const Camera& camera, const Light& sun );
	void prepareRender( const Camera& camera, const Light& sun );
	void unbind();
	void setUpVAO( Loader& loader );

private:
	RawModel quad;
	WaterFrameBuffer water_fbos;
	WaterShader shader;
	GLuint dudv_texture;
	GLuint normal_map_texture;
	GLfloat move_factor = 0;
	static constexpr const char* dudv_map = "waterdudv";
	static constexpr const char* normal_map = "matchingnormalmap";
	static constexpr const GLfloat wave_speed = 0.03f;
};

