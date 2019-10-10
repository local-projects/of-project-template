//
//  ofxTouchHelper.h
//  emptyExample
//
//  Created by Oriol Ferrer Mesià on 28/12/12.
//
//

#ifndef ofxTouchHelper_h
#define ofxTouchHelper_h

#include "ofMain.h"
#include "TouchAnimation.h"

#define	MAX_TOUCHES		100
#define SPEED_SMOOTH_RATIO	0.5f



class ofxTouchHelper{

	public:

	enum TouchStyle{ T_DOWN, T_UP, T_DOUBLE_TAP  };
	struct TouchAnim{
		ofVec2f pos;
		float life;
	};

	struct TouchUnit{
		TouchUnit(){
			doubleTap = false;
			speed = 0.0f;
			down = extra = false;
			duration = 0.0f;
		}
		bool doubleTap;
		bool down;
		float duration;
		ofVec2f pos;
		ofVec2f prevPos;
		ofVec2f smoothSpeed;
		float speed;
		bool extra;
	};


	void setup(){
		debug = false;
		for (int i = 0; i < MAX_TOUCHES; i++){
			touch[i].down = false;
			touch[i].duration = 0.0f;
			touch[i].speed = 0.0f;
		}
		timeSinceLastDownEvent = timeSinceLastUpEvent = 0.0f;

		touchCircle.loadImage("images/touchCircle.png");
		touchCircle2.loadImage("images/touchCircle2.png");
		hand.loadImage("images/hand.png");
		hand2.loadImage("images/hand2.png");
		touchAnims.setup(&touchCircle, &touchCircle2);
	}


	void update(float dt){

		touchAnims.update(dt);

		for (int i = 0; i < MAX_TOUCHES; i++){
			if( touch[i].down ){
				touch[i].duration += dt;
				touch[i].speed = (1.0f-SPEED_SMOOTH_RATIO) * touch[i].speed + SPEED_SMOOTH_RATIO * ( touch[i].pos - touch[i].prevPos ).length() / dt;
				touch[i].smoothSpeed = (1.0f-SPEED_SMOOTH_RATIO) * touch[i].smoothSpeed + SPEED_SMOOTH_RATIO * ( touch[i].pos - touch[i].prevPos ) / dt;
				touch[i].prevPos = touch[i].pos;
			}else{
				touch[i].smoothSpeed *= 0.5;
				touch[i].speed = 0.0f;
			}
		}
		timeSinceLastDownEvent += dt;
		timeSinceLastUpEvent += dt;
	}

	void drawPretty(bool drawHand = true){

		//ofSetRectMode(OF_RECTMODE_CENTER);
		touchAnims.draw(hand, drawHand);

		if(drawHand){
			ofSetColor(255,128);
			for (int i = 0; i < MAX_TOUCHES; i++){
				if( touch[i].down ){
					ofSetColor(255, 128 * ofClamp( 2 * touch[i].duration, 0, 1 ) );
					if (touch[i].doubleTap){
						hand2.draw(touch[i].pos.x - hand2.getWidth() * 0.5, touch[i].pos.y - hand2.getWidth() * 0.5 );
					}else{
						hand.draw(touch[i].pos.x - hand.getWidth() * 0.5, touch[i].pos.y - hand.getHeight() * 0.5);
					}

				}
			}
		}
	}
	
	void drawDebug(){
		for (int i = 0; i < MAX_TOUCHES; i++){
			if( touch[i].down ){
				ofFill();
				ofSetColor(255,32);
				ofDrawCircle(touch[i].pos, 40);
				ofNoFill();
				if (touch[i].extra)
					ofSetColor(96,0,0);
				else
					ofSetColor(96);

				ofDrawCircle(touch[i].pos, 40);
				if (touch[i].doubleTap){
					ofSetColor(96);
					ofDrawCircle(touch[i].pos, 47);
				}
				ofSetColor(255,64);

				ofDrawBitmapString( "#" + ofToString(i), touch[i].pos + ofVec2f(-10,-50));
				ofDrawBitmapString( "pos: " + ofToString(touch[i].pos), touch[i].pos + ofVec2f(50,-14));
				ofDrawBitmapString( "duration: " + ofToString(touch[i].duration,1) + " sec", touch[i].pos + ofVec2f(50,0));
				char aux[128];
				sprintf(aux, "speed: %5.1f pixels/sec", touch[i].speed);
				ofDrawBitmapString( aux, touch[i].pos + ofVec2f(50,14));
			}
		}
		ofFill();
	}


	void touchDown(ofTouchEventArgs &t){
		if(debug) printf("touchDown %d\n", t.id);
		timeSinceLastDownEvent = 0.0f;
		touch[t.id].duration = 0.0f;
		//touch[t.id].doubleTap = false;
		touch[t.id].pos.x = t.x;
		touch[t.id].pos.y = t.y;
		touch[t.id].prevPos = touch[t.id].pos;
		touch[t.id].down = true;
		touchAnims.addTouch(t.x, t.y, TouchAnimation::T_SINGLE);
	}


	void touchMoved(ofTouchEventArgs &t){
		if(debug) printf("touchMoved %d\n", t.id);
		if ( touch[t.id].down == false) return;
		touch[t.id].pos.x = t.x;
		touch[t.id].pos.y = t.y;
	}


	void touchUp(ofTouchEventArgs &t){
		if(debug) printf("touchUp %d\n", t.id);
		timeSinceLastUpEvent = 0.0f;
		touch[t.id].doubleTap = false;
		touch[t.id].down = false;
		touch[t.id].pos.x = t.x;
		touch[t.id].pos.y = t.y;
		touch[t.id].duration = 0.0f;
		touchAnims.addTouch(t.x, t.y, TouchAnimation::T_UP);
	};

	void touchDoubleTap(ofTouchEventArgs &t){
		if(debug) printf("touchDoubleTap %d\n", t.id);
		timeSinceLastUpEvent = 0.0f;
		touch[t.id].down = true;
		touch[t.id].doubleTap = true;
		touch[t.id].pos.x = t.x;
		touch[t.id].pos.y = t.y;
		touch[t.id].duration = 0.0f;
		touchAnims.addTouch(t.x, t.y, TouchAnimation::T_DOUBLE);
	}

	void touchCancelled(ofTouchEventArgs & touch){
	}

	TouchUnit* getTouchWithID(int ID){

		if (ID >= 0 && ID < MAX_TOUCHES){
			return &touch[ID];
		}
		return NULL;
	};

	
	vector<TouchUnit> getTouches(){
		vector<TouchUnit> t;
		for (int i = 0; i < MAX_TOUCHES; i++) {
			if (touch[i].down == true){
				t.push_back(touch[i]);
			}
		}
		return t;
	}

	void setVerbose(bool v){ debug = v;}

	float getTimeSinceLastUpEvent(){
		return timeSinceLastUpEvent;
	}


	float getTimeSinceLastDownEvent(){
		return timeSinceLastDownEvent;
	}


	int getNumTouches(){

		int touchDown = 0;
		for (int i = 0; i < MAX_TOUCHES; i++) {
			if (touch[i].down == true){
				touchDown ++;
			}
		}
		return touchDown;
	}

private:

	float					timeSinceLastDownEvent;
	float					timeSinceLastUpEvent;
	TouchUnit				touch[MAX_TOUCHES];
	bool					debug;

	ofImage					touchCircle;
	ofImage					touchCircle2;
	ofImage					hand;
	ofImage					hand2;

	TouchAnimation			touchAnims;

};

#endif
