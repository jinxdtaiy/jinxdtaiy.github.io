#include <bits/stdc++.h>
using namespace std;

const int N = 200050, SIZE = 26;

struct suff
{
    int length[N], link[N], next[N][SIZE];
    int SIZE, last;
    int newNode(int L)
    {
        length[++SIZE] = L;
        link[SIZE] = 0;
        for (int i = 0; i < SIZE; i++)
            next[SIZE][i] = 0;
        return SIZE;
    }
    void addCharacter(int c)
    {
        int cur = newNode(length[last] + 1);
        int p;
        for (p = last; p && !next[p][c]; p = link[p])
            next[p][c] = cur;

        if (!p)
            link[cur] = 1;
        else
        {
            int q = next[p][c];
            if (length[q] == length[p] + 1)
                link[cur] = q;
            else
            {
                int clone = newNode(length[p] + 1);
                for (int i = 0; i < SIZE; i++)
                    next[clone][i] = next[q][i];
                link[clone] = link[q];
                link[q] = link[cur] = clone;
                for (; p && next[p][c] == q; p = link[p])
                    next[p][c] = clone;
            }
        }
        last = cur;
    }

    void initialize()
    {
        SIZE = 0;
        last = newNode(0);
    }
} sam;

char str[N];
int num[N], idx[N];
int dp[N];

void solve(int k)
{
    int currentState = 1, length = 0;
    while (k)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (sam.next[currentState][j] == 0)
                continue;
            int nextState = sam.next[currentState][j];
            if (k > dp[nextState])
            {
                k -= dp[nextState];
            }
            else
            {
                str[length++] = 'a' + j;
                currentState = nextState;
                k--;
                if (k == 0)
                    break;
            }
        }
    }
    str[length] = '\0';
    cout << str << endl;
}

int main()
{
    int k;
    cin >> str;
    sam.initialize();
    for (int i = 0; str[i] != '\0'; i++)
        sam.addCharacter(str[i] - 'a');
    for (int i = 1; i <= sam.size; i++)
        num[i] = 0;
    for (int i = 1; i <= sam.size; i++)
        num[sam.length[i]]++;
    for (int i = 1; i <= sam.size; i++)
        num[i] += num[i - 1];
    for (int i = 1; i <= sam.size; i++)
        idx[num[sam.length[i]]--] = i;
    for (int i = sam.size; i >= 1; i--)
    {
        int now = idx[i];
        dp[now] = 1;
        for (int j = 0; j < size; j++)
            dp[now] += dp[sam.next[now][j]];
    }
    cin >> k;
    solve(k);
    return 0;
}
