#pragma once
#include "game2dHelper.h"

class TextureCollection
{
/// Attributes
private:
	static TEXTURES* instance;
	unordered_map<int, Texture> textures;
	TextureCollection() {}
/// Methods
public:
	static TEXTURES* getInstance();
	~TextureCollection();
	bool addTexture(int id, LPCWSTR filepath, D3DCOLOR transparent);
	Texture getTexture(int id);
};