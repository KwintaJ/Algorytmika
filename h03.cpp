//#########################//
//                         //
//      Jan Kwinta 2E      //
//                         //
//   Problem H03: Koleje   //
//                         //
//    Satori status: OK    //
//                         //
//#########################//

#include <bits/stdc++.h>
using namespace std;

/* query declaration */
int query(int tree[], int modf[], int v, int left, int right, int p, int q);


/* pushing modificators */
void push(int tree[], int modf[], int v, int left, int right)
{
    if(modf[v] != 0)
    {
        modf[2*v] += modf[v];
        modf[2*v+1] += modf[v];
        modf[v] = 0;
        int middle = (left + right) / 2;
        int child1 = query(tree, modf, 2*v, left, middle, left, middle);
        int child2 = query(tree, modf, 2*v+1, middle, right, middle, right);
        tree[v] = max(child1, child2);
    }
}

/* query */
int query(int tree[], int modf[], int v, int left, int right, int p, int q)
{
    if(p <= left && q >= right)
        return tree[v] + modf[v];

    if(right <= p || left >= q)
        return -1;

    push(tree, modf, v, left, right);

    int middle = (left + right) / 2;
    int child1 = query(tree, modf, 2*v, left, middle, p, q);
    int child2 = query(tree, modf, 2*v+1, middle, right, p, q);

    return max(child1, child2);
}

/* interval tree update +x on range (p, q) */
void update(int tree[], int modf[], int v, int left, int right, int p, int q, int x)
{
    if(p <= left && q >= right)
    {
        modf[v] += x;
        return;
    }

    if(right <= p || left >= q)
        return;

    push(tree, modf, v, left, right);

    int middle = (left + right) / 2;
    update(tree, modf, 2*v, left, middle, p, q, x);
    update(tree, modf, 2*v+1, middle, right, p, q, x);

    int child1 = query(tree, modf, 2*v, left, middle, left, middle);
    int child2 = query(tree, modf, 2*v+1, middle, right, middle, right);

    tree[v] = max(child1, child2);
}

/* query(), then if update possible update() and return true, else return false */
void tickets(int tree[], int modf[], int cityQty, int start, int end, int requredSeats, int seatQty)
{
    int maxTakenSeatOnRangeA = query(tree, modf, 1, 1, cityQty, start, end);
    if(maxTakenSeatOnRangeA + requredSeats <= seatQty)
    {
        update(tree, modf, 1, 1, cityQty, start, end, requredSeats);
        cout << "T" << endl;
        return;
    }

    cout << "N" << endl;
}

//#####################################
int main()
{
    int z; cin>>z;
    while(z--)
    {
        /* ===variables=== */
        int cityQty, seatQty, queryQty;
        cin >> cityQty >> seatQty >> queryQty;
        /* interval max() tree */
        int tree[4*cityQty+1];
        /* modificator array */
        int modf[4*cityQty+1];
        for(int i=0; i<4*cityQty+1; i++)
        {
            tree[i] = 0;
            modf[i] = 0;
        }

        //###########################
        for(int i=0; i<queryQty; i++)
        {
            /* =====input===== */
            int start, end, requredSeats;
            cin >> start >> end >> requredSeats;
            /* ===algorithm, output=== */
            tickets(tree, modf, cityQty, start, end, requredSeats, seatQty);
        }
    }
}

/* 
1
4 6 4
1 4 2
1 3 2
2 4 3
1 2 3
*/