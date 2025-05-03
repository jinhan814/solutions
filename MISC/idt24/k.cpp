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

using mint = modint<998'244'353>;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, m, k; cin >> n >> m >> k;
		vector v(m, pair(0, 0));
		for (int i = 0; i < m; i++) {
			char a, b; cin >> a >> b;
			v[i] = { a - 'a', b - 'a' };
		}

		auto get = [&](const int s) {
			vector adj(k, vector(0, 0));
			for (auto [a, b] : v) {
				if (~s >> a & 1) continue;
				if (~s >> b & 1) continue;
				adj[a].push_back(b);
				adj[b].push_back(a);
			}
			vector buc(0, 0), c(k, 0);
			auto dfs = [&](const auto& self, int cur) -> int {
				int ret = c[cur] = 1;
				for (int nxt : adj[cur]) if (!c[nxt]) ret += self(self, nxt);
				return ret;
			};
			for (int i = 0; i < k; i++) {
				if (~s >> i & 1) continue;
				if (!c[i]) buc.push_back(dfs(dfs, i));
			}
			return buc;
		};

		auto calc = [&](const auto& v) -> mint {
			const int m = reduce(v.begin(), v.end());
			vector psum(v.size() + 1, 0);
			for (int i = 0; i < v.size(); i++) psum[i + 1] = psum[i] + v[i];
			vector dp(1 << m, mint(0)); dp[0] = 1;
			for (int _ = 0; _ < n; _++) {
				vector ndp(1 << m, mint(0));
				for (int s = 0; s < 1 << m; s++) {
					for (int i = 0; i < v.size(); i++) {
						int pos = psum[i + 1] - 1;
						while (pos >= psum[i] && ~s >> pos & 1) pos--;
						if (pos >= psum[i]) ndp[s | 1 << pos] += dp[s];
						if (pos + 1 < psum[i + 1]) ndp[s | 1 << pos + 1] += dp[s];
					}
				}
				dp.swap(ndp);
			}
			return dp.back();
		};

		mint res = 0;
		for (int s = 1; s < 1 << k; s++) res += calc(get(s));
		cout << res << '\n';
	}
}