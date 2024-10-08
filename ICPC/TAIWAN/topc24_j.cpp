#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	string s; cin >> s;
	cout << s.substr(0, s.find('.')) << '\n';
}