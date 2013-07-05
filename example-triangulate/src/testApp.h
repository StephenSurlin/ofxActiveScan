#pragma once

#include "ofMain.h"

#include "ofxCv.h"
#include "ofxActiveScan.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int);
	
private:
	ofxActiveScan::Options options;
	ofMesh mesh;
	ofEasyCam cam;
	cv::Mat camIntrinsic, proIntrinsic, proExtrinsic;
	double camDist, proDist;
	ofxCv::Intrinsics camCalibration, proCalibration;
	cv::Size camSize, proSize;
	
	enum CameraMode {EASYCAM_MODE, PRO_MODE, CAM_MODE};
	CameraMode cameraMode;
	
	int cw, ch;
	
	string rootDir;
};
