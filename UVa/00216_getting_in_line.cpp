#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <utility>

using namespace std;

#define MAX 8
#define X first
#define Y second

double distances[MAX][MAX];
pair<double,double> points[MAX];
int N;

int main() {
	int number_case = 1;
	int min_indices[MAX], indices[MAX];
	double min_dist;
	while(cin >> N && N) {
		for(int i=0; i<N; i++)
			cin >> points[i].X >> points[i].Y;

		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				double X = points[i].X - points[j].X;
				double Y = points[i].Y - points[j].Y;
				double distance = sqrt(X*X + Y*Y);
				distances[i][j] = distances[j][i] = distance;
			}
		}
		for(int i=0; i<N; i++)
			indices[i] = i;
		min_dist = MAX * 150. * 150.;
		do {
			double dist = 0.0;
			for(int i=1; i<N; i++)
				dist += distances[indices[i-1]][indices[i]];
			if(dist < min_dist) {
				min_dist = dist;
				memcpy(min_indices, indices, N*sizeof(int));
			}
		} while(next_permutation(indices, indices+N));

		puts("**********************************************************");
		printf("Network #%d\n", number_case);
		for(int i=1; i<N; i++)
			printf("Cable requirement to connect (%.0lf,%.0lf) to (%.0lf,%.0lf) is %.2lf feet.\n",
				   points[min_indices[i-1]].X, points[min_indices[i-1]].Y,
				   points[min_indices[i]].X, points[min_indices[i]].Y,
				   distances[min_indices[i-1]][min_indices[i]] + 16.);
		printf("Number of feet of cable required is %.2lf.\n", min_dist + (N-1) * 16.);

		number_case++;
	}
	return 0;
}
