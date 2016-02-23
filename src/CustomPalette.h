#include "Palette.h"

using namespace ofxColorPalette;

class CustomPalette {
 public:
  CustomPalette(std::vector<ofColor> colors);
  CustomPalette(std::string filename);
  ~CustomPalette();
  std::shared_ptr<ofColor> nextColor();
  void reset();
};
