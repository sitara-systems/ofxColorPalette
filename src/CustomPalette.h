#pragma once

#include "Palette.h"

namespace ofxColorPalette {

	class CustomPalette : public Palette {
	public:
		CustomPalette(std::vector<ofColor> colors);
		CustomPalette(std::string filename);
		~CustomPalette();
		std::shared_ptr<ofColor> nextColor();
	protected:
		std::vector<ofColor> mCustomColors;
	};

}