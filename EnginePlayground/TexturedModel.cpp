#include "TexturedModel.h"

TexturedModel::TexturedModel( RawModel raw_model, ModelTexture texture )
{
	this->raw_model = raw_model;
	this->texture = texture;
}

RawModel& TexturedModel::getRawModel()
{
	return raw_model;
}

ModelTexture& TexturedModel::getTexture()
{
	return texture;
}
