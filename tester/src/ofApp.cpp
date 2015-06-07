#include "ofMain.h"

// 特に意味なし、テスト用
template <typename T>
static T yolo(const T &arg) {
	
	if (typeid(arg) == typeid(double))
		cout << __PRETTY_FUNCTION__ << " i am a double" << endl;
	
	else if (typeid(arg) == typeid(int))
		cout << __PRETTY_FUNCTION__ << " i am an integer" << endl;
	
	return arg;
}

// mapの中身をdumpする用
// sample code内で iteratorとvalue の両方渡したいのでtemplateに
// これがbiking on a tightrope...
template <typename T>
void dump(const T &t) {
	cout << t->first << ": " << t->second << endl;
}

// int, double, ofVec3f なんでもござれなadd
template <typename T, typename S>
auto add(const T &t, const S &s) // この時点では返り血の型が分からない
-> decltype(t + s) // ので、ここでdecltype
{
	return t + s;
}


class ofApp : public ofBaseApp
{
	
public:
	
	void setup() {
		
		{
			int twist = 10;
			
			// auto toats が何の型なのかをコンパイラが推論
			// decltype( ... ) で、引数が何の型なのかをコンパイラが推論
			auto toast = yolo<decltype(twist)>(10);
			decltype(twist) coast = yolo<double>(10.);
		}
		
		{
			// iterator回す時に非情に便利
			map<string, int> our_map = {
				{"a", 1},
				{"b", 2},
				{"c", 3},
				{"d", 4},
				{"e", 5}
			};
			
			for (auto it = begin(our_map); it != end(our_map); ++it) {
				dump(it);
			}
			
			cout << "---" << endl;
			
			// というか上記loopはrange baseのループでもっと簡単に
			for(const auto &it: our_map) {
				dump(&it);
			}
			
			cout << "---" << endl;
			
			// あるいはfor_each
			// see also:
			//
			// for_each は単純な繰り返し
			// http://homepage2.nifty.com/well/for_each.htmlx
			//
			// for loop vs std::for_each with lambda
			// http://stackoverflow.com/questions/11956374/for-loop-vs-stdfor-each-with-lambda
			
			for_each(begin(our_map),
					 end(our_map),
					 [](map<string, int>::value_type it) { dump(&it); });
		}
	}
	
	void draw() {
		
		const float t = ofGetElapsedTimef() * 2.5f;
		const int our_int = add(10, sin(t)*7);
		const ofVec3f our_vec = add(ofVec3f::zero(), ofVec3f{sin(t) * 100.f, cos(t) * 100.f});

		ofPushMatrix();
		{
			ofTranslate(ofGetWidth() * 0.5f, ofGetHeight() * 0.5f);
			ofRotate(t * 30.f, 0.f, 0.f, 1.f);
			ofSetCircleResolution(our_int);
			ofDrawCircle(our_vec, 50.f);
		}
		ofPopMatrix();
		
		stringstream report;
		report << "our_int: " << our_int << endl;
		report << "our_vec: " << floor(our_vec.x) << ", " << floor(our_vec.y);
		ofDrawBitmapStringHighlight(report.str(), 30, 30, ofColor::limeGreen);
	}
};



#pragma mark -
#pragma mark main
int main(){
	ofSetupOpenGL(500, 500, OF_WINDOW);
	ofRunApp(new ofApp());
}
