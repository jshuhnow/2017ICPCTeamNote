long long modmul(long long a, long long b, long long m)  /* (a*b)%m */
{
    long long y = (long long)((double)a*(double)b/(double)m + 0.5) * m;
    long long x = a * b, r = x - y;
    return (r < 0) ? r + m : r;
}

long long modexp(long long a, long long e, long long m)  /* (a^e)%m */
{
    if (!e) return 1;
    long long b = modexp(a, e/2, m);
    return (e & 1) ? modmul(modmul(b, b, m), a, m) : modmul(b, b, m);
}

bool isprime(long long n)  /* for n < 56897193526942024370326972321 */
{
    if (n <= 1) return false;
    if (n <= 3) return true;
    static long long a[] = {2,3,5,7,11,13,17,19,23,29,31};
    long long s = 0, d = n-1;
    while (d % 2 == 0) d /= 2, ++s;
    for (int i = 0; i < 11; ++i)
    {
        if (n == a[i]) return true;
        long long x = modexp(a[i], d, n);
        if (x != 1 && x != n-1)
        {
            for (int r = 1; r < s; ++r)
            {
                x = modmul(x, x, n);
                if (x == 1) return false;
                if (x == n-1) break;
            }
            if (x != n-1) return false;
        }
    }
    return true;
}

long long llrand()
{
    return ((long long)rand() << 32) + rand();
}

long long gcd(long long a, long long b)
{
    return (b == 0) ? a : gcd(b, a % b);
}


long long rho(long long n)
{
    long long d, c = llrand() % n, x = llrand() % n, xx = x;
    
    if (n % 2 == 0) return 2;
    do {
        x = (modmul(x, x, n) + c) % n;
        xx = (modmul(xx, xx, n) + c) % n;
        xx = (modmul(xx, xx, n) + c) % n;
        d = gcd(abs(x - xx), n);
    } while (d == 1);
    return d;
}

vector<long long> v;
void factor(long long n)
{
    if (n == 1) return;
    if (isprime(n)) { v.push_back(n); return; }
    long long d = rho(n);
    factor(d);
    factor(n/d);
}

//Usage
// factor(N);

