#include <stdio.h>
#include <string.h>

long long totmat[1000][1000], mat[1000][1000], mat2[1000][1000], ring[1000], s, mod;
int n;

static void
process_input(void)
{
	int l, r, x, i;

	scanf("%d %lld %d %d %d", &n, &s, &l, &r, &x);
	mod = 10;
	for(i=1; i<x; i++)
		mod *= 10;
	memset(mat, 0, 1000*1000*sizeof(long long));

	if(n==2) {
		mat[0][0] = mat[1][1] = 1;
		mat[0][1] = mat[1][0] = (l%mod + r%mod)%mod;
	} else {
		mat[0][0] = 1;
		mat[0][1] = r%mod;
		mat[0][n-1] = l%mod;

		for(i=1; i<n-1; i++) {
			mat[i][i] = 1;
			mat[i][i+1] = r%mod;
			mat[i][i-1] = l%mod;
		}

		mat[n-1][n-1] = 1;
		mat[n-1][0] = r%mod;
		mat[n-1][n-2] = l%mod;
	}

	memset(totmat, 0, 1000*1000*sizeof(long long));
	for(i=0; i<n; i++) {
		scanf("%lld", &ring[i]);
		ring[i] = ring[i] % mod;
		totmat[i][i] = 1;
	}

	/* print results
	printf("n: %d, s: %lld, mod: %lld\n", n, s, mod);
	puts("ring:");
	for(i=0; i<n; i++)
		printf("%lld ", ring[i]);
	puts("\n\nmat:");
	for(x=0; x<n; x++) {
		for(i=0; i<n; i++)
			printf("%lld ", mat[x][i]);
		putchar('\n');
	}
	putchar('\n');
	*/
}

static void
mmult(long long a[1000][1000], long long b[1000][1000], long long c[1000][1000])
{
	int i, j, k;

	memset(a, 0, 1000*1000*sizeof(long long));
	for(i=0; i<n; i++)
		for(k=0; k<n; k++)
			a[0][i] = (a[0][i] + (b[0][k] * c[k][i]) % mod) % mod;
	for(j=0; j<n-1; j++)
		for(i=0; i<n; i++)
			a[j+1][(i+1)%n] = a[j][i];
}

static void
elevate_matrix(void)
{
	int i, j, k;
	long long aux;

	for(i=0; (aux=(1<<((long long)i))) <= s; i++) {
		if(i%2) {
			if(s&aux) {
				memcpy(mat, totmat, 1000*1000*sizeof(long long));
				mmult(totmat, mat2, mat);
			}
			mmult(mat, mat2, mat2);
		} else {
			if(s&aux) {
				memcpy(mat2, totmat, 1000*1000*sizeof(long long));
				mmult(totmat, mat, mat2);
			}
			mmult(mat2, mat, mat);
		}

		/* print mats
		puts("mat:");
		for(j=0; j<n; j++) {
			for(k=0; k<n; k++)
				printf("%lld ", mat[j][k]);
			putchar('\n');
		}
		puts("mat2:");
		for(j=0; j<n; j++) {
			for(k=0; k<n; k++)
				printf("%lld ", mat2[j][k]);
			putchar('\n');
		}
		puts("totmat:");
		for(j=0; j<n; j++) {
			for(k=0; k<n; k++)
				printf("%lld ", totmat[j][k]);
			putchar('\n');
		}
		putchar('\n');
		*/
	}
}

static void
print_ring(void)
{
	int i, j;
	long long sum;

	for(j=0; j<n; j++) {
		if(s==0) {
			printf("%lld", ring[j]);
		} else {
			sum = 0;
			for(i=0; i<n; i++)
				sum = (sum + (ring[i] * totmat[j][i]) % mod) % mod;
			printf("%lld", sum);
		}
		if(j == n-1) putchar('\n');
		else putchar(' ');
	}
}

int
main()
{
	int i, cases;
	scanf("%d", &cases);
	for(i=0; i<cases; i++) {
		process_input();
		elevate_matrix();
		print_ring();
	}
	return 0;
}
