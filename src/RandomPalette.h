#pragma once

#include "Palette.h"

namespace ofxColorPalette {

	class RandomPalette : public Palette {
	public:
		RandomPalette() {};
		~RandomPalette() {};
		std::shared_ptr<ofColor> nextColor() {
			std::shared_ptr<ofColor> nextColor = std::shared_ptr<ofColor>(new ofColor(0));
			nextColor->setHsb(ofRandom(255.0), ofRandom(255.0), ofRandom(255.0));
			return nextColor;
		};
	};

}