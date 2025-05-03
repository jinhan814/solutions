#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	int acc = 0, g = 0;
	vector cnt(1 << 18, 0);
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		acc += a;
		g = gcd(g, b);
		cnt[a]++;
	}

	bitset<1 << 18> b; b[0] = 1;
	for (int i = 1; i <= acc; i++) {
		if (!cnt[i]) continue;
		for (int s = 1; cnt[i] >= s; cnt[i] -= s, s <<= 1) b |= b << i * s;
		b |= b << i * cnt[i];
	}

	auto sol = [&]() -> bool {
		if (cnt[0] && acc % g == 0) return 1;
		for (int i = 1; i <= acc - i; i++) {
			if (!b[i] || (acc - 2 * i) % g) continue;
			return 1;
		}
		return 0;
	};
	cout << "NY"[sol()] << '\n';
}