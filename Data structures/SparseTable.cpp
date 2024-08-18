template <typename T>
struct SparseTable{
	int n, r;
	vector<vector<T>> t;
	void build(vector<T> &a) {
		n = a.size();
		r = 32 - __builtin_clz(n);
		t.resize(r, vector<T>(n + 1));
		for(int i = 1; i <= n; ++i) t[0][i] = a[i - 1];
		for(int k = 1; k < r; ++k) {
			for(int i = 1; i + (1 << k) - 1 <= n; ++i) {
				t[k][i] = f(t[k - 1][i], t[k - 1][i + (1 << (k - 1))]);
			}
		}
	}

	T query(int l, int r) {
		int k = 31 - __builtin_clz(r - l + 1);
		return f(t[k][l], t[k][r - (1 << k) + 1]);
	}

	inline T f(T x, T y){
		return min(x, y);
	}
};
