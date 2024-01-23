const int INF = 1'000'000'007;
const int MOD = 1'000'000'007;
const int SZ = 1'000'007;

int fact[SZ];
int inv_fact[SZ];

int bpow(int x, int p){
	int res = 1;
	while(p){
		if (p % 2){
			res = (res * 1ll * x) % MOD;
		}
		p >>= 1;
		x = (x * 1ll * x) % MOD;
	}
	return res;
}

void solve(){
	fact[0] = 1;
	for (int i = 1; i < SZ; i++){
		fact[i] = (fact[i - 1] * 1ll * i) % MOD;
	}
	inv_fact[SZ - 1] = bpow(fact[SZ - 1], MOD - 2);
	for (int i = SZ - 2; i >= 0; i--){
		inv_fact[i] = (inv_fact[i + 1] * 1ll * (i + 1)) % MOD;
	}
}
