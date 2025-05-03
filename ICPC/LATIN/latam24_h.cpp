#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;

	vector buc(26, vector(0, i128(0)));
	for (int i = 0; i < s.size(); i++) {
		i128 h = 0;
		for (int j = 0; j < 26 && i + j < s.size(); j++) {
			h = 26 * h + s[i + j] - 97;
			buc[j].push_back(h);
		}
	}

	i128 mx = 0, opt = -1, sz = 0;
	for (int i = 0; i < 26; i++) {
		sort(buc[i].begin(), buc[i].end(), greater{});
		for (int l = 0, r = 0; l < buc[i].size(); l = r) {
			while (r < buc[i].size() && buc[i][l] == buc[i][r]) r++;
			if (mx > r - l) continue;
			mx = r - l;
			opt = buc[i][l];
			sz = i + 1;
		}
	}

	string res;
	while (sz--) res.push_back(opt % 26 + 97), opt /= 26;
	reverse(res.begin(), res.end());
	cout << res << '\n';
}