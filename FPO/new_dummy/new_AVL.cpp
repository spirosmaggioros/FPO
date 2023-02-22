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

node *rightRotate(node *root) {
    node *t = root->left;
    node *u = t->right;
    t->right = root;
    root->left = u;
    return t;
}

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

//insertion O(logn)
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

//evalueate O(logn)
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

ostream & operator << (ostream &out , node *root){
    assert(root != nullptr);
    int counter = 0;
    level_order(root , counter , out);
    return out;
}

int main() {
    node *root = nullptr;
    root = insert(root , 2 ,2);
    root = insert(root , 1 , 1);
    root = insert(root , 5 , 3);
    root = insert(root , 6 , 4);
    root = insert(root , 7 , 5);
    cout << root << '\n';
    cout << evaluate(root , 1) << '\n';
}
