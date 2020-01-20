#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofSetFrameRate(25);

    // add message
	ofxHelpMessage::addMessage("HELP (dummy message)", "line1");
	ofxHelpMessage::addMessage("Key S: Save", "line2");
	ofxHelpMessage::addMessage("Key L: Load", "line3");
	ofxHelpMessage::addMessage(" ", "line4");

    ofxHelpMessage::addVar(&f1, "myFloat1");
    ofxHelpMessage::addVar(&f2, "myFloat2");
    ofxHelpMessage::addVar(&f3, "myFloat3");
    ofxHelpMessage::addVar(&f4, "myFloat4");

    ofxHelpMessage::addTitle(&tit1, "title1");
    ofxHelpMessage::addTitle(&tit2, "title2");


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

    ofxHelpMessage::setTitle("FONTS DEBUG");
}

//--------------------------------------------------------------
void ofApp::update() {
	// nothing to do

    f1 = ofRandom (0,1);
    f2 = ofRandom (0,1);
    f3 = ofRandom (0,1);
    f4 = ofRandom (0,1);

    int strRandom1 = ofRandom(0,5);
    switch (strRandom1) {
        case 0:
            tit1 = "-1111";
            break;
        case 1:
            tit1 = "1-111";
            break;
        case 2:
            tit1 = "11-11";
            break;
        case 3:
            tit1 = "111-1";
            break;
        case 4:
            tit1 = "1111-";
            break;
        default:
            break;
    }

    float time = ofGetFrameNum();
    tit2 = ofToString(time);
}

//--------------------------------------------------------------
void ofApp::draw() {
	// nothing to show
}
