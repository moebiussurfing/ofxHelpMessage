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

void ofxHelpMessage::addText(string _message, string name, bool _newLine) {
    singletonGenerate();
    singleton->mutex.lock();

    singleton->messages.push_back(_message);
    int pos = singleton->messages.size()-1;
    singleton->items.push_back(MSG_Item{name, MSG_TEXT, pos});

    singleton->mutex.unlock();
    singleton->updateDrawPos();
}

void ofxHelpMessage::addString(string *label, string name, bool _newLine)
{
    singletonGenerate();
    singleton->mutex.lock();

    singleton->strings.push_back(label);
    int pos = singleton->strings.size()-1;
    singleton->items.push_back(MSG_Item{name, MSG_STRING, pos});

    singleton->mutex.unlock();
    singleton->updateDrawPos();
}

void ofxHelpMessage::addFloat(float *var, string name, bool _newLine)
{
    singletonGenerate();
    singleton->mutex.lock();

    singleton->floats.push_back(var);
    int pos = singleton->floats.size()-1;
    singleton->items.push_back(MSG_Item{name, MSG_FLOAT, pos});

    singleton->mutex.unlock();
    singleton->updateDrawPos();
}

void ofxHelpMessage::addInt(int *var, string name, bool _newLine)
{
    singletonGenerate();
    singleton->mutex.lock();

    singleton->ints.push_back(var);
    int pos = singleton->ints.size()-1;
    singleton->items.push_back(MSG_Item{name, MSG_INT, pos});

    singleton->mutex.unlock();
    singleton->updateDrawPos();
}

void ofxHelpMessage::addBool(bool *var, string name, bool _newLine)
{
    singletonGenerate();
    singleton->mutex.lock();

    singleton->bools.push_back(var);
    int pos = singleton->bools.size()-1;
    singleton->items.push_back(MSG_Item{name, MSG_BOOL, pos});

    singleton->mutex.unlock();
    singleton->updateDrawPos();
}

void ofxHelpMessage::updateItems()
{
    //to read pointers every frame cycle
    singletonGenerate();
    singleton->mutex.lock();

    //title
    singleton->messageBox = "";
    singleton->messageBox += title;
    singleton->messageBox += ":\n";

    //all variables
    int i = 0;
    for (auto &item : items)
    {
        switch (item.type) {

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

            case MSG_STRING:
            {
                int ii = singleton->items[i].position;
                string nn = singleton->items[i].name;
                string temp = *singleton->strings[ii];
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
                string temp = ofToString(*singleton->floats[ii]);
                singleton->messageBox += nn;
                singleton->messageBox += ": ";
                singleton->messageBox += temp;
                singleton->messageBox += "\n";
            }
                break;

            case MSG_INT:
            {
                int ii = singleton->items[i].position;
                string nn = singleton->items[i].name;
                string temp = ofToString(*singleton->ints[ii]);
                singleton->messageBox += nn;
                singleton->messageBox += ": ";
                singleton->messageBox += temp;
                singleton->messageBox += "\n";
            }
                break;

            case MSG_BOOL:
            {
                int ii = singleton->items[i].position;
                string nn = singleton->items[i].name;
                string temp = (*singleton->bools[ii] ? "TRUE":"FALSE");
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

//    ofEnableDataPath();


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
        updateItems();

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

//layout
void ofxHelpMessage::setMarginBorders(int _margin) {
    singletonGenerate();
    singleton->margin = _margin;
}

void ofxHelpMessage::setTabbed(bool b, int num){
    singletonGenerate();
    singleton->tabsNum = num;
}

void ofxHelpMessage::setRounded(bool b, int size){
    singletonGenerate();
    singleton->bRounded = b;
    singleton->roundedSize = size;
}
