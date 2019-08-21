#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){

  ofSetVerticalSync(true);
  videoHide = false;

  gui.setup();
  
  //videoNadar.load("videos/nadar1.mp4");
  //videoNadar.play(); 
    
  gui.add(lkMaxLevel.set("lkMaxLevel", 3, 0, 8));
  gui.add(lkMaxFeatures.set("lkMaxFeatures", 200, 1, 1000));
  gui.add(lkQualityLevel.set("lkQualityLevel", 0.01, 0.001, .02));
  gui.add(lkMinDistance.set("lkMinDistance", 4, 1, 16));
  gui.add(lkWinSize.set("lkWinSize", 8, 4, 64));
  gui.add(usefb.set("Use Farneback", true));
  gui.add(fbPyrScale.set("fbPyrScale", .5, 0, .99));
  gui.add(fbLevels.set("fbLevels", 4, 1, 8));
  gui.add(fbIterations.set("fbIterations", 2, 1, 8));
  gui.add(fbPolyN.set("fbPolyN", 7, 5, 10));
  gui.add(fbPolySigma.set("fbPolySigma", 1.5, 1.1, 2));
  gui.add(fbUseGaussian.set("fbUseGaussian", false));
  gui.add(fbWinSize.set("winSize", 25, 4, 64));

  // contour
  
  gui.add(thresholdQuad.set("thresholdQuad", 22, 10, 255)); // para detectar a la nadadora

  curFlow = &fb;

  contourFinder.setMinAreaRadius(10);
  contourFinder.setMaxAreaRadius(200);
  unwarped.allocate(150, 100, OF_IMAGE_COLOR);

  targetColor = ofColor(0);
  contourFinder.setTargetColor(targetColor, ofxCv::TRACK_COLOR_RGB);
  record = false;
  
}

//--------------------------------------------------------------
void ofApp::update(){

  if(videoON == true){
    //videoNadar.update(); // el video se tiene que actualizar
    videoNadarScaled.update(); 
  }

  if(videoNadarScaled.isFrameNew()) {

    //threshold = ofMap(mouseX, 0, ofGetWidth(), 0, 255);
    contourFinder.setThreshold(thresholdQuad);
    contourFinder.findContours(videoNadarScaled);

    /*
    int n = contourFinder.size();
    quads.clear();
    quads.resize(n);
    
    for(int i = 0; i < n; i++) {
      quads[i] = contourFinder.getFitQuad(i);			
      // convert integer image coordinates Point2i to unwarp positions Point2f
      vector<Point2f> warpPoints;
      copy(quads[i].begin(), quads[i].end(), back_inserter(warpPoints));
      unwarpPerspective(videoNadarScaled, unwarped, warpPoints);
      unwarped.update();
    }
    */

    if(usefb) {
      curFlow = &fb;
      fb.setPyramidScale(fbPyrScale);
      fb.setNumLevels(fbLevels);
      fb.setWindowSize(fbWinSize);
      fb.setNumIterations(fbIterations);
      fb.setPolyN(fbPolyN);
      fb.setPolySigma(fbPolySigma);
      fb.setUseGaussian(fbUseGaussian);
    } else {
      curFlow = &lk;
      lk.setMaxFeatures(lkMaxFeatures);
      lk.setQualityLevel(lkQualityLevel);
      lk.setMinDistance(lkMinDistance);
      lk.setWindowSize(lkWinSize);
      lk.setMaxLevel(lkMaxLevel);
    }
    
    curFlow->calcOpticalFlow(videoNadarScaled);

  }
  
}

//--------------------------------------------------------------
void ofApp::draw(){

  ofBackground(0, 0, 0, 0); // el fondo se conserva transparente para conservar alphas
  
  ofPushMatrix(); 
  ofScale(2);

  if(videoHide == false){
  videoNadarScaled.draw(0, 0);
  }

  //contourFinder.draw(); 

  /*
  //ofNoFill();
  ofSetColor(ofColor(255, 255, 255));
  for(int i = 0; i < quads.size(); i++) {
    toOf(quads[i]).draw();
  }
  */

  ofSetColor(ofColor(255, 255, 255)); 

  ofFill(); 
  
  curFlow->draw(0, 0);
  
  for(int i = 0; i < contourFinder.size(); i++) {
    //ofDrawBitmapString(ofToString(contourFinder.getCenter(i) *2), contourFinder.getCenter(i).x, contourFinder.getCenter(i).y);
    
  }

  ofPopMatrix();

  if(record == true){
    if(videoNadarScaled.isFrameNew()){  
      ofSaveScreen(vidSelektor+ofToString(ofGetFrameNum())+".png");
    }
  }
  
  // gui.draw();   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

  switch (key){

  case '1':
    //videoNadar.load("videos/nadar1.mp4");
    //videoNadar.stop();
    videoNadarScaled.load("videos/nadar1Scaled.mp4");
    videoNadarScaled.stop();
    vidSelektor = "pngVideo1/";
    break;

  case '2':
    //videoNadar.load("videos/nadar2.mp4");
    //videoNadar.stop();
    videoNadarScaled.load("videos/nadar2Scaled.mp4");
    videoNadarScaled.stop();
    vidSelektor = "pngVideo2/";
    break;

  case '3':
    //videoNadar.load("videos/nadar3.mp4");
    //videoNadar.stop();
    videoNadarScaled.load("videos/nadar3Scaled.mp4");
    videoNadarScaled.stop();
    vidSelektor = "pngVideo3/"; 
    break;

  case 'p':
    //videoNadar.play();
    videoNadarScaled.play(); 
    videoON = true; 
    break;

  case 's':
    //videoNadar.stop();
    videoNadarScaled.stop(); 
    videoON = false; 
    break;

  case 'h':
    videoHide = true;
    break;

  case 'H':
    videoHide = false;
    break;

  case 'r':
    record = true;
    break;
    
  case 'R':
    record = false;
    break; 
    
  }
  
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  //targetColor = videoNadarScaled.getPixels().getColor(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
