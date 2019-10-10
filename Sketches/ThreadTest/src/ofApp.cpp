#include "ofApp.h"

void ofApp::setup(){
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
			//t->thread.detach();
		}else{
			ofLogError("ofApp") << "cant detach this std::thread!";
		}
		threads.push_back(t);
	#endif
		numThreadsCreated++;
	}
}


void ofApp::update(){

	float dt = 1./60.;

	createThread(4); //spawn N threads per frame


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

