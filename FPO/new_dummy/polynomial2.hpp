#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef complex<double> cd;

double min(double &a , double &b){
    if(a <= b){return a;}
    return b;
}

int fast_power(double &a , int n){
    int result = 1;
    while(n > 0){
        if(!(~n & 1)){
            result *= a;
        }
        n = n / 2;
        a *= a;
    }
    return result;
}

class FPO{
private:
    unordered_map<int , int> adj;
public:
    FPO(){}
    void push(const int &a , const int &b){
        adj[b] += a;
    }

    double evaluate(double &a){
        double sum = 0;
        for(auto & x : adj){
            //sum += x.second * (fast_power(a , x.first));
            sum += x.second * (powf(a , x.first));
        }
        return sum;
    }

    static FPO add(FPO &a , FPO &b){
        assert(!a.adj.empty() && !b.adj.empty());
        FPO ans;
        ans.adj = a.adj;
        for(auto & x : b.adj){
           ans.adj[x.first] += x.second;
        }
        return ans;
    }

    static FPO substract(FPO &a , FPO &b){
        assert(!a.adj.empty() && !b.adj.empty());
        FPO ans;
        ans.adj = a.adj;
        for(auto & x : b.adj){
            ans.adj[x.first] -= x.second;
        }
        return ans;
    }

    void print(ostream & out){
        int counter = 0;
        for(auto & x : adj){
            if(counter == 0){out << x.second << "x^" << x.first;}
            else{
                if(x.second > 0){
                    out << " + " << x.second << "x^" << x.first;
                }
                else if(x.second < 0){
                    out << " - " << abs(x.second) << "x^" << x.first;
                }
            }
            counter++;
        }
    }

    string find_min_max(const int &a , const int &b){
        assert(a <= b);
        double minim = INT_MAX , maxim = INT_MIN;
        for(double i = a; i<=b; i += 0.1){
            minim = min(minim , evaluate(i));
            maxim = max(maxim , evaluate(i));
        }
        return "Minimum value , :"  + to_string(minim) + " Maximum value :" +  to_string(maxim);
    }
};

ostream & operator << (ostream &out , FPO &a){
    a.print(out);
    return out;
}
