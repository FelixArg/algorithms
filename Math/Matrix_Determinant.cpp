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
 
int det_gauss(vector<vector<int>> a){
	int n = a.size();
	int cnt = 0;
	for (int k = 0; k < n; k++){
		for (int i = k + 1; i < n; i++){
			if (a[i][k] != 0){
				cnt++;
				for (int j = 0; j < n; j++){
					swap(a[k][j], a[i][j]);
				}
				break;
			}
		}
		if (a[k][k] == 0){
			return 0;
		}
		for (int i = k + 1; i < n; i++){
			int sub = a[i][k] * 1ll * bpow(a[k][k], MOD - 2) % MOD;
			for (int j = k; j < n; j++){
				a[i][j] = (a[i][j] * 1ll - sub * 1ll * a[k][j] % MOD + MOD) % MOD;
			}
		}
	}
 
	int res = 1;
	for (int i = 0; i < n; i++){
		res = (res * 1ll * a[i][i]) % MOD;
	}
	if ((cnt & 1)){
		res = (MOD - res);
	}
	return res;
}
