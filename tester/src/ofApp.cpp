#include "ofMain.h"

class Dragon
{
	int resolution;
	bool inited_without_argument = false;
	
public:
	Dragon(int res)
	: resolution(res)
	{}
	
	Dragon()
	: Dragon(3) // <-- c++11からconstructorのdelegationがつかえる
//	, inited_without_argument(true) // <-- ただし他の変数初期化はここでは出来ない。コメント解くと死亡
	{
		inited_without_argument = true;
	}
	
	inline int getResolution() const { return resolution; }
	inline bool isInitedWithoutArgs() const { return inited_without_argument; }
	
	inline void shoutout() {
		cout << "yo i'm inited with " << (inited_without_argument ? "no args" : "argument " + ofToString(resolution)) << endl;
	}
};


class ofApp : public ofBaseApp
{
	
	vector<Dragon*> dragons;
	
public:
	
	void setup() {
		
		cout << endl << __PRETTY_FUNCTION__ << endl;
		
		dragons = {
			// 引数ありなしどちらもOK
			// c++11から `std::initializer_list` が使えるので `push_back` 等いらずでコリっと書ける
			new Dragon(),
			new Dragon(ofRandom(4, 10)),
			new Dragon(),
			new Dragon(ofRandom(4, 10)),
			new Dragon(),
			new Dragon(ofRandom(4, 10))
		};
		
		for (auto d: dragons) { d->shoutout(); }
		
		ofBackground(0, 0, 20);
	}
	
	
	void draw()
	{
		const double radius = 100.;
		const double t = ofGetElapsedTimef() * 100.;
		
		ofPushMatrix();
		{
			ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
			
			for (int i=0; i<dragons.size(); i++)
			{
				ofPushMatrix();
				{
					ofTranslate(radius * sin((2 * PI / dragons.size()) * i),
								radius * cos((2 * PI / dragons.size()) * i));
					ofRotate(t * static_cast<int>(dragons[i]->isInitedWithoutArgs()), 0., 0., 1.);
					ofSetColor(dragons[i]->isInitedWithoutArgs() ? ofColor::limeGreen : ofColor::gray);
					ofSetCircleResolution(dragons[i]->getResolution());
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
