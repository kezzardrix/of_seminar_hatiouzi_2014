#include "ofApp.h"

ofPoint pos;
float rad;

//--------------------------------------------------------------
void ofApp::setup(){
    //ポート番号 コンピュータ内部でのソフトウェアの番地
    reciever.setup(9000);
    
    pos.set(ofGetWidth() * 0.5,ofGetHeight() * 0.5);
    rad = 10;
}

//--------------------------------------------------------------
void ofApp::update(){
    while (reciever.hasWaitingMessages()) {
        
        //メッセージを取得
        ofxOscMessage m;
        reciever.getNextMessage(&m);
        
        if(m.getAddress() == "/position"){ //名前をチェック
            pos.set(m.getArgAsFloat(0),
                    m.getArgAsFloat(1)); //float型の引数を取得
        }
        
        if(m.getAddress() == "/rad"){ //名前をチェック
            rad = m.getArgAsFloat(0);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    ofSetColor(255,255,255);
    ofCircle(pos.x,pos.y,rad);
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
