#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    receiver.setup(PORT);
    
    for(int i = 0; i < MAX_RIPPLE; i++){
        ripples.push_back(Ripple());
    }
    
    counter = 0;
    ofSetLineWidth(8);
    ofSetCircleResolution(60);
}

void ofApp::appear(ofPoint _pos,ofColor _color){
    ripples[counter].appear(_pos,_color);
    counter++;
    counter %= MAX_RIPPLE;
}

//--------------------------------------------------------------
void ofApp::update(){
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        if(m.getAddress() == "/appear"){
            appear(ofPoint(m.getArgAsFloat(0),
                                            m.getArgAsFloat(1)),
                                    ofColor(m.getArgAsFloat(2),
                                            m.getArgAsFloat(3),
                                            m.getArgAsFloat(4)));
        }
    }
    
    for(int i = 0; i < ripples.size(); i++){
        ripples[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for(int i = 0; i < ripples.size(); i++){
        ripples[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    appear(ofPoint(x,y), ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
