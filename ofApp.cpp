#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto radius = 150;
	auto span = 1;
	for (auto deg = 0; deg < 360; deg += 6) {

		auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		auto left = glm::vec2(radius * cos((deg + span * 0.5) * DEG_TO_RAD), radius * sin((deg + span * 0.5) * DEG_TO_RAD));
		auto right = glm::vec2(radius * cos((deg - span * 0.5) * DEG_TO_RAD), radius * sin((deg - span * 0.5) * DEG_TO_RAD));
		auto noise_radius = ofMap(ofNoise(glm::vec3(location * 0.1, ofGetFrameNum() * 0.025)), 0, 1, radius * 0.2, radius * 0.8);
		auto noise_location = glm::vec2(noise_radius * cos(deg * DEG_TO_RAD), noise_radius * sin(deg * DEG_TO_RAD));

		ofSetColor(255);

		ofBeginShape();

		ofVertex(left);
		ofVertex(noise_location + left);
		ofVertex(noise_location + right);
		ofVertex(right);

		ofEndShape(true);

		auto circle_radius = ofMap(ofNoise(glm::vec3(location * 0.1, ofGetFrameNum() * 0.025)), 0, 1, 0, radius * 0.8);
		auto prev_circle_radius = ofMap(ofNoise(glm::vec3(location * 0.1, (ofGetFrameNum() - 3) * 0.025)), 0, 1, 0, radius * 0.8);
		auto gap = abs(prev_circle_radius - circle_radius);
		auto alpha = gap < 0.5 ? 0 : ofMap(gap, 0.5, 6, 0, 255);

		ofSetColor(255, alpha);
		ofDrawCircle(glm::vec2(circle_radius * cos(deg * DEG_TO_RAD), circle_radius * sin(deg * DEG_TO_RAD)), 2);
	}


}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}