#include "ofApp.h"
#include "ofxRemoteUIServer.h"

void ofApp::setup(){

	RUI_SETUP();

	// PARAMS
	RUI_NEW_GROUP("PARAMS");
	RUI_SHARE_PARAM(myFloat, 0, 1);
	RUI_SHARE_COLOR_PARAM(myColor);
	RUI_SHARE_PARAM(myBool);
	RUI_SHARE_PARAM(myInt, 0, 100);
	RUI_SHARE_PARAM(myString);
	RUI_SHARE_ENUM_PARAM(myEnum, 0, NUM_ENUMS - 1, {"ENUM_1", "ENUM_2", "ENUM_3"});

	ofBackground(22);

}


void ofApp::update(){

}


void ofApp::draw(){

	string msg = "myFloat: " + ofToString(myFloat) +
	"\nmyColor: " + ofToString(myColor) +
	"\nmyBool: " + ofToString(myBool) +
	"\nmyInt: " + ofToString(myInt) +
	"\nmyString: " + ofToString(myString) +
	"\nmyEnum: " + ofToString(myEnum);

	ofSetColor(myColor);
	ofDrawBitmapString(msg, 20, 20);
	ofSetColor(255);
}


void ofApp::keyPressed(int key){

}


void ofApp::keyReleased(int key){

}


void ofApp::mouseMoved(int x, int y ){

}


void ofApp::mouseDragged(int x, int y, int button){

}


void ofApp::mousePressed(int x, int y, int button){

}


void ofApp::mouseReleased(int x, int y, int button){

}


void ofApp::windowResized(int w, int h){

}


void ofApp::gotMessage(ofMessage msg){

}


void ofApp::dragEvent(ofDragInfo dragInfo){
	
}


