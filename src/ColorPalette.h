#include "Palette.h"

using namespace ofxColorPalette;

class ColorPalette {
 public:
  ColorPalette();
  ~ColorPalette();
  std::shared_ptr<ofColor> nextColor();
  void reset();
};
