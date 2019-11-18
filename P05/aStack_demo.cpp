//
// Tomás Oliveira e Silva, AED, October 2014, September 2015
//
// matched-parenthesis verification
//

#include <iostream>
#include <string.h>
#include "aStack.h"

using std::cout;
using std::cerr;
using std::endl;

int check_parenthesis(const char *s) {
    aStack<int> myStack(10);
    int ret = 0;

    for (int i = 0; i < (int) strlen(s); i++) {
        if (s[i] == '(') {
            myStack.push(i);
        } else if (s[i] == ')') {
            if (!myStack.is_empty()) {
                cout << "'(' at position " << myStack.pop() << " and ')' at position " << i << endl;
            } else {
                cout << "unmatched ')' at position " << i << endl;
                ret = -1;
            }
        }
    }
    while (!myStack.is_empty()) {
        int i = myStack.pop();
        cout << "unmatched '" << s[i] << "' at position " << i << endl;
        ret = -1;
    }

    return ret;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        cerr << "usage: " << argv[0] << " [arguments...]" << endl;
        cerr << "example: " << argv[0] << " 'abc(def)ghi' 'x)(y'" << endl;
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        cout << argv[i] << endl;
        if (check_parenthesis(argv[i]) == 0)
            cout << "  good" << endl;
        else
            cout << "  bad" << endl;
    }
    return 0;
}
