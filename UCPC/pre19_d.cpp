#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
constexpr int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
constexpr int mul(int a, int b) { return 1LL * a * b % mod; }

auto sol = [](int n, string s, auto v) {
	vector nxt(1, array<int, 26>{});
	vector cnt(1, 0);
	for (int i = 0; i < n; i++) {
		int p = 0;
		for (char c : v[i]) {
			if (!nxt[p][c - 97]) {
				nxt[p][c - 97] = nxt.size();
				nxt.push_back({});
				cnt.push_back({});
			}
			p = nxt[p][c - 97];
			cnt[p]++;
		}
	}
	vector dp(s.size() + 1, 0); dp[0] = 1;
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0, p = 0; i + j < s.size(); j++) {
			if (!nxt[p][s[i + j] - 97]) break;
			p = nxt[p][s[i + j] - 97];
			int val = mul(dp[i], cnt[p]);
			dp[i + j + 1] = add(dp[i + j + 1], val);
		}
	}
	return dp.back();
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	string s; cin >> s;
	cout << sol(n, s, v) << '\n';
}