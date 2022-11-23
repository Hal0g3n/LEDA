/**
 * @file        Asset.h
 * @author      your name (you@domain.com)
 * @brief       ...
 * @version     0.1
 * @date        23-11-2022
 *
 * @copyright   Copyright (c) 2022
 *
 */

#pragma once

#ifndef LEDA_ASSET_H_
#define LEDA_ASSET_H_

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

	/*
	struct LEDA_API Shader : Asset {
		Shader(std::string vecFile, std::string fragFile);
		~Shader();
	};
	*/

	struct LEDA_API Audio : Asset {
		Audio(std::string filename);
		~Audio();
	};

}

#endif // LEDA_ASSET_H_