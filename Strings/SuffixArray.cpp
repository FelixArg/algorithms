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

struct SuffixArray{
    int n;
    vector<int> sa;
    vector<int> lcp;

    vector<int> _s;
    vector<int> _inv_sa;
    SparseTable<int> _st_lcp;

    SuffixArray(){}

    void build(const string& s){
        _s.assign(s.size(), 0);
        for (int i = 0; i < s.size(); i++){
            _s[i] = s[i];
        }
        _build(_s);
        _build_lcp_array();
        _st_lcp.build(lcp);
    }

    void build(const vector<int>& s){
        _s.assign(s.size(), 0);
        for (int i = 0; i < s.size(); i++){
            _s[i] = s[i];
        }
        _build(_s);
        _build_lcp_array();
        _st_lcp.build(lcp);
    }

    void _build(const vector<int>& s){
        map<int, int> mp;
        for (int ch : s){
            mp[ch] = 0;
        }
        int cc = 1;
        for (auto& [key, val]: mp){
            val = cc++;
        }

        n = s.size() + 1;
        vector<int> c(n);
        sa.assign(n, 0);

        for (int i = 0; i < s.size(); i++){
            c[i] = mp[s[i]];
            sa[i] = i;
        }
        c[n - 1] = 0;
        sa[n - 1] = n - 1;

        for (int i = 1; (i >> 1) < n; i <<= 1){
            if (i != 1){
                for (int j = 0; j < n; j++){
                    sa[j] = (sa[j] - (i >> 1) + n) % n;
                }
            }
            vector<int> cnt(n);
            for (int j = 0; j < n; j++){
                cnt[c[sa[j]]]++;
            }
            int su = 0;
            for (int j = 0; j < n; j++){
                su += cnt[j];
                cnt[j] = su - cnt[j];
            }
            vector<int> new_sa(n);
            for (int j = 0; j < n; j++){
                new_sa[cnt[c[sa[j]]]++] = sa[j];
            }
            sa.swap(new_sa);

            if (i != 1){
                vector<int> new_c(n);
                new_c[sa[0]] = 0;
                for (int j = 1; j < n; j++){
                    if (c[sa[j]] > c[sa[j - 1]] || c[(sa[j] + (i >> 1)) % n] > c[(sa[j - 1] + (i >> 1)) % n]){
                        new_c[sa[j]] = new_c[sa[j - 1]] + 1;
                    }
                    else{
                        new_c[sa[j]] = new_c[sa[j - 1]];
                    }
                }
                c.swap(new_c);
            }
        }
    }

    void _build_lcp_array(){
        lcp.assign(n - 1, 0);
        _inv_sa.assign(n, 0);
        for (int i = 0; i < n; i++){
            _inv_sa[sa[i]] = i;
        }
        for (int i = 0; i < n; i++){
            if (_inv_sa[i] == n - 1){
                continue;
            }
            lcp[_inv_sa[i]] = 0;
            if (i > 0 && _inv_sa[i - 1] != n - 1){
                lcp[_inv_sa[i]] = max(0, lcp[_inv_sa[i - 1]] - 1);
            }

            int len = min(n - 1 - i, n - 1 - sa[_inv_sa[i] + 1]);
            while (lcp[_inv_sa[i]] < len && _s[i + lcp[_inv_sa[i]]] == _s[sa[_inv_sa[i] + 1] + lcp[_inv_sa[i]]]){
                lcp[_inv_sa[i]]++;
            }
        }
    }

    int get_lcp(int i, int j){
        assert(i != j);
        i = _inv_sa[i];
        j = _inv_sa[j];
        if (i > j){
            swap(i, j);
        }
        j--;
        return _st_lcp.query(i + 1, j + 1);
    }
};
