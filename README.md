# ofxColorPalette
A set of classes for generatively creating visually pleasing color schemes.

## Requirements
None!  This addon will work right out of the box.

## Usage
All palettes inherit from the class `Palette.h`, and therefore have the same interface.  For any palette included here, you can use it by:

* Creating a color palette:

  ofxColorPalette::ColorPalette palette = new RandomPalette();

* Calling `nextColor()` to get a `std::shared_ptr` to a color:

  std::shared_ptr<ofColor> color_to_be_used = palette->nextColor();

* Using the color as you normally would!  You'll need to use the dereference operator (`*`) to get the `ofColor` object.

  ofFill();
  ofSetColor(*color_to_be_used);
  ofCircle(0, 0, 100);


The included examples show this particular behavior.

We've included several color palette options in this addon:

### RandomPalette

The `RandomPalette` palette creates color with a random HSB triplet -- use this to create truly random colors.

### RandomSaturatedPalette

The `RandomSaturatedPalette` palette creates color with a random hue and random brightness, but always with a full saturation value.  This will produce random saturated colors, with zero probability of black or white.  This palette will also not create any pastels -- just fully saturated colors.

### ColorPalette

This palette is by far the most complex with the greatest number of options.  The constructor takes a root hue as the 'base' of the pallete, and a `PALETTE_TYPE` argument, which provides 9 options for a color palette:

* `MONOCHROME` -- A single hue, the root hue.
* `COMPLEMENTARY` -- Two hues: the root hue, and it's complementary color 180 degrees on the color wheel.
* `SPLIT_COMPLEMENTARY` -- Three hues: the root hue, and two hues evenly offset from the complement.
* `TRIADIC` -- Three hues evenly spaced on the color wheel.
* `TETRADIC` -- Four hues evenly spaced on the color wheel.
* `FOUR_TONE` -- The root, a color closely offset from the hue by 60 degrees, and then the two complements.
* `FIVE_TONE` -- The root and four split complementary colors.
* `SIX_TONE` -- Like `TRIADIC`, but with a neighboring tone for each of the three.
* `NEUTRAL` -- Six evenly spaced colors on the color wheel.

#### Basic Usage
Once you've created a `ColorPalette` object, it has random probabilities for generating black, white, and saturated (both partially and fully) colors.  If you'd like to set the probabilities to a specific ratio, you can do so using the function

     setProbabilities(float black, float white, float saturated)

All three probabilities should add up to one.  The colors that are generated will have randomly assigned values for brightness and saturation; if you wish to have a minimum or maximum for the randomly generated values, you can do so with

    setMinimumSaturation(float minimum_saturation);
    setMaximumSaturation(float maximum_saturation);
    setMinimumBrightness(float minimum_brightness);
    setMaximumBrightness(float maximum_brightness);

#### Saturation Options
In addition to the above options, there are three types of saturation options, described in the enum `SATURATION_TYPE`:

* `STATIC` -- The saturation will always be staticly set to the maximum value (default is 255.0).
* `LEVELS` -- The saturation will be quantized to a finite number of saturation values, up to the maximum value.  These levels do not include white (saturation = 0).  The default number of levels is 8, and this is the default behavior for the class.
* `RANDOM` -- This will make the saturation a random number chosen between the minimum and maximum saturation bounds.

The number of saturation levels is adjustable via the corresponding setter.

#### Hue Options
There are two options for hue, defined in the enum `HUE_TYPE`:

* `UNIFORM` -- all hues, as set by the `PALETTE_TYPE` variable, are equally probable.
* `SKEWED_ROOT` -- the root hue has a skewed probablity set by `mRootProbability`.

If you choose `SKEWED_ROOT`, the root probability can be set via:

    setProbabilities(float black, float white, float saturated, float root)

Not that this probability is seperate from the black/white/saturated probabilities, and does not have to add up to one.  This is because the hue is chosen after the type of color.

## Examples

* `example-paletteSelector` draws randomly placed circles on the screen using the color palette's `nextColor()` function.
* `example-colorVisualization` shows an alternative way to use the `ColorPalette` class, using it as a container to generate hues and saturations, but not using the color non-randomly to visualize a color wheel.