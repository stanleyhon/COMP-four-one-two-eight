#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

class mycomparison
{
    bool reverse;
    public:
    mycomparison(const bool& revparam=false) {
        reverse=revparam;
    }

    bool operator() (const int& lhs, const int&rhs) const {
        if (reverse) return (lhs>rhs);
        else return (lhs<rhs);
    }
};

int main (void) {
    // stack
    stack< int > s;
    s.push (5);
    s.top (); // 5
    s.pop (); // pop off
    

    // priority queue
    priority_queue< int > pq;
    priority_queue< int, vector< int >, mycomparison > pq_cc; // custom comparitor
    priority_queue< int, vector< int >, greater< int > >; // greater than instead of less than, reverse sorted   

    pq.push (5);
    pq.front (); // 5;
    pq.size(); // num elements
    pq.empty();
    pq.pop(); // remove 5
 
    return 0;
}
