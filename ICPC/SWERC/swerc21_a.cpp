#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		vector dp(10, -1);
		for (int i = 0; i < n; i++) {
			int a, b; cin >> a >> b;
			dp[b - 1] = max(dp[b - 1], a);
		}
		auto it = ranges::find(dp, -1);
		auto acc = reduce(dp.begin(), dp.end());
		if (it != dp.end()) cout << "MOREPROBLEMS" << '\n';
		else cout << acc << '\n';
	}
}