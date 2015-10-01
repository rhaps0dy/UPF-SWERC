#include <vector>
#include <cassert>
#include <cstdio>
#include <iomanip>
#include <cmath>
#include <iostream>

using namespace std;

typedef long long LI;

struct {
	LI value, integral, max;
	int max_i, max_j, max_k;

	void print() {
	    printf("(%lld, %lld, %lld; %d %d %d)", value, integral, max, max_i, max_j, max_k);
	}
} garbage[20][20][20];

int A, B, C;
LI maximum;

static LI
cube(int i1, int j1, int k1, int i2, int j2, int k2) {
	LI val = garbage[i2][j2][k2].integral;
	i1--;
	j1--;
	k1--;
	if(i1 >= 0) {
		val -= garbage[i1][j2][k2].integral;
		if(j1 >= 0) {
			val += garbage[i1][j1][k2].integral;
			if(k1 >= 0)
				val -= garbage[i1][j1][k1].integral;
		}
		if(k1 >= 0)
			val += garbage[i1][j2][k1].integral;
	}
	if(j1 >= 0) {
		val -= garbage[i2][j1][k2].integral;
		if(k1 >= 0)
			val += garbage[i2][j1][k1].integral;
	}
	if(k1 >= 0)
		val -= garbage[i2][j2][k1].integral;
	return val;
}

template<bool dim2, bool dim3> static void
dynamic(int i, int i_1, int i_2, int i_3,
		int j, int j_1, int j_2, int j_3,
		int k, int k_1, int k_2, int k_3) {

	LI val = garbage[i][j][k].value;
	LI candidate1;
	int indi, indj, indk;
	if(!dim2 && !dim3) {
		candidate1 = val + garbage[i_1][j_1][k_1].max;
	} else {
		candidate1 = cube(garbage[i_1][j_1][k_1].max_i,
						  garbage[i_1][j_1][k_1].max_j,
						  garbage[i_1][j_1][k_1].max_k,
						  i, j, k);
	}
	indi = garbage[i_1][j_1][k_1].max_i;
	indj = garbage[i_1][j_1][k_1].max_j;
	indk = garbage[i_1][j_1][k_1].max_k;

	if(dim2) {
		LI candidate2 = cube(garbage[i_2][j_2][k_2].max_i,
							 garbage[i_2][j_2][k_2].max_j,
							 garbage[i_2][j_2][k_2].max_k,
							 i, j, k);
		if(candidate2 > candidate1) {
			candidate1 = candidate2;
			indi = garbage[i_2][j_2][k_2].max_i;
			indj = garbage[i_2][j_2][k_2].max_j;
			indk = garbage[i_2][j_2][k_2].max_k;
		}
	}
	if(dim3) {
		LI candidate3 = cube(garbage[i_3][j_3][k_3].max_i,
							 garbage[i_3][j_3][k_3].max_j,
							 garbage[i_3][j_3][k_3].max_k,
							 i, j, k);
		if(candidate3 > candidate1) {
			candidate1 = candidate3;
			indi = garbage[i_3][j_3][k_3].max_i;
			indj = garbage[i_3][j_3][k_3].max_j;
			indk = garbage[i_3][j_3][k_3].max_k;
		}
	}
	if(candidate1 > val) {
		garbage[i][j][k].max = candidate1;
		garbage[i][j][k].max_i  = indi;
		garbage[i][j][k].max_j  = indj;
		garbage[i][j][k].max_k  = indk;
	} else {
		garbage[i][j][k].max = val;
		garbage[i][j][k].max_i  = i;
		garbage[i][j][k].max_j  = j;
		garbage[i][j][k].max_k  = k;
	}
	if(garbage[i][j][k].max > maximum)
		maximum = garbage[i][j][k].max;
}

int main() {
	int Ncases;
	cin >> Ncases;
	while(Ncases--) {
		cin >> A >> B >> C;
		for(int i=0; i<A; i++)
			for(int j=0; j<B; j++)
				for(int k=0; k<C; k++) {
					cin >> garbage[i][j][k].value;
					garbage[i][j][k].integral = garbage[i][j][k].value;
				}

		// create integral garbage
		for(int i=0; i<A; i++)
			for(int j=0; j<B; j++)
				for(int k=1; k<C; k++)
					garbage[i][j][k].integral = garbage[i][j][k-1].integral + garbage[i][j][k].integral;
		for(int i=0; i<A; i++)
			for(int j=1; j<B; j++)
				for(int k=0; k<C; k++)
					garbage[i][j][k].integral = garbage[i][j-1][k].integral + garbage[i][j][k].integral;
		for(int i=1; i<A; i++)
			for(int j=0; j<B; j++)
				for(int k=0; k<C; k++)
					garbage[i][j][k].integral = garbage[i-1][j][k].integral + garbage[i][j][k].integral;

		maximum = garbage[A-1][B-1][C-1].integral;

		garbage[0][0][0].max = garbage[0][0][0].value;
		garbage[0][0][0].max_i = garbage[0][0][0].max_j = garbage[0][0][0].max_k = 0;

		// Fill the dynamic programming array
		for(int i=1; i<A; i++)
			dynamic<false, false>(i, i-1, -9, -9, 0, 0, -9, -9, 0, 0, -9, -9);
		for(int j=1; j<B; j++)
			dynamic<false, false>(0, 0, -9, -9, j, j-1, -9, -9, 0, 0, -9, -9);
		for(int k=1; k<C; k++)
			dynamic<false, false>(0, 0, -9, -9, 0, 0, -9, -9, k, k-1, -9, -9);

		for(int i=1; i<A; i++)
			for(int j=1; j<B; j++)
				dynamic<true, false>(i, i-1, i, -9, j, j, j-1, -9, 0, 0, 0, -9);
		for(int j=1; j<B; j++)
			for(int k=1; k<C; k++)
				dynamic<true, false>(0, 0, 0, -9, j, j-1, j, -9, k, k, k-1, -9);
		for(int k=1; k<C; k++)
			for(int i=1; i<A; i++)
				dynamic<true, false>(i, i, i-1, -9, 0, 0, 0, -9, k, k-1, k, -9);

		for(int i=1; i<A; i++)
			for(int j=1; j<B; j++)
				for(int k=1; k<C; k++)
					dynamic<true, true>(i, i-1, i, i, j, j, j-1, j, k, k, k, k-1);

#ifndef ONLINE_JUDGE
		// print
		for(int i=0; i<A; i++) {
			for(int j=0; j<B; j++) {
				for(int k=0; k<C; k++) {
					garbage[i][j][k].print();
					putchar(' ');
				}
				putchar('\n');
			}
			putchar('\n');
		}
#endif

		cout << maximum << endl;

		if(Ncases)
			cout << endl;
	}
	return 0;
}
