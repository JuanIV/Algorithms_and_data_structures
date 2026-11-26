#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct FenwickTree2D {
  int n, m;
  vector<vector<ll>> bit;  // bit[i][j], indices 1-indexed internamente

  // Constructor vacio (todo a 0)
  FenwickTree2D(int n, int m) : n(n), m(m), bit(n + 1, vector<ll>(m + 1, 0)) {}

  // Constructor a partir de matriz en O(n*m)
  FenwickTree2D(const vector<vector<ll>>& a)
      : FenwickTree2D(a.size(), a[0].size()) {
    for (int i = 1; i <= n; i++)  // 1) construir cada fila como Fenwick 1D
      for (int j = 1; j <= m; j++) {
        bit[i][j] += a[i - 1][j - 1];
        int pj = j + (j & -j);
        if (pj <= m) bit[i][pj] += bit[i][j];
      }
    for (int i = 1; i <= n; i++) {  // 2) propagar filas completas al padre
      int pi = i + (i & -i);
      if (pi <= n)
        for (int j = 1; j <= m; j++) bit[pi][j] += bit[i][j];
    }
  }

  // Anadir delta en el punto (x, y) (0-indexed)
  void add(int x, int y, ll delta) {
    for (int i = x + 1; i <= n; i += i & -i)
      for (int j = y + 1; j <= m; j += j & -j) bit[i][j] += delta;
  }

  // Suma del rectangulo (0,0)->(x,y) (0-indexed). Con x o y = -1 devuelve 0
  ll sum(int x, int y) {
    ll ret = 0;
    for (int i = x + 1; i > 0; i -= i & -i)
      for (int j = y + 1; j > 0; j -= j & -j) ret += bit[i][j];
    return ret;
  }

  // Suma del rectangulo (x1,y1)->(x2,y2) (0-indexed)
  ll sum(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) +
           sum(x1 - 1, y1 - 1);
  }
};