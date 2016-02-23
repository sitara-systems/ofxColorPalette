#include "Palette.h"

using namespace ofxColorPalette;

class RandomSaturatedPalette {
 public:
  RandomSaturatedPalette();
  ~RandomSaturatedPalette();
  std::shared_ptr<ofColor> nextColor() {
    std::shared_ptr<ofColor> nextColor = std::shared_ptr<ofColor>(new ofColor(0));
    nextColor.setHsb(ofRandom(255.0), 255.0, 255.0);
    return nextColor;
  };
  void reset();
};
