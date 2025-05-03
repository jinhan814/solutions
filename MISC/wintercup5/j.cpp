#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

template<int mod>
struct modint {
	constexpr modint() : r(0) {}
	constexpr modint(int x) : r(x % mod) { if (r < 0) r += mod; }
	constexpr modint(i64 x) : r(x % mod) { if (r < 0) r += mod; }
	static modint pow(modint x, size_t n) {
		modint ret = 1;
		for (; n; n >>= 1, x *= x) if (n & 1) ret *= x;
		return ret;
	}
	modint inv() const { return pow(*this, mod - 2); }
	modint operator- () const { return r ? mod - r : 0; }
	modint operator+ (const modint& x) const { return modint(*this) += x; }
	modint operator- (const modint& x) const { return modint(*this) -= x; }
	modint operator* (const modint& x) const { return modint(*this) *= x; }
	modint operator/ (const modint& x) const { return modint(*this) /= x; }
	modint& operator+= (const modint& x) { r += x.r; if (r >= mod) r -= mod; return *this; }
	modint& operator-= (const modint& x) { r -= x.r; if (r < 0) r += mod; return *this; }
	modint& operator*= (const modint& x) { r = (i64)r * x.r % mod; return *this; }
	modint& operator/= (const modint& x) { return *this *= x.inv(); }
	bool operator== (const modint& x) const { return r == x.r; }
	bool operator!= (const modint& x) const { return r != x.r; }
	operator int() const { return r; }
	friend istream& operator>> (istream& in, modint& x) { i64 t; in >> t; x = modint(t); return in; }
	friend ostream& operator<< (ostream& out, const modint& x) { return out << x.r; }
private:
	int r;
};

using mint = modint<1'000'000'007>;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n, m; cin >> n >> m;
	vector a(n + 1, mint(0));
	for (int i = 1; i <= n; i++) cin >> a[i];

	auto bino = [](i64 n, i64 r) -> mint {
		mint ret = 1;
		for (int i = 0; i < r; i++) ret *= mint(n - i);
		for (int i = 0; i < r; i++) ret /= mint(i + 1);
		return ret;
	};

	vector f(n + 1, mint(1));
	vector c(n + 1, 0);
	for (int i = 2; i <= n; i++) {
		if (c[i]) continue;
		for (int j = i; j <= n; j += i) {
			int k = 0, x = j; c[j] = 1;
			while (x % i == 0) x /= i, k++;
			f[j] *= bino(m + k - 1, k);
		}
	}

	vector b(n + 1, mint(0));
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j += i) b[j] += f[j / i] * a[i];
		cout << b[i] << ' ';
	}
}