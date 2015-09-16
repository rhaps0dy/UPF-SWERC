#include <iostream>
#include <string>

using namespace std;

int
main()
{
    int N;
    string rpn;
    cin >> N;
    getline(cin, rpn);
    for(int n_case=1; n_case<=N; n_case++) {
	getline(cin, rpn);

	int sz = (int)rpn.size();

	int n_ops, stack_size, cur_stack_growth, first_index;
	if(rpn[0] == 'a') {
	    n_ops = 0;
	    stack_size = 1;
	    first_index = 1;
	} else {
	    if(sz >= 3 && rpn[1] == 'a' && rpn[2] == 'a') {
		// we can use a swap and continue like normal
		n_ops = 1;
		stack_size = 0;
		first_index = 2;
	    } else {
		// we have to add two a's and then continue like normal
		n_ops = 2;
		stack_size = 1;
		first_index = 1;
	    }
	}

	for(int i=first_index; i < sz; i++) {
	    cur_stack_growth = (rpn[i] == 'a' ? 1 : -1);
	    if(stack_size == 0) {
		if(cur_stack_growth == 1) {
		    if(i+1 < sz && rpn[i+1] == '+') {
			// add a letter operation
			stack_size = 2;
			n_ops++;
		    } else {
			// swap operation
			stack_size = 1;
			n_ops++;
		    }
		} else {
		    // add a letter operation
		    stack_size = 0;
		    n_ops++;
		}
	    } else {
		stack_size += cur_stack_growth;
	    }
	}
	// if we have too many a's, add +'s.
	if(stack_size > 1)
	    n_ops += stack_size - 1;
	// if we have one a too little, add it.
	if(stack_size == 0)
	    n_ops++;
	cout << "Case " << n_case << ": " << n_ops << endl;
    }
    return 0;
}
