#pragma once

#include <vector>

namespace Kirin {

	class IOManager
	{
		public:
			static bool readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer);
	};

}