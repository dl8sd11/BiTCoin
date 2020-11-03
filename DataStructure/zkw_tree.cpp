int n;  // array size
int seg[2 * maxn];

void build() {  // build the tree
  for (int i = maxn - 1; i > 0; --i) seg[i] = max(seg[i<<1] , seg[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
    for (seg[p += maxn] = value; p > 1; p >>= 1) seg[p>>1] = max(seg[p] , seg[p^1]);
}

int query(int l, int r) {  // sum on interval [l, r)
    int res = 0;
    for (l += maxn, r += maxn; l < r; l >>= 1, r >>= 1) {
        if (l&1) res = max(res, seg[l++]);
        if (r&1) res = max(res, seg[--r]);
    }
    return res;
}
