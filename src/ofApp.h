#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "pin.h"

#define NBX 100
#define NBY 60
#define SIZE 2
#define PADDING 1

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofSerial serial;
		char lastChar;
		ofxJSONElement jsonEl;
        std::string json;

        ofEasyCam cam;
        ofLight pointLight;
        ofLight pointLight2;
        ofLight pointLight3;
        ofMaterial material;

        int choice;
        void changeHeightmap();
        float ease(float value, float target, float easingVal);
        ofPlanePrimitive ground;
        ofImage heightmap;
        float z[NBX][NBY];
        ofBoxPrimitive box[NBX][NBY];

        bool isFullScreen;
};
