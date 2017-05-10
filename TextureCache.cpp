#include "TextureCache.h"
#include "ImageLoader.h"

namespace Kirin {

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(const std::string& texturePath) {
		auto mit = _textureMap.find(texturePath);
		if (mit == _textureMap.end()) {
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);
			_textureMap.insert(make_pair(texturePath, newTexture));
			return newTexture;
		}

		return mit->second;
	}

}