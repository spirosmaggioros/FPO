#include <bits/stdc++.h>

using namespace std;

class polynomial{
public:
	polynomial(){}
	polynomial operator = (const polynomial &a){
		polynomial ans;
		ans.l = a.l;
		return ans;
	}
	void append(const int &a , const int &b){
		if(l.empty()){
			l.push_back({a,b});
			return;
		}
		for(auto & x : l){
			if(x.second == b){
				x.first += a;
				return;
			}
		}
		l.push_back({a,b});
	}

	double evaluate(const double &a){
		double ans = 0.0;
		for(auto & x : l){
			ans += x.first * pow(a , x.second);
		}
		return ans;
	}
	
	polynomial add(polynomial &a , polynomial &b){
		polynomial ans = a;
		for(auto & x : b.l){
			ans.append(x.first , x.second);
		}
		return ans;
	}

	polynomial multiply(polynomial &a , polynomial &c){
		polynomial ans;
		for(auto & x : a.l){
			for(auto &y : c.l){
				ans.append(x.first * y.first , x.second + y.second);
			}
		}
		return ans;
	}

	void print(polynomial &a){
		for(auto & x : a.l){
			cout << x.first << "x^" << x.second << " ";
		}
		cout << '\n';
	}
private:
	list<pair<int ,int> > l;
};


int main(){
	polynomial a;
	int w; cin >> w;
	while(w--){
		int b , c; cin >> b >> c;
		a.append(b , c);
	}
	polynomial p;
	cin >> w;
	while(w--){
		int b , c; cin >> b >> c;
		p.append(b, c);
	}
	cout << a.evaluate(2) << '\n';	
}
