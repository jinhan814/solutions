#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	int cnt = 0;
	for (int i = 0; i < n; i++) if (~v[i] & 1) cnt++;
	return ~cnt & 1;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		bool res = sol(n, v);
		cout << "Case #" << tc_num << '\n';
		cout << (res ? "1st" : "2nd") << '\n';
	}
}