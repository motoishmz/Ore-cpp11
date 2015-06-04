#include "ofMain.h"

class Shape
{
	int resolution = 60;
	bool inited_without_argument = false;
	
public:
	Shape(int res)
	: resolution(res)
	{}
	
	Shape()
	// c++11からconstructorのdelegationがつかえる
	: Shape(3)
	// ただし他の変数初期化はここでは出来ない。
	// ↓コメント解くと死亡
	//	, inited_without_argument(true)
	{
		inited_without_argument = true;
	}
	
	inline int getResolution() const {
		return resolution;
	}
	inline bool isInitedWithoutArgs() const {
		return inited_without_argument;
	}
	inline void shoutout() {
		cout << "yo i'm inited with " << (inited_without_argument ? "no args" : "argument " + ofToString(resolution)) << endl;
	}
};


class ofApp : public ofBaseApp
{
	
	vector<Shape*> shapes;
	
public:
	
	void setup() {
		
		cout << endl << __PRETTY_FUNCTION__ << endl;
		
		shapes = {
			// 引数ありなしどちらもOK
			// c++11から `std::initializer_list` が使えるので `push_back` 等いらずでコリっと書ける
			new Shape(),
			new Shape(ofRandom(4, 10)),
			new Shape(),
			new Shape(ofRandom(4, 10)),
			new Shape(),
			new Shape(ofRandom(4, 10))
		};
		
		for (auto s: shapes) { s->shoutout(); }
		
		ofBackground(0, 0, 20);
	}
	
	
	void draw()
	{
		const double radius = 100.;
		const double t = ofGetElapsedTimef() * 100.;
		
		ofPushMatrix();
		{
			ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
			
			for (int i=0; i<shapes.size(); i++)
			{
				const ofPoint pos(radius * sin((2 * PI / shapes.size()) * i),
								  radius * cos((2 * PI / shapes.size()) * i));
				
				const int resolution = shapes[i]->getResolution();
				const double degrees = t * static_cast<int>(shapes[i]->isInitedWithoutArgs());
				const ofColor color = shapes[i]->isInitedWithoutArgs() ? ofColor::limeGreen : ofColor::gray;
				
				ofPushMatrix();
				{
					ofTranslate(pos);
					ofRotate(degrees, 0., 0., 1.);
					ofSetColor(color);
					ofSetCircleResolution(resolution);
					ofDrawCircle(0, 0, 30);
				}
				ofPopMatrix();
			}
		}
		ofPopMatrix();
		
		ofDrawBitmapString("[spacebar] to refresh", 20, 20);
		ofDrawBitmapStringHighlight("with argument", 30, 50, ofColor::gray);
		ofDrawBitmapStringHighlight("without argument", 30, 70, ofColor::limeGreen);
	}
	
	void keyPressed(int key) {
		if (key == ' ') {
			setup();
		}
	}
};



#pragma mark -
#pragma mark main
int main(){
	ofSetupOpenGL(500, 500, OF_WINDOW);
	ofRunApp(new ofApp());
}
