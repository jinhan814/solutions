#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m, k; cin >> n >> m >> k;
	vector cnt(n + 1, 0);
	for (int i = 0; i < k; i++) {
		int x; cin >> x >> x;
	}
	for (int i = 0; i < n * m; i++) {
		int x; cin >> x;
		cout << ++cnt[x] << ' ';
	}
}