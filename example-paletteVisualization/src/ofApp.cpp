#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("ofxColorPalette -- Palette Visualization Example");
	mFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

	mPalette = std::make_shared<ofxColorPalette::ColorPalette>(ofxColorPalette::PALETTE_TYPE::TETRADIC, 0.0);
	mPalette->setNumberOfSaturationLevels(11);
	mSelectedHueIndex = 0;
	mSelectedSaturationLevel = 5;
	drawPalette();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	mFbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case '1':
		mPalette->setPaletteType(ofxColorPalette::PALETTE_TYPE::MONOCHROME);
		drawPalette();
		break;
	case '2':
		mPalette->setPaletteType(ofxColorPalette::PALETTE_TYPE::COMPLEMENTARY);
		drawPalette();
		break;
	case '3':
		mPalette->setPaletteType(ofxColorPalette::PALETTE_TYPE::SPLIT_COMPLEMENTARY);
		drawPalette();
		break;
	case '4':
		mPalette->setPaletteType(ofxColorPalette::PALETTE_TYPE::TRIADIC);
		drawPalette();
		break;
	case '5':
		mPalette->setPaletteType(ofxColorPalette::PALETTE_TYPE::TETRADIC);
		drawPalette();
		break;
	case '6':
		mPalette->setPaletteType(ofxColorPalette::PALETTE_TYPE::FOUR_TONE);
		drawPalette();
		break;
	case '7':
		mPalette->setPaletteType(ofxColorPalette::PALETTE_TYPE::FIVE_TONE);
		drawPalette();
		break;
	case '8':
		mPalette->setPaletteType(ofxColorPalette::PALETTE_TYPE::SIX_TONE);
		drawPalette();
		break;
	case '9':
		mPalette->setPaletteType(ofxColorPalette::PALETTE_TYPE::NEUTRAL);
		drawPalette();
		break;
	case OF_KEY_DOWN:
		mSelectedSaturationLevel++;
		if (mSelectedSaturationLevel > mPalette->getNumberOfSaturationLevels() - 2) {
			mSelectedSaturationLevel = mPalette->getNumberOfSaturationLevels() - 2;
		}
		drawPalette();
		break;
	case OF_KEY_UP:
		mSelectedSaturationLevel--;
		if (mSelectedSaturationLevel < 0) {
			mSelectedSaturationLevel = 0;
		}
		drawPalette();
		break;
	case OF_KEY_LEFT:
		mSelectedHueIndex--;
		if (mSelectedHueIndex < 0) {
			mSelectedHueIndex = 9;
		}
		mPalette->setRootHue(mSelectedHueIndex * 255.0 / 10.0);
		drawPalette();
		break;
	case OF_KEY_RIGHT:
		mSelectedHueIndex++;
		if (mSelectedHueIndex > 9) {
			mSelectedHueIndex = 0;
		}
		mPalette->setRootHue(mSelectedHueIndex * 255.0 / 10.0);
		drawPalette();
		break;

	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::drawPalette() {
	mFbo.begin();
	ofBackground(0);

	// draw saturation boxes

	float box_x = 0.167*ofGetWidth();
	float box_y = 0.1*ofGetHeight();
	float box_size = 0.8*ofGetHeight() / (1.5 * (mPalette->getNumberOfSaturationLevels() - 1.0));
	float saturation = 0;

	std::vector<float> saturation_levels = mPalette->getSaturationLevels();

	ofFill();
	for (int i = 0; i < mPalette->getNumberOfSaturationLevels() - 1; i++) {
		ofColor c = ofColor(0.0);
		c.setHsb(mPalette->getRootHue(), saturation_levels[i], 255);
		ofSetColor(c);
		ofRect(box_x, box_y + 1.5*i*box_size, box_size, box_size);
		if (i == mSelectedSaturationLevel) {
			saturation = saturation_levels[i];
			ofNoFill();
			ofSetColor(255);
			ofRect(box_x - 0.05*box_size, box_y + 1.5*i*box_size - 0.05*box_size, 1.1*box_size, 1.1*box_size);
			ofFill();
		}
	}
	
	// draw possible root hues
	box_x = 0.167*ofGetWidth() + 1.5*box_size;
	box_y = 0.9*ofGetHeight();

	ofFill();
	for (int i = 0; i < 10.0; i++) {
		ofColor c = ofColor(0.0);
		c.setHsb(255.0 * i / 10.0, saturation, 255.0);
		ofSetColor(c);
		ofRect(box_x + 1.5*i*box_size, box_y, box_size, box_size);
		if (i == mSelectedHueIndex) {
			ofNoFill();
			ofSetColor(255);
			ofRect(box_x + 1.5*i*box_size - 0.05*box_size, box_y - 0.05*box_size, 1.1*box_size, 1.1*box_size);
			ofFill();
		}
	}


	// draw color wedges
	std::vector<float> hues = mPalette->getHues();

	ofSetColor(saturation);
	float circle_radius = 100;
	ofCircle(0.5*ofGetWidth(), 0.5*ofGetHeight(), circle_radius);

	ofTranslate(0.5*ofGetWidth(), 0.5*ofGetHeight());

	float startAngle = 0;
	float endAngle = 0;

	for (int j = 0; j < 10; j++) {
		startAngle = std::fmod(255.0 * j / 10.0, 255);
		endAngle = std::fmod(255.0 * (j + 1.0) / 10.0, 255);

		ofSetColor(0.2 * 255);
		for (auto color : hues) {
			if (color >= startAngle && color < endAngle) {
				ofColor c = ofColor(0.0);
				c.setHsb(color, saturation, 255);
				ofSetColor(c);
			}
			else if (startAngle >= 255.0 * 9.0 / 10.0 && color >= 255.0 * 9.0 / 10.0) {
				ofColor c = ofColor(0.0);
				c.setHsb(color, saturation, 255);
				ofSetColor(c);
			}
		}


		ofPushMatrix();
		ofBeginShape();
		float inner_radius = 1.25*circle_radius;
		float outer_radius = inner_radius + 0.25*ofGetHeight();
		for (int i = 0; i < 10; i++) {
			float angle = TWO_PI * (1.0 / 12.0) * (i / 10.0) + TWO_PI * j / 10.0;
			ofVertex(outer_radius*cos(angle), outer_radius*sin(angle));
		}
		for (int i = 10; i > 0; i--) {
			float angle = TWO_PI * (1.0 / 12.0) * (i / 10.0) + TWO_PI * j / 10.0;
			ofVertex(inner_radius*cos(angle), inner_radius*sin(angle));
		}

		ofEndShape();
		ofPopMatrix();
	}

	mFbo.end();
}