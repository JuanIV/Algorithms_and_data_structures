#include <bits/stdc++.h>
using namespace std;
#define ll long long

// Neutro de combine:  suma→0  min→LLONG_MAX  max→LLONG_MIN
const ll NEU = 0;

// Combina dos nodos:  suma→a+b  min→min(a,b)  max→max(a,b)
ll combine(ll a, ll b) { return a + b; }

struct SegTree {
  int n;
  vector<ll> t;

  SegTree(const vector<ll>& a) : n(a.size()), t(4 * a.size(), NEU) {
    build(a, 1, 0, n - 1);
  }

  void build(const vector<ll>& a, int v, int l, int r) {
    if (l == r) {
      t[v] = a[l];
      return;
    }
    int m = (l + r) / 2;
    build(a, 2 * v, l, m);
    build(a, 2 * v + 1, m + 1, r);
    t[v] = combine(t[2 * v], t[2 * v + 1]);
  }

  // Actualización: asigna val en idx
  void update(int idx, ll val, int v = 1, int l = 0, int r = -1) {
    if (r == -1) r = n - 1;
    if (l == r) {
      t[v] = val;
      return;
    }
    int m = (l + r) / 2;
    if (idx <= m)
      update(idx, val, 2 * v, l, m);
    else
      update(idx, val, 2 * v + 1, m + 1, r);
    t[v] = combine(t[2 * v], t[2 * v + 1]);
  }

  // Query en rango [ql, qr]
  ll query(int ql, int qr, int v = 1, int l = 0, int r = -1) {
    if (r == -1) r = n - 1;
    if (ql > r || qr < l) return NEU;
    if (ql <= l && r <= qr) return t[v];
    int m = (l + r) / 2;
    return combine(query(ql, qr, 2 * v, l, m), query(ql, qr, 2 * v + 1, m + 1, r));
  }
};