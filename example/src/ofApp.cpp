#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofSetFrameRate(25);

    // add message
	ofxHelpMessage::addMessage("HELP (dummy message)");
	ofxHelpMessage::addMessage("Key S: Save");
	ofxHelpMessage::addMessage("Key L: Load");

    a = ofRandom (0,1);
    b = ofRandom (0,1);
    c = ofRandom (0,1);
    d = ofRandom (0,1);

    ofxHelpMessage::addVar(&a);
    ofxHelpMessage::addVar(&b);
    ofxHelpMessage::addVar(&c);

	// clear message
	//ofxHelpMessage::clear();

	// set text color
	// default: ofColor::white
	//ofxHelpMessage::setTextColor(ofColor(255, 255, 0));

	// set background color
	// default: ofColor(0, 0, 0, 150) this is black transparently
	//ofxHelpMessage::setBackgroundColor(ofColor(0));

	// set font
	// draw with ofTrueTypeFont if loaded
	//ofxHelpMessage::loadFont("arial.ttf", 20);

	// set position
	// default: (10, 10)
	//ofxHelpMessage::setPos(500, 500);

	// change show message key
	// default: '?'
    ofxHelpMessage::setHelpKey(' ');

	// set show mode to momentary/toggle
	// default: true (momentary)
    ofxHelpMessage::setMomentary(false); // toggle mode


}

//--------------------------------------------------------------
void ofApp::update() {
	// nothing to do
    float time = ofGetFrameNum();
    a = ofRandom (0,1);
    b = ofRandom (0,1);
    c = ofRandom (0,1);
    d = ofRandom (0,1);

}

//--------------------------------------------------------------
void ofApp::draw() {
	// nothing to show
}
