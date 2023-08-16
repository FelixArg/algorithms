#include <bits/stdc++.h>

using namespace std;
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	vector<pair<int,int>> edges;

	for (int i = 0; i < m; i++){
		int f, t;
		cin >> f >> t;
		f--;
		t--;
		g[f].push_back(edges.size());
		g[t].push_back(edges.size());
		edges.emplace_back(f, t);
	}

	vector<int> dep(n);
	vector<int> fup(n);
	vector<int> used(n);
	vector<int> usede(m);


	vector<vector<int>> comp;
	stack<int> st;

	function<void(int)> new_comp = [&](int idx){
		comp.emplace_back();
		while(!st.empty() && st.top() != idx){
			comp.back().push_back(st.top());
			st.pop();
		}
		if (!st.empty()){
			comp.back().push_back(st.top());
			st.pop();
		}
	};

	function<void(int, int)> dfs = [&](int v, int pred){
		int predv = (pred == -1 ? v : (edges[pred].first ^ edges[pred].second ^ v));
		dep[v] = dep[predv] + 1;
		fup[v] = dep[v];
		used[v] = 1;
		int chi = 0;

		bool is_cp = 0;

		for (int idx : g[v]){
			int to = (edges[idx].first ^ edges[idx].second ^ v);
			if (!used[to]){
				st.push(idx);
				usede[idx] = 1;
				dfs(to, idx);
				if (fup[to] >= dep[v]){
					new_comp(idx);
				}
				fup[v] = min(fup[v], fup[to]);
				chi++;
			}
			else{
				if (!usede[idx]){
					st.push(idx);
					usede[idx] = 1;
				}
				if (idx != pred){
					fup[v] = min(fup[v], dep[to]);
				}
			}
		}
	};

	for (int i = 0; i < n; i++){
		if (!used[i]){
			dfs(i, -1);
		}
	}

	cout << comp.size() << '\n';
	for (auto e : comp){
		cout << e.size() << '\n';
		for (int idx : e){
			cout << edges[idx].first + 1 << ' ' << edges[idx].second + 1 << '\n';
		}
	}
	
	return 0;
}