#pragma once

#include "RawModel.h"
#include "ModelTexture.h"

class TexturedModel
{
public:
	TexturedModel() = default;
	TexturedModel( RawModel raw_model, ModelTexture texture );
	const RawModel& getRawModel() const;
	const ModelTexture& getTexture() const;
	ModelTexture& getTexture();
	bool operator==( const TexturedModel& rhs ) const;

private:
	RawModel raw_model;
	ModelTexture texture;
};
