#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	//ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);

	ofGLFWWindowSettings winSettings;
	winSettings.numSamples = 8;
	winSettings.width = 400;
	winSettings.height = 250;


	shared_ptr<ofAppBaseWindow> win = ofCreateWindow(winSettings);	// sets up the opengl context!
	((ofAppGLFWWindow*)win.get())->setMultiDisplayFullscreen(true);

	// 10 x 1 screens
	//ofSetupOpenGL(&win, w, h, OF_WINDOW /*OF_FULLSCREEN*/);	// <-------- setup the GL context

	ofRunApp(win, shared_ptr<ofBaseApp>(new ofApp()));
	ofRunMainLoop();
}
