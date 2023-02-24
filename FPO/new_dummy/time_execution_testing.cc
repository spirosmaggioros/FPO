#include <bits/stdc++.h>
#include <chrono>
#include "a.hpp"

using namespace std;
using namespace std::chrono;

long double evaluate(vector<int> &d , const int &a){
    long double ans = 0;
    int size = d.size();
    for(int i = 0; i<size; i++){
        ans += d[i]*powl(a,i);
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

int main() {
    node *all_in_line = nullptr , *sparse = nullptr , *normal = nullptr;
    vector<int> v_in_line(10000 , 0) , v_sparse(100000 , 0);
    for(int i = 0; i<10000; i++){
        all_in_line = insert(all_in_line , i , i);
        v_in_line[i] = i;
    }

   for(int i = 0; i<100000; i += rand() % 99999 + 999){
       int temp = rand() % 100 + 1;
       sparse = insert(sparse , temp , i);
       v_sparse[i] = temp;
   }


   node *sparse2 = nullptr;
   vector<int> v_sparse_2(100000 , 0);
    for(int i = 0; i<100000; i += rand() % 9999 + 99){
        int temp = rand() % 100 + 1;
        sparse2 = insert(sparse2 , temp , i);
        v_sparse_2[i] = temp;
    }


   test_case_1(all_in_line);
   test_case_1(sparse);

   test_case_2(v_in_line);
   test_case_2(v_sparse);

   test_case_3(sparse, sparse2);
   test_case_4(v_sparse , v_sparse_2);
}
