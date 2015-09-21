#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

#define MP make_pair
#define PB push_back
#define X first
#define Y second

/* contains sets of friends and the set who they're enemies of. 0 doesn't count */
vector<pair<set<int>, int> > friends;

/* attendees contains to which set belongs every attendee. 0 means none yet */
int attendees[10000];

int cache[10000][10000];

#define NOPRINT 5

static int setFriends(int a, int b);
static int setEnemies(int a, int b);
static int areFriends(int a, int b);
static int areEnemies(int a, int b);

static void
merge_friends(int ia, int ib)
{
    /* TODO: remove this linear task. Store a set of friends on top of the enemy. */
    {
	/* friends */
	set<int> &aset = friends[ia].X, &bset = friends[ib].X;
	aset.insert(bset.begin(), bset.end());
	for(set<int>::iterator i = aset.begin(); i != aset.end(); i++)
	    attendees[*i] = ia;
    }
    {
	/* enemies */
	set<int> &aset = friends[friends[ia].Y].X, &bset = friends[friends[ib].Y].X;
	aset.insert(bset.begin(), bset.end());
    }
}

static int
setFriends(int a, int b)
{
    if(areEnemies(a, b) == 1)
	return -1;

    if(!attendees[a])
	swap(a, b);

    int ia = attendees[a];
    int ib = attendees[b];

    if(!ia) {
	/* none is known, create new friend set */
	set<int> s;
	s.insert(a);
	s.insert(b);
	int i = friends.size();
        friends.push_back(MP(s, 0));
        attendees[a] = attendees[b] = i;
	return NOPRINT;
    }

    if(!ib) {
	/* ia is known, add ib to it */
        friends[ia].X.insert(b);
        attendees[b] = ia;
	return NOPRINT;
    } 

    /* both are known, merge friend and enemy sets. No need to delete the old set */
    merge_friends(ia, ib);
    return NOPRINT;
}

static int
setEnemies(int a, int b)
{
    if(areFriends(a, b) == 1)
	return -1;

    if(!attendees[a])
	swap(a, b);

    int ia = attendees[a];
    int ib = attendees[b];

    if(!ia) {
	/* none is known, create two sets that are enemies */
	set<int> sa, sb;
	sa.insert(a);
	sb.insert(b);
	int i = friends.size();
	friends.push_back(MP(sa, i+1));
	friends.push_back(MP(sb, i));
	attendees[a] = i;
	attendees[b] = i+1;
	return NOPRINT;
    }

    if(!ib) {
	/* ia is known, add ib to its enemy */
	int enemy = friends[ia].Y;
	if(enemy != 0) {
	    friends[enemy].X.insert(b);
	    attendees[b] = enemy;
	} else {
	    set<int> sen;
	    sen.insert(b);
	    int i = friends.size();
	    friends.push_back(MP(sen, ia));
	    friends[ia].Y = i;
	    attendees[b] = i;
	}
	return NOPRINT;
    }

    /* both are known, merge friend and enemy sets */
    merge_friends(ia, friends[ib].Y);

    return NOPRINT;
}

static int
areEnemiesEx(int a, int b)
{
    if(!attendees[a] || !attendees[b])
        return NOPRINT;

    if(attendees[a] == attendees[b])
	return 0;

    if(friends[attendees[a]].Y == attendees[b] && friends[attendees[b]].Y == attendees[a])
	return 1;

    return NOPRINT;
}

static int
areEnemies(int a, int b)
{
    return areEnemiesEx(a, b) == 1 ? 1 : 0;
}

static int
areFriends(int a, int b)
{
    int e = areEnemiesEx(a, b);
    if(e == 1) return 0;
    if(e == 0) return 1;
    return 0;
}

int
main()
{
    int op, a, b;
    int (*f)(int a, int b);

    int N;

    // prevent from using the 0
    friends.push_back(MP(set<int>(), 0));

    cin >> N;

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

/*	for(int i=0; i<N; i++)
	    cout << attendees[i] << " ";
	cout << endl;
	for(int i=0; i<friends.size(); i++) {
	    cout << "friends[" << i << "]: enemy " << friends[i].Y << ". ";
	    set<int> &s = friends[i].X;
	    cout << endl;
	}
	cout << endl; */
    }
    return 0;
}
