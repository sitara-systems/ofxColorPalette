#include "CustomPalette.h"

using namespace ofxColorPalette;

CustomPalette::CustomPalette(std::vector<ofColor> colors) {
	mCustomColors = colors;
}

CustomPalette::CustomPalette(std::string filename) {
}


CustomPalette::~CustomPalette() {

}

std::shared_ptr<ofColor> CustomPalette::nextColor() {
	ofColor selectedColor = mCustomColors[(int)ofRandom(mCustomColors.size())];

	std::shared_ptr<ofColor> nextColor = std::shared_ptr<ofColor>(new ofColor(0));
	nextColor->set(selectedColor);
	return nextColor;
}