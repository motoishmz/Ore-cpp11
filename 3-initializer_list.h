#include "ofMain.h"

class SceneManager {
	
public:
	
	class Scene {
		
		bool active;
		uint my_id;
		ofPoint pos;
		
	public:
		
		Scene(int id)
		: my_id(id)
		, active(false)
		{}
		
		inline void setActive(bool active) { this->active = active; }
		inline uint getId() const { return my_id; }
		inline bool getActive() const { return active; }
	};
	
	
	SceneManager(initializer_list<Scene> scenes) {
		
		our_scenes.clear();
		our_scenes.insert(end(our_scenes),
						  begin(scenes),
						  end(scenes));
	}
	
	
	void draw() {
		
		ofPushStyle();
		{
			for (int i=0; i<our_scenes.size(); i++) {
				
				const SceneManager::Scene &scene = our_scenes[i];
				
				const ofPoint pos = {
					(float)(ofGetWidth() * 0.7 / our_scenes.size() * i + ofGetWidth() * 0.15),
					(float)(ofGetHeight() * 0.5)
				};
				
				ofSetColor(scene.getActive() ? ofColor::limeGreen : ofColor::red);
				ofDrawBitmapString(ofToString(scene.getId()), pos+10);
				ofDrawCircle(pos, 10);
				
			}
		}
		ofPopStyle();
	}
	
	
	void refresh(vector<int> scene_indeces) {
		for (auto &scene: our_scenes) {
			scene.setActive(find(begin(scene_indeces),
								 end(scene_indeces),
								 scene.getId()) != end(scene_indeces));
		}
	}
	
	size_t size() const { return our_scenes.size(); }
	
protected:
	
	deque<Scene> our_scenes;
};


class ofApp : public ofBaseApp
{
	
	SceneManager *SM;
	vector<int> test_list;
	
public:
	
	void setup() {
		
		{
			// initializer_listでinit
			vector<int> our_vector = {1, 2, 3, 4, 5};
			
			for (auto &i: our_vector) { cout << i << endl; }
			
			cout << "---" << endl;
		}
		{
			// initializer_listでinit
			deque<int> our_queue = {234, 52, 36, 356, 7, 246};
			
			// begin(std::initializer_list), end(std::initializer_list) が今まで使えなかった
			// sort比較式をlambdaで書ける
			sort(begin(our_queue),
				 end(our_queue),
				 [](const int &lhs, const int &rhs) {
					 return lhs < rhs;
				 });
			
			for (auto &i: our_queue) { cout << i << endl; }
			
			cout << "---" << endl;
		}
		{
			// 便利がいい
			map<string, int> dict = {{"Akira", 22}, {"Johnny", 38}, {"Millia", 16}};
			for (auto &obj: dict)
				cout << obj.first << ":" << obj.second << endl;
		}
		
		SM = new SceneManager{ // <-- () じゃなくて {}
			SceneManager::Scene(0),
			SceneManager::Scene(1),
			SceneManager::Scene(2),
			SceneManager::Scene(3),
			SceneManager::Scene(4),
			SceneManager::Scene(5),
			SceneManager::Scene(6),
			SceneManager::Scene(7),
			SceneManager::Scene(8),
			SceneManager::Scene(9)
		};
	}
	
	
	void draw() {
		
		SM->draw();
		
		stringstream report;
		report << "[spacebar] to refresh:" << endl;
		for (auto &id: test_list) { report << id << " "; }
		ofDrawBitmapStringHighlight(report.str(), 30, 30, ofColor::limeGreen);
	}
	
	
	void keyPressed(int key) {
		
		if (key == ' ') {
			test_list.clear();
			test_list = {
				static_cast<int>(ofRandom(0, SM->size())),
				static_cast<int>(ofRandom(0, SM->size())),
				static_cast<int>(ofRandom(0, SM->size())),
				static_cast<int>(ofRandom(0, SM->size())),
				static_cast<int>(ofRandom(0, SM->size()))
			};
			
			sort(begin(test_list), end(test_list));
			test_list.erase(unique(begin(test_list), end(test_list)), end(test_list));
			
			SM->refresh(test_list);
		}
	}
};



#pragma mark -
#pragma mark main
int main(){
	ofSetupOpenGL(500, 500, OF_WINDOW);
	ofRunApp(new ofApp());
}
