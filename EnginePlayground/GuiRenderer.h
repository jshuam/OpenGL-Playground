#pragma once

#include "GuiShader.h"
#include "GuiTexture.h"
#include "Loader.h"

class GuiRenderer
{
public:
	GuiRenderer( Loader loader );

	void render( std::vector<GuiTexture>& guis );
	void cleanUp();

private:
	RawModel quad;
	GuiShader shader;
};

