//
//  BoxDragger.h
//  remoteUI_Sketch
//
//  Created by Oriol Ferrer Mesià on 19/02/14.
//
//

#ifndef __remoteUI_Sketch__BoxDragger__
#define __remoteUI_Sketch__BoxDragger__

#include <iostream>
#define MULTITOUCH_HACK /*to get box2d to use multitouch*/


#include "ofMain.h"
#include "ofxBox2d.h"


class BoxDragger{

public:

	void setup();
	void update();
	void draw();

	void addBody(ofPoint p);
	ofxBox2dCircle* hit(ofPoint p);
	void removeBody(ofxBox2dCircle*);
	void destroyAll();

	ofxBox2d                            box2d;			  //	the box2d world
	vector    <ofxBox2dCircle* >	circles;
	vector    <ofColor>					colors;


	float objectScale;
	bool gravity;
	ofColor bgColor;
	ofColor circleColor;
};



#endif /* defined(__remoteUI_Sketch__BoxDragger__) */
