int v[10000]; // primes

void savePrimes()
{
    int k = 0;
    v[k++] = 2;
    for (int i = 3; i <= 10010; i += 2) {
        bool b = true;
        for (int j = 0; b && v[j] * v[j] <= i; j++)
            b = i%v[j] > 0;
        if (b)
            v[k++] = i;
    }
}

bool isPrime(int x){
	bool prime = true;
	for (int j = 0; prime && v[j] * v[j] <= x; j++)
		prime = x%v[j] > 0;
	return prime;
}

// probar si un numero x <= 100000000 es primo
int main()
{
    savePrimes();
    cout << isPrime(4);
}
