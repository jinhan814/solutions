#include <bits/stdc++.h>
using namespace std;

auto subset_sum = [](int n, auto buc) {
	bitset<1024> b, c; b[0] = 1;
	for (int x : buc) c[x] = 1;
	for (int i = 1; i <= n; i++) if (!c[i]) b |= b << i;
	int res = n;
	while (!b[res]) res--;
	return n - res;
};

auto sol = [](int n, int k, int a, int b) -> int {
	if (a > b) swap(a, b);
	if (a < k) return subset_sum(b, vector{ k, a });
	if (b > k) return subset_sum(a, vector{ k, b });
	if (k == 1) return 2;
	if (k == 2) return 3;
	return subset_sum(k, vector{ k, k - 1, 1 });
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k, a; cin >> n >> k >> a;
	int b = n - a - k;
	cout << sol(n, k, a, b) << '\n';
}