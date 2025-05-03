#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	while (1) {
		vector v(4, 0);
		for (int i = 0; i < 4; i++) cin >> v[i];
		if (v[0] + v[1] + v[2] + v[3] == 0) break;
		while (1) {
			sort(v.begin(), v.end(), greater{});
			int i = 0;
			while (i + 1 < 4 && v[i + 1]) i++;
			if (!i) break;
			for (int j = 0; j < i; j++) v[j] -= v[i];
		}
		cout << v[0] << '\n';
	}
}