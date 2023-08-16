template <typename T>
struct SparseTable{
	int n, r;
	vector<vector<T>> t;
	void build(vector<T> &a) {
		n = a.size();
		r = 32 - __builtin_clz(n);
		t.resize(n + 1, vector<T>(r));
		for(int i = 1; i <= n; ++i) t[i][0] = a[i - 1];
		for(int k = 1; k < r; ++k) {
			for(int i = 1; i + (1 << k) - 1 <= n; ++i) {
				t[i][k] = f(t[i][k - 1], t[i + (1 << (k - 1))][k - 1]);
			}
		}
	}

	T query(int l, int r) {
		int k = 31 - __builtin_clz(r - l + 1);
		return f(t[l][k], t[r - (1 << k) + 1][k]);
	}

	inline T f(T x, T y){
		return min(x, y);
	}
};