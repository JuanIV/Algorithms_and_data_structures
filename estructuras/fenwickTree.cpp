#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct FenwickTree {
  vector<ll> bit; int n;

  //Constructor
  FenwickTree(int N) : n(N+1), bit(N+1,0) {}

  //Constructor a partir de array
  FenwickTree(vector<ll> ar) {
    this->bit = ar;
    this->n = ar.size();

    for(int i = 1; i < this->bit.size(); i++){
      int p = i + (i & -i);
      if(p < this->bit.size()){
        this->bit[p] = this->bit[p] + this->bit[i];
      }
    }
  }

  //Funcion anadir valor
  void add(int idx, ll delta) {
    for(; idx<n; idx += idx & -idx) bit[idx]+=delta;
  }

  //Funcion obtener query de 0 a r
  ll sum(int r) { // [0, r]
    ll ret=0;
    for(; r>0; r -= r & -r) ret+=bit[r];
    return ret;
  }

  //Funcion obtener query de l a r
  ll sum(int l, int r) { return sum(r)-sum(l-1); }
};
