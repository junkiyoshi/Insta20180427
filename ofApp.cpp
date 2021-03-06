#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(239);
	ofSetWindowTitle("Insta");

	this->alpha = 255;
	this->seed_values = { 0, 0, 0, 0 };
}

//--------------------------------------------------------------
void ofApp::update() {
	
}

//--------------------------------------------------------------
void ofApp::draw() {

	// サイクル(増加、停止、フェードアウト)管理
	int number_of_circles = ofGetFrameNum() % 450;
	if (number_of_circles > 400) {
		
		this->alpha = ofMap(number_of_circles, 400, 450, 255, 0);
		number_of_circles = 350;
	}
	else if (number_of_circles > 350) {

		number_of_circles = 350;
	}else{

		this->alpha = 255;
	}
	
	//　サイクルが1周したらリセット
	if (number_of_circles == 0) {

		this->seed_values[0] = ofRandom(10, 30);
		this->seed_values[1] = ofRandom(50, 80);
		this->seed_values[2] = ofRandom(100, 130);
		this->seed_values[3] = ofRandom(150, 180);
		return;
	}

	// 4カ所に描写
	this->draw_circles(ofPoint(ofGetWidth() / 4, ofGetHeight() / 4), number_of_circles, this->seed_values[0]);
	this->draw_circles(ofPoint(ofGetWidth() / 4, ofGetHeight() / 4 * 3), number_of_circles, this->seed_values[1]);
	this->draw_circles(ofPoint(ofGetWidth() / 4 * 3, ofGetHeight() / 4), number_of_circles, this->seed_values[2]);
	this->draw_circles(ofPoint(ofGetWidth() / 4 * 3, ofGetHeight() / 4 * 3), number_of_circles, this->seed_values[3]);
}

//--------------------------------------------------------------
void ofApp::draw_circles(ofPoint range_point, int number_of_circles, int seed_value) {

	ofSeedRandom(seed_value);

	ofPushMatrix();
	ofTranslate(range_point);

	vector<tuple<ofColor, ofPoint, float>> circles;
	int range_radius = 150;

	// 重ならないCircleをnumber_of_circles数だけ生成
	while (circles.size() < number_of_circles) {

		ofPoint point = ofPoint(ofRandom(-range_radius, range_radius), ofRandom(-range_radius, range_radius));
		if (point.length() > range_radius) {

			continue;
		}

		ofColor color;
		color.setHsb(ofRandom(seed_value - 10, seed_value + 10), ofRandom(139, 239), ofRandom(139, 239));
		float radius = ofRandom(2, 35);

		bool flag = true;
		for (int i = 0; i < circles.size(); i++) {

			if (point.distance(get<1>(circles[i])) < get<2>(circles[i]) + radius) {

				flag = false;
				break;
			}
		}

		if (flag) {

			circles.push_back(make_tuple(color, point, radius));
		}
	}

	// 生成したCircleの描写
	for (int circles_index = 0; circles_index < circles.size(); circles_index++) {

		ofColor color = get<0>(circles[circles_index]);
		ofPoint point = get<1>(circles[circles_index]);
		float radius = get<2>(circles[circles_index]);

		ofSetColor(color, this->alpha);
		ofDrawCircle(point, radius);
	}

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}