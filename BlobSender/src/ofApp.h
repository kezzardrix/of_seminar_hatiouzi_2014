#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"

#define RECEIVE_PORT 9600
#define SEND_PORT 10000

class ofApp : public ofBaseApp{

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
    
        void findBlob();
		
        ofxCvColorImage			colorImg;
    
        ofxCvGrayscaleImage 	grayImage;
        ofxCvGrayscaleImage 	grayDiff;
        ofxCvGrayscaleImage 	grayBg;
    
        ofxCvContourFinder 	contourFinder;
    
        int 				threshold;
    
        ofVideoGrabber grabber;
    
        int w;
        int h;
    
        ofxOscSender sender;
    
        ofShader shader;
        ofFbo fbo;
    
        bool isUseSandboxVisual;
    
        //sandbox param
        ofPoint moveRange;
        float size;
        ofxOscReceiver receiver;
};
