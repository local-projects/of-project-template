#include "ofApp.h"


void ofApp::setup(){
	ofxApp::get().setup(this); //start the ofxApp setup process
}

void ofApp::ofxAppPhaseWillBegin(ofxApp::Phase p){

	if(p == ofxApp::Phase::WILL_BEGIN_RUNNING){ //app starts here!

		slideshow = ofxApp::get().textures().getTextureNames();
		if(slideshow.size() > 0){
			index = 0;
		}

		RUI_SHARE_ENUM_PARAM(scaleMode, OF_SCALEMODE_FIT, OF_SCALEMODE_STRETCH_TO_FILL, {"OF_SCALEMODE_FIT", "OF_SCALEMODE_FILL", "OF_SCALEMODE_CENTER", "OF_SCALEMODE_STRETCH_TO_FILL"} );
	}
};


void ofApp::update(){
	float dt = 1./60.;
}


void ofApp::draw(){

	if(ofxApp::get().getState() == ofxApp::State::RUNNING){

		//draw all textures
		//ofxApp::get().textures().drawAll(ofRectangle(100, 100, ofGetMouseX() - 100, ofGetMouseY() - 100));

		if(index >= 0){
			string texName = slideshow[index];
			ofTexture * tex = G_TEX(texName);
			if(tex){
				ofRectangle texRect = ofRectangle(0,0, tex->getWidth(), tex->getHeight());
				ofRectangle vp = ofGetCurrentViewport();
				texRect.scaleTo(vp, scaleMode);
				tex->draw(texRect);
			}
		}
	}
}


void ofApp::keyPressed(int key){

	if(key == OF_KEY_RIGHT){
		if(index >= 0){
			index++;
			if(index >= slideshow.size()) index = 0;
			RUI_LOG("Showing %s [%d/%d]", slideshow[index].c_str(), index + 1, slideshow.size());
		}

	}

	if(key == OF_KEY_LEFT){
		if(index >= 0){
			index--;
			if(index < 0) index = slideshow.size() - 1;
			RUI_LOG("Showing %s [%d/%d]", slideshow[index].c_str(), index + 1, slideshow.size());
		}
	}

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
