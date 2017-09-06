#pragma once

#include "ofMain.h"

#define USE_OF_THREAD	 false

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
		//thread = std::thread(std::bind(&ThreadTest::threadedFunction,this));
	}

	void threadedFunction(){
		//ofSleepMillis(1);
		done = true;
		thread.detach();
	}
};

#endif


//////////////////////////////////////////////////////////////////////////////////////

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	vector<ThreadTest*> threads;
	vector<ThreadTest*> leakedThreads;

	int numThreadsCreated = 0;

	void createThread(int n);
};

