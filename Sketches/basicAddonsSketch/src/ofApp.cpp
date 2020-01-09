#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // Set the directory where config files are saved
    RUI_SET_CONFIGS_DIR("configs");
    
    // Setup remote UI parameters
    RUI_SETUP();
    RUI_NEW_GROUP("General Params");
    RUI_SHARE_PARAM_WCN("Speed", speed, 0, 100);
    RUI_SHARE_PARAM_WCN("Radius", radius, 0, 1000);
    
    // Load configs from file
    RUI_LOAD_FROM_XML();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Update the position of the ball
    position += direction;
    
    // Update the direction based on the position and canvas bounds
    if (abs(position.x - (ofGetWidth()/2.0)) > ofGetWidth()/2.0-radius) direction.x *= -1.0;
    if (abs(position.y - (ofGetHeight()/2.0)) > ofGetHeight()/2.0-radius) direction.y *= -1.0;

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 200, 200);
    
    // Set the color of the ball and draw it
    ofSetColor(255, 0, 0);
    ofDrawCircle(position, radius);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
