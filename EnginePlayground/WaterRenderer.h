#pragma once

#include "Loader.h"
#include "RawModel.h"
#include "WaterShader.h"
#include "WaterTile.h"

class WaterRenderer
{
public:
	WaterRenderer( Loader& loader, WaterShader& shader, const glm::mat4& projection_matrix );

	void render(const std::vector<WaterTile>& water, const Camera& camera);
	void prepareRender( const Camera& camera );
	void unbind();
	void setUpVAO( Loader& loader );

private:
	RawModel quad;
	WaterShader shader;

};

