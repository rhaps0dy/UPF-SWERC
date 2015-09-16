#include <iostream>

using namespace std;

#define MP make_pair
#define PB push_back
#define X first
#define Y second

#define MAX_NUM 10000
#define NOPRINT 5
#define DONTKNOW NOPRINT

int mf[MAX_NUM];

static int
find(int n) {
   if (mf[n] == n) return n;
   return mf[n] = find(mf[n]);
}

static void
merge(int r1, int r2) {
   mf[r2] = r1;
}

/* who is the enemy of every root */
int enemies[MAX_NUM];

static int setFriends(int a, int b);
static int setEnemies(int a, int b);
static int areFriends(int a, int b);
static int areEnemies(int a, int b);

static int
setFriends(int a, int b)
{
    if(areEnemies(a, b))
	return -1;

    a = find(a);
    b = find(b);

    if(enemies[b] == -1) {
	merge(a, b);
	return NOPRINT;
    }

    if(enemies[a] == -1) {
	merge(b, a);
	return NOPRINT;
    }

    merge(a, b);
    merge(enemies[a] = find(enemies[a]), find(enemies[b]));
    return NOPRINT;
}

static int
setEnemies(int a, int b)
{
    if(areFriends(a, b))
	return -1;

    a = find(a);
    b = find(b);

    if(enemies[a] == -1 && enemies[b] == -1) {
	enemies[a] = b;
	enemies[b] = a;
	return NOPRINT;
    }

    // a has enemies for sure
    if(enemies[b] == -1) {
	merge((enemies[a] = find(enemies[a])), b);
	return NOPRINT;
    }

    // b has enemies for sure if we're here
    if(enemies[a] == -1) {
	merge((enemies[b] = find(enemies[b])), a);
	return NOPRINT;
    }

    merge(a, find(enemies[b]));
    merge(b, find(enemies[a]));
    enemies[b] = a;
    enemies[a] = b; 
    return NOPRINT;
}

static int
areEnemies(int a, int b)
{
    a = find(a);
    b = find(b);
    if(enemies[a] == b)
	return 1;
    return 0;
}

static int
areFriends(int a, int b)
{
    a = find(a);
    b = find(b);
    if(a == b)
	return 1;
    return 0;
}

int
main()
{
    int op, a, b;
    int (*f)(int a, int b);

    int N;
    cin >> N;
    for(int i=0; i<N; i++) {
	mf[i] = i;
	enemies[i] = -1;
    }

    while(cin >> op >> a >> b) {
	switch(op) {
	case 0: return 0;
	case 1: f = setFriends; break;
	case 2: f = setEnemies; break;
	case 3: f = areFriends; break;
	case 4: f = areEnemies; break;
	}

	int ret = f(a, b);
	if(ret != NOPRINT)
	    cout << ret << endl;

/*	cout << "mf:";
	for(int i=0; i<N; i++)
	    cout << " " << mf[i];
	cout << endl;
	cout << "enemies:";
	for(int i=0; i<N; i++)
	    cout << " " << enemies[i];
	cout << endl; */
    }
    return 0;
}
