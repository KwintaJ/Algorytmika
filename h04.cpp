//#########################//
//                         //
//      Jan Kwinta 2E      //
//                         //
//  Problem H04: Skretka   //
//                         //
//    Satori status: OK    //
//                         //
//#########################//

#include <bits/stdc++.h>
using namespace std;

struct permutation
{
    int sigma[8] = {1, 2, 3, 4, 5, 6, 7, 8};
};

permutation compound(permutation &X, permutation &Y)
{
    // cerr << "." << endl;
    permutation new_p; // the compound of X and Y
    for(int i=0; i<8; i++)
        new_p.sigma[i] = X.sigma[Y.sigma[i]-1];

    return new_p;
}

permutation update(permutation tree[], int v, int left, int right, int k, permutation &x)
{
    // cerr << left << " " << right << " " << k << endl;
    if(right - left == 1) // v is leaf
    {
        // cerr << "a" << endl;
        if(left == k) 
            tree[v] = x;

        return tree[v];
    }

    if(left <= k && k < right) // v is not leaf but k is in range (left, right)
    {
        // cerr << "b" << endl;
        int middle = (left + right) / 2;
        permutation child1 = update(tree, 2*v, left, middle, k, x);
        permutation child2 = update(tree, 2*v+1, middle, right, k, x);
        tree[v] = compound(child1, child2);
    }

    // cerr << "c" << endl;
    return tree[v]; // k is not in range (left, right)
}

//#####################################
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;

    permutation tree[4*n+1];
    for(int i=0; i<4*n+1; i++)
    {
        permutation N;
        tree[i] = N;
    } 

    for(int i=0; i<n; i++)
    {
        permutation inp; // input permutation
        for(int j=0; j<8; j++)
            cin >> inp.sigma[j];

        update(tree, 1, 0, n, i, inp);
    }

    int m;
    cin >> m;
    for(int i=0; i<m; i++)
    {
        int k; cin >> k;
        k--;
        permutation inp; // input permutation
        for(int j=0; j<8; j++)
            cin >> inp.sigma[j];

        update(tree, 1, 0, n, k, inp);

        for(int j=0; j<8; j++)
           cout << tree[1].sigma[j] << " ";
        cout << endl;
    }
}