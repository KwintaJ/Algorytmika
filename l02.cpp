//#########################//
//                         //
//      Jan Kwinta 3E      //
//                         //
//    Problem L02: Lista   //
//                         //
//    Satori status: OK    //
//                         //
//#########################//
 
#include <bits/stdc++.h>
using namespace std;
 
struct block
{
    int val = -1;
    block* left = nullptr;
    block* right = nullptr;
    block* up = nullptr;
    int cLen = 0; // left child length
    int h = 0; // height
    block(int v, block* p)
    {
        val = v;
        up = p;
    }
};
 
int height(block* &ptrQ)
{
    int leftH = 0, rightH = 0;
    if(ptrQ->left != nullptr)
        leftH = ptrQ->left->h;
    if(ptrQ->right != nullptr)
        rightH = ptrQ->right->h;
    return max(leftH, rightH) + 1;
}
 
void rotateR(block* &Q)
{
    block* P;
    P = Q->left;
    Q->left = P->right;
    P->right = Q;
    Q = P;
 
    P->right->h = height(P->right);
    P->h = height(P);
    P->right->cLen -= (P->cLen + 1);
}
 
void rotateL(block* &Q)
{
    block* P;
    P = Q->right;
    Q->right = P->left;
    P->left = Q;
    Q = P;
 
    P->left->h = height(P->left);
    P->h = height(P);
    P->cLen += (P->left->cLen + 1);
}
 
int bilance(block* &ptrQ)
{
    int leftH = 0, rightH = 0;
    if(ptrQ->left != nullptr)
        leftH = ptrQ->left->h;
    if(ptrQ->right != nullptr)
        rightH = ptrQ->right->h;
    return rightH - leftH;
}
 
void pushQ(int p, int v, block* &ptrQ, block* parent)
{
    if(ptrQ == nullptr)
    {
        ptrQ = new block(v, parent);
        return;
    }
 
    if(p <= ptrQ->cLen)
    {
        ptrQ->cLen++;
        pushQ(p, v, ptrQ->left, ptrQ);
    }
    else
        pushQ(p - ptrQ->cLen - 1, v, ptrQ->right, ptrQ);
 
    ptrQ->h = height(ptrQ);
    int b = bilance(ptrQ);
    if(b > 1)
    {
        if(bilance(ptrQ->right) < 0)
            rotateR(ptrQ->right);
        rotateL(ptrQ);
    }
    else if(b < -1)
    {
        if(bilance(ptrQ->left) > 0)
            rotateL(ptrQ->left);
        rotateR(ptrQ);
    }
}
 
void writeQ(block* ptrQ)
{
    if(ptrQ->left != nullptr)
        writeQ(ptrQ->left);
 
    cout << ptrQ->val << " ";
 
    if(ptrQ->right != nullptr)
        writeQ(ptrQ->right);
}
 
//#####################################
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
 
    int z; cin>>z;
    while(z--)
    {
        /* ===variables=== */
        int n; // length
        block* ptrQ = nullptr; // AVL queue
 
        /* =====input, algorithm===== */
        cin >> n;
        for(int i = 1; i <= n; i++)
        {
            int p;
            cin >> p; // position
            pushQ(p, i, ptrQ, nullptr);
        }
 
        /* =====output==== */
        writeQ(ptrQ);
        cout << endl;
    }
}
