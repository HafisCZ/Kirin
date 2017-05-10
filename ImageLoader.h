#pragma once

#include <string>
#include "GLTexture.h"

namespace Kirin {

	class ImageLoader
	{
		public:
			static GLTexture loadPNG(const std::string& filePath);

	};

}