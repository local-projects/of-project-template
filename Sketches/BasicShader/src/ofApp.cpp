#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(66);

	ofDisableArbTex(); //shader tex coords [0..1]
	ofLoadImage(mask, "mask.png");
	ofLoadImage(img, "img.png");

	shader.load("shader/mask");

	float w = img.getWidth();
	float h = img.getHeight();

	//triangle 1
	m.addVertex(ofVec3f(0,0));
	m.addVertex(ofVec3f(w,0));
	m.addVertex(ofVec3f(w,h));
	m.addTexCoord(ofVec2f(0,0));
	m.addTexCoord(ofVec2f(1,0));
	m.addTexCoord(ofVec2f(1,1));

	//triangle 1
	m.addVertex(ofVec3f(0,0));
	m.addVertex(ofVec3f(w,h));
	m.addVertex(ofVec3f(0,h));
	m.addTexCoord(ofVec2f(0,0));
	m.addTexCoord(ofVec2f(1,1));
	m.addTexCoord(ofVec2f(0,1));
}

//--------------------------------------------------------------
void ofApp::update(){

	//reload shader for live edits
	if(ofGetFrameNum()%60 == 0){
		shader.load("shader/mask");
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	int pad = 10;
	img.draw(0,0);
	mask.draw(pad + img.getWidth(),0);

	ofTranslate(0, img.getHeight() + pad);

	shader.begin();
		shader.setUniformTexture("img", img, 0);
		shader.setUniformTexture("mask", mask, 1);
		m.draw();
	shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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