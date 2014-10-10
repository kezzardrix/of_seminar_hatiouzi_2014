#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class Ripple{
public:
    
    Ripple():alphaSpeed(4),radSpeed(4){}
    
    void appear(ofPoint _pos,ofColor _color){
        
        pos = _pos;
        color = _color;
        rad = 1;
        alpha = 255;
        
    }
    
    void update(){
        rad += radSpeed;
        alpha -= alphaSpeed;
        
    }
    void draw(){
        
        if(alpha > 0){
        
            ofPushStyle();
            ofNoFill();
            ofSetColor(color.r,color.g,color.b,alpha);
            ofCircle(pos.x,pos.y,rad);
            ofPopStyle();
        }
    }
private:
    ofPoint pos;
    float rad;
    float radSpeed;
    float alpha;
    float alphaSpeed;
    ofColor color;
};

#define PORT 9000
#define MAX_RIPPLE 300

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
    
        void appear(ofPoint _pos,ofColor _color);
        ofxOscReceiver receiver;
    
        vector<Ripple>ripples;
        int counter;
};
