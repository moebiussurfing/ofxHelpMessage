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
        MSG_STRING,
        MSG_FLOAT,
        MSG_INT,
        MSG_BOOL
    };

    static void setTitle(string _title);

    static void addText(string name, string _message, bool _newLine = true);
    static void addString(string name, string *label, bool _newLine = true);
    static void addFloat(string name, float *var, bool _newLine = true);
    static void addInt(string name, int *var, bool _newLine = true);
    static void addBool(string name, bool *var, bool _newLine = true);

	//TODO:
	//add abstractParameter

    ///-

    void draw(ofEventArgs &e);
    void keyPressed(ofKeyEventArgs& key);

    // static function

    static void clear();
  
	static void setHelpKey(char _key);
    static char getHelpKey();
    static void setMomentary(bool _momentary);
    static bool getMomentary();
    static bool getSwhoing();
	static void setShowing(bool _showing);

    static void loadFont(string _path, float _size);
	static void setPos(ofVec2f _pos);
	static void setPos(float _x, float _y);
	static ofVec2f getPos();

	static void setTextColor(ofColor _color);
	static ofColor getTextColor();
	static void setBackgroundColor(ofColor _color);
	static ofColor getBackgroundColor();

    static void setTabbed(bool b, int num = 1);
    static void setFloatResolution(int res = 2);
    static void setMarginBorders(int _margin);
    static void setRounded(bool b, float size = 10.0f);

	static void setShowFPS(bool _showing);

private:

//    unordered_map<string, double> maptest;

    static ofxHelpMessage *singleton;
    static void singletonGenerate();
    ofMutex mutex;
	bool initialized;
	    
    char helpKey;
    bool showing, momentary;
	bool BBoxShowing;
    ofColor textColor, bgColor;
    ofVec2f pos;
    ofVec2f drawPos;

    ofTrueTypeFont font;

    void updateDrawPos();

    ///-

    string messageBox;

    struct MSG_Item {
        string name;
        MSG_TYPES type;
        int position;
    };
    vector<MSG_Item> items;

    std::string title;
    vector<std::string> messages;
    vector<std::string*> strings;
    vector<float *> floats;
    vector<int *> ints;
    vector<bool *> bools;

    void updateItems();

    ///-

    //layout
    bool bTabbed = false;
    int tabsNum = 1;
    int fRes = 2;
    int margin = 5;
    bool bRounded = false;
    float roundedSize = 10.0f;
	bool showFPS;

    ofRectangle rectBB;

};

