#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, string s) {
	int ret = 0;
	for (int i = 1; i < n; i++) {
		if (s[i] != 'A') continue;
		if (s[i - 1] == 'A') ret += 2;
		else if (i > 1 && s[i - 2] == 'A') ret++;
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