#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

bool f(int n) {
	for (int i = 2; i * i <= n; i++) if (n % i == 0) return 0;
	return 1;
}

int main() {
	fastio;
	int n; cin >> n;
	for (int i = 2; i < n; i++) {
		if (!f(i) || n % i == 0) continue;
		cout << i << '\n'; break;
	}
}