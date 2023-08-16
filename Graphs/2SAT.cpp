struct TwoSat{
	int n;
	vector<vector<int>> g, gr;
	TwoSat(int _n){
		n = _n;
		g.resize(2 * n);
		gr.resize(2 * n);
	}
 
	int _not(int x){
		if (x >= n){
			return x - n;
		}
		else{
			return x + n;
		}
	}
 
	void add_or(int x, int y, int val){
		if (val == 1){
			g[_not(x)].push_back(y);
			g[_not(y)].push_back(x);
		}
		else{
			g[_not(x)].push_back(_not(y));
			g[y].push_back(x);
 
			g[_not(y)].push_back(_not(x));
			g[x].push_back(y);		
 
			g[x].push_back(_not(y));
			g[y].push_back(_not(x));				
		}
	}
 
	void add_and(int x, int y, int val){
		if (val == 1){
			g[_not(x)].push_back(_not(y));
			g[y].push_back(x);
 
			g[_not(y)].push_back(_not(x));
			g[x].push_back(y);		
 
			g[_not(x)].push_back(y);
			g[_not(y)].push_back(x);
		}
		else{
			g[x].push_back(_not(y));
			g[y].push_back(_not(x));						
		}
	}
 
	void add_xor(int x, int y, int val){
		if (val == 1){
			g[_not(x)].push_back(y);
			g[_not(y)].push_back(x);
 
			g[x].push_back(_not(y));
			g[y].push_back(_not(x));
		}
		else{
			g[_not(x)].push_back(_not(y));
			g[y].push_back(x);
 
			g[_not(y)].push_back(_not(x));
			g[x].push_back(y);									
		}
	}
 
	pair<bool, vector<int>> find_solution(){
		for (int i = 0; i < 2 * n; i++){
			for (int to : g[i]){
				gr[to].push_back(i);
			}
		}
 
		vector<int> used(2 * n);
		vector<int> ord;
		function<void(int)> dfs1 = [&](int v){
			used[v] = 1;
			for (int to : g[v]){
				if (!used[to]){
					dfs1(to);
				}
			}
			ord.push_back(v);
		};
	
		for (int i = 0; i < 2 * n; i++){
			if (!used[i]){
				dfs1(i);
			}
		}
	
		used.assign(2 * n, 0);
	
		vector<int> comp;
		function<void(int)> dfs2 = [&](int v){
			used[v] = 1;
			for (int to : gr[v]){
				if (!used[to]){
					dfs2(to);
				}
			}
			comp.push_back(v);
		};
	
		int c = 0;
		vector<int> col(2 * n);
	
		for (int i = 2 * n - 1; i >= 0; i--){
			int v = ord[i];
			if (!used[v]){
				dfs2(v);
				for (auto u : comp){
					col[u] = c;
				}
				c++;
				comp.clear();
			}
		}
 
		bool ok = 1;
		for (int i = 0; i < n; ++i){
			if (col[i] == col[_not(i)]){
				ok = 0;
			}
		}
 
		vector<int> res(n);
		for (int i = 0; i < n; ++i) {
			res[i] = (col[i] > col[_not(i)] ? 1 : 0);
		}
		return {ok, res};
	}
 
};