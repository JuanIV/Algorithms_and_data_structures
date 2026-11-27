#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Neutro de combine: suma: 0
const ll NEU = 0;

// Combina dos nodos hijos
ll combine(ll a, ll b) { return a + b; }

struct SegmentTree {
  int n;
  vector<ll> tree;

  // Lazy para suma pendiente
  vector<ll> lazyAdd;

  // Lazy para asignacion pendiente
  vector<ll> lazySet;

  // Indica si hay una asignacion pendiente en el nodo
  vector<bool> hasSet;

  SegmentTree(const vector<ll>& a) {
    n = (int)a.size();
    tree.resize(4 * n);

    // Neutro de lazy: no hay actualizacion pendiente
    lazyAdd.assign(4 * n, 0);
    lazySet.assign(4 * n, 0);
    hasSet.assign(4 * n, false);

    if (n > 0) build(1, 0, n - 1, a);
  }

  void build(int node, int l, int r, const vector<ll>& a) {
    if (l == r) {
      tree[node] = a[l];
      return;
    }
    int mid = l + (r - l) / 2;
    build(node * 2, l, mid, a);
    build(node * 2 + 1, mid + 1, r, a);
    tree[node] = combine(tree[node * 2], tree[node * 2 + 1]);
  }

  // Como afecta "add" al valor de un nodo que cubre "len" elementos
  // suma: val + len*add
  void applyAdd(int node, int l, int r, ll val) {
    ll len = (ll)(r - l + 1);
    tree[node] += val * len;

    // Composicion de lazy:
    // si habia un set pendiente, el add se acumula sobre el set;
    // si no, se acumula sobre lazyAdd.
    if (hasSet[node]) {
      lazySet[node] += val;
    } else {
      lazyAdd[node] += val;
    }
  }

  // Asignacion: deja el nodo en val*len y descarta sumas pendientes
  void applySet(int node, int l, int r, ll val) {
    ll len = (ll)(r - l + 1);
    tree[node] = val * len;
    hasSet[node] = true;
    lazySet[node] = val;
    lazyAdd[node] = 0;
  }

  void push(int node, int l, int r) {
    if (l == r) return;
    int mid = l + (r - l) / 2;

    // Se propaga primero el set, porque tiene prioridad sobre el add
    if (hasSet[node]) {
      applySet(node * 2, l, mid, lazySet[node]);
      applySet(node * 2 + 1, mid + 1, r, lazySet[node]);
      hasSet[node] = false;
      lazySet[node] = 0;
    }

    // Despues se propaga la suma pendiente
    if (lazyAdd[node] != 0) {
      applyAdd(node * 2, l, mid, lazyAdd[node]);
      applyAdd(node * 2 + 1, mid + 1, r, lazyAdd[node]);
      lazyAdd[node] = 0;
    }
  }

  void updateAdd(int node, int l, int r, int ql, int qr, ll val) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
      applyAdd(node, l, r, val);
      return;
    }
    push(node, l, r);
    int mid = l + (r - l) / 2;
    updateAdd(node * 2, l, mid, ql, qr, val);
    updateAdd(node * 2 + 1, mid + 1, r, ql, qr, val);
    tree[node] = combine(tree[node * 2], tree[node * 2 + 1]);
  }

  void updateSet(int node, int l, int r, int ql, int qr, ll val) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
      applySet(node, l, r, val);
      return;
    }
    push(node, l, r);
    int mid = l + (r - l) / 2;
    updateSet(node * 2, l, mid, ql, qr, val);
    updateSet(node * 2 + 1, mid + 1, r, ql, qr, val);
    tree[node] = combine(tree[node * 2], tree[node * 2 + 1]);
  }

  ll query(int node, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return NEU;
    if (ql <= l && r <= qr) return tree[node];
    push(node, l, r);
    int mid = l + (r - l) / 2;
    return combine(query(node * 2, l, mid, ql, qr),
                   query(node * 2 + 1, mid + 1, r, ql, qr));
  }

  void updateAdd(int l, int r, ll val) { updateAdd(1, 0, n - 1, l, r, val); }
  void updateSet(int l, int r, ll val) { updateSet(1, 0, n - 1, l, r, val); }
  ll query(int l, int r) { return query(1, 0, n - 1, l, r); }
};