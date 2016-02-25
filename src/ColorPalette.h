#pragma once

#include "Palette.h"
#include <vector>

namespace ofxColorPalette {

	class ColorPalette : public Palette {
	public:
		ColorPalette(PALETTE_TYPE palette, float rootHue);
		ColorPalette(PALETTE_TYPE palette);
		~ColorPalette();
		float getRootHue();
		std::vector<float> getHues();
		std::shared_ptr<ofColor> nextColor();
		void init(PALETTE_TYPE palette);
		void randomizePalette();
		void setProbabilities(float black, float white, float saturated);
		float getBlackProbability();
		float getWhiteProbability();
		float getSaturatedProbability();
		void setMaximumSaturation(float maximum_saturation);
		float getMaximumSaturation();
		void setMaximumBrightness(float maximum_brightness);
		float getMaximumBrightness();
		void setMinimumSaturation(float minimum_saturation);
		float getMinimumSaturation();
		void setMinimumBrightness(float minimum_brightness);
		float getMinimumBrightness();

	protected:
		PALETTE_TYPE mPaletteType;
		std::vector<float> mHueOffsets;
		float mBlackProbability;
		float mWhiteProbability;
		float mSaturatedProbability;
		float mMaximumBrightness;
		float mMaximumSaturation;
		float mMinimumBrightness;
		float mMinimumSaturation;
		float mRootHue;
	};

}