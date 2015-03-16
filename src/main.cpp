#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    // raspebrry pi : 1366x768
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1366,768,OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
