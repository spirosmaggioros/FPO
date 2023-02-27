#include <bits/stdc++.h>
#include <chrono>
#include "a.hpp"

using namespace std;
using namespace std::chrono;

int *multiply(int A[], int B[], int m, int n)
{
    int *prod = new int[m+n-1];

    for (int i = 0; i<m+n-1; i++)
        prod[i] = 0;

    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
            prod[i+j] += A[i]*B[j];
    }

    return prod;
}

long double evaluate(vector<int> &d , const int &a){
    long double ans = 0;
    int size = d.size();
    for(int i = 0; i<size; i++){
        ans += d[i]*powl(a,i);
    }
    return ans;
}

vector<int> mult(vector<int> &v1 , vector<int> &v2){
    int n = v1.size() , m = v2.size();
    vector<int> ans(m + n - 1 , 0);
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            ans[i + j] += v1[i]*v2[j];
        }
    }
    return ans;
}

vector<int> add(vector<int> &v1 , vector<int> &v2){
    vector<int> ans = v1;
    for(int i = 0; i<v2.size(); i++){
        ans[i] += v2[i];
    }
    return ans;
}

void test_case_1(node *root){
    auto start = high_resolution_clock::now();
    cout << evaluate(root , 1) << '\n';
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time to execute evaluation function with tree is , : " << duration.count() << " ms" << '\n';
}

void test_case_2(vector<int> &v){
    auto start  = high_resolution_clock::now();
    cout << evaluate(v , 1) << '\n';
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time to execute evaluation function with array is , : " << duration.count() << " ms" << '\n';
}


void test_case_3(node *root1 , node *root2){
    auto start = high_resolution_clock::now();
    node *added = add(root1 , root2);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time to execute add function with tree is , : " << duration.count() << " ms" << '\n';
}

void test_case_4(vector<int> &v1 , vector<int> &v2){
    auto start  = high_resolution_clock::now();
    vector<int> v = add(v1 , v2);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time to execute add function with array is , : " << duration.count() << " ms" << '\n';
}

void test_case_5(node *root1 , node *root2){
    auto start = high_resolution_clock::now();
    node *temp = multiply(root1 , root2);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time to execute multiply function with tree is , : " << duration.count() << " ms" << '\n';
}

void test_case_6(vector<int> &v1 , vector<int> &v2){
    auto start = high_resolution_clock::now();
    vector<int> ans = mult(v1 , v2);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time to execute multiply function with array is , : " << duration.count() << " ms" << '\n';
}

int main() {
    std::ofstream add_ls_to_normal_v , add_fs_to_normal_v;
    std::ofstream mult_fs_to_normal_tree , mult_ls_to_normal_v , mult_fs_to_normal_v;
    mult_fs_to_normal_tree.open("mult_fs_normal_tree.csv");
    for(int i = 1; i<=6354; i++){
        node *full = nullptr , *f_sparse = nullptr , *l_sparse = nullptr , *normal = nullptr;//f_sparse means full sparse , l_sparse means les sparse
        vector<int> full_v(i) , f_sparse_v(i) , l_sparse_v(i) , normal_v(i);//the same as before
        for(int j = 0; j<=i;){
            normal = insert(normal , rand() % 50 + 1 , j);
            j += rand() % 50 + 1;
        }

        for(int j = 0; j<=i; j++){
            f_sparse = insert(f_sparse , rand() % 50 + 1 , j);
            j += rand() % 1000 + 1;
        }

        auto start = high_resolution_clock::now();
        node *temp = multiply(f_sparse , normal);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);

        mult_fs_to_normal_tree << to_string(i) << "," << to_string(duration.count()) << "\n";

    }
    mult_fs_to_normal_tree.close();
}
