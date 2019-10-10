//
//  BoxDragger.cpp
//  remoteUI_Sketch
//
//  Created by Oriol Ferrer Mesià on 19/02/14.
//
//

#include "BoxDragger.h"
float w = 7. * 1632 / 4.;

//--------------------------------------------------------------
void BoxDragger::setup() {
	ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_NOTICE);

	box2d.init();
	box2d.setGravity(0, 00);
	//box2d.createBounds(ofGetWidth()-w, 0, w, ofGetHeight());
	box2d.createBounds();
	box2d.setFPS(60.0);
	box2d.registerGrabbing();
	//bgColor = ofColor(22);
	circleColor = ofColor::red;
}

//--------------------------------------------------------------
void BoxDragger::update() {
	if(gravity){
		box2d.setGravity(0, 10);
	}else{
		box2d.setGravity(0, 00);
	}
	box2d.update();
}

void BoxDragger::destroyAll(){

	for(int i=0; i<circles.size(); i++) {
		circles[i]->destroy();
	}
	colors.clear();
	circles.clear();
}

ofxBox2dCircle* BoxDragger::hit(ofPoint p){

	for(int i=0; i<circles.size(); i++) {
		ofVec2f pos = circles[i]->getPosition();
		float rad = circles[i]->getRadius();
		if (pos.distance(p) < rad){
			return circles[i];
		}
	}
	return NULL;
}

void BoxDragger::removeBody(ofxBox2dCircle* c){
	std::vector< ofxBox2dCircle* >::iterator it;
	it = find(circles.begin(), circles.end(), c);
	if (it != circles.end()){
		int index = it - circles.begin();
		circles[index]->destroy();
		circles.erase(circles.begin() + index);
		colors.erase(colors.begin() + index);
	}
}

//--------------------------------------------------------------
void BoxDragger::draw() {

	//ofClear(bgColor);

	//ofFill();


	for(int i=0; i<circles.size(); i++) {
		ofSetColor(colors[i]);
		circles[i]->draw();
	}

	// draw the ground
	//box2d.drawGround();
	//ofSetColor(0);
	//ofRect(0, 0, ofGetWidth() - w, ofGetHeight());

}


void BoxDragger::addBody(ofPoint p){

	float r = ofRandom(20, 30) * objectScale;
	circles.push_back(new ofxBox2dCircle());
	circles.back()->setPhysics(3.0, 0.53, 0.1);
	circles.back()->setup(box2d.getWorld(), p.x, p.y, r);
	colors.push_back(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));

}
