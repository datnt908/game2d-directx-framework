#include "TextureCollection.h"

TEXTURES* TextureCollection::instance = NULL;

TEXTURES * TextureCollection::getInstance()
{
	if (instance == NULL)
		instance = new TextureCollection();
	return instance;
}

TextureCollection::~TextureCollection()
{
	for (auto texture : textures)
		texture.second->Release();
}

bool TextureCollection::addTexture(int id, LPCWSTR filepath, D3DCOLOR transparent)
{
	if (textures.find(id) != textures.end())
		return false;
	Texture texture = loadTexture(filepath, transparent);
	if (texture == NULL)
		return false;
	textures[id] = texture;
	return true;
}

Texture TextureCollection::getTexture(int id)
{
	if (textures.find(id) != textures.end())
		return textures[id];
	return NULL;
}
