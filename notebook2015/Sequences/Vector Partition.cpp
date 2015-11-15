bidirectional_iterator partition(bidirectional_iterator start,
                             bidirectional_iterator end,
                             Predicate p);

bool IsOdd(int i) {return (i%2==1);}

int main () {
    vector<int> myvector; 
    vector<int>::iterator it, bound;

    // set some values:
    for (int i=1; i<10; ++i)
        myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

    bound = partition(myvector.begin(), myvector.end(), IsOdd);

    // print out content:
    cout << "odd members:";
    for (it=myvector.begin(); it!=bound; ++it)
        cout << " " << *it;
    cout << "\neven members:";
    for (it=bound; it!=myvector.end(); ++it)
        cout << " " << *it;
    cout << endl;
}
