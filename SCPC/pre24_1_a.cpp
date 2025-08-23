#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, string s) {
	while (s.size() && s.back() == 'B') s.pop_back();
	reverse(s.begin(), s.end());
	while (s.size() && s.back() == 'B') s.pop_back();
	int ret = 0;
	for (int i = 0, j = 0; i < s.size(); i = j) {
		while (j < s.size() && s[i] == s[j]) j++;
		if (s[i] == 'A') ret += (j - i - 1) * 2;
		else if (j - i == 1) ret++;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		string s; cin >> s;
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, s) << '\n';
	}
}