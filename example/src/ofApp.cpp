#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofSetFrameRate(25);

    // add message

    title = "APP INFO                  \n";//+spaces to avoid resizing on bbox
    ofxHelpMessage::setTitle(title);

    //name not showed in text type
    ofxHelpMessage::addText("text1", "HELP:");
    ofxHelpMessage::addText("text2", "KEY [SPACE]: HIDE/SHOW");
    ofxHelpMessage::addText("text3", "");

    ofxHelpMessage::addText("text4", "DEBUG:");
    ofxHelpMessage::addString("myString2", &str2);
    ofxHelpMessage::addFloat("myFloat1 ", &f1);
    ofxHelpMessage::addFloat("myFloat2 ", &f2);
    ofxHelpMessage::addFloat("myFloat3 ", &f3);
    ofxHelpMessage::addString("myString1", &str1);

    ofxHelpMessage::addText("text", "\nCOUNTERS:");
    ofxHelpMessage::addInt("myInt1   ", &i1);
    ofxHelpMessage::addInt("myInt2   ", &i2);
    ofxHelpMessage::addFloat("myFloat4 ", &f4);

    ofxHelpMessage::addText("text", "\nSWITCHES:");
    ofxHelpMessage::addBool("myBool1  ", &b1);
    ofxHelpMessage::addBool("myBool2  ", &b2);

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
    //ofxHelpMessage::loadFont("arial.ttf", fontSize);
    //ofxHelpMessage::loadFont("overpass-mono-light.otf", fontSize);
	ofxHelpMessage::loadFont("mono.ttf", fontSize);

    // set position
    // default: (10, 10)
    ofxHelpMessage::setPos(10, 10);

    // change show message key
    // default: '?'
    ofxHelpMessage::setHelpKey(' ');

    // set show mode to momentary/toggle
    // default: true (momentary)
    ofxHelpMessage::setMomentary(false); // toggle mode


    // set margin borders
    // default 5
    ofxHelpMessage::setMarginBorders(20);

    // tab labels and values
    ofxHelpMessage::setTabbed(true, 1);

    // float decimals
    ofxHelpMessage::setFloatResolution(1);

    // round bbox
    //ofxHelpMessage::setRounded(true);

	// show fps
	ofxHelpMessage::setShowFPS(true);

    // show box. hidden by default
    ofxHelpMessage::setShowing(true);
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
