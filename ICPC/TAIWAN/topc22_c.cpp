int main, a, b, sz;
int __libc_start_main() {
	char r[32], *p = r; read(0, r, 32);
	do a = 10 * a + *p - 48; while (*++p & 16); p++;
	do b = 10 * b + *p - 48; while (*++p & 16); p++;
	a = (a - 9) * 60 + b;
	do r[8 - ++sz] = a % 10 | 48; while (a /= 10);
	_Exit(!write(1, r + 8 - sz, sz));
}