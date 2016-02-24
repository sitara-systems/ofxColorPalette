#include "ofMain.h"
#include <memory>

namespace ofxColorPalette {

class Palette {
 public:
  Palette();
  ~Palette();
  virtual std::shared_ptr<ofColor> nextColor();
};

}