#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
    w = ofGetWidth();
    h = ofGetHeight();
    
    isUseSandboxVisual = false;
    
    grabber.initGrabber(w,h);
    
    colorImg.allocate(w, h);
    
    grayImage.allocate(w, h);
    grayDiff.allocate(w, h);
    grayBg.allocate(w, h);
    
    threshold = 10;
    
    sender.setup("localhost",SEND_PORT);
    
    shader.load("","shaders/sandbox.frag");
    
    fbo.allocate(ofGetWidth(), ofGetHeight(),GL_RGB);

    size = 128;
    moveRange.set(10.0,1);
    receiver.setup(RECEIVE_PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        if(m.getAddress() == "/moveRange"){
            moveRange.set(m.getArgAsFloat(0),m.getArgAsFloat(1));
        }
        
        if(m.getAddress() == "/size"){
            size = m.getArgAsFloat(0);
        }
        
        if(m.getAddress() == "/isUseSandboxVisual"){
            isUseSandboxVisual = m.getArgAsInt32(0);
        }
    }
    
    if(isUseSandboxVisual){
        //shaderで生成したビジュアルをfboへ書き込む
        fbo.begin();
        ofBackground(0,0,0);
        shader.begin();
        shader.setUniform1f("time", ofGetElapsedTimef());
        shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
        shader.setUniform2f("moveRange", moveRange.x, moveRange.y);
        shader.setUniform1f("size", size);
        ofRect(0,0,ofGetWidth(),ofGetHeight());
        shader.end();
        fbo.end();
        
        ofPixels pix;
        fbo.readToPixels(pix);
        colorImg.setFromPixels(pix.getPixels(),w,h);
        findBlob();
        
    }else{
        
        grabber.update();
    
        if(grabber.isFrameNew()){
            colorImg.setFromPixels(grabber.getPixels(),w,h);
            findBlob();
        }
    
    }
}

void ofApp::findBlob(){
    //特定の範囲で変化した部分を解析
    grayImage = colorImg;
    grayDiff.absDiff(grayBg,grayImage);
    grayDiff.threshold(threshold);
    
    grayBg = grayImage;
    
    float minArea = 200;
    float maxArea = (w*h)/3;
    
    contourFinder.findContours(grayDiff, minArea, maxArea, 10, true);
    
    for(int i = 0; i < contourFinder.blobs.size(); i++){
        ofxOscMessage m;
        
        ofPoint centroid = contourFinder.blobs[i].centroid;
        float area = contourFinder.blobs[i].area;
        
        m.setAddress("/blob/" + ofToString(i));
        m.addFloatArg(ofMap(centroid.x,0,ofGetWidth(),0.1,10.0));
        m.addFloatArg(ofMap(centroid.y,0,ofGetHeight(),100,40.0));
        m.addFloatArg(ofMap(area,minArea,maxArea,0.01,100.0));
        
        sender.sendMessage(m);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(isUseSandboxVisual)fbo.draw(0,0);
    else grayDiff.draw(0,0);
    contourFinder.draw();
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
    isUseSandboxVisual = !isUseSandboxVisual;
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
