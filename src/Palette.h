#pragma once

#include "ofMain.h"
#include <memory>

namespace ofxColorPalette {

	enum PALETTE_TYPE {
		MONOCHROME,
		COMPLEMENTARY,
		SPLIT_COMPLEMENTARY,
		TRIADIC,
		TETRADIC,
		FOUR_TONE,
		FIVE_TONE,
		SIX_TONE,
		NEUTRAL
	};

	class Palette {
	public:
		Palette() {};
		~Palette() {};
		virtual std::shared_ptr<ofColor> nextColor() = 0;
	};

}