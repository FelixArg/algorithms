template <typename T>
struct SegmentTree {
private:
	#define lc (n << 1)
	#define rc ((n << 1) | 1)
	#define _null 0

	int n;
	vector<T> t, lazy;

	inline void push(int n, int b, int e) {
		if (lazy[n] == 0) return;
		t[n] = t[n] + lazy[n];
		if (b != e) {
			lazy[lc] = lazy[lc] + lazy[n];
			lazy[rc] = lazy[rc] + lazy[n];
		}
		lazy[n] = 0;
	}

	inline T combine(T a, T b) {
		return a + b;
	}

	inline void pull(int n) {
		t[n] = t[lc] + t[rc];
	}

	void build(int n, int b, int e, vector<T>& a) {
		lazy[n] = 0;
		if (b == e) {
			t[n] = a[b];
			return;
		}
		int mid = (b + e) >> 1;
		build(lc, b, mid, a);
		build(rc, mid + 1, e, a);
		pull(n);
	}

	void upd(int n, int b, int e, int i, int j, T v) {
		push(n, b, e);
		if (j < b || e < i) return;
		if (i <= b && e <= j) {
			lazy[n] += v; //set lazy
			push(n, b, e);
			return;
		}
		int mid = (b + e) >> 1;
		upd(lc, b, mid, i, j, v);
		upd(rc, mid + 1, e, i, j, v);
		pull(n);
	}

	T query(int n, int b, int e, int i, int j) {
		push(n, b, e);
		if (i > e || b > j) return _null; //return null
		if (i <= b && e <= j) return t[n];
		int mid = (b + e) >> 1;
		return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
	}

public:
	SegmentTree(int _n) {
		n = _n;
		t.resize(4 * n);
		lazy.resize(4 * n);
  	}

	SegmentTree(vector<T>& a) {
		n = a.size();
		t.resize(4 * n);
		lazy.resize(4 * n);
		build(1, 0, n - 1, a);
	}

	void upd(int l, int r, T val){
		upd(1, 0, n - 1, l, r, val);
	}

	T query(int l, int r){
		return query(1, 0, n - 1, l, r);
	}
};