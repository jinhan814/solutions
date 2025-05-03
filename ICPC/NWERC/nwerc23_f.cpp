#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128;

auto sol = [](i64 a, i64 b, i64 c, i64 d) -> pair<string, string> {
	string sa = to_string(a);
	string sb = to_string(b);

	auto get_mask = [&](int s) -> string {
		string res;
		for (int i = 0; i < sa.size(); i++) {
			if (~s >> i & 1) continue;
			res.push_back(sa[i]);
		}
		return res[0] != 48 ? res : "";
	};

	auto get_denom = [&](string ta) -> string {
		i128 x = stoll(ta);
		if (x * d % c || x * d / c > b) return "";
		string tb = to_string(i64(x * d / c));
		int p = 0;
		for (int i = 0; i < sb.size() && p < tb.size(); i++) p += sb[i] == tb[p];
		return p < tb.size() ? "" : tb;
	};

	auto check_rem = [&](string ta, string tb) -> bool {
		int cnt[128]{};
		for (char c : sa) cnt[c]++;
		for (char c : sb) cnt[c]--;
		for (char c : ta) cnt[c]--;
		for (char c : tb) cnt[c]++;
		for (int i = 0; i < 10; i++) if (cnt[48 + i]) return 0;
		return 1;
	};

	for (int s = 1; s < 1 << sa.size(); s++) {
		string ta = get_mask(s);
		if (ta.empty()) continue;
		string tb = get_denom(ta);
		if (tb.empty()) continue;
		if (check_rem(ta, tb)) return pair(ta, tb);
	}
	return { "", "" };
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 a, b, c, d; cin >> a >> b >> c >> d;
	auto [x, y] = sol(a, b, c, d);
	if (x.empty()) {
		cout << "impossible" << '\n';
	}
	else {
		cout << "possible" << '\n';
		cout << x << ' ' << y << '\n';
	}
}