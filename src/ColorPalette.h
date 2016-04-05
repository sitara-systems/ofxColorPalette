#pragma once

#include "Palette.h"
#include <vector>

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

	enum SATURATION_TYPE {
		STATIC,
		LEVELS,
		RANDOM
	};

	class ColorPalette : public Palette {
	public:
		ColorPalette(PALETTE_TYPE palette, float rootHue);
		ColorPalette(PALETTE_TYPE palette);
		~ColorPalette();
		float getRootHue();
		void setRootHue(float root);
		std::vector<float> getHues();
		std::shared_ptr<ofColor> nextColor();
		void init(PALETTE_TYPE palette);
		void resetPalette(PALETTE_TYPE palette, float rootHue);
		void randomizePalette();
		void setProbabilities(float black, float white, float saturated);
		float getBlackProbability();
		float getWhiteProbability();
		float getSaturatedProbability();

		void setSaturationType(SATURATION_TYPE type);
		SATURATION_TYPE getSaturationType();
		void setMaximumSaturation(float maximum_saturation);
		float getMaximumSaturation();
		void setMinimumSaturation(float minimum_saturation);
		float getMinimumSaturation();
		void setNumberOfSaturationLevels(int levels);
		int getNumberOfSaturationLevels();
		std::vector<float> getSaturationLevels();

		void setMaximumBrightness(float maximum_brightness);
		float getMaximumBrightness();
		void setMinimumBrightness(float minimum_brightness);
		float getMinimumBrightness();

	protected:
		PALETTE_TYPE mPaletteType;
		SATURATION_TYPE mSaturationType;
		std::vector<float> mHues;
		std::vector<float> mSaturationLevels;
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