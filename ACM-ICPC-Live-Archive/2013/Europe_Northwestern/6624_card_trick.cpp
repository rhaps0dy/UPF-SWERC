#include<iostream>
#include<cstdio>
#include<utility>
#include<algorithm>
#include<cstring>

using namespace std;

double n_probs[12] = {0, 0, 1./13., 1./13., 1./13., 1./13., 1./13., 1./13., 1./13., 1./13., 4./13., 1./13.};

#define MAX_LEN 10000

int known_cards[MAX_LEN];
double probs[MAX_LEN];

int main() {
	int N;
	while(cin >> N) {
		int m;
		cin >> m;
		m--;

		string card;
		for(int i=0; i<MAX_LEN; i++)
			known_cards[i] = 0;
		for(int i=0; i<N; i++) {
			cin >> card;
			if(card[0] == 'J' || card[0] == 'Q' || card[0] == 'K' || (card[0] == '1' && card.size() > 1))
				known_cards[m] = 10;
			else if(card[0] == 'A')
				known_cards[m] = 11;
			else
				known_cards[m] = card[0] - '0';
			if(i != N-1)
				m += known_cards[m];
		}
		for(int i=0; i<10; i++)
			probs[i] = 1./10.;
		for(int i=10; i<=m; i++)
			probs[i] = 0.;

		for(int i=0; i<=m; i++) {
			for(int j=2; j<12; j++) {
				int k = i-j;
				if(k<0) break;
				if(known_cards[k] != 0) {
					if(known_cards[k] == j)
						probs[i] += probs[k];
				} else {
					probs[i] += probs[k] * n_probs[j];
				}
			}
		}
		printf("%.12lf\n", probs[m]);
	}
	return 0;
}
