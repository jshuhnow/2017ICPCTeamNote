ii floydCycleFinding(int x) {
	int a = f(x), b = f(f(x));
	while( a != b) { a=f(a); b=f(f(a)); }

	int mu = 0, b = x;
	while(a!= b) { a=f(a); b = f(b); mu++; }
	int lambda = 1; b = f(a);
	while(a!=b) { b = f(b); lambda++; }
	return ii(mu, lambda);
}
