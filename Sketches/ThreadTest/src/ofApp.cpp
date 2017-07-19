#include "ofApp.h"


void ofApp::setup(){

	CustomApp::setup();

	// LISTENERS
	ofAddListener(screenSetup.setupChanged, this, &ofApp::setupChanged);
	ofAddListener(RUI_GET_OF_EVENT(), this, &ofApp::remoteUIClientDidSomething);
}


void ofApp::createThread(int n){

	for(int i = 0; i < n; i++){
	#if USE_OF_THREAD
		ThreadTest * t = new ThreadTest();
		threads.push_back(t);
		t->startThread();
	#else
		ThreadTest * t = new ThreadTest();
		if(t){
			t->thread.detach();
		}else{
		}
		threads.push_back(t);
	#endif
		numThreadsCreated++;
	}
}


void ofApp::update(){

	float dt = 1./60.;

	createThread(3); //spawn N threads per frame


	int index = threads.size() -1;
	for(int i = index; i >= 0; i--){

		#if USE_OF_THREAD
		ThreadTest * t = threads[i];
		if(!t->isThreadRunning()){
			if(t->getNativeThread().get_id() == std::thread::id()){
				delete t; //OK!
			}else{
				ofLogError("ofApp") << "ofThread is done but we will crash if we try to delete - LEAKING";
				leakedThreads.push_back(t);
			}
			threads.erase(threads.begin() + i);
		}

		#else

		ThreadTest * t = threads[i];
		if(t->done == true){
			if(t->thread.get_id() == std::thread::id()){
				delete t; //OK!
			}else{
				ofLogError("ofApp") << "std::thread is done but we will crash if we try to delete - LEAKING";
				leakedThreads.push_back(t);
			}
			threads.erase(threads.begin() + i);
		}

		#endif
	}
}


void ofApp::draw(){

	string msg =
	"Using " + string(USE_OF_THREAD ? "ofThread" : "std::thread") +
	"\nnumThreadsCreated=" + ofToString(numThreadsCreated) +
	"\nNumThreadsAlive=" + ofToString(threads.size()) +
	"\nNumLeakedThreads=" + ofToString(leakedThreads.size());
	ofDrawBitmapStringHighlight(msg, 30, 30);
}


void ofApp::keyPressed(int key){

	if(key == 'w'){
		screenSetup.cycleToNextScreenMode();
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


//////// CALLBACKS //////////////////////////////////////

void ofApp::setupChanged(ofxScreenSetup::ScreenSetupArg &arg){
	ofLogNotice()	<< "ofxScreenSetup setup changed from " << screenSetup.stringForMode(arg.oldMode)
	<< " (" << arg.oldWidth << "x" << arg.oldHeight << ") "
	<< " to " << screenSetup.stringForMode(arg.newMode)
	<< " (" << arg.newWidth << "x" << arg.newHeight << ")";
}


//define a callback method to get notifications of client actions
void ofApp::remoteUIClientDidSomething(RemoteUIServerCallBackArg &arg){
	switch (arg.action) {
		case CLIENT_CONNECTED: cout << "CLIENT_CONNECTED" << endl; break;
		case CLIENT_DISCONNECTED: cout << "CLIENT_DISCONNECTED" << endl; break;
		case CLIENT_UPDATED_PARAM: cout << "CLIENT_UPDATED_PARAM: "<< arg.paramName << " - ";
			arg.param.print();
			break;
		case CLIENT_DID_SET_PRESET: cout << "CLIENT_DID_SET_PRESET" << endl; break;
		case CLIENT_SAVED_PRESET: cout << "CLIENT_SAVED_PRESET" << endl; break;
		case CLIENT_DELETED_PRESET: cout << "CLIENT_DELETED_PRESET" << endl; break;
		case CLIENT_SAVED_STATE: cout << "CLIENT_SAVED_STATE" << endl; break;
		case CLIENT_DID_RESET_TO_XML: cout << "CLIENT_DID_RESET_TO_XML" << endl; break;
		case CLIENT_DID_RESET_TO_DEFAULTS: cout << "CLIENT_DID_RESET_TO_DEFAULTS" << endl; break;
		default:
			break;
	}
}
