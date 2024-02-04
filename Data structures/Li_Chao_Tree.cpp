const int INF = 1'000'000'007;
 
struct line {
	long long k = INF, m = INF;
	line() {}
	line(long long k, long long m): k(k), m(m) {}
	long long get(long long x) {
		return k * x + m;
	}
};
 
struct li_chao_tree{
	struct node
	{
		line lin;
		node* l = nullptr;
		node* r = nullptr;
	};
 
	int n;
	node* root = nullptr;
 
	li_chao_tree(int _n) : n(_n){}
 
	node* upd(node* n, int tl, int tr, line L) {
		if (!n){
			n = new node();
		}
		if (tl > tr) {
			return n;
		}
		int tm = (tl + tr) / 2;
		bool l = L.get(tl) < n->lin.get(tl);
		bool mid = L.get(tm) < n->lin.get(tm);
		bool r = L.get(tr) < n->lin.get(tr);
		if (!mid && !l && !r){
			return n;
		}
		if (mid) {
			swap(L, n->lin);
			l = L.get(tl) < n->lin.get(tl);
			r = L.get(tr) < n->lin.get(tr);
		}
		if (l) {
			n->l = upd(n->l, tl, tm - 1, L);
		}
		else {
			n->r = upd(n->r, tm + 1, tr, L);
		}
		return n;
	}
 
	long long get(node* n, int tl, int tr, int x) {
		if (!n || tl > tr) {
			return INF * 1ll * INF;
		}
		int tm = (tl + tr) / 2;
		if (x == tm) {
			return n->lin.get(x);
		}	
		if (x < tm) {
			return min(n->lin.get(x), get(n->l, tl, tm - 1, x));
		}
		else {
			return min(n->lin.get(x), get(n->r, tm + 1, tr, x));
		}
	}
};
