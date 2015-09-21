#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct Edge {
    int coord, start, end, i;
};

inline bool edge_sorter(const Edge & a, const Edge & b) {
    if(a.coord == b.coord) {
	return a.start < b.start;
    }
    return a.coord < b.coord;
}

struct MergeFind {
    vector<int> sets;
    vector<int> setAreas;
    int recordArea;

    MergeFind(const vector<int> &areas) : sets(areas.size()), setAreas(areas), recordArea(0) {
	for(int i=0; i<(int)areas.size(); i++) {
	    sets[i] = i;
	    if(setAreas[i] > recordArea)
		recordArea = setAreas[i];
	}
    }

    int find(int i) {
	if(sets[i] == i) return i;
	return sets[i] = find(sets[i]);
    }

    void merge(int a, int b) {
	a = find(a);
	b = find(b);
	if(a != b) {
	    sets[b] = a;
	    setAreas[a] += setAreas[b];
	    if(setAreas[a] > recordArea)
		recordArea = setAreas[a];
	}
    }
};

static void
mergeRectangles(MergeFind &mf, vector<Edge> &open, vector<Edge> &close) {
    sort(open.begin(), open.end(), edge_sorter);
    sort(close.begin(), close.end(), edge_sorter);
    for(int i=0, j=0; i < (int)open.size() && j < (int)close.size(); ) {
	Edge o = open[i], c = close[j];
	if(o.coord < c.coord) {
	    i++;
	    continue;
	}
	if(o.coord > c.coord) {
	    j++;
	    continue;
	}
	// now open and close are in the same vertical

	if(o.start == c.start) {
	    mf.merge(o.i, c.i);
	} else if(o.start < c.start) {
	    if(o.end >= c.start) {
		mf.merge(o.i, c.i);
	    } else {
		i++;
		continue;
	    }
	    
	} else {
	    if(c.end >= o.start) {
		mf.merge(o.i, c.i);
	    } else {
		j++;
		continue;
	    }
	}
	// now if the rectangles touch their areas have been merged

	if(o.end < c.end)
	    i++;
	else
	    j++;
    }
}


int
main()
{
    int N, x, y, w, h;
    Edge e;
    vector<int> rectangleAreas;
    vector<Edge> xOpenEdges, xCloseEdges, yOpenEdges, yCloseEdges;

    rectangleAreas.reserve(50000);
    xOpenEdges.reserve(50000);
    xCloseEdges.reserve(50000);
    yOpenEdges.reserve(50000);
    yCloseEdges.reserve(50000);

    while(cin >> N) {
	rectangleAreas.clear();
	xOpenEdges.clear();
	xCloseEdges.clear();
	yOpenEdges.clear();
	yCloseEdges.clear();
	for(int i=0; i<N; i++) {
	    cin >> x >> y >> w >> h;
	    rectangleAreas.push_back(w * h);
	    e.i = i;

	    e.coord = x;
	    e.start = y;
	    e.end = y + h;
	    xOpenEdges.push_back(e);

	    e.coord = x + w;
	    xCloseEdges.push_back(e);

	    e.coord = y;
	    e.start = x;
	    e.end = x + w;
	    yOpenEdges.push_back(e);

	    e.coord = y + h;
	    yCloseEdges.push_back(e);
	}

	MergeFind mf(rectangleAreas);
	mergeRectangles(mf, xOpenEdges, xCloseEdges);
	mergeRectangles(mf, yOpenEdges, yCloseEdges);
	cout << mf.recordArea << endl;
    }
}
