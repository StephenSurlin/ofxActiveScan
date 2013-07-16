/*
    This file is part of ofxActiveScan.

    ofxActiveScan is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ofxActiveScan is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ofxActiveScan.  If not, see <http://www.gnu.org/licenses/>.

    Naoto Hieda <micuat@gmail.com> 2013
 */

#include "testApp.h"

using namespace ofxActiveScan;

void levmar_2dnorm(double *p, double *x, int m, int n, void *data) {
	int i;
	double x0, x1, dif0, dif1;
	double *d;
	
	d = (double *)data;
	
	for( i = 0 ; i < n ; i++ ) {
		x0 = d[i*4] * cos(p[0]) - d[i*4+1] * sin(p[0]) + p[1];
		x1 = d[i*4] * sin(p[0]) + d[i*4+1] * cos(p[0]) + p[2];
		dif0 = x0 - d[i*4+2];
		dif1 = x1 - d[i*4+3];
		x[i] = dif0 * dif0 + dif1 * dif1;
	}
}

void testApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	rootDir = "../../../SharedData/";
	
	/*
	cv::FileStorage fs(ofToDataPath(rootDir + "/config.yml"), cv::FileStorage::READ);
	fs["proWidth"] >> options.projector_width;
	fs["proHeight"] >> options.projector_height;
	fs["camWidth"] >> cw;
	fs["camHeight"] >> ch;
	fs["vertical_center"] >> options.projector_horizontal_center;
	fs["nsamples"] >> options.nsamples;
	
	// load correspondences estimated by decode program 
	Map2f horizontal(ofToDataPath(rootDir + "/h.map", true));
	Map2f vertical(ofToDataPath(rootDir + "/v.map", true));  
	ofImage mask;
	ofLoadImage(mask, ofToDataPath(rootDir + "/mask.bmp"));
	*/
	
	int ret;
	double p[3], x[4];
	int m, n;
	double opts[LM_OPTS_SZ], info[LM_INFO_SZ];
	double data[] = {0.0, 0.0, 2.0, -2.0,
	1.0, 0.0, 2.0, -1.0,
	0.0, 1.0, 1.0, -2.0,
	-1.0, -1.0, 3.0, -3.0
	};
	
	opts[0] = LM_INIT_MU;
	opts[1] = 1E-15;
	opts[2] = 1E-15;
	opts[3] = 1E-20;
	opts[4] = LM_DIFF_DELTA;
	
	m = 3;
	n = 4;
	p[0] = 0.0;
	p[1] = 0.0;
	p[2] = 0.0;
	x[0] = 0.0;
	x[1] = 0.0;
	x[2] = 0.0;
	x[3] = 0.0;
	ret = dlevmar_dif(levmar_2dnorm, p, x, m, n, 10000, opts, info, NULL, NULL, data);
	
	printf("Levenberg-Marquardt returned %d in %g iter, reason %g\nSolution: ", ret, info[5], info[6]);
	
	for( int i = 0 ; i < m ; ++i )
		cout << p[i] << " ";
	
	cout << "\n\nMinimization info:\n";
	
	for( int i = 0 ; i < LM_INFO_SZ ; ++i )
		cout << info[i] << " ";
	
	cout << endl;
}

void testApp::update() {
}

void testApp::draw() {
	ofBackground(0);
}

void testApp::keyPressed(int key) {
}
