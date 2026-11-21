#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct SparseTable {
  // Layout table[k][i]: nivel en fila exterior, posición en interior
  // acceso secuencial durante construcción Y durante query
  vector<vector<ll>> table;
  vector<int> lg;
  int n;

  SparseTable(const vector<ll>& a) {
    n = a.size();

    // Precomputar logaritmos
    lg.resize(n + 1);
    lg[1] = 0;
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;

    int M = lg[n] + 1;

    // M niveles, cada uno con n posiciones
    // table[k] es un vector contiguo de n elementos
    table.assign(M, vector<ll>(n));

    // Caso base: bloques de tamaño 1
    table[0] = a;

    // Construcción: table[k][i] = min en [i, i + 2^k - 1]
    for (int k = 1; k < M; k++)
      for (int i = 0; i + (1 << k) <= n; i++)
        table[k][i] = min(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
  }

  // Query O(1): dos bloques solapados de tamaño 2^k cubren [l, r]
  ll query(int l, int r) {
    int k = lg[r - l + 1];
    return min(table[k][l], table[k][r - (1 << k) + 1]);
  }
};