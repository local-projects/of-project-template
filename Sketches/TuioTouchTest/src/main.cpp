#include "ofMain.h"
#include "testApp.h"
//========================================================================
int main( ){

    ofGLFWWindowSettings winSettings;
    winSettings.numSamples = 0;

    shared_ptr<ofAppBaseWindow> win = ofCreateWindow(winSettings);	// sets up the opengl context!
    //((ofAppGLFWWindow*)win.get())->setMultiDisplayFullscreen(true);
    
    //ofSetupOpenGL(&win, w, h, OF_WINDOW /*OF_FULLSCREEN*/);	// <-------- setup the GL context
    
    ofRunApp(win, shared_ptr<ofBaseApp>(new testApp()));
    ofSetFullscreen(true);
    ofRunMainLoop();

}
