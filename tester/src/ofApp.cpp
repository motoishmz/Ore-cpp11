#include "ofMain.h"

// 昔JavaScriptで書いてたfunctional programmingテストを移植するテスト
// https://gist.github.com/motoishmz/8176963

namespace op {
	
	template <typename T>
	static T inc (T t) {
		return t + 1;
	}
	
	template <typename T>
	static T dec (T t) {
		return t - T(1);
	}
	
	template <typename T>
	static T doubly (T t) {
		return t + t;
	}
	
	template <typename T, typename S>
	static auto sum (T t, S s)
	-> decltype(t + s) {
		return t + s;
	}
}

namespace pred {
	static bool isEven(int i) {
		return i%2 == 0;
	}
	
	static bool isOdd(int i) {
		return i%2 == 1;
	}
	
	static bool isOverground(ofVec3f pos) {
		return pos.y > 0;
	}
}


class ofApp : public ofBaseApp
{
	
#pragma mark -
#pragma mark shortcuts
	
	template <typename Collection>
	void dump(Collection col) {
		
		for (const auto &c: col) {
			cout << c << ", ";
		}
		cout << endl << "---" << endl;
	}
	
	template <typename Value>
	void cat(Value val) {
		cout << val;
		cout << endl << "---" << endl;
	}
	
	template <typename Operation, typename Collection>
	void for_each(Collection col, Operation op) {
		std::for_each(col.begin(),
					  col.end(),
					  op);
	}
	
#pragma mark -
#pragma mark functional
	
	template <typename Operation, typename Collection>
	Collection map(Operation op, Collection col) {
		transform(col.begin(),
				  col.end(),
				  col.begin(),
				  op);
		
		return col;
	}
	
	template <typename Operation, typename T, typename Collection>
	T reduce(Operation op, T init, Collection col) {
		
		/* [保留]
		 return accumulate(begin(col),
		 end(col),
		 op);
		 */
		
		T acc = init;
		
		for (auto &v: col) {
			acc = op(acc, v);
		}
		
		return acc;
	}
	
	template <typename Predicate, typename Collection>
	Collection filterNot(Predicate pred, Collection col) {
		
		auto iter = remove_if(begin(col),
							  end(col),
							  pred);
		
		col.erase(iter, end(col));
		
		return col;
	}
	
	template <typename Predicate, typename Collection>
	Collection filter(Predicate pred, Collection col) {
		
		return filterNot([pred]
						 (typename Collection::value_type i) {
							 return !pred(i);
						 }, col);
	}
	
	template <typename F1, typename F2>
	auto compose(F1 f, F2 g)
	-> function< int(int) > {
		// intで決め打ち。。
		// 本当はなんでも受け取れるようにしたい。
		// c++14なら auto ... で解決
		// http://stackoverflow.com/questions/19071268/function-composition-in-c-c11
		// https://functionalcpp.wordpress.com/2013/08/09/function-composition/
		// http://rosettacode.org/wiki/Function_composition#C.2B.2B
		
		return [=](int x) { return f( g(x) ); };
	}
	
	template <typename T>
	T identity(T x) {
		return x;
	}
	
public:
	
	void setup() {
		
		vector<int> data = { 1, 2, 3, 4, 5 };
		
		cat( compose(op::inc<int>, op::doubly<int>)(10) ); // 21
		cat( compose(op::doubly<int>, op::inc<int>)(10) ); // 22
		cat( reduce(op::sum<int, int>, 0, data) ); // 15
		cat( reduce(op::sum<int, int>, 10, data) ); // 25
		
		dump( filter(pred::isOdd, data) ); // 1, 3, 5,
		dump( filter(pred::isEven, data) ); // 2, 4,
		dump( map(op::inc<int>, data) ); // 2, 3, 4, 5, 6,
		dump( map(op::doubly<int>, map(op::dec<int>, data)) ); // 0, 2, 4, 6, 8,
		dump( map(op::doubly<int>, filter(pred::isOdd, data)) ); // 2, 6, 10,
		
		
		vector<ofVec3f> positions = { ofVec3f(-100), ofVec3f::one(), ofVec3f(100) };
		
		// cat( compose(op::doubly<ofVec3f>, op::inc<ofVec3f>)(ofVec3f::one()) ); // compose( ... ) をintで決め打ちしてるので出来ない。。
		cat( reduce(op::sum<ofVec3f, ofVec3f>, ofVec3f::zero(), positions) ); // 1, 1, 1
		dump( filter(pred::isOverground, positions) ); // 1, 1, 1, 100, 100, 100,
		dump( map(op::doubly<ofVec3f>, positions) ); // -200, -200, -200, 2, 2, 2, 200, 200, 200,
		
		ofExit(); // 今回もサンプル描画ナシ
	}
};



#pragma mark -
#pragma mark main
int main(){
	ofSetupOpenGL(500, 500, OF_WINDOW);
	ofRunApp(new ofApp());
}
