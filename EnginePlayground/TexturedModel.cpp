#include "TexturedModel.h"

TexturedModel::TexturedModel( RawModel raw_model, ModelTexture texture )
{
	this->raw_model = raw_model;
	this->texture = texture;
}

const RawModel& TexturedModel::getRawModel() const
{
	return raw_model;
}

const ModelTexture& TexturedModel::getTexture() const
{
	return texture;
}

ModelTexture& TexturedModel::getTexture()
{
	return texture;
}

bool TexturedModel::operator==( const TexturedModel & rhs ) const
{
	return this->raw_model.getVaoId() == rhs.raw_model.getVaoId() 
		&& this->texture.getID() == rhs.texture.getID();
}
