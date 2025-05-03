#include <bits/stdc++.h>
using namespace std;

auto add = [](const auto& a, const auto& b) {
	string res(max(a.size(), b.size()) + 1, 0);
	for (int i = 0; i < res.size(); i++) {
		if (i < a.size()) res[i] += a[a.size() - 1 - i] - 48;
		if (i < b.size()) res[i] += b[b.size() - 1 - i] - 48;
	}
	for (int i = 0; i + 1 < res.size(); i++) {
		res[i + 1] += res[i] / 10;
		res[i] = res[i] % 10;
	}
	while (res.size() > 1 && res.back() == 0) res.pop_back();
	reverse(res.begin(), res.end());
	for (char& c : res) c += 48;
	return res;
};

auto cmp = [](const auto& a, const auto& b) -> bool {
	if (a.size() != b.size()) return a.size() < b.size();
	for (int i = 0; i < a.size(); i++) if (a[i] != b[i]) return a[i] < b[i];
	return 0;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, k; cin >> n >> k;
		string s; cin >> s;

		map dp{ pair(pair(string{}, 0), string{}) }; dp.clear();
		auto dfs = [&](const auto& self, const string& s, int k) -> string {
			if (k == 1) return s;
			if (dp.count({ s, k })) return dp[{ s, k }];
			string& res = dp[{ s, k }];
			for (int i = (int)s.size() / k - 1; i <= (int)s.size() / k + 2; i++) {
				if (i < 1 || i > s.size() - k + 1) continue;
				auto&& val = add(s.substr(0, i), self(self, s.substr(i), k - 1));
				if (res.empty() || cmp(val, res)) res = val;
			}
			return res;
		};

		string res = dfs(dfs, s, k + 1);
		cout << res << '\n';
	}
}