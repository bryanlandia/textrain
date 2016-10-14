#include "ofApp.h"
#include "ofxGui.h"

#define RAIN_COUNT 50


//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(640, 480);
    image.allocate(640, 480, OF_IMAGE_COLOR);
    gui.setup();
    gui.add(thresh.setup("Threshold", 127, 0, 255));
    gui.add(showVideo.setup("Show Video"));
    
    ofSetFullscreen(true);
    
    for (int i = 0; i < RAIN_COUNT; i++) {
        // ofPoint is a x,y
        ofPoint point = ofPoint(ofRandom(ofGetWidth()),
                                ofRandom(ofGetHeight())
                               );
        rain.push_back(point);
        //text.push_back(ofRandom('A', 'Z'));
        text.push_back(ofRandom(0, 256));
        velocities.push_back(ofRandom(1.0,10.0));
        //velocities.push_back(0);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update(); // get a new frame from video feed
    
    unsigned char *imgPixels = image.getPixels().getData();
    unsigned char *vidPixels = grabber.getPixels().getData();
    // unsigned int thresh = ofMap(ofGetMouseX(), 0, 800, 0, 255);
    
    
    for (int i=0; i< 640*480; i++) {
        unsigned char gray = (vidPixels[i*3+0] + vidPixels[i*3+1] + vidPixels[i*3+2])/3.0;
        if (gray < thresh) {
            imgPixels[i*3+0] = imgPixels[i*3+1] = imgPixels[i*3+2] = 0;
        }
        else {
            imgPixels[i*3+0] = imgPixels[i*3+1] = imgPixels[i*3+2] = 255;
        }
    }
    image.update();
    
    for (int i = 0; i< RAIN_COUNT; i++) {
        
        // rain should stop when it hits a white pixel
        // find pixel color where our rain is
        int smW = rain[i].x / ofGetWidth() * 640; // translate from full-screen to original coordinate system
        int smH = rain[i].y / ofGetHeight() * 480;
        int p = (smW + smH*640)*3;
        velocities[i] += 0.3;
        rain[i].y += velocities[i];

        if (imgPixels[p] < thresh) {
            
            
            if (rain[i].y > ofGetHeight()) {
                rain[i].y = 0;
                rain[i].x = ofRandom(ofGetWidth());
                text[i] = ofRandom(0, 256);
                velocities[i] = ofRandom(1, 10);
            }
        }
    }
        
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255,255);
    if (showVideo){
        grabber.draw(0,0, ofGetWidth(), ofGetHeight());
    }
    else {
        image.draw(0,0, ofGetWidth(), ofGetHeight());
    }
    
    for (int i = 0; i< RAIN_COUNT; i++) {
        ofDrawBitmapString(text[i], rain[i]);
        //ofDrawCircle(rain[i], 5);

    }
    
    if (showGui) {
     gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        showGui = !showGui;
    }
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
