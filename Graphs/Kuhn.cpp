#include <bits/stdc++.h>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);

	for (int i = 0; i < n; i++){
		int v;
		while(1){
			cin >> v;
			if (v == 0){
				break;
			}
			v--;
			g[i].push_back(v);
		}
	}

	vector<int> mat(m, -1);
	vector<int> used(n);

	int iter = 1;
	function<bool(int)> try_kuhn = [&](int v){
		if (used[v] >= iter){
			return false;
		}
		used[v] = iter;
		for (int to : g[v]){
			if (mat[to] == -1){
				mat[to] = v;
				return true;
			}
		}
		for (int to : g[v]){
			if (try_kuhn(mat[to])){
				mat[to] = v;
				return true;				
			}
		}
		return false;
	};

	for (int i = 0; i < n; i++){
		if (try_kuhn(i)){
			iter++;
		}
	}

	int mm = 0;
	vector<pair<int,int>> ans;
	for (int i = 0; i < m; i++){
		if (mat[i] != -1){
			mm++;
			ans.emplace_back(mat[i], i);
		}
	}

	cout << mm << '\n';
	for (auto [x, y] : ans){
		cout << x + 1 << ' ' << y + 1 << '\n';
	}

	return 0;
}