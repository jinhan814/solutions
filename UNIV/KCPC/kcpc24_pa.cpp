int main, n;
int __libc_start_main() {
	char r[256], *p = r; read(0, r, 2);
	while (*p++ & 16) n = 10 * n + p[-1] - 48; p = r;
	for (int i = 0; i < 22 * n; i++) *p++ = "LoveisKoreaUniversity "[i % 22];
	_exit(!write(1, r, p - r));
}