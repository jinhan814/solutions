#include <bits/stdc++.h>
using namespace std;

template<int mod>
struct modint {
	using i64 = long long;
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

mint f(int p, int k) {
	return mint(p + 1) * mint::pow(p - 1, 2) * mint::pow(p, 4 * k - 3);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		mint res = 1;
		for (int i = 2; i * i <= n; i++) {
			if (n % i) continue;
			int k = 0;
			while (n % i == 0) n /= i, k++;
			res *= f(i, k);
		}
		if (n > 1) res *= f(n, 1);
		cout << res << '\n';
	}
}