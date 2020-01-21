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
    static void addText(string _message, string name, bool _newLine = true);
    static void addString(string *label, string name, bool _newLine = true);
    static void addFloat(float *var, string name, bool _newLine = true);
    static void addInt(int *var, string name, bool _newLine = true);
    static void addBool(bool *var, string name, bool _newLine = true);

    ///-

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

//    unordered_map<string, double> maptest;

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

    ofTrueTypeFont font;

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
    int margin = 5;
    bool bTabbed = false;
    int tabsNum = 1;
    bool bRounded = false;
    float roundedSize = 10.0f;

    static void setMarginBorders(int _margin);
    static void setTabbed(bool b, int num = 1);
    static void setRounded(bool b, int size = 10.0f);

};

