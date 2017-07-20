#pragma once

#include "ofMain.h"
#include "CustomApp.h"


#define 	USE_OF_THREAD	 false

//////////////////////////////////////////////////////////////////////////////////////

#if USE_OF_THREAD

class ThreadTest : public ofThread{
	public:
		void threadedFunction(){
			//ofSleepMillis(1);
		}
};

#else

class ThreadTest{
public:

	std::thread thread;
	std::atomic<bool> done;

	ThreadTest() : done(false) {
		thread = std::thread(&ThreadTest::threadedFunction, this);
	}

	void threadedFunction(){
		//ofSleepMillis(1);
		done = true;
	}
};

#endif


//////////////////////////////////////////////////////////////////////////////////////

class ofApp : public CustomApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void setupChanged(ofxScreenSetup::ScreenSetupArg &arg);
	void remoteUIClientDidSomething(RemoteUIServerCallBackArg & arg);


	vector<ThreadTest*> threads;
	vector<ThreadTest*> leakedThreads;

	int numThreadsCreated = 0;

	void createThread(int n);
};


//////////////////////////////////////////////////////////////////////////////////////
