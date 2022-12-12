
#include <bits/stdc++.h>

using namespace std;

struct node{
    int coeff;
    int exponent;
    node *right , *left;
};

struct node_derivative{
    pair<int ,int> coeff;
    int exponent;
    node_derivative *right , *left;
};

void inorder(ostream & out , node_derivative *root){
    if(root){
        inorder(out , root -> left);
        out << root -> coeff.first << "/" << root -> coeff.second << "x^" << root -> exponent << " ";
        inorder(out , root -> right);
    }
}

void simplify(node_derivative *root){
    if(!root){return;}
    stack<node_derivative*> s;
    s.push(root);
    auto simplify = [&](int a , int b) -> pair<int , int>{
            int denom = __gcd(a , b);
            a /= denom;
            b /= denom;
            return {a,b};
        };
    while(!s.empty()){
        node_derivative *current = s.top();
        pair<int , int> temp = simplify(current -> coeff.first , current -> coeff.second);
        current -> coeff = temp;
        s.pop();
        if(current -> right){s.push(current -> right);}
        if(current -> left)s.push(current -> left);
    }
}

ostream & operator << (ostream & out , node_derivative *root){
    if(!root){out << "Empty!" << '\n'; return out;}
    simplify(root);
    inorder(out , root);
    return out;
}

node_derivative *new_node(const int & a , const int &b , const int &exponent){
    node_derivative *p = new node_derivative;
    p -> coeff = {a , b};
    p -> exponent = exponent;
    p -> right = p -> left = nullptr;
    return p;
    
}

node_derivative *insert_der(node_derivative *root , const int &a , const int &b ,const int &exponent){
    if(!root){
        return new_node(a , b , exponent);
    }
    else{
        if(root -> exponent < exponent){
          root -> right = insert_der(root -> right , a , b , exponent);
        }
        else if(root -> exponent > exponent){
            root -> left = insert_der(root -> left , a , b, exponent);
        }
        else{
            auto simplify = [&](int a , int b) -> pair<int , int>{
                int denom = __gcd(a , b);
                a /= denom;
                b /= denom;
                return {a,b};
            };
            pair<int , int> temp= simplify(root -> coeff.first + a , root -> coeff.second + b);    
            root -> coeff = temp; 
            return root;       
        }
    }
    return root;
}


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

//
node *node_derivative_to_node(node_derivative *root_derivative){
    if(!root_derivative){
        return nullptr;
    }
    node *head = nullptr;
    queue<node_derivative*> q;
    q.push(root_derivative);
    while(!q.empty()){
        node_derivative *current = q.front();
        int coeff = current -> coeff.first / current -> coeff.second;
        int exp = current -> exponent;
        head = insert(head , coeff , exp);
        if(current -> right){q.push(current -> right);}
        if(current -> left){q.push(current -> left);}
    }
    return head;
}
//need to change the types


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

node_derivative *intergal(node *root){
    node_derivative *p = nullptr;
    if(!root){return p;}
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        node *current = q.front();
        int coeff_a = current -> coeff;
        int coeff_b = current -> exponent + 1;
        int exp = current -> exponent + 1;
        p = insert_der(p , coeff_a , coeff_b , exp);
        q.pop();
        if(current -> right){q.push(current -> right);}
        if(current -> left){q.push(current -> left);}
    }
    return p;
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
