#include "Palette.h"

#include <vector>

using namespace ofxColorPalette;

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

class ColorPalette {
 public:
	 ColorPalette(PALETTE_TYPE palette, float rootHue);
	 ColorPalette(PALETTE_TYPE palette);
	 ~ColorPalette();
  std::shared_ptr<ofColor> nextColor();
  void init();
  void reset();
protected:
	PALETTE_TYPE mPaletteType;
	std::vector<float> mHueOffsets;
	float mBlackProbability;
	float mWhiteProbability;
	float mSaturatedProbability;
	float mRootHue;
};
