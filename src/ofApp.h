#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
public:
  void setup();
  void update();
  void draw();
  
  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
  
  ofVideoPlayer videoNadar;
  ofVideoPlayer videoNadarScaled; 

  int videoNum;
  bool videoON;
  bool videoHide;

  ofxCv::FlowFarneback fb;
  ofxCv::FlowPyrLK lk;
  
  ofxCv::Flow* curFlow;
		
  ofxPanel gui;
  ofParameter<float> fbPyrScale, lkQualityLevel, fbPolySigma, thresholdQuad;
  ofParameter<int> fbLevels, lkWinSize, fbIterations, fbPolyN, fbWinSize, lkMaxLevel, lkMaxFeatures, lkMinDistance;
  ofParameter<bool> fbUseGaussian, usefb;

  vector< vector<cv::Point> > quads;
  //float thresholdQuad;
  ofxCv::ContourFinder contourFinder;
  ofColor targetColor;
  ofImage unwarped;

  string vidSelektor;
  bool record; 

};
