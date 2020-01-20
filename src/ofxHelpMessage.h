#pragma once
#include "ofMain.h"

class ofxHelpMessage
{
private:
	ofxHelpMessage();
	~ofxHelpMessage();

public:

    enum MSG_TYPES{
        MSG_TITLE = 0,
        MSG_TEXT,
        MSG_FLOAT,
        MSG_STRING,
        MSG_BOOL
    };

    struct MSG_Item {
        string name;
        MSG_TYPES type;
        int position;
    };
    vector<MSG_Item> items;

    vector<std::string> messages;
    vector<std::string*> titles;
    vector<float *> vars;



    static void addMessage(string _message, string name, bool _newLine = true);
    static void addVar(float *var, string name, bool _newLine = true);
    static void addTitle(string *label, string name, bool _newLine = true);




//    std::string varsTitle;
//    string messageVars;


	void draw(ofEventArgs &e);
	void keyPressed(ofKeyEventArgs& key);

	// static function
	static void loadFont(string _path, float _size);


    static void clear();
	static void setPos(ofVec2f _pos);
	static void setPos(float _x, float _y);
	static ofVec2f getPos();
	static void setTextColor(ofColor _color);
	static ofColor getTextColor();
	static void setBackgroundColor(ofColor _color);
	static ofColor getBackgroundColor();
	static void setHelpKey(char _key);
	static char getHelpKey();
	static void setMomentary(bool _momentary);
	static bool getMomentary();
	static bool getSwhoing();

private:

	unordered_map<string, double> maptest;

	static ofxHelpMessage *singleton;
	static void singletonGenerate();

	bool initialized;
	bool showing, momentary;
	ofColor textColor, bgColor;
	ofVec2f pos;
	void updateDrawPos();
	ofVec2f drawPos;
	char helpKey;
	ofMutex mutex;

	string message;
    string message2;
	string messageBox;

    ofTrueTypeFont font;


    void updateVars();
};

