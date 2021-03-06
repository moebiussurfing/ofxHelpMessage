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

void ofxHelpMessage::addNewLine() {
	string name = "noName";

	singletonGenerate();
	singleton->mutex.lock();

	singleton->messages.push_back("\n");
	int pos = singleton->messages.size() - 1;
	singleton->items.push_back(MSG_Item{ name, MSG_TEXT, pos });

	singleton->mutex.unlock();
	singleton->updateDrawPos();
}

//name is hidden in MSG_TEXT types. maybe not required but could search item by name..
void ofxHelpMessage::addText(string _message, bool _newLine) {
	string name = "noName";
	
	singletonGenerate();
	singleton->mutex.lock();

	singleton->messages.push_back(_message);
	int pos = singleton->messages.size() - 1;
	singleton->items.push_back(MSG_Item{ name, MSG_TEXT, pos });

	if (_message.size() > singleton->maxChars)
		singleton->maxChars = _message.size();

	singleton->mutex.unlock();
	singleton->updateDrawPos();
}

void ofxHelpMessage::addText(string name, string _message, bool _newLine) {
	singletonGenerate();
	singleton->mutex.lock();

	singleton->messages.push_back(_message);
	int pos = singleton->messages.size() - 1;
	singleton->items.push_back(MSG_Item{ name, MSG_TEXT, pos });

	if(_message.size()> singleton->maxChars)
		singleton->maxChars = _message.size();

	singleton->mutex.unlock();
	singleton->updateDrawPos();
}

void ofxHelpMessage::addString(string name, string *label, bool _newLine)
{
	singletonGenerate();
	singleton->mutex.lock();

	singleton->strings.push_back(label);
	int pos = singleton->strings.size() - 1;
	singleton->items.push_back(MSG_Item{ name, MSG_STRING, pos });

	if (name.size() > singleton->maxChars)
		singleton->maxChars = name.size();

	singleton->mutex.unlock();
	singleton->updateDrawPos();
}

void ofxHelpMessage::addFloat(string name, float *var, bool _newLine)
{
	singletonGenerate();
	singleton->mutex.lock();

	singleton->floats.push_back(var);
	int pos = singleton->floats.size() - 1;
	singleton->items.push_back(MSG_Item{ name, MSG_FLOAT, pos });

	if (name.size() > singleton->maxChars)
		singleton->maxChars = name.size();

	singleton->mutex.unlock();
	singleton->updateDrawPos();
}

void ofxHelpMessage::addInt(string name, int *var, bool _newLine)
{
	singletonGenerate();
	singleton->mutex.lock();

	singleton->ints.push_back(var);
	int pos = singleton->ints.size() - 1;
	singleton->items.push_back(MSG_Item{ name, MSG_INT, pos });

	if (name.size() > singleton->maxChars)
		singleton->maxChars = name.size();

	singleton->mutex.unlock();
	singleton->updateDrawPos();
}

void ofxHelpMessage::addBool(string name, bool *var, bool _newLine)
{
	singletonGenerate();
	singleton->mutex.lock();

	singleton->bools.push_back(var);
	int pos = singleton->bools.size() - 1;
	singleton->items.push_back(MSG_Item{ name, MSG_BOOL, pos });

	if (name.size() > singleton->maxChars)
		singleton->maxChars = name.size();

	singleton->mutex.unlock();
	singleton->updateDrawPos();
}

void ofxHelpMessage::addParamFloat(ofParameter<float> p, bool _newLine)
//void ofxHelpMessage::addParamFloat(ofParameter<float> *p, bool _newLine)
{
	singletonGenerate();
	singleton->mutex.lock();

	//string name = p->getName();
	string name = p.getName();
	singleton->paramsFloats.push_back(p);
	int pos = singleton->paramsFloats.size() - 1;
	singleton->items.push_back(MSG_Item{ name, MSG_PARAM_FLOAT, pos });

	if (name.size() > singleton->maxChars)
		singleton->maxChars = name.size();

	singleton->mutex.unlock();
	singleton->updateDrawPos();
}

//--

void ofxHelpMessage::updateItems()
{
	//to read pointers every frame cycle
	singletonGenerate();
	singleton->mutex.lock();

	//title
	singleton->messageBox = "";
	singleton->messageBox += title;
	singleton->messageBox += "\n";

	//all variables
	int i = 0;
	for (auto &item : items)
	{
		switch (item.type) {

		case MSG_TEXT:
		{
			int ii = singleton->items[i].position;

			//name is hidden in MSG_TEXT types. maybe not require but could search item by name..
			if (false)
			{
				string n = singleton->items[i].name;
				fillName(n);

				singleton->messageBox += n;
				//singleton->messageBox += ":";
				if (bTabbed)
				{
					for (int i = 0; i < tabsNum; i++)
					{
						singleton->messageBox += "\t";
					}
				}
			}
			//value
			string v = singleton->messages[ii];
			singleton->messageBox += v;
			singleton->messageBox += "\n";
		}
		break;

		case MSG_STRING:
		{
			int ii = singleton->items[i].position;
			
			string n = singleton->items[i].name;
			fillName(n);

			string v = *singleton->strings[ii];
			singleton->messageBox += n;
			//singleton->messageBox += ":";
			if (bTabbed)
			{
				for (int i = 0; i < tabsNum; i++)
				{
					singleton->messageBox += "\t";
				}
			}
			//singleton->messageBox += ":";
			singleton->messageBox += v;
			singleton->messageBox += "\n";
		}
		break;

		case MSG_FLOAT:
		{
			int ii = singleton->items[i].position;
			
			string n = singleton->items[i].name;
			fillName(n);

			string v = ofToString(*singleton->floats[ii], fRes);
			singleton->messageBox += n;
			//singleton->messageBox += ":";
			if (bTabbed)
			{
				for (int i = 0; i < tabsNum; i++)
				{
					singleton->messageBox += "\t";
				}
			}
			//singleton->messageBox += ":";
			singleton->messageBox += v;
			singleton->messageBox += "\n";
		}
		break;

		case MSG_INT:
		{
			int ii = singleton->items[i].position;
			
			string n = singleton->items[i].name;
			fillName(n);

			string v = ofToString(*singleton->ints[ii]);
			singleton->messageBox += n;
			//singleton->messageBox += ":";
			if (bTabbed)
			{
				for (int i = 0; i < tabsNum; i++)
				{
					singleton->messageBox += "\t";
				}
			}
			//singleton->messageBox += ":";
			singleton->messageBox += v;
			singleton->messageBox += "\n";
		}
		break;

		case MSG_BOOL:
		{
			int ii = singleton->items[i].position;
			
			string n = singleton->items[i].name;
			fillName(n);

			string v = (*singleton->bools[ii] ? "TRUE" : "FALSE");
			singleton->messageBox += n;
			//singleton->messageBox += ":";
			if (bTabbed)
			{
				for (int i = 0; i < tabsNum; i++)
				{
					singleton->messageBox += "\t";
				}
			}
			//singleton->messageBox += ":";
			singleton->messageBox += v;
			singleton->messageBox += "\n";
		}
		break;

		case MSG_PARAM_FLOAT:
		{
			int ii = singleton->items[i].position;
			
			string n = singleton->items[i].name;
			fillName(n);

			//string v = ofToString(*singleton->paramsFloats[ii].get(), fRes);
			string v = ofToString(singleton->paramsFloats[ii].get(), fRes);
			singleton->messageBox += n;
			//singleton->messageBox += ":";
			if (bTabbed)
			{
				for (int i = 0; i < tabsNum; i++)
				{
					singleton->messageBox += "\t";
				}
			}
			//singleton->messageBox += ":";
			singleton->messageBox += v;
			singleton->messageBox += "\n";
		}
		break;

		default:
			break;
		}

		//next
		i++;
	}

	if (showFPS)
	{
		singleton->messageBox += "\n";
		singleton->messageBox += ofToString(ofGetFrameRate(), 0);
		singleton->messageBox += " FPS";
	}

	singleton->mutex.unlock();
	singleton->updateDrawPos();
}

///-

ofxHelpMessage::ofxHelpMessage() {
	showing = false;
	BBoxShowing = true;
	momentary = false;
	initialized = true;
	textColor = ofColor::white;
	bgColor = ofColor(0, 150);
	pos.set(10, 10);
	helpKey = '?';
	showFPS = false;
	bTabbed = false;

	messageBox = "";
	maxChars = 0;

	ofAddListener(ofEvents().draw, this, &ofxHelpMessage::draw, OF_EVENT_ORDER_AFTER_APP);
	ofAddListener(ofEvents().keyPressed, this, &ofxHelpMessage::keyPressed, OF_EVENT_ORDER_AFTER_APP);
}

ofxHelpMessage::~ofxHelpMessage() {
	ofRemoveListener(ofEvents().draw, this, &ofxHelpMessage::draw);
	ofRemoveListener(ofEvents().keyPressed, this, &ofxHelpMessage::keyPressed);
}

void ofxHelpMessage::draw(ofEventArgs& e) {

	ofEnableAlphaBlending();

	if (momentary) {
		showing = ofGetKeyPressed(helpKey);
	}

	if (showing) {
		updateItems();

		ofPushStyle();
		if (font.isLoaded()) {

			//bbox
			if (BBoxShowing)
			{
				ofSetColor(bgColor);
				ofFill();

				//bbox
				rectBB = font.getStringBoundingBox(messageBox, drawPos.x, drawPos.y);
				rectBB.x -= margin;
				rectBB.y -= margin;
				rectBB.height += 2 * margin;
				rectBB.width += 2 * margin;

				//to compensate pos after margin
				ofPushMatrix();
				ofTranslate(margin, margin);

				//rounded
				if (bRounded)
				{
					ofDrawRectRounded(rectBB, roundedSize);
				}
				else
				{
					ofDrawRectangle(rectBB);
				}
			}

			//text
			ofSetColor(textColor);
			font.drawString(messageBox, drawPos.x, drawPos.y);

			ofPopMatrix();
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

void ofxHelpMessage::clear() {
	singletonGenerate();
	singleton->messageBox = "";
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

void ofxHelpMessage::setShowing(bool _showing) {
	singletonGenerate();
	singleton->showing = _showing;
}

void ofxHelpMessage::setShowFPS(bool _showing) {
	singletonGenerate();
	singleton->showFPS = _showing;
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

//colors
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

void ofxHelpMessage::setBackgroundAlpha(int _alpha) {
	singletonGenerate();
	ofColor c = singleton->bgColor;
	singleton->bgColor.set(c.r, c.g, c.b, _alpha);
}

ofColor ofxHelpMessage::getBackgroundColor() {
	singletonGenerate();
	return singleton->bgColor;
}

//font
void ofxHelpMessage::loadFont(string _path, float _size) {
	singletonGenerate();
	singleton->font.load(_path, _size);
	singleton->updateDrawPos();
}

//layout
void ofxHelpMessage::setMarginBorders(int _margin) {
	singletonGenerate();
	singleton->margin = _margin;
}

void ofxHelpMessage::setRounded(bool b, float size) {
	singletonGenerate();
	singleton->bRounded = b;
	singleton->roundedSize = size;
}

//TODO:
//must repair columns align by tabs
void ofxHelpMessage::setTabbed(bool b, int num) {
	singletonGenerate();
	singleton->bTabbed = b;
	singleton->tabsNum = num;
}

void ofxHelpMessage::setFloatResolution(int res) {
	singletonGenerate();
	singleton->fRes = res;
}
