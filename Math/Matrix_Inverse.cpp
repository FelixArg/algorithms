const int MOD = 998'244'353;

int bpow(int x, int p){
	int res = 1;
	while(p){
		if ((p & 1)){
			res = (res * 1ll * x) % MOD;
		}
		p >>= 1;
		x = (x * 1ll * x) % MOD;
	}
	return res;
}

vector<vector<int>> inv_gauss(vector<vector<int>> a){
	int n = a.size();
	vector<vector<int>> temp(n, vector<int> (n));
	vector<int> p(n);
	for (int i = 0; i < n; i++){
		temp[i][i] = 1;
		p[i] = i;
	}
	for (int k = 0; k < n; k++){
		for (int i = k + 1; i < n; i++){
			if (a[i][k] != 0){
				for (int j = 0; j < n; j++){
					swap(a[k][j], a[i][j]);
					swap(temp[k][j], temp[i][j]);
				}
				swap(p[k], p[i]);
				break;
			}
		}
		if (a[k][k] == 0){
			return {};
		}
		int inv = bpow(a[k][k], MOD - 2);
		for (int i = 0; i < n; i++){
			a[k][i] = (a[k][i] * 1ll * inv) % MOD;
			temp[k][i] = (temp[k][i] * 1ll * inv) % MOD;
		}
		for (int i = k + 1; i < n; i++){
			int sub = a[i][k];
			for (int j = 0; j < n; j++){
				a[i][j] = (a[i][j] * 1ll - sub * 1ll * a[k][j] % MOD + MOD) % MOD;
				temp[i][j] = (temp[i][j] * 1ll - sub * 1ll * temp[k][j] % MOD + MOD) % MOD;
			}
		}
	}

	for (int i = n - 1; i > 0; i--){
		for (int j = 0; j < i; j++){
			int sub = a[j][i];
			for (int k = 0; k < n; k++){
				a[j][k] = (a[j][k] * 1ll - sub * 1ll * a[i][k] % MOD + MOD) % MOD;
				temp[j][k] = (temp[j][k] * 1ll - sub * 1ll * temp[i][k] % MOD + MOD) % MOD;
			}
		}
	}

	return temp;
}
