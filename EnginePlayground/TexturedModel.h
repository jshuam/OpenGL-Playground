#pragma once

#include "RawModel.h"
#include "ModelTexture.h"

class TexturedModel
{
public:
	TexturedModel() = default;
	TexturedModel( RawModel raw_model, ModelTexture texture );
	RawModel getRawModel() const;
	ModelTexture getTexture() const;

private:
	RawModel raw_model;
	ModelTexture texture;
};

