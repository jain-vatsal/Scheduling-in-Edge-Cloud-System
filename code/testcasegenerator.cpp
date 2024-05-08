#include <bits/stdc++.h>
using namespace std;
typedef long long int li;
#define vi vector<li>
#define vvi vector<vi>
#define pi pair<li, li>
#define PYES cout << "YES\n"
#define PNO cout << "NO\n"
#define fi first
#define sec second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for (li i = a; i < b; i++)
#define show(C)           \
    for (auto J : C)      \
        cout << J << " "; \
    cout << endl
#define all(C) C.begin(), C.end()
#define mxa(A) *max_element(A.begin(), A.end())
#define mia(A) *min_element(A.begin(), A.end())
#define take(A) rep(i, 0, A.size()) cin >> A[i];
const li MOD = 1e9 + 7;
int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    queue<li> numbers;
    cout << "Number of virtual machines on a node(s) = ";
    li s = rand() % 10 + 1;
    cout << s << endl;
    numbers.push(s);

    cout << "Number of chunks that can be assigned to a machine(b) = ";
    li b = rand() % 10 + 1;
    cout << b << endl;
    numbers.push(b);

    cout << "Max different types of chunks = ";
    li chunks = rand() % 10 + 1;
    cout << chunks << endl;
    numbers.push(chunks);

    cout << "Number of jobs = ";
    li jobs = rand() % 10 + 1;
    cout << jobs << endl;
    numbers.push(jobs);

    rep(i, 0, jobs)
    {
        cout << "Deadline of job " << i + 1 << " = ";
        li d = rand() % 20 + 1;
        cout << d << endl;
        numbers.push(d);

        cout << "Number of chunks for job " << i + 1 << " = ";
        li c = rand() % 20 + 1;
        cout << c << endl;
        numbers.push(c);

        cout << "The chunks for job " << i + 1 << " = ";
        rep(j, 0, c)
        {
            li rt = rand() % chunks + 1;
            cout << rt << " ";
            numbers.push(rt);
        }
        cout << endl;
    }
    cout << endl;
    cout << "Copy paste this line directly into your terminal = ";
    while (numbers.size())
    {
        cout << numbers.front() << " ";
        numbers.pop();
    }
    cout << endl;
    return 0;
}