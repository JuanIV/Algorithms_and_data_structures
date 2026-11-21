#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct MergeSortTree { //0-indexed
  int n;
  vector<vector<ll>> tree;

  MergeSortTree(const vector<ll> &arr) {
    n = arr.size();
    tree.resize(4 * n);
    if (n > 0) build(1, 0, n - 1, arr);
  }

  void build(int p, int l, int r, const vector<ll> &arr) {
    if (l == r) {
      tree[p].push_back(arr[l]);
      return;
    }
    int m = (l + r) / 2;
    build(2 * p, l, m, arr);
    build(2 * p + 1, m + 1, r, arr);
    merge(tree[2 * p].begin(), tree[2 * p].end(), tree[2 * p + 1].begin(),
          tree[2 * p + 1].end(), back_inserter(tree[p]));
  }

  // Cuenta los elementos de posiciones [ql, qr]
  // cuyos valores pertenecen a [low, up].
  ll query(int ql, int qr, ll low, ll up) {
    if (n == 0 || ql > qr || low > up) return 0;
    return query(1, 0, n - 1, ql, qr, low, up);
  }

  ll query(int p, int l, int r, int ql, int qr, ll low, ll up) {
    // Caso 1: intervalo completamente fuera.
    if (r < ql || qr < l) return 0;
    // Caso 2: intervalo completamente dentro.
    if (ql <= l && r <= qr) {
      const auto &v = tree[p];
      auto it1 = lower_bound(v.begin(), v.end(), low);
      auto it2 = upper_bound(v.begin(), v.end(), up);
      return it2 - it1;
    }
    // Caso 3: intervalo parcialmente dentro.
    int m = (l + r) / 2;
    return query(2 * p, l, m, ql, qr, low, up) +
           query(2 * p + 1, m + 1, r, ql, qr, low, up);
  }
};