#include "ofApp.h"

using namespace ofxColorPalette;

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("ofxColorPalette -- Palette Sampler Example");
	mFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

	mPaletteNames.push_back("Monochrome");
	mPaletteNames.push_back("Complementary");
	mPaletteNames.push_back("Split Complementary");
	mPaletteNames.push_back("Triadic");
	mPaletteNames.push_back("Tetradic");
	mPaletteNames.push_back("Four Tone");
	mPaletteNames.push_back("Five Tone");
	mPaletteNames.push_back("Six Tone");
	mPaletteNames.push_back("Neutral");

	drawCircles(ofxColorPalette::PALETTE_TYPE::MONOCHROME);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	mFbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case '1':
		drawCircles(ofxColorPalette::PALETTE_TYPE::MONOCHROME);
		break;
	case '2':
		drawCircles(ofxColorPalette::PALETTE_TYPE::COMPLEMENTARY);
		break;
	case '3':
		drawCircles(ofxColorPalette::PALETTE_TYPE::SPLIT_COMPLEMENTARY);
		break;
	case '4':
		drawCircles(ofxColorPalette::PALETTE_TYPE::TRIADIC);
		break;
	case '5':
		drawCircles(ofxColorPalette::PALETTE_TYPE::TETRADIC);
		break;
	case '6':
		drawCircles(ofxColorPalette::PALETTE_TYPE::FOUR_TONE);
		break;
	case '7':
		drawCircles(ofxColorPalette::PALETTE_TYPE::FIVE_TONE);
		break;
	case '8':
		drawCircles(ofxColorPalette::PALETTE_TYPE::SIX_TONE);
		break;
	case '9':
		drawCircles(ofxColorPalette::PALETTE_TYPE::NEUTRAL);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::drawCircles(ofxColorPalette::PALETTE_TYPE palette_type) {
	ColorPalette* palette = new ColorPalette(palette_type, 25.0);
	palette->setProbabilities(0.1, 0.1, 0.3);

	mFbo.begin();
	ofBackground(128);

	for (int i = 0; i < 100; i++) {
		std::shared_ptr<ofColor> color = palette->nextColor();
		ofSetColor(*color.get());
		ofCircle(ofPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())), 10);
	}

	ofSetColor(255);

	char palette_name[256];
	sprintf(palette_name, "Color Palette: %s \n-----------------------------------", mPaletteNames.at(palette_type).c_str());
	ofDrawBitmapString(palette_name, 50, 50);

	char color_title[256];
	sprintf(color_title, "Hues", mPaletteNames[palette_type]);
	ofDrawBitmapString(color_title, 50, 75);

	int count = 1;
	for (auto hue : palette->getHues()) {
		char color_name[256];
		sprintf(color_name, "%f", std::fmod(palette->getRootHue() + hue, 255.0));
		ofDrawBitmapString(color_name, 50, 75 + count * 12.5);
		count++;
	}

	mFbo.end();

	delete palette;
}
