#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k; cin >> n >> k;

	auto ask = [&](int x, int y) {
		cout << x << ' ' << y << endl;
		string s; cin >> s;
		if (s == "sunk" && !--k) exit(0);
		return s != "miss";
	};

	auto kill = [&](int x, int y) {
		for (int d = 0; d < 4; d++) for (int i = 1; i <= 4; i++) {
			int nx = x + ("1012"[d] - '1') * i;
			int ny = y + ("2101"[d] - '1') * i;
			if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
			ask(nx, ny);
		}
	};

	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
		if ((i + j) % 5) continue;
		if (ask(i, j)) kill(i, j);
	}
}