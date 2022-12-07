//#########################//
//                         //
//      Jan Kwinta 2E      //
//                         //
//   Problem H01:Naczelny  //
//  statystyk kontratakuje //
//                         //
//    Satori status: OK    //
//                         //
//#########################//

#include <bits/stdc++.h>
using namespace std;


int update(int tree[], int v, int left, int right, int k, int x)
{
    if(right - left == 1) // v is leaf
    {
        if(left == k) 
            tree[v] = x;

        return tree[v];
    }

    if(left <= k && k < right) // v is not leaf but k is in range (left, right)
    {
        int middle = (left + right) / 2;
        int child1 = update(tree, 2*v, left, middle, k, x);
        int child2 = update(tree, 2*v+1, middle, right, k, x);
        tree[v] = max(child1, child2);
    }

    return tree[v]; // k is not in range (left, right)
}

int query(int tree[], int v, int left, int right, int p, int q)
{
    if(p <= left && q >= right)
        return tree[v];

    if(right <= p || left >= q)
        return numeric_limits<int>::min();

    if(right - left == 1)
    {
        if(p <= left && q > left)
            return tree[v];

        return numeric_limits<int>::min();
    }

    int middle = (left + right) / 2;
    int child1 = query(tree, 2*v, left, middle, p, q);
    int child2 = query(tree, 2*v+1, middle, right, p, q);

    return max(child1, child2);
}

//#########################################################################
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int z; cin>>z;
    while(z--)
    {
        /* ===variables=== */
        /* n - BytemenCount, m - correctionsCount */
        int n, m; cin >> n >> m; 
        /* interval max() tree */
        int tree[4*n];
        for(int i=0; i<4*n; i++)
            tree[i] = numeric_limits<int>::min();

        /* =====input===== */
        for(int i=0; i<n; i++)
        {
            int BytemanProfit; cin >> BytemanProfit; 
            update(tree, 1, 0, n, i, BytemanProfit);
        } 

        /* ===algorithm=== */
        for(int i=0; i<m; i++)
        {
            string method; cin >> method;
            int a, b; cin >> a >> b;
            a--;

            if(method == "UPDATE")
                update(tree, 1, 0, n, a, b);

            if(method == "MAX")
            {
                int bestProfit = query(tree, 1, 0, n, a, b);
                cout << bestProfit << endl;
            }
        }
    }
}