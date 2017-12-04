#include "testApp.h"

bool recalcNow;
string PORT;
string host;
string from;
ofxOscReceiver receiver;
ofxOscSender sender;

int num = 0;
//define a callback method to get notifications of client actions
void serverCallback(RemoteUIServerCallBackArg arg){
	switch (arg.action) {
		case CLIENT_DID_SET_PRESET:
		case CLIENT_UPDATED_PARAM:
			receiver.setup(ofToInt(PORT));
			sender.setup(host, ofToInt(PORT));
			recalcNow = true;
			break;
	}
}


void testApp::setup(){

	host = "127.0.0.1";
	PORT = "3333";
	ofSetFrameRate(120);

	ofSetVerticalSync(false);
	ofBackground(22);

	OFX_REMOTEUI_SERVER_SET_CALLBACK(serverCallback);
	OFX_REMOTEUI_SERVER_SETUP(); 	//start server

	OFX_REMOTEUI_SERVER_SET_UPCOMING_PARAM_GROUP("DEBUG");

	OFX_REMOTEUI_SERVER_SET_UPCOMING_PARAM_GROUP("PARAMS");
	OFX_REMOTEUI_SERVER_SET_NEW_COLOR();
	OFX_REMOTEUI_SERVER_SHARE_PARAM(host);
	OFX_REMOTEUI_SERVER_SHARE_PARAM(PORT);

	OFX_REMOTEUI_SERVER_LOAD_FROM_XML();

	TIME_SAMPLE_SET_FRAMERATE(60);
	TIME_SAMPLE_DISABLE();

	receiver.setup(ofToInt(PORT));
	sender.setup(host, ofToInt(PORT));
	ofSetWindowTitle("OSC / TUIO Forwarder");

}


void testApp::update(){

	float dt = 1./60.;

	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);

		from = m.getRemoteIp();

		sender.sendMessage(m);
		num++;
	}
}


void testApp::draw(){

	ofDrawBitmapString("num packets: " + ofToString(num) + "\n"
				   "From Host:" + from + "\n"+
				   "to Host: " + host + ":" + PORT
				   , 20,20);
}



void testApp::keyPressed(int key){

}


void testApp::keyReleased(int key){

}


void testApp::mouseMoved(int x, int y ){

}


void testApp::mouseDragged(int x, int y, int button){

}


void testApp::mousePressed(int x, int y, int button){

}


void testApp::mouseReleased(int x, int y, int button){

}


void testApp::windowResized(int w, int h){

}


void testApp::gotMessage(ofMessage msg){

}


void testApp::dragEvent(ofDragInfo dragInfo){
	
}
