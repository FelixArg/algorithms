typedef long double dbl;
namespace fft {
    struct cmpl {
        dbl x, y;
        cmpl() {
            x = y = 0;
        }
        cmpl(dbl x, dbl y) : x(x), y(y) {}
        inline cmpl conjugated() const {
            return cmpl(x, -y);
        }
    };
    inline cmpl operator+(cmpl a, cmpl b) {
        return cmpl(a.x + b.x, a.y + b.y);
    }
    inline cmpl operator-(cmpl a, cmpl b) {
        return cmpl(a.x - b.x, a.y - b.y);
    }
    inline cmpl operator*(cmpl a, cmpl b) {
        return cmpl(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
    }

    int base = 1; // current power of two (2^base >= n)
    vector<cmpl> roots = {{0, 0}, {1, 0}}; // complex roots of 1 (with bases from 1 to base), 1-based indexing
    vector<int> rev = {0, 1}; // rev[i] = reversed bit representation of i
    const dbl PI = static_cast<dbl>(acosl(-1.0));

    void ensure_base(int nbase) { // if base < nbase increase it
        if (nbase <= base) {
            return;
        }
        rev.resize(1 << nbase);
        for (int i = 1; i < (1 << nbase); i++) {
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
        }
        roots.resize(1 << nbase);
        while (base < nbase) {
            dbl angle = 2 * PI / (1 << (base + 1));
            for (int i = 1 << (base - 1); i < (1 << base); i++) {
                roots[i << 1] = roots[i];
                dbl angle_i = angle * (2 * i + 1 - (1 << base));
                roots[(i << 1) + 1] = cmpl(cos(angle_i), sin(angle_i));
            }
            base++;
        }
    }

    void fft(vector<cmpl>& a, int n = -1) {
        if (n == -1) {
            n = (int) a.size();
        }
        assert((n & (n - 1)) == 0); // ensure that n is a power of two
        int zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for (int i = 0; i < n; i++) {
            if (i < (rev[i] >> shift)) {
                swap(a[i], a[rev[i] >> shift]);
            }
        }
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    cmpl v = a[i + j + k] * roots[j + k];
                    a[i + j + k] = a[i + j] - v;
                    a[i + j] = a[i + j] + v;
                }
            }
        }
    }

    vector<cmpl> fa, fb;
    
    // INTERFACE

    vector<long long> square(const vector<int>& a) {
        if (a.empty()) {
            return {};
        }
        int need = (int) a.size() + (int) a.size() - 1;
        int nbase = 1;
        while ((1 << nbase) < need) {
            nbase++;
        }
        ensure_base(nbase);
        int sz = 1 << nbase;
        if ((sz >> 1) > (int) fa.size()) {
            fa.resize(sz >> 1);
        }
        for (int i = 0; i < (sz >> 1); i++) {
            int x = (2 * i < (int) a.size() ? a[2 * i] : 0);
            int y = (2 * i + 1 < (int) a.size() ? a[2 * i + 1] : 0);
            fa[i] = cmpl(x, y);
        }
        fft(fa, sz >> 1);
        cmpl r(1.0 / (sz >> 1), 0.0);
        for (int i = 0; i <= (sz >> 2); i++) {
            int j = ((sz >> 1) - i) & ((sz >> 1) - 1);
            cmpl fe = (fa[i] + fa[j].conjugated()) * cmpl(0.5, 0);
            cmpl fo = (fa[i] - fa[j].conjugated()) * cmpl(0, -0.5);
            cmpl aux = fe * fe + fo * fo * roots[(sz >> 1) + i] * roots[(sz >> 1) + i];
            cmpl tmp = fe * fo;
            fa[i] = r * (aux.conjugated() + cmpl(0, 2) * tmp.conjugated());
            fa[j] = r * (aux + cmpl(0, 2) * tmp);
        }
        fft(fa, sz >> 1);
        vector<long long> res(need);
        for (int i = 0; i < need; i++) {
            res[i] = llround(i % 2 == 0 ? fa[i >> 1].x : fa[i >> 1].y);
        }
        return res;
    }

    vector<long long> multiply(const vector<int>& a, const vector<int>& b) {
        if (a.empty() || b.empty()) {
            return {};
        }
        if (a == b) {
            return square(a);
        }
        int need = (int) a.size() + (int) b.size() - 1;
        int nbase = 1;
        while ((1 << nbase) < need) nbase++;
        ensure_base(nbase);
        int sz = 1 << nbase;
        if (sz > (int) fa.size()) {
            fa.resize(sz);
        }
        for (int i = 0; i < sz; i++) {
            int x = (i < (int) a.size() ? a[i] : 0);
            int y = (i < (int) b.size() ? b[i] : 0);
            fa[i] = cmpl(x, y);
        }
        fft(fa, sz);
        cmpl r(0, -0.25 / (sz >> 1));
        for (int i = 0; i <= (sz >> 1); i++) {
            int j = (sz - i) & (sz - 1);
            cmpl v = (fa[j] * fa[j] - (fa[i] * fa[i]).conjugated()) * r;
            fa[j] = (fa[i] * fa[i] - (fa[j] * fa[j]).conjugated()) * r;
            fa[i] = v;
        }
        for (int i = 0; i < (sz >> 1); i++) {
            cmpl A0 = (fa[i] + fa[i + (sz >> 1)]) * cmpl(0.5, 0);
            cmpl A1 = (fa[i] - fa[i + (sz >> 1)]) * cmpl(0.5, 0) * roots[(sz >> 1) + i];
            fa[i] = A0 + A1 * cmpl(0, 1);
        }
        fft(fa, sz >> 1);
        vector<long long> res(need);
        for (int i = 0; i < need; i++) {
            res[i] = llround(i % 2 == 0 ? fa[i >> 1].x : fa[i >> 1].y);
        }
        return res;
    }

    vector<int> multiply_mod(const vector<int>& a, const vector<int>& b, int m) {
        if (a.empty() || b.empty()) {
            return {};
        }
        int need = (int) a.size() + (int) b.size() - 1;
        int nbase = 0;
        while ((1 << nbase) < need) {
            nbase++;
        }
        ensure_base(nbase);
        int sz = 1 << nbase;
        if (sz > (int) fa.size()) {
            fa.resize(sz);
        }
        for (int i = 0; i < (int) a.size(); i++) {
            int x = (a[i] % m + m) % m;
            fa[i] = cmpl(x & ((1 << 15) - 1), x >> 15);
        }
        fill(fa.begin() + a.size(), fa.begin() + sz, cmpl{0, 0});
        fft(fa, sz);
        if (sz > (int) fb.size()) {
            fb.resize(sz);
        }
        if (a == b) {
            copy(fa.begin(), fa.begin() + sz, fb.begin());
        } else {
            for (int i = 0; i < (int) b.size(); i++) {
                int x = (b[i] % m + m) % m;
                fb[i] = cmpl(x & ((1 << 15) - 1), x >> 15);
            }
            fill(fb.begin() + b.size(), fb.begin() + sz, cmpl{0, 0});
            fft(fb, sz);
        }
        dbl ratio = 0.25 / sz;
        cmpl r2(0, -1);
        cmpl r3(ratio, 0);
        cmpl r4(0, -ratio);
        cmpl r5(0, 1);
        for (int i = 0; i <= (sz >> 1); i++) {
            int j = (sz - i) & (sz - 1);
            cmpl a1 = (fa[i] + fa[j].conjugated());
            cmpl a2 = (fa[i] - fa[j].conjugated()) * r2;
            cmpl b1 = (fb[i] + fb[j].conjugated()) * r3;
            cmpl b2 = (fb[i] - fb[j].conjugated()) * r4;
            if (i != j) {
                cmpl c1 = (fa[j] + fa[i].conjugated());
                cmpl c2 = (fa[j] - fa[i].conjugated()) * r2;
                cmpl d1 = (fb[j] + fb[i].conjugated()) * r3;
                cmpl d2 = (fb[j] - fb[i].conjugated()) * r4;
                fa[i] = c1 * d1 + c2 * d2 * r5;
                fb[i] = c1 * d2 + c2 * d1;
            }
            fa[j] = a1 * b1 + a2 * b2 * r5;
            fb[j] = a1 * b2 + a2 * b1;
        }
        fft(fa, sz);
        fft(fb, sz);
        vector<int> res(need);
        for (int i = 0; i < need; i++) {
            long long aa = llround(fa[i].x);
            long long bb = llround(fb[i].x);
            long long cc = llround(fa[i].y);
            res[i] = static_cast<int>((aa + ((bb % m) << 15) + ((cc % m) << 30)) % m);
        }
        return res;
    }
} // namespace fft
