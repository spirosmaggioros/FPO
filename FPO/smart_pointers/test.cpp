#include "polynomial_header.hpp"

int main(){
    string str;
    BST root;
    do{
        char c;
        cout << "1 : insert" << '\n';
        cout << "2 : contain check" << '\n';
        cout << "3 : get elements inorder" << '\n';
        cout << "4 : get elements preorder" << '\n';
        cout << "5 : get elements postorder" << '\n';
        cout << "6: evalueate f(x)" << '\n';
        cout << "7 : simplify" << '\n';
        cout << "8 : derivative" << '\n';
        cout << "9 : intergal" << '\n';
        cout << "w : add" << '\n';
        cout << "e : multiply" << '\n';
        cout << "Q : exit" << '\n';
        cin >> c;
        switch(c){
            case '1':{
                int a , b ,c;
                cout << "polynomial to be inserted,(3 values a/bx^c) :"; cin >> a >> b >> c;
                root.insert(a , b, c);
                break;
            }
            case '2':{
                int a , b, c;
                cout << "Check if f(X) contains a/bx^c , : "; cin >> a >> b >> c;
                bool check = root.contains(a , b, c);
                if(check){
                    cout << "True" << '\n';
                }
                else{
                    cout << "No" << '\n';
                }
                break;
            }
            case '3':{
                cout << "Elements inorder:" << '\n';
                vector<tuple<int , int , int> > v = root.get_elements_inorder();
                print_array(v); cout << '\n';
                break;
            }
            case '4':{
                cout << "Elements preorder:" << '\n';
                vector<tuple<int ,int , int> > v = root.get_elements_preorder();
                print_array(v); cout << '\n';
                break;
            }
            case '5':{
                cout << "Elements postorder:" << '\n';
                vector<tuple<int ,int , int> > v = root.get_elements_postorder();
                print_array(v); cout << '\n';
                break;
            }
            case '6':{
                float x;
                cout << "Evalueate f(x) for some x , : "; cin >> x;
                cout << "f(x) = " <<  root.evaluate(x) << '\n';
                break;
            }
            case '7':{
                cout << "f(x) has been simplified!" << '\n';
                root.simplify();
                break;
            }
            case '8':{
                int n;
                cout << "d^n(f(x))/dx^n , give the n , :" ; cin >> n;
                BST derivative = root.derivative(n);
                cout << "f^n(x) = ";
                vector<tuple<int ,int , int> > v = derivative.get_elements_inorder();
                print_array(v); cout << '\n';
                break;
            }
            case '9':{
                int n;
                cout << "[F(x)]^n , give the n , : "; cin  >> n;
                BST intergal = root.intergal(n);
                cout << "[F(x)]^n = ";
                vector<tuple<int , int , int> > v = intergal.get_elements_inorder(); cout << '\n';
                print_array(v);
                break;
            }
            case 'w':{
                int x;
                BST g;
                BST added;
                cout << "Values of the g(x) to be added to f(x) , give the number of insertions , : "; cin >> x;
                for(int i = 0; i<x; i++){
                    int a , b ,c;
                    cout << i + 1 << '\n';
                    cout << "a:"; cin >> a;
                    cout << "b:"; cin >> b;
                    cout << "c:"; cin >> c;
                    g.insert(a,b,c);
                }
                added = root._add(g);
                vector<tuple<int , int , int> > v = added.get_elements_inorder();
                print_array(v); cout << '\n';
                break;
            }
            case 'e':{
                int x;
                BST g;
                BST multiplied;
                cout << "Values of the g(x) to be multiplied to f(x) , give the number of insertions , : "; cin >> x;
                for(int i = 0; i<x; i++){
                    int a , b ,c;
                    cout << i + 1 << '\n';
                    cout << "a:"; cin >> a;
                    cout << "b:"; cin >> b;
                    cout << "c:"; cin >> c;
                    g.insert(a,b,c);
                }
                multiplied = root._multiply(g);
                vector<tuple<int , int , int> > v = multiplied.get_elements_inorder();
                print_array(v); cout << '\n';
                break;
            }
            case 'Q':{
                exit(0);
            }
            
        }
    }while(str != "END");


}
