int good(int val) {}

int lastTrueBBin(int lo, int hi) {
  // Buscamos el último índice i tal que good(i) == true.
  // Sino, devuelve -1

  while (lo < hi) {
    // Midpoint sesgado hacia la derecha.
    int mid = (lo + hi + 1)/ 2;

    if (good(mid)) {
      // mid podría ser la respuesta.
      // Buscamos algo más a la derecha.
      lo = mid;
    } else {
      // mid no sirve.
      // Tampoco sirven los índices posteriores.
      hi = mid - 1;
    }
  }

  return lo;
}

int firstTrueBBin(int lo, int hi) {
  // Buscamos el primer índice i tal que good(i) == true.
  // Sino, devuelve n

  while (lo < hi) {
    int mid = (lo + hi) / 2;

    if (good(mid)) {
      // mid podría ser la respuesta.
      // Conservamos mid.
      hi = mid;
    } else {
      // mid no sirve, ni ningún índice menor que mid.
      lo = mid + 1;
    }
  }

  return lo;
}