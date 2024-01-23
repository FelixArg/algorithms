template <class T>
struct BIT { //1-indexed
  int n; vector<vector<T>> t;
  BIT() {}
  BIT(int _n) {
    n = _n; t.assign(n + 1, vector<T>(n + 1));
  }
  T query(int i, int j) {
    T ans = 0;
    for (int ii = i; ii >= 1; ii -= (ii & -ii)){
		for (int jj = j; jj >= 1; jj -= (jj & -jj)){
			ans += t[ii][jj];
		}
	}
    return ans;
  }
  void upd(int i, int j, T val) {
    if (i <= 0 || j <= 0) return;
    for (int ii = i; ii <= n; ii += (ii & -ii)){
		for (int jj = j; jj <= n; jj += (jj & -jj)){
			t[ii][jj] += val;
		}
	}
  }
};
