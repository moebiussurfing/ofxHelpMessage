#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofSetFrameRate(25);

//    ofEnableDataPath();

    // add message

    title = "FONTS DEBUG";
    ofxHelpMessage::setTitle(title);

    ofxHelpMessage::addText("HELP:", "text1");
	ofxHelpMessage::addText("Key [SPACE]: HIDE/SHOW", "text2");
	ofxHelpMessage::addText("Key [D]: DEBUG", "text3");
	ofxHelpMessage::addText(" ", "text4");

    ofxHelpMessage::addString(&str1, "myString1");
    ofxHelpMessage::addString(&str2, "myString2");

    ofxHelpMessage::addFloat(&f1, "myFloat1");
    ofxHelpMessage::addFloat(&f2, "myFloat2");
    ofxHelpMessage::addFloat(&f3, "myFloat3");
    ofxHelpMessage::addFloat(&f4, "myFloat4");

    ofxHelpMessage::addInt(&i1, "myInt1");
    ofxHelpMessage::addInt(&i2, "myInt2");

    ofxHelpMessage::addBool(&b1, "myBool1");
    ofxHelpMessage::addBool(&b2, "myBool2");

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
//    ofxHelpMessage::loadFont("arial.ttf", fSize);
//    ofxHelpMessage::loadFont("Kazesawa-Extrabold.ttf", fSize);
//    ofxHelpMessage::loadFont("Kazesawa-Light.ttf", fSize);
    ofxHelpMessage::loadFont("overpass-mono-light.otf", fSize);

	// set position
	// default: (10, 10)
    ofxHelpMessage::setPos(200, 200);

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

    ///-

    //make random changes to our variables to demo

    int time = ofGetFrameNum();

    //string
    int myRandom = ofRandom(0,5);
    switch (myRandom) {
        case 0:
            str1 = "|----";
            break;
        case 1:
            str1 = "-|---";
            break;
        case 2:
            str1 = "--|--";
            break;
        case 3:
            str1 = "---|-";
            break;
        case 4:
            str1 = "----|";
            break;
        default:
            break;
    }

    //string
    str2 = ofToString(time);

    //floats
    f1 = ofRandom (0,1);
    f2 = ofRandom (0,1);
    f3 = ofRandom (0,1);
    f4 = ofRandom (0,1);

    //ints
    i1 = time;
    i2 = ofGetFrameNum() % 60;

    //bools
    if (ofGetFrameNum() % 60) b1=!b1;
    if (myRandom == 4) b2=!b2;

}

//--------------------------------------------------------------
void ofApp::draw() {
	// nothing to show
}
