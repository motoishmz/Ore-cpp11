#include "ofMain.h"
#include <functional>

class Oscillator
{
	
protected:
	
	typedef enum {
		UPDATE_FN_0 = 0,
		UPDATE_FN_1,
		UPDATE_FN_2,
		NUM_UPDATE_FN
	} UpdateFnType;
	
	function<void()> fn[NUM_UPDATE_FN];
	UpdateFnType type;
	
	void fn1() {
		cout << __PRETTY_FUNCTION__ << endl;
		ofDrawCircle(ofGetWidth()*0.5, ofGetHeight()*0.5, 100);
	}
	void fn2() {
		cout << __PRETTY_FUNCTION__ << endl;
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofDrawRectangle(ofGetWidth()*0.5, ofGetHeight()*0.5, 200, 200);
	}
	void fn3() {
		cout << __PRETTY_FUNCTION__ << endl;
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofDrawRectRounded(ofGetWidth()*0.5, ofGetHeight()*0.5, 200, 200, 50);
	}
	
	double t;
	
public:
	
	Oscillator()
	: type(UPDATE_FN_0)
	{
		// ポインタでも出来るけど、、、
		fn[UPDATE_FN_0] = bind(mem_fn(&Oscillator::fn1), this);
		fn[UPDATE_FN_1] = bind(mem_fn(&Oscillator::fn2), this);
		fn[UPDATE_FN_2] = bind(mem_fn(&Oscillator::fn3), this);
	}
	
	void randomize() {
		type = static_cast<UpdateFnType>(rand() % NUM_UPDATE_FN);
		t = 1.;
	}
	
	void update() {
		t *= 0.98;
	}
	
	void draw() {
		ofPushStyle();
		ofSetColor(250.*t, 50., 50.);
		fn[type]();
		ofPopStyle();
		
		stringstream report;
		report << "UpdateFnType: " << (type+1) << "/" << NUM_UPDATE_FN;
		ofDrawBitmapStringHighlight(report.str(), 30, 30, ofColor::limeGreen);
	}
};


class ofApp : public ofBaseApp
{

	Oscillator oscllator;
	
public:
	
	void setup() {
		ofSetFrameRate(60);
	}
	void update() {
		oscllator.update();
	}
	void draw() {
		oscllator.draw();
	}
	
	void keyPressed(int key) {
		if (key == ' ') {
			oscllator.randomize();
		}
	}
};



#pragma mark -
#pragma mark main
int main(){
	ofSetupOpenGL(500, 500, OF_WINDOW);
	ofRunApp(new ofApp());
}
