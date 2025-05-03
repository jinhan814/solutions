#include <bits/stdc++.h>
using namespace std;

using T = vector<string>;

vector db = {
	T { "#...", "####", "#...", },
	T { ".#..", "####", "#...", },
	T { "..#.", "####", "#...", },
	T { "...#", "####", "#...", },
	T { ".#..", "####", ".#..", },
	T { "..#.", "####", ".#..", },
	T { "..##", ".##.", "##..", },
	T { "..##", "###.", "#...", },
	T { "##..", ".###", ".#..", },
	T { ".#..", "###.", "..##", },
	T { "..###", "###..", },
};

auto sol = [](auto v) {
	auto rotate = [](auto v) {
		const int n = v.size();
		const int m = v[0].size();
		vector res(m, string(n, 0));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				res[j][n - 1 - i] = v[i][j];
		}
		return res;
	};
	auto flip = [](auto v) {
		const int n = v.size();
		const int m = v[0].size();
		vector res(n, string(m, 0));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				res[i][m - 1 - j] = v[i][j];
		}
		return res;
	};
	auto match = [](auto v, auto t) {
		const int n = t.size();
		const int m = t[0].size();
		for (int x = 0; x + n <= 6; x++) for (int y = 0; y + m <= 6; y++) {
			int f = 1;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++)
					if (v[x + i][y + j] != t[i][j]) f = 0;
			}
			if (f) return 1;
		}
		return 0;
	};
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 11; j++) if (match(v, db[j])) return 1;
		for (int j = 0; j < 11; j++) db[j] = rotate(db[j]);
		if (i != 3) continue;
		for (int j = 0; j < 11; j++) db[j] = flip(db[j]);
	}
	return 0;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector v(6, string{});
	for (int i = 0; i < 6; i++) cin >> v[i];
	cout << (sol(v) ? "can fold" : "cannot fold") << '\n';
}