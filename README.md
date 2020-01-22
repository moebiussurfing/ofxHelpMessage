# ofxHelpMessage

## CHANGES IN THIS FORK:

You can add text messages like the original addon, but you can add/show variables too.

Added variables (string, float, int, bool) are referenced, and can be showed in realtime in the same text box.
You dont need to update nothing.

The class uses a singleton, so you can add referenced variables (or text) from any of your included classes. You just need to add this header to your classes. All classes will "share" the same text box.

Changes by MoebiusSurfing. Original author: Toru Takata, Thanks!

![Alt text](/screenshot.jpg?raw=true "MoebiusSurfing")

## Usage

### ofApp.h
```cpp
    #include "ofxHelpMessage.h"

    string st1;
    float f1;
    int i1;
    bool b1;
```

### ofApp.cpp
```cpp 

setup()

    // set first line tittle
    ofxHelpMessage::setTitle("APP INFO                \n");
    
    // name is not used in this type. no variable, just the string text
    ofxHelpMessage::addText("noName", "KEY [SPACE]: HIDE/SHOW");
    
    // add the referenced variables that you what to show printed in the screen box
    // pass all variables as reference
    ofxHelpMessage::addString("myString1", &str1);ofxHelpMessage::addFloat("myFloat1 ", &f1);
    ofxHelpMessage::addInt("myInt1", &i1);
    ofxHelpMessage::addBool("myBool1", &b1);
    
    // customize style
    // set margin borders
    ofxHelpMessage::setMarginBorders(20);
    // tab labels and values
    ofxHelpMessage::setTabbed(true, 1);
    // round bbox
    ofxHelpMessage::setRounded(true, 5.0f);
    // show
    ofxHelpMessage::setVisible(true);

update()

    //your variables will change...
    //but nothing more to do.
```

You can use this workaround to add ofParameters too:
```cpp 
ofParameter<float> floatParam;
ofxHelpMessage::addFloat(floatParam.getName(), (float*)&floatParam.get());//get name from parameter

ofParameter<string> stringParam;
ofxHelpMessage::addString("myString", (string*)&stringParam.get());//put your custom name
```

### TODO:

+ improve string columns align by tabs '\t'.
+ enable drag box position by mouse.
+ store/recall position and settings to xml.
+ enable multiple boxes or just split to another addon without singleton.

-------------------------------------------------------------------------------------------------------

## Overview

This is an addon for openFrameworks.
I made it to show help message on window easily.

## Requirement

ofxHelpMessage doesn't depend other addons.

## Tested system

- Windows 10 + VS2017 +  of0.10.1 .

I think compatible almost all versions, because it's simple addon.

## Usage

1. Add this addon.
1. Include `ofxHelpMessage.h`.
1. Put the static method `ofxHelpMessage::addMessage("Key S: save")`  in setup().
1. When program running, press '?' key to show help message.



You can use some method to change appearance and behaviour.
For example.

```cpp
// add message
ofxHelpMessage::addMessage("HELP (dummy message)");
ofxHelpMessage::addMessage("Key S: Save");
ofxHelpMessage::addMessage("Key L: Load");

// clear message
//ofxHelpMessage::clear();

// set text color
// default: ofColor::white
ofxHelpMessage::setTextColor(ofColor(255, 255, 0));

// set background color
// default: ofColor(0, 0, 0, 150) this is black transparently
ofxHelpMessage::setBackgroundColor(ofColor(0));

// set font
// draw with ofTrueTypeFont if loaded
ofxHelpMessage::loadFont("arial.ttf", 30);

// set position
// default: (10, 10)
ofxHelpMessage::setPos(500, 500);

// change show message key
// default: '?'
ofxHelpMessage::setHelpKey(' ');

// set show mode to momentary/toggle
// default: true (momentary)
ofxHelpMessage::setMomentary(false); // toggle mode

```

## Author

Toru Takata in Japan.

github: https://github.com/tettou771

link: http://tettou771.com
