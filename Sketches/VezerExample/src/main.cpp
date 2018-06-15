#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	//ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);

	ofGLFWWindowSettings winSettings;
	winSettings.numSamples = 8;
	int w = 400;
	int h = 250;
#if OF_VERSION_MINOR < 10
	winSettings.width = w;
	winSettings.height = w;
#else
	winSettings.setSize(w, h);
#endif

	shared_ptr<ofAppBaseWindow> win = ofCreateWindow(winSettings);	// sets up the opengl context!
	((ofAppGLFWWindow*)win.get())->setMultiDisplayFullscreen(true);

	// 10 x 1 screens
	//ofSetupOpenGL(&win, w, h, OF_WINDOW /*OF_FULLSCREEN*/);	// <-------- setup the GL context

	ofRunApp(win, shared_ptr<ofBaseApp>(new ofApp()));
	ofRunMainLoop();
}
