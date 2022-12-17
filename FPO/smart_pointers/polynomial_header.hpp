#include <bits/stdc++.h>

using namespace std;

typedef complex<double> cd;

class BST{
private:
	struct BST_node{
		pair<int , int> coeff;
		int exponent;
		unique_ptr<BST_node> left;
		unique_ptr<BST_node> right;

		explicit BST_node(const int &a ,const int &b ,const int &c){
			coeff = {a,b};
			exponent = c;
			left = nullptr;
			right = nullptr;
		}
	};
	unique_ptr<BST_node> root;
	size_t size = 0;

	bool insert(unique_ptr<BST_node> &node , const int &a , const int &b , const int &c){
		if(node == root && !root){
			root = unique_ptr<BST_node>(new BST_node(a , b ,c));
			return true;
		}
		if(c < node -> exponent){
			if(!node -> left){
				node -> left = unique_ptr<BST_node>(new BST_node(a , b ,c));
				return true;
			}
			else{
				return insert(node -> left , a , b , c);
			}
		}
		else if(c > node -> exponent){
			if(!node -> right){
				node -> right = unique_ptr<BST_node>(new BST_node(a , b, c));
				return true;
			}
			else{
				return insert(node -> right , a , b, c);
			}
		}
		else if(c == node -> exponent){
			pair<int , int> temp = make_pair((a*node -> coeff.second) + (node -> coeff.first*b) , b*node -> coeff.second);
			node -> coeff = temp;
			return true;
		}
		else{
			return false;
		}
	}

	bool contains(unique_ptr<BST_node> &node , const int &a ,const int &b , const int &c){
		if(!node){return false;}
		if(c < node -> exponent){
			return contains(node  -> left , a , b , c);
		}
		else if(c > node -> exponent){
			return contains(node -> right , a , b, c);
		}
		else{
			if(node -> coeff.first == a && node -> coeff.second == b){
				return true;
			}
		}
		return false;
	}

	void _preorder(function<void(tuple<int ,int , int>)> callback, unique_ptr<BST_node> &node){
		if(!node){return;}
		callback(make_tuple(node -> coeff.first , node -> coeff.second , node -> exponent));
		_preorder(callback , node);
		_preorder(callback, node);
	}

	void _postorder(function<void(tuple<int , int , int>)> callback , unique_ptr<BST_node> &node){
		if(!node){return;}
		_postorder(callback , node -> left);
		_postorder(callback , node -> right);
		callback(make_tuple(node -> coeff.first , node -> coeff.second , node -> exponent));
	}

	void _inorder(ostream &out, unique_ptr<BST_node> &node){
		if(!node){return;}
		_inorder(out, node -> left);
		if(node -> coeff.second != 1){
			out << node -> coeff.first << "/" << node -> coeff.second << "x^" << node -> exponent << " ";
		}
		else{
			out << node -> coeff.first << "x^" << node -> exponent << " ";
		}
		_inorder(out , node -> right);
	}

	void _inorder(function<void(tuple<int , int , int>)> callback , unique_ptr<BST_node> &node){
		if(!node){return;}
		_inorder(callback , node -> left);
		callback(make_tuple(node -> coeff.first , node -> coeff.second , node -> exponent));
		_inorder(callback , node -> right);
	}

	long double evaluate(unique_ptr<BST_node> &node , const double &d ){
		if(!root){return 0.0;}
		long double ans = 0;
		stack<const unique_ptr<BST_node> *> s;
		s.push(&node);
		while(!s.empty()){
			auto current = s.top();
			ans += (float(float((*current) -> coeff.first) / float((*current) -> coeff.second)) * powf(d , (*current) -> exponent));
			s.pop();
			if((*current) -> right){s.push(&((*current)-> right));}
			if((*current) -> left){s.push(&((*current) -> left));}
		}
		return ans;
	}

	void simplify(unique_ptr<BST_node> &node){
		if(!node){return;}
		stack<const unique_ptr<BST_node> *> s;
		s.push(&node);

		auto it = [&](int a , int b) -> pair<int ,int>{
			int denom = __gcd(a,b);
			a /= denom;
			b /= denom;
			return {a,b};
		};
		while(!s.empty()){
			auto current = s.top();
			pair<int ,int> temp = it((*current) -> coeff.first , (*current) -> coeff.second);
			(*current) -> coeff = temp;
			s.pop();
			if((*current) -> right){s.push(&(*current) -> right);}
			if((*current) -> left){s.push(&(*current) -> left);}
		}
		return;
	}

	BST derivative(unique_ptr<BST_node> &node, int times){
		BST new_node;
		if(!node){return new_node;}
		stack<const unique_ptr<BST_node> *> s;
		s.push(&node);
		while(!s.empty()){
			auto current = s.top();
			int exponent = (*current) -> exponent - 1;
			int coeff_first =(*current) -> coeff.first *  (*current) -> exponent;
			int coeff_second = (*current) -> coeff.second;
			new_node.insert(coeff_first , coeff_second , exponent);
			s.pop();
			if((*current) -> right){s.push(&(*current) -> right);}
			if((*current) -> left){s.push(&(*current) -> left);}
		}
		return new_node;
	}

	BST intergal(unique_ptr<BST_node> &node , int times){
		BST new_node;
		if(!node){return new_node;}
		stack<const unique_ptr<BST_node> *> s;
		s.push(&node);
		while(!s.empty()){
			auto current = s.top();
			int exponent = (*current) -> exponent + 1;
			int coeff_first = (*current) -> coeff.first;
			int coeff_second = (*current) -> coeff.second * ((*current) -> exponent + 1);
			new_node.insert(coeff_first , coeff_second , exponent);
			s.pop();
			if((*current) -> right){s.push(&(*current) -> right);}
			if((*current) -> left){s.push(&(*current) -> left);}
		}
		return new_node;
	}

	BST _add(BST &node1 , BST &node2){
		BST tree;
		if((!node1.root && !node2.root) || (node1.root && !node2.root)){
			return tree; 
		}
		stack<const unique_ptr<BST_node> *> s;
		s.push(&node1.root);
		while(!s.empty()){
			auto *current = s.top();
			bool res = tree.insert((*current) -> coeff.first , (*current) -> coeff.second , (*current) -> exponent);
			s.pop();
			if((*current) -> right){s.push(&(*current) -> right);}
			if((*current) -> left){s.push(&(*current) -> left);}
		}

		stack<const unique_ptr<BST_node> *> p;
		p.push(&node2.root);
		while(!p.empty()){
			auto *current = p.top();
			bool res = tree.insert((*current) -> coeff.first , (*current) -> coeff.second , (*current) -> exponent);
			p.pop();
			if((*current) -> right){p.push(&(*current) -> right);}
			if((*current) -> left){p.push(&(*current) -> left);}
		}
		return tree;
	}

	BST _multiply(BST &node1 , BST &node2){
		BST tree;
		if(!node1.root || !node2.root){return tree;}
		stack<const unique_ptr<BST_node> *> s;
		s.push(&node1.root);
		vector<tuple<int , int , int> > list_node;
		while(!s.empty()){
			auto *current = s.top();
			list_node.push_back(make_tuple((*current) -> coeff.first , (*current) -> coeff.second , (*current) -> exponent));
			s.pop();
			if((*current) -> right){s.push(&(*current) -> right);}
			if((*current) -> left){s.push(&(*current) -> left);}
		}
		int n = list_node.size();
		for(int i = 0; i<n; i++){
			stack<const unique_ptr<BST_node> *> p;
			p.push(&node2.root);
			while(!p.empty()){
				auto *current = p.top();
				tree.insert(get<0>(list_node[i]) * (*current) -> coeff.first , get<1>(list_node[i]) * (*current) -> coeff.second , (*current) -> exponent + get<2>(list_node[i]));
				p.pop();
				if((*current) -> right){p.push(&(*current) -> right);}
				if((*current) -> left){p.push(&(*current) -> left);}
			}
		}
		return tree;
	}

public:
	BST(){
		root = nullptr;
		size = 0;
	}

	bool insert(const int &a , const int &b , const int &c){
		bool result = insert(root , a , b, c);
		if(result){size++;}
		return result;
	}

	bool contains(const int &a , const int &b , const int &c){
		return contains(root , a , b, c);
	}

	size_t size_of(){return size;}

	vector<tuple<int , int , int> > get_elements_inorder(){
		vector<tuple<int , int , int> > ans;
		_inorder([&](tuple<int ,int , int> callbacked) {ans.push_back(callbacked);}, root);
		return ans;
	}

	vector<tuple<int , int , int> > get_elements_preorder(){
		vector<tuple<int , int , int> > ans;
		_preorder([&](tuple<int ,int , int> callbacked) {ans.push_back(callbacked);}, root);
		return ans;
	}

	vector<tuple<int , int , int> > get_elements_postorder(){
		vector<tuple<int , int , int> > ans;
		_postorder([&](tuple<int ,int , int> callbacked) {ans.push_back(callbacked);}, root);
		return ans;
	} 

	float evaluate(const float &d){
		if(!root){return 0.0;}
		float ans = evaluate(root , d);
		return ans;
	}

	void simplify(){
		if(!root){return;}
		return simplify(root);
	}

	BST derivative(int times){
		return derivative(root , times);
	}

	BST intergal(int times){
		return intergal(root , times);
	}

	BST _add(BST &tree1){
		return _add(*this , tree1);
	}
	
	BST _multiply(BST &tree1){
		return _multiply(*this , tree1);
	}

};

void print_array(vector<tuple<int ,int ,int> > &_inserted){
	if(_inserted.empty()){
		cout << "Empty!" << '\n';
		return;
	}
	for(auto & x : _inserted){
		cout << get<0>(x) << "/" << get<1>(x) << "x^" << get<2>(x) << " ";
  	}
	return;
}
