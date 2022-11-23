#pragma once

#include "pch.h"
#include <string>

namespace LEDA {
	
	struct LEDA_API Asset {
		Asset() = default;
		~Asset() = default;
	};


	struct LEDA_API Image : Asset {
		Image(std::string filename);
		~Image();
	};

	struct LEDA_API Font : Asset {
		Font(std::string filename);
		~Font();
	};

	struct LEDA_API Shader : Asset {
		Shader(std::string vecFile, std::string fragFile);
		~Shader();
	};

	struct LEDA_API Audio : Asset {
		Audio(std::string filename);
		~Audio();
	};
}