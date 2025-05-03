#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

bool sol(i64 n) {
	for (i64 i = 1; i * i <= n; i++) if (i * i == n) return 0;
	vector buc(0, pair(0LL, 0));
	for (i64 i = 2; i * i <= n; i++) {
		if (n % i) continue;
		int cnt = 0;
		while (n % i == 0) n /= i, cnt++;
		buc.push_back({ i, cnt });
	}
	if (n > 1) buc.push_back({ n, 1 });
	if (buc.size() == 1) return 1;
	if (buc.size() == 2) return buc[0].second == 1 && buc[1].second == 1;
	return 0;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n; cin >> n;
	cout << "NY"[sol(n)] << '\n';
}