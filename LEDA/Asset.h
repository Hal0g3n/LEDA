#pragma once

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
}