#include "ofMain.h"
#include <memory>

using namespace ofxColorPalette;

class Palette {
 public:
  Palette();
  ~Palette();
  virtual std::shared_ptr<ofColor> nextColor();
  virtual void reset();
};
