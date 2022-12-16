#include <bits/stdc++.h>

using namespace std;

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
			pair<int , int> temp = make_pair(a*node -> coeff.second + node -> coeff.first*b , b*node -> coeff.second);
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
			if(node -> coeff.first == a && node -> coeff.second == b){\
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

