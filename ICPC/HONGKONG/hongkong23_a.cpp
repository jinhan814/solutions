#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		vector adj(n + 1, vector(0, 0));
		for (int i = 1; i <= n; i++) {
			int x; cin >> x;
			if (x) adj[x].push_back(i);
		}
		vector dp(n + 1, 1);
		for (int i = n; i >= 1; i--) {
			int mx = -1, smx = -1;
			for (int j : adj[i]) {
				if (smx < dp[j]) smx = dp[j];
				if (mx < smx) swap(mx, smx);
			}
			if (mx != -1) dp[i] = max(mx, smx + 1);
		}
		cout << dp[1] << '\n';
	}
}