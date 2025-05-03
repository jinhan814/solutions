#include <bits/stdc++.h>
using namespace std;

auto sol = [](int a, int b) {
	vector res(200, string(200, '.'));
	if (b & 1) return vector(0, string(0, 0));
	if (b == 0) {
		int x = 0, y = 0;
		if (a % 3 == 0) x = 2, y = 4, a -= 12;
		if (a % 3 == 2) x = 2, y = 2, a -= 8;
		if (a < 0) return vector(0, string(0, 0));
		for (int i = 0; i <= y; i++) res[0][i] = res[x][i] = 'O';
		for (int i = 0; i <= x; i++) res[i][0] = res[i][y] = 'O';
		for (int i = 0; i < a / 3; i++) {
			res[x + i][y + i + 1] = 'O';
			res[x + i + 1][y + i] = 'O';
			res[x + i + 1][y + i + 1] = 'O';
		}
		return res;
	}
	else {
		res[1][0] = res[1][1] = 'O';
		for (int i = 1; i < b / 2; i++) res[1][i + 1] = res[i & 1 ? 0 : 2][i] = 'O';
		for (int i = 0; i < a; i++) res[1][b / 2 + 1 + i] = 'O';
		return res;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b; cin >> a >> b;
	auto res = sol(a, b);
	if (res.empty()) {
		cout << "NO" << '\n';
	}
	else {
		cout << "YES" << '\n';
		cout << 200 << ' ' << 200 << '\n';
		for (int i = 0; i < 200; i++) cout << res[i] << '\n';
	}
}