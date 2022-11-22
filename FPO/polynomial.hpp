#include <bits/stdc++.h>

using namespace std;

struct node{
    int coeff;
    int exponent;
    node *right , *left;
};

void inorder(ostream &out  , node *root){
    if(root){
        inorder(out , root -> left);
        out << root -> coeff << "x^" << root -> exponent << " ";
        inorder(out , root -> right);
    }
}

ostream & operator <<  (ostream &out , node *root){
    if(!root){out << "Empty"; return out;}
    inorder(out , root);
    return out;
}

node *new_node(const int &coefficient , const int &exponent){
	node*p = new node;
	p -> coeff = coefficient;
	p -> exponent = exponent;
	p -> right = p -> left = nullptr;
	return p;
}

node *insert(node *root , const int &coefficient , const int &exponent){
    if(!root){
        return new_node(coefficient , exponent);
    }
    else{
        if(root -> exponent < exponent){
            root -> right = insert(root -> right , coefficient , exponent);
        }
        else if(root -> exponent > exponent){
            root -> left = insert(root -> left , coefficient , exponent);
        }
        else{
            root -> coeff += coefficient;
            return root;
        }
    }
    return root;
}


float evaluate(node *root , const double &d){
    if(!root){return 0.0;}
    stack<node*> s;
    float sum = 0;
    s.push(root);
    while(!s.empty()){
        node *current = s.top();
        sum += current -> coeff * (powf(d,current -> exponent));
        s.pop();
        if(current -> right){s.push(current -> right);}
        if(current -> left){s.push(current -> right);}
    }
    return sum;
}

node *derivative_helper(node *root){
	node *p = nullptr;
	if(!root){return root;}
	queue<node*> q;
	q.push(root);
	while(!q.empty()){
		node *current = q.front();
		int coeff = current -> coeff * current -> exponent;
		int exp = current -> exponent - 1;
		p = insert(p , coeff , exp);
		q.pop();
		if(current -> right){q.push(current -> right);}
		if(current -> left){q.push(current -> left);}
	}
	return p;
}

node *derivative(node *root , int &times){
    node *temp = root;
    while(times--){
        temp = derivative_helper(temp);
    }
    return temp;
}

string find_min_max(node *root ,const int &a ,const int &b){
	int mini = min(a, b);
	int maxi = max(a, b);
	set<float> evaluate_ans; 
	for(int i = mini; i <= maxi; i++){
		evaluate_ans.insert(evaluate(root , i));
	}
	string first = to_string(*evaluate_ans.begin());
    set<float>::iterator it = evaluate_ans.end();
    it--;
	string last = to_string(*it);
	return "Max , : " + last + " Min , : " + first;
}

node* add__(node *root1 , node *root2){
	if((!root1 && !root2) || (root1 && !root2)){
		return root1;
	}
	else if(!root1 && root2){return root2;}
	node *root = nullptr;
	stack<node*> s;
	s.push(root1);
	while(!s.empty()){
		node *current = s.top();
		root = insert(root , current -> coeff , current -> exponent);
		s.pop();
		if(current -> right){s.push(current -> right);}
		if(current -> left){s.push(current -> left);}
	}
	stack<node*> p;
	s.push(root2);
	while(!s.empty()){
		node *current = s.top();
		root = insert(root , current -> coeff , current -> exponent);
		s.pop();
		if(current -> right){s.push(current -> right);}
		if(current -> left){s.push(current -> left);}
	}
	return root;
}

node *multiply__(node *root1 , node *root2){
	if(!root1 || !root2){return nullptr;}
	node *root = nullptr;
	vector<pair<int , int> > list_node;
	stack<node*> s;
	s.push(root1);
	while(!s.empty()){
		node *current = s.top();
		list_node.push_back(make_pair(current -> coeff , current -> exponent));
		s.pop();
		if(current -> left){s.push(current -> left);}
		if(current -> right){s.push(current -> right);}
	}
	vector<pair<int , int > > ans;
	for(int i = 0; i<list_node.size(); i++){
		stack<node*> p;
		p.push(root2);
		while(!p.empty()){
			node *current = p.top();
			ans.push_back(make_pair(list_node[i].first * current -> coeff , list_node[i].second + current -> exponent));
			p.pop();
			if(current -> left){p.push(current -> left);}
			if(current -> right){p.push(current -> right);}
		}
	}
	for(const auto & x : ans){
		root = insert(root , x.first , x.second);
	}
	return root;
}
