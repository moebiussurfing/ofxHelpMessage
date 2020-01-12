#include "ofxHelpMessage.h"

ofxHelpMessage* ofxHelpMessage::singleton;

void ofxHelpMessage::addVar(float *var)
{
    singletonGenerate();
    singleton->mutex.lock();

////    if (_newLine && singleton->message != "") singleton->message += '\n';
////    singleton->message += _message;
//    singletonGenerate();

    singleton->vars.push_back(var);

//    string str;
//    str ="\n";
//
//    float val;
//    val = *var;
//
//    str += ofToString(val);
//    cout<< str << endl;

//    singleton->message2 += str;
//    singleton->message2 += "_var\n";

    singleton->mutex.unlock();
    singleton->updateDrawPos();
}

void ofxHelpMessage::updateVars()
{
    singletonGenerate();
    singleton->mutex.lock();

    message2 ="";
    message2+="POINTER VARS:\n";
    int i = 0;
    for (auto &var:vars)
    {
        float val = *var;
        singleton->message2 += ofToString(i);
        singleton->message2 += "_";
        singleton->message2 += ofToString(val);
        singleton->message2 +="\n";
        i++;

    }

    cout << message2 << endl;

    singleton->mutex.unlock();
    singleton->updateDrawPos();
}


ofxHelpMessage::ofxHelpMessage() {
	showing = false;
	momentary = true;
	initialized = true;
	textColor = ofColor::white;
	bgColor = ofColor(0, 150);
	pos.set(10, 10);
	helpKey = '?';

//    vars.resize(8);
//    for (auto var:messageVars)
//    {
//
//    }

	ofAddListener(ofEvents().draw, this, &ofxHelpMessage::draw, OF_EVENT_ORDER_AFTER_APP);
	ofAddListener(ofEvents().keyPressed, this, &ofxHelpMessage::keyPressed, OF_EVENT_ORDER_AFTER_APP);
}

ofxHelpMessage::~ofxHelpMessage() {
	ofRemoveListener(ofEvents().draw, this, &ofxHelpMessage::draw);
	ofRemoveListener(ofEvents().keyPressed, this, &ofxHelpMessage::keyPressed);
}

void ofxHelpMessage::draw(ofEventArgs& e) {
	if (momentary) {
		showing = ofGetKeyPressed(helpKey);
	}

	if (showing) {
        updateVars();

		ofPushStyle();
		if (font.isLoaded()) {
			ofSetColor(bgColor);
			ofFill();
			ofDrawRectangle(font.getStringBoundingBox(message, drawPos.x, drawPos.y));
			ofSetColor(textColor);
			font.drawString(message, drawPos.x, drawPos.y);

            font.drawString(message2, drawPos.x, drawPos.y+200);

		}
		else {
			ofDrawBitmapStringHighlight(message, drawPos, bgColor, textColor);

            ofDrawBitmapStringHighlight(message2, drawPos.x, drawPos.y+200, bgColor, textColor);
		}
		ofPopStyle();
	}
}

void ofxHelpMessage::keyPressed(ofKeyEventArgs& key) {
	if (!momentary && key.key == helpKey) {
		showing = !showing;
	}
}

void ofxHelpMessage::loadFont(string _path, float _size) {
	singletonGenerate();
	singleton->font.load(_path, _size);
	singleton->updateDrawPos();
}

void ofxHelpMessage::addMessage(string _message, bool _newLine) {
	singletonGenerate();
	singleton->mutex.lock();
	if (_newLine && singleton->message != "") singleton->message += '\n';
	singleton->message += _message;
	singleton->mutex.unlock();

	singleton->updateDrawPos();
}

void ofxHelpMessage::clear() {
	singletonGenerate();
	singleton->message = "";
}

void ofxHelpMessage::setPos(ofVec2f _pos) {
	singletonGenerate();
	singleton->pos.set(_pos);
	singleton->updateDrawPos();
}

void ofxHelpMessage::setPos(float _x, float _y) {
	setPos(ofVec2f(_x, _y));
}

ofVec2f ofxHelpMessage::getPos() {
	singletonGenerate();
	return singleton->pos;
}

void ofxHelpMessage::setTextColor(ofColor _color) {
	singletonGenerate();
	singleton->textColor.set(_color);
}

ofColor ofxHelpMessage::getTextColor() {
	singletonGenerate();
	return singleton->textColor;
}

void ofxHelpMessage::setBackgroundColor(ofColor _color) {
	singletonGenerate();
	singleton->bgColor = _color;
}

ofColor ofxHelpMessage::getBackgroundColor() {
	singletonGenerate();
	return singleton->bgColor;
}

void ofxHelpMessage::setHelpKey(char _key) {
	singletonGenerate();
	singleton->helpKey = _key;
}

char ofxHelpMessage::getHelpKey() {
	singletonGenerate();
	return singleton->helpKey;
}

void ofxHelpMessage::setMomentary(bool _momentary) {
	singletonGenerate();
	singleton->momentary = _momentary;
	if (singleton->momentary) singleton->showing = ofGetKeyPressed(singleton->helpKey);
}

bool ofxHelpMessage::getMomentary() {
	singletonGenerate();
	return 	singleton->momentary;
}

bool ofxHelpMessage::getSwhoing() {
	singletonGenerate();
	return singleton->showing;
}

void ofxHelpMessage::singletonGenerate() {
	if (singleton == nullptr) {
		singleton = new ofxHelpMessage();
	}
}

void ofxHelpMessage::updateDrawPos() {
	// calc position
	if (font.isLoaded()) {
		auto fontBoundingBox = singleton->font.getStringBoundingBox(message, pos.x, pos.y);
		drawPos = pos * 2 - ofVec2f(fontBoundingBox.x, fontBoundingBox.y);
	}
	else {
		float lineHeight = 12;
		drawPos = pos + ofVec2f(0, lineHeight);
	}
}
