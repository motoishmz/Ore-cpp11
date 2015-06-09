#include "ofMain.h"

class ofApp : public ofBaseApp
{
	
public:
	
	void setup() {
		
		// [lambda capture]
		// 外部変数を扱う場合、関数実体に渡す変数をコピーにするか参照にするか等をここで明示できる
		[]
		
		// [parameter declaration clause]
		// 関数の引数定義
		()
		
		// [compound statement]
		// 関数の本体
		{}
		
		// function call expression
		// 関数の呼び出し
		()
		;
		
		{
			auto our_function = [](int a, int b)
			// -> unsigned int
			{
				
				// auto ofApp::setup()::(anonymous class)::operator()() const
				cout << __PRETTY_FUNCTION__ << endl;
				
				// 返り値の型は、decltype(a + b)。
				// unsigned int あたりのコメントを外すと型指定ができる
				return a + b;
			};
			
			cout << our_function(10, 20) << endl;
		}
		
		{
			const int k_size = 30;
			const int k_max = 50;
			
			auto our_comparison = [](int &lhs, int &rhs) { return lhs < rhs; };
			auto our_generator = [](){ return floor(ofRandom(k_max)); };
			
			vector<int> array(k_size);
			
			generate(begin(array),
					 end(array),
					 our_generator);
			
			sort(begin(array),
				 end(array),
				 our_comparison);
			
			for (const auto &v: array)
				cout << v << endl;
		}
		
		{
			/*
			 http://ja.wikipedia.org/wiki/C%2B%2B11
			[]        //ラムダ関数外のどの変数も使うことができない。
			[x, &y]   //xはコピーされる。yは参照渡しされる。
			[&]       //すべての外部変数は、もし使われれば暗黙的に参照渡しされる。
			[=]       //すべての外部変数は、もし使われれば暗黙的にコピーされる。
			[&, x]    //xは明示的にコピーされる。その他の変数は参照渡しされる。
			[=, &z]   //zは明示的に参照渡しされる。その他の変数はコピーされる。
			 */
			
			auto dump = [](int a, int b) { cout << "a:" << a << ", b:" << b << endl; };
			
			{
				cout << "---" << endl;
				
				int v1 = 10, v2 = 20;
				
				dump(v1, v2); // 10, 20
				
				// すべての外部変数をコピーとして扱う
				// コピーした値を変更したい場合は mutable修飾
				[=]() mutable {
					v1 += 10;
					v2 += 10;
				}();
				dump(v1, v2); // 10, 20
			}
			{
				cout << "---" << endl;
				
				int v1 = 10, v2 = 20;
				
				dump(v1, v2); // 10, 20
				
				// すべての外部変数を参照として扱う
				[&]() {
					v1 += 10;
					v2 += 10;
				}();
				dump(v1, v2); // 20, 30
			}
			{
				cout << "---" << endl;
				
				int v1 = 10, v2 = 20;
				
				dump(v1, v2); // 10, 20
				
				// v1だけコピー、その他は参照
				[&, v1]() mutable {
					v1 += 10;
					v2 += 10;
				}();
				dump(v1, v2); // 10, 30
			}
		}
		
		{
			cout << "---" << endl;
			
			// ↓これは通らない。
			// 関数中から ofApp::hi() は見えない
			// [](){ hi(); }();
			
			// scopeとして this を渡すと通る
			[this](){ hi(); }();
			
		}
		
		ofExit(); // 今回はサンプル描画ナシ
	}
	
	void hi() {
		cout << "hi." << endl;
	}
};



#pragma mark -
#pragma mark main
int main(){
	ofSetupOpenGL(500, 500, OF_WINDOW);
	ofRunApp(new ofApp());
}
