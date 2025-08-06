#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int k, auto v) {
	vector nxt(30, vector(6, 0));
	for (int i = 0; i < 30; i++) {
		for (int j = 1; j <= 5; j++) {
			nxt[i][j] = i + j;
			if (16 <= i && i <= 20 && i + j > 20) nxt[i][j] = 40;
			if (21 <= i && i <= 25 && i + j > 25) nxt[i][j] = i + j - 11;
			if (28 <= i && i <= 29) nxt[i][j]++;
			if (i == 5) nxt[i][j] = 20 + j;
			if (i == 10) nxt[i][j] = 25 + j;
			if (i == 23) nxt[i][j] = 28 + j;
			if (nxt[i][j] == 28) nxt[i][j] = 23;
			if (nxt[i][j] == 29) nxt[i][j] = 28;
			if (nxt[i][j] == 30) nxt[i][j] = 29;
			if (nxt[i][j] == 31) nxt[i][j] = 20;
			if (nxt[i][j] > 30) nxt[i][j] = 30;
		}
	}
	vector a(30, 0), b(30, 0);
	for (int i = 0; i < 30; i++) {
		int x = i;
		for (int j = 0 ; j < n; j++) {
			x = nxt[x][v[j]];
			if (x == 30) a[i]++, x = 0;
		}
		b[i] = x;
	}
	i64 ret = 0;
	for (int i = 0, x = 0; i < k; i++) ret += a[x], x = b[x];
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, k; cin >> n >> k;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, k, v) << '\n';
	}
}