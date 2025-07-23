#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	vector p(n + 1, 0);
	for (int i = 0; i < n; i++) p[i + 1] = p[i] + (s[i] == 'S');
	auto f = [&](int x) {
		int ret = 0;
		for (int i = 0; i + x <= n;) {
			ret++;
			int val = p[i + x] - p[i];
			if (val == x) break;
			i += x, x -= val;
		}
		return ret;
	};
	for (int i = 1; i <= n; i++) cout << f(i) << ' ';
	cout << '\n';
}