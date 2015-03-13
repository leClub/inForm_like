#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //init Serial communication
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 9600;
    serial.setup("/dev/ttyACM0", baud);
    json = "";

    // ground
    ground.set( PADDING + NBX * (SIZE + PADDING ) , PADDING + NBY * (SIZE + PADDING ) );
    ground.setPosition( (PADDING + NBX * ( SIZE + PADDING ))/2, (PADDING + NBY * ( SIZE + PADDING ))/2, 0);

    //boxes
    choice = 0;
    changeHeightmap();

    for( int x = 0; x < NBX; ++x ){
        for( int y = 0; y < NBY; ++y ){
            box[x][y].set( SIZE, SIZE, SIZE );
            box[x][y].setPosition( ( PADDING + SIZE )*(x+1) - SIZE/2 , ( PADDING + SIZE )*(y+1) - SIZE/2, 0);
        }
    }

    //camera
    cam.setDistance(10);

    //lights & material
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

    pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));

    pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );

    // shininess is a value between 0 - 128, 128 being the most shiny //
	material.setShininess( 120 );
    // the light highlight of the material //
	material.setSpecularColor(ofColor(255, 255, 255, 255));
}

//--------------------------------------------------------------
void ofApp::update(){

    if( serial.available() ){
        //cout << "\tavailable: " << ofToString( serial.available() ) << endl;
        while( serial.available() ){
            lastChar = char( serial.readByte() );
            json += ofToString( lastChar );
        }

        if(lastChar == '\n'){
            bool parsingSuccessful = jsonEl.parse( json );
            std::cout << json << std::endl;
            std::cout << "parsingSuccessful: " << ofToString( parsingSuccessful ) << std::endl;

            if( parsingSuccessful ){
                ofLog() << "btnA: " + ofToString( jsonEl[ "btnA" ] );
                changeHeightmap();
            }
            json = "";
        }
    }

    for( int x = 0; x < NBX; ++x ){
        for( int y = 0; y < NBY; ++y ){
            ofColor c = heightmap.getColor(x, y);
            float zTar = c.getLightness();
            z[x][y] = ease(z[x][y], zTar, 0.1);
            box[x][y].setDepth(z[x][y]);
            box[x][y].setPosition( ( PADDING + SIZE )*(x+1) - SIZE/2 , ( PADDING + SIZE )*(y+1) - SIZE/2, -z[x][y]/2);
        }
    }

    pointLight.setPosition(
       (ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3),
       ofGetHeight()/2,
       500
    );
    pointLight2.setPosition(
        (ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
        ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()),
        -300
    );

    pointLight3.setPosition(
        cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
        sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
        cos(ofGetElapsedTimef()*.2) * ofGetWidth()
    );
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDisableDepthTest();
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    //heightmap.draw(0,0);
    ofEnableDepthTest();


    cam.begin();
    ofEnableLighting();
    pointLight.enable();
    pointLight2.enable();
    pointLight3.enable();

    ofPushMatrix();
    ofTranslate(-(PADDING + NBX * ( SIZE + PADDING ))/2, -(PADDING + NBY * ( SIZE + PADDING ))/2, -500);
    // ofRotateX( 90 );

	material.begin();

    ofFill();
    ofSetColor(255);
    ground.draw();
    for( int x = 0; x < NBX; ++x ){
        for( int y = 0; y < NBY; ++y ){
            box[x][y].draw();
        }
    }

    ofPopMatrix();

    material.end();
    ofDisableLighting();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::changeHeightmap(){
    //random texture
    choice = (choice + 1) % 2;
    //choice = int(ofRandom(31));
    string result;          // string which will contain the result
    ostringstream convert;   // stream used for the conversion
    convert << choice;      // insert the textual representation of 'Number' in the characters in the stream
    result = convert.str(); // set 'Result' to the contents of the stream
    heightmap.loadImage("maps/" + result + ".png");
}

//--------------------------------------------------------------
float ofApp::ease(float value, float target, float easingVal) {
    float d = target - value;
    if (abs(d)>1) value+= d*easingVal;
    else value = target;
    return value;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    changeHeightmap();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
