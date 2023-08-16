#include <bits/stdc++.h>

using namespace std;
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;
	vector<vector<pair<int,int>>> g(n);
	for (int i = 0; i < m; i++){
		int f, t;
		cin >> f >> t;
		f--;
		t--;
		g[f].emplace_back(t, i);
		g[t].emplace_back(f, i);
	}

	vector<int> dep(n);
	vector<int> fup(n);
	vector<int> used(n);
	set<int> bri;

	function<void(int, int)> dfs = [&](int v, int pred){
		dep[v] = dep[pred] + 1;
		fup[v] = dep[v];
		used[v] = 1;
		for (auto [to, idx] : g[v]){
			if (!used[to]){
				dfs(to, v);
				if (fup[to] > dep[v]){
					bri.insert(idx);
				}
				fup[v] = min(fup[v], fup[to]);
			}
			else{
				if (to != pred){
					fup[v] = min(fup[v], dep[to]);
				}
			}
		}
	};

	for (int i = 0; i < n; i++){
		if (!used[i]){
			dfs(i, i);
		}
	}

	cout << bri.size() << '\n';
	for (int x : bri){
		cout << x + 1 << ' ';
	}
	
	return 0;
}