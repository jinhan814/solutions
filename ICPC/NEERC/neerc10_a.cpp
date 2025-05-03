#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector v(0, vector(0, string{}));
	for (string s; getline(cin, s);) {
		stringstream in(s);
		v.push_back({});
		while (in >> s) v.back().push_back(s);
	}
	vector res(v.size(), string{});
	for (int j = 0; j < 180; j++) {
		int mx = 0;
		for (int i = 0; i < v.size(); i++) {
			mx = max(mx, (int)res[i].size());
		}
		for (int i = 0; i < v.size(); i++) {
			if (v[i].size() <= j) continue;
			while (j && res[i].size() <= mx) res[i].push_back(' ');
			res[i] += v[i][j];
		}
	}
	for (auto s : res) cout << s << '\n';
}