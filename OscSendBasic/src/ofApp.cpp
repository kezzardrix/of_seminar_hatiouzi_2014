#include "ofApp.h"

float rad;

//--------------------------------------------------------------
void ofApp::setup(){
    sender.setup("127.0.0.1", 9000); //送り先のIPアドレスとポート番号を指定
    
    rad = 10;
}

//--------------------------------------------------------------
void ofApp::update(){
    ofxOscMessage m; //Oscメッセージを作る
    m.setAddress("/position"); //名前
    m.addFloatArg(mouseX); //引数を順番に追加
    m.addFloatArg(mouseY);
    
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    ofCircle(mouseX, mouseY, rad);
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
    ofxOscMessage m; //Oscメッセージを作る
    m.setAddress("/rad"); //名前
    m.addFloatArg(100); //引数を順番に追加
    sender.sendMessage(m);
    
    rad = 100;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ofxOscMessage m; //Oscメッセージを作る
    m.setAddress("/rad"); //名前
    m.addFloatArg(10); //引数を順番に追加
    sender.sendMessage(m);
    
    rad = 10;
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
