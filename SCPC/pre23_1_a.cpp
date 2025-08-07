#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int a, int b) {
	int ret = 0;
	for (int i = 0; i <= n / a; i++) {
		if ((n - i * a) % b) continue;
		ret = max(ret, i + (n - i * a) / b);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, a, b; cin >> n >> a >> b;
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, a, b) << '\n';
	}
}