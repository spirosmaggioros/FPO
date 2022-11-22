#include "polynomial.hpp"

using namespace std;

int main (){
    cin.tie(0);
    ios::sync_with_stdio(0);
    node *root = nullptr;
    int a; cin >> a;
    while(a--){
        int coeff , expon; cin >> coeff >> expon;
        root = insert(root , coeff , expon);
    }
    cout << root << '\n';
    int times; cin >> times;
    node *root_timerd_derivative = derivative(root , times);
    cout << find_min_max(root , -100 , 100 ) << '\n';
    node *root3 = add__(root , root_timerd_derivative);
    cout << root3 << '\n';
    cout << multiply__(root , root_timerd_derivative) << '\n';
    return 0;
}
