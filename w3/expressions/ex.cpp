#include <stack>
#include <iostream>
#include <locale>
#include <queue>

class node {
  public:
    char name;
    node * left;
    node * right;

    node (char newName) {
        name = newName;
        left = NULL;
        right = NULL;
    }
};

using namespace std;

node * treeify (string s) {
    stack<node*> st;

    node * root = NULL;

    int i = 0;
    while (i < s.length()) {
        if (islower (s[i])) {
            st.push (new node(s[i]));
        } else {
            node * right = st.top();
            st.pop();
            node * left = st.top();
            st.pop();
            node * newNode = new node(s[i]);
            newNode->left = left;
            newNode->right = right;
            st.push (newNode);
            root = newNode;
        }
        i++;
    }

    return root;
}

void printIt (node * root) {
    // now do a breadth first search, push the result onto a
    // stack, print that stack out and you have your answer.
    stack<char> answer;
    queue<node*> bfsHelper;
    bfsHelper.push(root);
    while (bfsHelper.empty() == false) {
        node * target = bfsHelper.front();
        bfsHelper.pop();
        if (target->left != NULL) {
            bfsHelper.push(target->left);
        } 

        if (target->right != NULL) {
            bfsHelper.push(target->right);
        }

        answer.push(target->name);
    }

    // ok now print each char from the stack
    while (answer.empty() == false) {
        cout << answer.top();
        answer.pop();
    }
    cout << "\n";
    return;
}

int main (void) {
    int cases;
    cin >> cases;
    int currentCase = 0;
    while (currentCase < cases) {
        string s;
        cin >> s;

        node * myTree = treeify (s);
        
        printIt (myTree);
        currentCase++;
    }

    return 0;
}
