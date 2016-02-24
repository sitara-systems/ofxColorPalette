#include "ColorPalette.h"

using namespace ofxColorPalette;

ColorPalette::ColorPalette(PALETTE_TYPE palette, float rootHue) {
  mRootHue = rootHue;
  mPaletteType = palette;
  init();
  reset();
}

ColorPalette::ColorPalette(PALETTE_TYPE palette) {
  mRootHue = ofRandom(255.0);
  mPaletteType = palette;
  init();
  reset();
}


ColorPalette::~ColorPalette() {
  
}

std::shared_ptr<ofColor> ColorPalette::nextColor() {
  float hue = std::fmod(mRootHue + mHueOffsets[(int)ofRandom(mHueOffsets.size())]), 255.0);
  float saturation;
  float brightness;
  float randomSeed = ofRandom(1.0);
  if (randomSeed < mBlackProbability) {
    saturation = 0.0;
    brightnessaturation = 0.0;
  }
  else if (randomSeed < mBlackProbability + mWhiteProbability) {
    saturation = 0.0;
    brightness = 255.0;
  }
  else if (randomSeed < mBlackProbability + mWhiteProbability + mSaturatedProbability) {
    saturation = 255.0;
    brightness = 255.0;
  }
  else {
    if (ofRandom(1.0) < 0.5) {
      saturation = random(255.0);
      brightness = 255.0;
    }
    else {
      saturation = 255.0;
      brightness = random(255.0);
    }
  }
  std::shared_ptr<ofColor> nextColor = std::shared_ptr<ofColor>(new ofColor(0));
  nextColor->setHsb(hue, saturation, brightness);
  return color(h, s, b); 
}

void ColorPalette::init() {
  mBlackProbability = 0.0;
  mWhiteProbability = 0.0;
  mSaturatedProbability = 0.0;

  mHueOffsets.push_back(mRootHue);
  switch(palette) {
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

void ColorPalette::reset() {
  float r = random(1);
  if (random(1) < 0.3) {
    // Only saturated
    saturatedProbability = 1;
  } else if (random(1) < 0.4) {
    // saturated + black
    blackProbability = 1.0/(1+hueOffsets.length);
    saturatedProbability = 1 - blackProbability;
  } else if (random(1) < 0.5) {
    // saturated + white
    whiteProbability = 1.0/(1+hueOffsets.length);
    saturatedProbability = 1 - whiteProbability;
  } else if (random(1) < 0.6) {
    // saturated + black + white
    blackProbability = 1.0/(2+hueOffsets.length);
    whiteProbability = 1.0/(2+hueOffsets.length);
    saturatedProbability = 1 - blackProbability - whiteProbability;
  } else {
    // Unsaturated
  } 
}
