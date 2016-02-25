#include "ColorPalette.h"

using namespace ofxColorPalette;

ColorPalette::ColorPalette(PALETTE_TYPE palette, float rootHue) {
	mRootHue = rootHue;
	init(palette);
}

ColorPalette::ColorPalette(PALETTE_TYPE palette) {
	mRootHue = ofRandom(255.0);
	init(palette);
}


ColorPalette::~ColorPalette() {

}

std::shared_ptr<ofColor> ColorPalette::nextColor() {
	float hue = std::fmod(mRootHue + mHueOffsets[(int)ofRandom(mHueOffsets.size())], 255.0);
	float saturation;
	float brightness;
	float randomSeed = ofRandom(1.0);
	if (randomSeed < mBlackProbability) {
		saturation = 0.0;
		brightness = 0.0;
	}
	else if (randomSeed < mBlackProbability + mWhiteProbability) {
		saturation = 0.0;
		brightness = mMaximumBrightness;
	}
	else if (randomSeed < mBlackProbability + mWhiteProbability + mSaturatedProbability) {
		saturation = mMaximumSaturation;
		brightness = mMaximumBrightness;
	}
	else {
		if (ofRandom(1.0) < 0.5) {
			saturation = ofRandom(mMaximumSaturation);
			brightness = mMaximumBrightness;
		}
		else {
			saturation = mMaximumSaturation;
			brightness = ofRandom(mMaximumBrightness);
		}
	}

	std::shared_ptr<ofColor> nextColor = std::shared_ptr<ofColor>(new ofColor(0));
	nextColor->setHsb(hue, saturation, brightness);
	return nextColor;
}

float ColorPalette::getRootHue() {
	return mRootHue;
}

std::vector<float> ColorPalette::getHues() {
	return mHueOffsets;
}

void ColorPalette::init(PALETTE_TYPE palette) {
	mPaletteType = palette;
	mBlackProbability = 0.0;
	mWhiteProbability = 0.0;
	mSaturatedProbability = 0.0;
	mMaximumBrightness = 255.0;
	mMaximumSaturation = 255.0;
	mMinimumBrightness = 0.0;
	mMinimumSaturation = 0.0;

	mHueOffsets.push_back(0.0);

	switch (mPaletteType) {
	case MONOCHROME:
		break;
	case COMPLEMENTARY:
		mHueOffsets.push_back(255.0 / 2.0);
		break;
	case SPLIT_COMPLEMENTARY:
		mHueOffsets.push_back(255.0 * 5.0 / 12.0);
		mHueOffsets.push_back(255.0 * 7.0 / 12.0);
		break;
	case TRIADIC:
		mHueOffsets.push_back(255.0 / 3.0);
		mHueOffsets.push_back(255.0 * 2.0 / 3.0);
		break;
	case TETRADIC:
		mHueOffsets.push_back(255.0 / 4.0);
		mHueOffsets.push_back(255.0 * 2.0 / 4.0);
		mHueOffsets.push_back(255.0 * 3.0 / 4.0);
		break;
	case FOUR_TONE:
		mHueOffsets.push_back(255.0 / 6.0);
		mHueOffsets.push_back(255.0 * 3.0 / 6.0);
		mHueOffsets.push_back(255.0 * 4.0 / 6.0);
		break;
	case FIVE_TONE:
		mHueOffsets.push_back(255.0 * 23.0 / 72.0);
		mHueOffsets.push_back(255.0 * 31.0 / 72.0);
		mHueOffsets.push_back(255.0 * 41.0 / 72.0);
		mHueOffsets.push_back(255.0 * 49.0 / 72.0);
		break;
	case SIX_TONE:
		mHueOffsets.push_back(255.0 / 12.0);
		mHueOffsets.push_back(255.0 * 4.0 / 12.0);
		mHueOffsets.push_back(255.0 * 5.0 / 12.0);
		mHueOffsets.push_back(255.0 * 8.0 / 12.0);
		mHueOffsets.push_back(255.0 * 9.0 / 12.0);
		break;
	case NEUTRAL:
		mHueOffsets.push_back(255.0 / 24.0);
		mHueOffsets.push_back(255.0 * 2.0 / 24.0);
		mHueOffsets.push_back(255.0 * 3.0 / 24.0);
		mHueOffsets.push_back(255.0 * 4.0 / 24.0);
		mHueOffsets.push_back(255.0 * 5.0 / 24.0);
		break;
	}
}

void ColorPalette::randomizePalette() {
	float randomSeed = ofRandom(1.0);
	if (randomSeed < 0.3) {
		mSaturatedProbability = 1.0;
		mBlackProbability = 0;
		mWhiteProbability = 0;
	}
	else if (randomSeed < 0.4) {
		mBlackProbability = 1.0 / (1 + mHueOffsets.size());
		mSaturatedProbability = 1.0 - mBlackProbability;
		mWhiteProbability = 0.0;
	}
	else if (randomSeed < 0.5) {
		mWhiteProbability = 1.0 / (1 + mHueOffsets.size());
		mSaturatedProbability = 1.0 - mWhiteProbability;
		mBlackProbability = 0.0;
	}
	else if (randomSeed < 0.6) {
		mBlackProbability = 1.0 / (2 + mHueOffsets.size());
		mWhiteProbability = 1.0 / (2 + mHueOffsets.size());
		mSaturatedProbability = 1 - mBlackProbability - mWhiteProbability;
	}
}

void ColorPalette::setProbabilities(float black, float white, float saturated) {
	mBlackProbability = black;
	mWhiteProbability = white;
	mSaturatedProbability = saturated;
}


float ColorPalette::getBlackProbability() {
	return mBlackProbability;
}

float ColorPalette::getWhiteProbability() {
	return mWhiteProbability;
}

float ColorPalette::getSaturatedProbability() {
	return mSaturatedProbability;
}

void ColorPalette::setMaximumSaturation(float maximum_saturation) {
	mMaximumSaturation = maximum_saturation;
}

float ColorPalette::getMaximumSaturation() {
	return mMaximumSaturation;
}

void ColorPalette::setMaximumBrightness(float maximum_brightness) {
	mMaximumBrightness = maximum_brightness;
}

float ColorPalette::getMaximumBrightness() {
	return mMaximumBrightness;
}

void ColorPalette::setMinimumSaturation(float minimum_saturation) {
	mMinimumSaturation = minimum_saturation;
}

float ColorPalette::getMinimumSaturation() {
	return mMinimumSaturation;
}

void ColorPalette::setMinimumBrightness(float minimum_brightness) {
	mMinimumBrightness = minimum_brightness;
}

float ColorPalette::getMinimumBrightness() {
	return mMinimumBrightness;
}