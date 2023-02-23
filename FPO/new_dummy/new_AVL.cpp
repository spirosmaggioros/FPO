#include <bits/stdc++.h>

using namespace std;

typedef struct node {
    int coeff;
    int expon;
    int height;
    struct node *left;
    struct node *right;
} node;

node *createNode(const int &a , const int &b) {
    node *nn = new node();
    nn -> coeff = a;
    nn ->  expon = b;
    nn->height = 0;
    nn->left = nullptr;
    nn->right = nullptr;
    return nn;
}

int height(node *root) {
    if (root == nullptr)
        return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

int getBalance(node *root) { return height(root->left) - height(root->right); }

//rotations in O(1)
node *rightRotate(node *root) {
    node *t = root->left;
    node *u = t->right;
    t->right = root;
    root->left = u;
    return t;
}

//rotarions in O(1)
node *leftRotate(node *root) {
    node *t = root->right;
    node *u = t->left;
    t->left = root;
    root->right = u;
    return t;
}

node *minValue(node *root) {
    if (root->left == NULL)
        return root;
    return minValue(root->left);
}

//insertion O(logd)
node *insert(node *root, const int &a , const int &b) {
    node *nn = createNode(a, b);
    if (root == nullptr)
        return nn;
    if (b < root->expon) {
        root->left = insert(root->left, a, b);
    }
    else if (b > root->expon){
        root->right = insert(root->right, a, b);
    }
    else {
        root->coeff += a;
        return root;
    }
    int w = getBalance(root);
    if (w > 1) {
        if (getBalance(root->left) < 0)
            root->left = leftRotate(root->left);  // Left-Right Case
        return rightRotate(root);                 // Left-Left Case
    } else if (w < -1) {
        if (getBalance(root->right) > 0)
            root->right = rightRotate(root->right);  // Right-Left Case
        return leftRotate(root);                     // Right-Right Case
    }
    return root;
}

//level order O(logd)
void level_order(node *root , int &counter , ostream &out){
    if(root){
        level_order(root -> left , counter , out);
        if(counter == 0){out << root -> coeff << "x^" << root -> expon;counter++;}
        else{
            if(root -> coeff > 0){
                if(root -> coeff == 1){
                    out << " + x^" << root -> expon;
                }
                else {
                    out << " + " << root->coeff << "x^" << root->expon;
                }
            }
            else if(root -> coeff < 0) {
                if (root->coeff == -1) {
                    out << " - x^" << root->expon;
                }
                else {
                    out << " - " << abs(root->coeff) << "x^" << root->expon;
                }
            }
        }
        level_order(root -> right ,counter, out);
    }
}

//evaluate O(logd)
void evaluate_helper(node *root , const int &a , double &ans){
    if(root){
        evaluate_helper(root -> left , a , ans);
        ans += root -> coeff * (powf(a , root -> expon));
        evaluate_helper(root -> right , a , ans);
    }
}

double evaluate(node *root , const int &a){
    assert(root != nullptr);
    double ans = 0;
    evaluate_helper(root , a , ans);
    return ans;
}

void __inorder(function<void(node*)> callback , node *root){
    if(root){
        __inorder(callback , root -> left);
        callback(root);
        __inorder(callback , root -> right);
    }
}

//adding O(log^2(d))
node *add(node *root1 , node *root2){
    if(!root1 && root2){return root2;}
    if(!root2 && root1){return root1;}
    if(!root1 && !root2){return nullptr;}
    node *temp = root1;
    __inorder([&](node* callbacked){temp = insert(temp , callbacked -> coeff , callbacked -> expon);}, root2);
    return temp;
}


//substraction O(log^2(d))
node *substract(node *root1 , node *root2){
    if(!root1 && root2){return root2;}
    if(!root2 && root1){return root1;}
    if(!root1 && !root2){return nullptr;}
    node *temp = root1;
    __inorder([&](node *callbacked){temp = insert(temp , -callbacked -> coeff , callbacked -> expon);} , root2);
    return temp;
}


//multiplication O(d^2logd)
node *multiply(node *root1 , node *root2){
    if(!root1 || !root2){return nullptr;}
    node *ans = nullptr;
    stack<node*> s;
    s.push(root1);
    while(!s.empty()){
        auto current = s.top();
        s.pop();
        __inorder([&](node *callbacked){ans = insert(ans , callbacked -> coeff * current -> coeff , callbacked -> expon + current -> expon);} , root2);
        if(current -> right){s.push(current -> right);}
        if(current -> left){s.push(current -> left);}
    }
    return ans;
}

ostream & operator << (ostream &out , node *root){
    assert(root != nullptr);
    int counter = 0;
    level_order(root , counter , out);
    return out;
}

int main() {
    node *root1 = nullptr , *root2 = nullptr;
    root1 = insert(root1 , 1 , 2);
    root1 = insert(root1 , 1 , 1);

    root2 = insert(root2 , 1 , 3);
    root2 = insert(root2 , 3 , 2);

    node *root3 = multiply(root1 , root2);
    cout << root3 << '\n';
}
