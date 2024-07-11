mt19937_64 rng(chrono::high_resolution_clock().now().time_since_epoch().count());
const int ITER_MAX = 200'000;
const long long MAX_SQRT = 1'000'000'000'000LL;

long long F(long long x, long long n){
    return (__int128_t(x) * x + 1) % n;
}

long long get_fact(long long n){
    auto gen = uniform_int_distribution<long long>(1, n - 2);
    long long x = gen(rng);
    long long y = F(F(x, n), n);
    for (int i = 0; i < ITER_MAX; i++){
        long long g = gcd(n, abs(x - y));
        if (g != 1 && g != n){
            return g;
        }
        x = F(x, n);
        y = F(F(y, n), n);
    }
    return 1;
}

void Rho_Pollard(long long n, vector<long long>& fact){
    if (n < MAX_SQRT){
        for (long long i = 2; i * i <= n; i++){
            while(n % i == 0){
                fact.push_back(i);
                n /= i;
            }
        }
        if (n != 1){
            fact.push_back(n);
        }
        return;
    }

    auto f = get_fact(n);
    if (f == 1 || f == n){
        fact.push_back(n);
        return;
    }
    Rho_Pollard(n / f, fact);
    Rho_Pollard(f, fact);
}
