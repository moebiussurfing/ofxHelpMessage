#include "ofxHelpMessage.h"

ofxHelpMessage* ofxHelpMessage::singleton;

void ofxHelpMessage::setTitle(string _title)
{
    singletonGenerate();
    singleton->mutex.lock();

    singleton->title = _title;

    singleton->mutex.unlock();
    singleton->updateDrawPos();
}

void ofxHelpMessage::addMessage(string _message, string name, bool _newLine) {
    singletonGenerate();
    singleton->mutex.lock();

    singleton->messages.push_back(_message);
    int pos = singleton->messages.size()-1;
    singleton->items.push_back(MSG_Item{name, MSG_TEXT, pos});

    singleton->mutex.unlock();
    singleton->updateDrawPos();
}

void ofxHelpMessage::addVar(float *var, string name, bool _newLine)
{
	singletonGenerate();
	singleton->mutex.lock();

    singleton->vars.push_back(var);
    int pos = singleton->vars.size()-1;
    singleton->items.push_back(MSG_Item{name, MSG_FLOAT, pos});

	singleton->mutex.unlock();
	singleton->updateDrawPos();
}

void ofxHelpMessage::addTitle(string *label, string name, bool _newLine)
{
	singletonGenerate();
	singleton->mutex.lock();

    singleton->titles.push_back(label);
    int pos = singleton->titles.size()-1;
    singleton->items.push_back(MSG_Item{name, MSG_TITLE, pos});

	singleton->mutex.unlock();
	singleton->updateDrawPos();
}

void ofxHelpMessage::updateVars()
{
	//to read pointers every frame cycle
	singletonGenerate();
	singleton->mutex.lock();

    singleton->messageBox = "";
    singleton->messageBox += title;
    singleton->messageBox += ":\n";

	int i = 0;
	for (auto &item : items)
	{
        switch (item.type) {
            case MSG_TITLE:
            {
                int ii = singleton->items[i].position;
                string nn = singleton->items[i].name;
                string temp = *singleton->titles[ii];
                singleton->messageBox += nn;
                singleton->messageBox += ": ";
                singleton->messageBox += temp;
                singleton->messageBox += "\n";
            }
                break;

            case MSG_TEXT:
            {
                int ii = singleton->items[i].position;
                string nn = singleton->items[i].name;
                string temp = singleton->messages[ii];
                singleton->messageBox += nn;
                singleton->messageBox += ": ";
                singleton->messageBox += temp;
                singleton->messageBox += "\n";
            }
                break;

            case MSG_FLOAT:
            {
                int ii = singleton->items[i].position;
                string nn = singleton->items[i].name;
                string temp = ofToString(*singleton->vars[ii]);
                singleton->messageBox += nn;
                singleton->messageBox += ": ";
                singleton->messageBox += temp;
                singleton->messageBox += "\n";
            }
                break;

            default:
                break;
        }
		i++;
	}

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

    messageBox = "";

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
			ofDrawRectangle(font.getStringBoundingBox(messageBox, drawPos.x, drawPos.y));
			ofSetColor(textColor);

			font.drawString(messageBox, drawPos.x, drawPos.y);

		}
		else {
			ofDrawBitmapStringHighlight(messageBox, drawPos, bgColor, textColor);
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


void ofxHelpMessage::clear() {
	singletonGenerate();
	singleton->messageBox = "";
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
		auto fontBoundingBox = singleton->font.getStringBoundingBox(messageBox, pos.x, pos.y);
		drawPos = pos * 2 - ofVec2f(fontBoundingBox.x, fontBoundingBox.y);
	}
	else {
		float lineHeight = 12;
		drawPos = pos + ofVec2f(0, lineHeight);
	}
}
