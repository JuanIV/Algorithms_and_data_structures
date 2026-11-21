#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct PersistentSegmentTree {
  struct Node {
    int left = 0, right = 0;
    int cnt = 0;
  };

  int n, sigma;
  vector<ll> vals;
  vector<Node> st;
  vector<int> root;

  PersistentSegmentTree(const vector<ll>& a) {
    n = a.size();

    vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    sigma = vals.size();

    // El nodo 0 representa un árbol vacío.
    st.push_back({});
    root.resize(n + 1, 0);

    for (int i = 0; i < n; i++) {
      int pos = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
      root[i + 1] = update(root[i], 0, sigma - 1, pos);
    }
  }

  // Crea una nueva versión copiando únicamente el camino modificado.
  int update(int prev, int l, int r, int pos) {
    int cur = st.size();
    st.push_back(st[prev]);
    st[cur].cnt++;

    if (l == r) return cur;
    int m = (l + r) / 2;
    if (pos <= m)
      st[cur].left = update(st[prev].left, l, m, pos);
    else
      st[cur].right = update(st[prev].right, m + 1, r, pos);
    return cur;
  }

  // Cuenta elementos con coordenada en [0, k).
  // La consulta utiliza la diferencia entre dos versiones.
  int queryPrefix(int u, int v, int l, int r, int k) const {
    if (k <= l) return 0;
    if (r < k) return st[u].cnt - st[v].cnt;

    int m = (l + r) / 2;

    return queryPrefix(st[u].left, st[v].left, l, m, k) +
           queryPrefix(st[u].right, st[v].right, m + 1, r, k);
  }

  // Cuenta valores de posiciones [l, r] que pertenecen a [low, up].
  int count(int l, int r, ll low, ll up) const {
    if (n == 0 || l > r || low > up) return 0;

    int lo = lower_bound(vals.begin(), vals.end(), low) - vals.begin();
    int hi = upper_bound(vals.begin(), vals.end(), up) - vals.begin();

    return queryPrefix(root[r + 1], root[l], 0, sigma - 1, hi) -
           queryPrefix(root[r + 1], root[l], 0, sigma - 1, lo);
  }

  // Devuelve el k-esimo menor de las posiciones [l, r].
  // k es 1-indexado.
  ll kth(int l, int r, int k) const {
    int u = root[r + 1];
    int v = root[l];

    int left = 0, right = sigma - 1;

    while (left < right) {
      int m = (left + right) / 2;

      int cntLeft = st[st[u].left].cnt - st[st[v].left].cnt;

      if (k <= cntLeft) {
        u = st[u].left;
        v = st[v].left;
        right = m;
      } else {
        k -= cntLeft;
        u = st[u].right;
        v = st[v].right;
        left = m + 1;
      }
    }

    return vals[left];
  }
};
