#pragma once

#define MULTITOUCH_HACK /*to get box2d to use multitouch on non-ios*/

#include "ofMain.h"
#include "ofxTimeMeasurements.h"
#include "ofxRemoteUIServer.h"
#include "ofxTuio.h"
#include "BoxDragger.h"
#include "ofxTouchHelper.h"
#include "ofxFontStash.h"
#include "ofxScreenSetup.h"
#include "ofxSuperLog.h"
#include "ofxTuio.h"

#define MAX_FINGERS 100

class testApp : public ofBaseApp{

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

	int frameRate = 60;
	bool enableVsync = true;
	bool drawTouches;

	//tuio
	void	tuioAdded(ofxTuioCursor & tuioCursor);
	void	tuioRemoved(ofxTuioCursor & tuioCursor);
	void	tuioUpdated(ofxTuioCursor & tuioCursor);

	ofxTuioClient   tuioClient;
	BoxDragger	*	dragger;

	ofxTouchHelper touch;

	bool deleteAll;
	bool touchCreatesBodies;
	bool touchDeletesBodies;
	bool drawTouchPaths;
	bool clearTouchPaths;

	struct FingerLines{
		ofVboMesh points;
		vector<ofVboMesh> oldPoints;
	};

	enum FingerState{
		FINGER_UP = 0,
		FINGER_DOWN,
	};

	map<int, FingerState> fingerState;
	map<int, FingerLines> fingerLines;
	
	struct ScreenMessage{
		string msg;
		ofColor color;
		float timeLeft;
	};
	
	int highestFingerID = 10;
	
	void clearFingerLines();
	void drawFingerLines();
	
	vector<ScreenMessage> screenMsgs;
	
	void addMessage(string msg, ofColor color = ofColor(255));

	float speed;
	bool vSyncTestHorizontal;
	bool vSyncTestVertical;

	bool logTouches = false;

	ofxFontStash font;
	vector<ofColor> colors;

	ofPtr<ofxSuperLog> *	loggerStorage; //note its a * to an ofPtr - TODO!

	ofxScreenSetup ss;
};
