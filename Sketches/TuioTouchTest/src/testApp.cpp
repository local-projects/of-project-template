#include "testApp.h"

bool recalcNow;
//define a callback method to get notifications of client actions
void serverCallback(RemoteUIServerCallBackArg arg){
	switch (arg.action) {
		case CLIENT_DID_SET_PRESET:
		case CLIENT_UPDATED_PARAM:
			recalcNow = true;
			break;
	}
}

void testApp::setup(){

	ofSetVerticalSync(false);
	ofEnableAlphaBlending();
	ofBackground(0);

	tuioClient.start(3333);
    ofAddListener(tuioClient.cursorAdded,this,&testApp::tuioAdded);
	ofAddListener(tuioClient.cursorRemoved,this,&testApp::tuioRemoved);
	ofAddListener(tuioClient.cursorUpdated,this,&testApp::tuioUpdated);
	
	dragger = new BoxDragger();


	OFX_REMOTEUI_SERVER_GET_INSTANCE()->setCallback(serverCallback);
	OFX_REMOTEUI_SERVER_GET_INSTANCE()->setBuiltInUiScale(2.0);
	OFX_REMOTEUI_SERVER_GET_INSTANCE()->drawUiWithFontStash("fonts/VeraMono.ttf");
	OFX_REMOTEUI_SERVER_GET_INSTANCE()->setSaveToXMLOnExit(false);
	OFX_REMOTEUI_SERVER_SETUP(); 	//start server


	OFX_REMOTEUI_SERVER_SET_UPCOMING_PARAM_GROUP("APP");
	OFX_REMOTEUI_SERVER_SHARE_PARAM(frameRate, 30, 120);
	OFX_REMOTEUI_SERVER_SHARE_PARAM(logTouches);

	OFX_REMOTEUI_SERVER_SET_UPCOMING_PARAM_GROUP("TOUCH");
	OFX_REMOTEUI_SERVER_SHARE_PARAM(drawTouches);
	
	OFX_REMOTEUI_SERVER_SET_UPCOMING_PARAM_GROUP("VSYNC");
	OFX_REMOTEUI_SERVER_SHARE_PARAM(enableVsync);
	OFX_REMOTEUI_SERVER_SHARE_PARAM(vSyncTestHorizontal);
	OFX_REMOTEUI_SERVER_SHARE_PARAM(vSyncTestVertical);
	OFX_REMOTEUI_SERVER_SHARE_PARAM(speed, 10,500);
	OFX_REMOTEUI_SERVER_SET_UPCOMING_PARAM_GROUP("FLASH TEST");
	OFX_REMOTEUI_SERVER_SHARE_PARAM(flashTest);


	OFX_REMOTEUI_SERVER_SET_UPCOMING_PARAM_GROUP("BEHAVIORS");
	OFX_REMOTEUI_SERVER_SET_NEW_COLOR();
	OFX_REMOTEUI_SERVER_SHARE_PARAM(dragger->gravity);
	OFX_REMOTEUI_SERVER_SHARE_COLOR_PARAM(dragger->bgColor);
	OFX_REMOTEUI_SERVER_SHARE_PARAM(dragger->objectScale, 0.2, 5);
	OFX_REMOTEUI_SERVER_SHARE_PARAM(touchCreatesBodies);
	OFX_REMOTEUI_SERVER_SHARE_PARAM(touchDeletesBodies);
	OFX_REMOTEUI_SERVER_SHARE_PARAM(drawTouchPaths);
	OFX_REMOTEUI_SERVER_SHARE_PARAM(clearTouchPaths);

	OFX_REMOTEUI_SERVER_SET_UPCOMING_PARAM_GROUP("RESET");
	OFX_REMOTEUI_SERVER_SHARE_PARAM(deleteAll);

	ofSetFrameRate(frameRate);
	TIME_SAMPLE_SET_FRAMERATE(frameRate);

	TIME_SAMPLE_DISABLE();
	TIME_SAMPLE_SET_DRAW_LOCATION(TIME_MEASUREMENTS_TOP_RIGHT);
	TIME_SAMPLE_GET_INSTANCE()->drawUiWithFontStash("fonts/VeraMono.ttf");
	TIME_SAMPLE_GET_INSTANCE()->setUiScale(2);


	ofxSuperLog::getLogger()->setFont(&(TIME_SAMPLE_GET_INSTANCE()->getFont()), 20);
	loggerStorage = new ofPtr<ofxSuperLog>(); //note this 2* madness is to avoid the logger being delete b4 the app is finished logging
	*loggerStorage = ofxSuperLog::getLogger(true, true, "");
	ofSetLoggerChannel(*loggerStorage);
	(*loggerStorage)->setScreenLoggingEnabled(false);
	(*loggerStorage)->setMaximized(true);
	(*loggerStorage)->setMaxNumLogLines(2000);
	(*loggerStorage)->setUseScreenColors(true);
	(*loggerStorage)->setSyncronizedLogging(false);
	(*loggerStorage)->getDisplayLogger().setDisplayLogTimes(true);


	dragger->setup();
	touch.setup();
	
	font.setup("fonts/VeraMono-Bold.ttf");

	for(int i = 0; i < MAX_FINGERS; i++){
		fingerState[i] = FINGER_UP;
		colors.push_back(ofColor::fromHsb((i * 45)% 255, 255, 255));
		fingerLines[i].points.setMode(OF_PRIMITIVE_LINE_STRIP);
	}

	ss.setup(ofGetWidth(), ofGetHeight(), ofxScreenSetup::WINDOWED);
}


void testApp::update(){

	float dt = 1./60.;
	tuioClient.getMessage();

	if(ofGetFrameNum()%60 == 1){
		ofSetVerticalSync(enableVsync);
	}

	dragger->update();
	touch.update(dt);

	if(deleteAll){
		dragger->destroyAll();
		deleteAll = false;
		OFX_REMOTEUI_SERVER_PUSH_TO_CLIENT();
	}

	if(clearTouchPaths){
		clearFingerLines();
		clearTouchPaths = false;
		OFX_REMOTEUI_SERVER_PUSH_TO_CLIENT();
	}
}


void testApp::clearFingerLines(){
	map<int, FingerLines>::iterator it = fingerLines.begin();
	while(it != fingerLines.end()){
		it->second.points.clear();
		it->second.oldPoints.clear();
		++it;
	}
}


void testApp::drawFingerLines(){
	
	map<int, FingerLines>::iterator it = fingerLines.begin();
	int c = 0;
	while(it != fingerLines.end()){
		ofSetLineWidth(10);
		ofSetColor(colors[c%colors.size()]);
		it->second.points.draw();
		it->second.points.setMode(OF_PRIMITIVE_POINTS);
		glPointSize(8);
		it->second.points.draw();
		it->second.points.setMode(OF_PRIMITIVE_LINE_STRIP);
		glPointSize(1);
		
//		ofSetColor(colors[c%colors.size()], 128);
		ofSetLineWidth(1);

		for(int i = 0; i < it->second.oldPoints.size(); i++){
			it->second.oldPoints[i].draw();
		}
		++it;
		c++;
	}
	ofSetLineWidth(1);
}


void testApp::addMessage(string msg, ofColor color){

	ScreenMessage m;
	m.msg = msg;
	m.color = color;
	m.timeLeft = 5;
	
	screenMsgs.push_back(m);
}

void testApp::draw(){

	dragger->draw();

	if(drawTouches){
		touch.drawDebug();
	}
	
	tuioClient.drawCursors();

	if(drawTouchPaths){
		drawFingerLines();
	}

	if (flashTest) {
		if (ofGetFrameNum() % 30 == 1) {
			ofClear(255);
		}
	}
	ofSetColor(255);
	font.drawMultiLine("PRESS 'd' to delete all\nPRESS 'v' to toggle Vertical Sync Tests\nPRESS 'TAB' for Settings\nPRESS 'PgDwn' for Timings\nPRESS 'w' to cycle window modes\n", 30, 40, ofGetHeight() - 140);

	int skip = 400;
	float offset = (int)( speed  * ofGetElapsedTimef())%skip;
	ofSetColor(255,128);
	int lineW = 2;
	if(vSyncTestVertical){
		for(int i = 0; i < ofGetHeight(); i+=skip){
			ofRect(0, i + offset, ofGetWidth(), lineW);
		}
	}
	
	if(vSyncTestHorizontal){
		for(int i = 0; i < ofGetWidth(); i+=skip){
			ofRect(i + offset, 0, lineW, ofGetHeight());
		}
	}
	
	// SCREEN MESSAGES
	
	ofVec2f msgPos = ofVec2f(20,100);
	vector<int> toDelete;
	for(int i = 0; i < screenMsgs.size(); i++){
		screenMsgs[i].timeLeft -= ofGetLastFrameTime();
		if(screenMsgs[i].timeLeft > 0.0){
			int a = 255 * ofMap(screenMsgs[i].timeLeft, 0, 3, 0, 1, true);
			ofSetColor(screenMsgs[i].color, a);
			font.draw(screenMsgs[i].msg, 20, msgPos.x, msgPos.y + i * 20);
		}else{
			toDelete.push_back(i);
		}
	}
	
	for(int i = toDelete.size() -1; i >= 0; i--){
		screenMsgs.erase(screenMsgs.begin() + toDelete[i]);
	}
	
	// FINGER ID BOXES
	
	for(int i = 0; i < highestFingerID; i++){
		if(fingerState[i] == FINGER_UP) ofSetColor(66);
		else ofSetColor(colors[i%colors.size()]);

		float x = 20 + i * 50;
		float y = 20;
		ofDrawRectangle(x, y , 45, 45);
		ofSetColor(255);
		font.draw(ofToString(i), 22, x + 19, y + 70);
	}
}


void testApp::tuioAdded(ofxTuioCursor &tuioCursor){
	ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	if(logTouches) ofLogNotice("TUIO") << "Point n " << tuioCursor.getFingerId() << " ADD at " << loc;

	if(fingerState[tuioCursor.getFingerId()] == FINGER_UP){
		//addMessage("TouchDown " + ofToString(tuioCursor.getFingerId()), colors[tuioCursor.getFingerId()%colors.size()]);
		fingerState[tuioCursor.getFingerId()] = FINGER_DOWN;
		if(drawTouchPaths ){
			fingerLines[tuioCursor.getFingerId()].points.addVertex(loc);
		}
	}else{
		addMessage(">> TouchDown " + ofToString(tuioCursor.getFingerId()) + " FINGER ALREADY DOWN!",
				   colors[tuioCursor.getFingerId()%colors.size()]);
	}
	
	ofxBox2dCircle* touched = dragger->hit(loc);
	if(touched == NULL && touchCreatesBodies){
		dragger->addBody(loc);
	}
	if(touched != NULL && touchDeletesBodies){
		dragger->removeBody(touched);
	}
	dragger->box2d.grabShapeDown(loc.x, loc.y, tuioCursor.getFingerId());

	ofTouchEventArgs a;
	a.x = loc.x;
	a.y = loc.y;
	a.id = tuioCursor.getFingerId();
	touch.touchDown(a);
	
	if(tuioCursor.getFingerId() > highestFingerID){
		highestFingerID = tuioCursor.getFingerId();
	}
}


void testApp::tuioUpdated(ofxTuioCursor &tuioCursor){
	ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());

	if(logTouches) ofLogNotice("TUIO") << "Point n " << tuioCursor.getFingerId() << " UPDATED at " << loc ;
	dragger->box2d.grabShapeDragged(loc.x, loc.y, tuioCursor.getFingerId());

	if(fingerState[tuioCursor.getFingerId()] == FINGER_DOWN){
		//addMessage("TouchUp " + ofToString(tuioCursor.getFingerId()), colors[tuioCursor.getFingerId()]);
		if(drawTouchPaths){
			fingerLines[tuioCursor.getFingerId()].points.addVertex(loc);
		}
	}else{
		addMessage(">> TouchMove " + ofToString(tuioCursor.getFingerId()) + " UP BUT WASN'T DOWN!?",
				   colors[tuioCursor.getFingerId()%colors.size()]);
	}

	ofTouchEventArgs a;
	a.x = loc.x;
	a.y = loc.y;
	a.id = tuioCursor.getFingerId();
	touch.touchMoved(a);
}


void testApp::tuioRemoved(ofxTuioCursor &tuioCursor){
	ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	if(logTouches) ofLogNotice("TUIO") << "Point n " << tuioCursor.getFingerId() << " REMOVED at " << loc;
	dragger->box2d.grabShapeUp(loc.x, loc.y, tuioCursor.getFingerId());

	if(fingerState[tuioCursor.getFingerId()] == FINGER_DOWN){
		//addMessage("TouchUp " + ofToString(tuioCursor.getFingerId()), colors[tuioCursor.getFingerId()%colors.size()]);
		fingerState[tuioCursor.getFingerId()] = FINGER_UP;
		if(drawTouchPaths ){
			fingerLines[tuioCursor.getFingerId()].points.addVertex(loc);
			ofMesh m = fingerLines[tuioCursor.getFingerId()].points;
			fingerLines[tuioCursor.getFingerId()].points.clear();

			ofVboMesh vbo = m;
			vbo.setMode(OF_PRIMITIVE_LINE_STRIP);
			fingerLines[tuioCursor.getFingerId()].oldPoints.push_back(vbo);
		}
	}else{
		addMessage(">> TouchUp " + ofToString(tuioCursor.getFingerId()) + " UP BUT WASN'T DOWN!?",
				   colors[tuioCursor.getFingerId()%colors.size()]);
	}

	ofTouchEventArgs a;
	a.x = loc.x;
	a.y = loc.y;
	a.id = tuioCursor.getFingerId();
	touch.touchUp(a);
}


void testApp::keyPressed(int key){

	if(key=='d'){
		dragger->destroyAll();
		clearFingerLines();
	}

	if(key=='f'){
		ofToggleFullscreen();
	}
	
	if(key=='v'){
		vSyncTestHorizontal ^= true;
		vSyncTestVertical ^= true;
	}

	if(key=='w'){
		ss.cycleToNextScreenMode();
	}

	if(key=='L'){
		ofxSuperLog::getLogger()->setScreenLoggingEnabled(!ofxSuperLog::getLogger()->isScreenLoggingEnabled());
	}

}


void testApp::keyReleased(int key){

}


void testApp::mouseMoved(int x, int y ){
}


void testApp::mouseDragged(int x, int y, int button){

}


void testApp::mousePressed(int x, int y, int button){

	if(touchCreatesBodies){
		if(!dragger->hit(ofVec2f(x,y))){
			dragger->addBody(ofVec2f(x,y));
		}
	}
}


void testApp::mouseReleased(int x, int y, int button){

}


void testApp::windowResized(int w, int h){
	dragger->box2d.createBounds();

}


void testApp::gotMessage(ofMessage msg){

}


void testApp::dragEvent(ofDragInfo dragInfo){ 

}
