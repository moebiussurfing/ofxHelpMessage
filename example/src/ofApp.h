#pragma once

#include "ofMain.h"
#include "ofxHelpMessage.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

    float a, b, c, d;

    float *aPtr;
};
