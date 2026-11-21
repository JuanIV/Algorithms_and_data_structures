#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct PrefixSum1D {
  vector<ll> ps;

  PrefixSum1D(const vector<ll>& a) {
    int n = a.size();
    ps.assign(n + 1, 0);  // ps[0] = 0 como caso base
    for (int i = 0; i < n; i++) ps[i + 1] = ps[i] + a[i];
  }

  // Suma en [l, r] (0-indexed)
  ll query(int l, int r) { return ps[r + 1] - ps[l]; }
};

struct PrefixSum2D {
  // ps tiene tamano (n+1)*(m+1) para evitar casos especiales en los bordes.
  // ps[i][j] = suma del rectangulo (0,0)->(i-1,j-1) en el array original.
  // La fila/columna 0 actuan como caso base con valor 0.
  vector<vector<ll>> ps;
  int n, m;

  PrefixSum2D(const vector<vector<ll>>& a) {
    n = a.size();
    m = a[0].size();
    ps.assign(n + 1, vector<ll>(m + 1, 0));

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        ps[i][j] = a[i - 1][j - 1] + ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1];
  }

  // Suma del rectangulo (r1,c1)->(r2,c2) en 0-indexed
  ll query(int r1, int c1, int r2, int c2) {
    return ps[r2 + 1][c2 + 1] - ps[r1][c2 + 1] - ps[r2 + 1][c1] + ps[r1][c1];
  }
};