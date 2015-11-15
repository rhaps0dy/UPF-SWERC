// returns true if the first argument goes before the second argument 
// in the strict weak ordering it defines, and false otherwise.
struct classcomp {
    bool operator() (const int& lhs, const int& rhs) const
    {return lhs > rhs;}
};

int main() {
    set<int> set1;
    set<int, classcomp> set2;
    set1.insert(26); set1.insert(93); set1.insert(42); // 26, 42, 93
    set2.insert(26); set2.insert(93); set2.insert(42); // 93, 42, 26
    
    for (auto it=set1.begin(); it!=set1.end(); ++it) cout << *it << " ";
    cout << "\n";
    for (auto it=set2.begin(); it!=set2.end(); ++it) cout << *it << " ";
}
