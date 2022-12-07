//#########################//
//                         //
//      Jan Kwinta 2E      //
//                         //
//    Problem H02:Large    //
//     Hadron Collider     //
//                         //
//    Satori status: OK    //
//                         //
//#########################//    
   
#include <bits/stdc++.h>
using namespace std;

/* (x, y) point on plain */
struct poinT
{
    int number = -1; // beam number
    /* coordinates */
    int x = -1;
    int y = -1;
    /* defines type of beam ending on this point 
    true - vertical // false - horizontal */
    bool type; 
    /* defines if this point is a start or end of a beam 
    true - its an end // false - its a start */
    bool endP;
    /* defines which way broom is moving
    true - left->right // false - up->down */
    bool sortCount = true;
};

/* overloading comparison operators for poinT */
bool operator<(const poinT &A, const poinT &B)
{
   if(A.sortCount)
    {
        if(A.x == B.x)
        {
            return true;
        }
        return A.x < B.x;
    }
    else
    {
        if(A.y == B.y)
        {
            return true;
        }
        return A.y < B.y;
    }
}
bool operator>(const poinT &A, const poinT &B)
{
   if(A.sortCount)
    {
        if(A.x == B.x)
        {
            return true;
        }
        return A.x > B.x;
    }
    else
    {
        if(A.y == B.y)
        {
            return true;
        }
        return A.y > B.y;
    }
}
bool operator<=(const poinT &A, const poinT &B)
{
    if(A.sortCount)
        return A.x <= B.x;

    return A.y <= B.y;        
}


/* beam (x1, y1) -> (x2, y2) */
struct beaM 
{
    poinT start;
    poinT end;
};

struct evenT
{
    poinT eventPoint;
    int eventType; // 1-2-3
};

/* priority_queue sorts if coods are the same:
if(A.sortCount) first is horizontal start, second vertical, third hor end */
bool operator>(const evenT &A, const evenT &B)
{
    if(A.eventPoint.sortCount)
    {
        if(A.eventPoint.x == B.eventPoint.x)
        {
            return A.eventType > B.eventType;
        }
        return A.eventPoint.x > B.eventPoint.x;
    }
    else
    {
        if(A.eventPoint.y == B.eventPoint.y)
        {
            return A.eventType > B.eventType;
        }
        return A.eventPoint.y > B.eventPoint.y;
    }
}

//#############################################################################


/* fenwick tree query on range (beaM e.start - beaM e.end) */
int query(beaM e, int tree[])
{
    int sum1 = 0, sum2 = 0;
    int i, j; // (i, j) - range
    
    /* if broom goes from left to right take y coords, else take x */
    if(e.start.sortCount) 
    {
        i = min(e.start.y, e.end.y);
        j = max(e.start.y, e.end.y);
    }
    else
    {
        i = min(e.start.x, e.end.x);
        j = max(e.start.x, e.end.x);
    }

    /* sum range (0, i-1] */
    i--;
    while(i > 0)
    {
        sum1 += tree[i];
        i -= (i & (-i));
    }

    /* sum range (0, j] */
    while(j > 0)
    {
        sum2 += tree[j];
        j -= (j & (-j));
    }

    /* sum(0, j] - sum(0, i-1] = sum[i, j] */
    return (sum2 - sum1);
}

void update(int K, beaM e, int tree[], bool unsign)
{
    /* if the beam starts update +1, if it ends update -1 */
    int val = -1;
    if(unsign)
        val = 1;
    
    // cerr << "update with value " << val;

    /* update on i-th element of fenwick tree
    if the broom goes left to right update tree[e.start.y]
    else update tree[e.start.x] */
    int i;
    if(e.start.sortCount)
        i = e.start.y;
    else
        i = e.start.x;

    // cerr << " on " << i << " beam " << e.start.number <<  endl;
    
    /* update */
    while(i <= K)
    {
        tree[i] += val;
        i += (i & (-i));
    }
}

/* broom swipe from left to right */
void sweepLR(int n, int K, beaM plain[], int crossed[], bool beamType)
{
    /* filling priority queue of points comparing by x coord */
    priority_queue<evenT, vector<evenT>, greater<evenT>> nextBeam;
    for(int i=1; i<=n; i++)
    {
        evenT A, B;
        A.eventPoint = plain[i].start;
        if(A.eventPoint.type)
            A.eventType = 2;
        else if(!A.eventPoint.endP)
            A.eventType = 1;
        else
            A.eventType = 3;

        B.eventPoint = plain[i].end;
        if(B.eventPoint.type)
            B.eventType = 2;
        else if(!B.eventPoint.endP)
            B.eventType = 1;
        else
            B.eventType = 3;

        nextBeam.push(A);
        nextBeam.push(B);
    }
    
    /* fenwick tree declaration */
    int tree[K+1] = {0};

    /* broom swipe */
    while(!nextBeam.empty())
    {
        poinT current = (nextBeam.top()).eventPoint;
        nextBeam.pop();

        // cerr << "(" << current.x << ", " << current.y << ") "; 
        
        if(!current.type)
        {
            poinT cPair; // point that is on the other side of beam
            if(current.endP)
                cPair = plain[current.number].start;
            else
                cPair = plain[current.number].end;

            /* checking to do +1_update or -1_update */
            if(current <= cPair)
                update(K, plain[current.number], tree, true);
            else
                update(K, plain[current.number], tree, false);
        }
        else if(current.endP) // query on only one side of a beam
        {
            // cerr << query(plain[current.number], tree) << endl;
            crossed[current.number] = query(plain[current.number], tree);
        }
        // else cerr << "v s" << endl;
    }
}

/* function to change comparison, and query/update coord */
void changeDirection(int n, int K, beaM plain[])
{
    for(int i=1; i<=n; i++)
    {
        plain[i].start.sortCount = false;
        plain[i].end.sortCount = false;
    }
}

/* broom swipe from up to down */
void sweepUD(int n, int K, beaM plain[], int crossed[], bool beamType)
{
    /* filling priority queue of points comparing by y coord */
    priority_queue<evenT, vector<evenT>, greater<evenT>> nextBeam;
    for(int i=1; i<=n; i++)
    {
        evenT A, B;
        A.eventPoint = plain[i].start;
        if(!A.eventPoint.type)
            A.eventType = 2;
        else if(!A.eventPoint.endP)
            A.eventType = 1;
        else
            A.eventType = 3;

        B.eventPoint = plain[i].end;
        if(!B.eventPoint.type)
            B.eventType = 2;
        else if(!B.eventPoint.endP)
            B.eventType = 1;
        else
            B.eventType = 3;

        nextBeam.push(A);
        nextBeam.push(B);
    }
    
    /* fenwick tree declaration */
    int tree[K+1] = {0};

    /* broom swipe */
    while(!nextBeam.empty())
    {
        poinT current = (nextBeam.top()).eventPoint;
        nextBeam.pop();
        
        // cerr << "(" << current.x << ", " << current.y << ") "; 

        if(current.type)
        {
            poinT cPair; // point that is on the other side of beam
            if(current.endP)
                cPair = plain[current.number].start;
            else
                cPair = plain[current.number].end;

            /* checking to do +1_update or -1_update */
            if(current <= cPair)
                update(K, plain[current.number], tree, true);
            else
                update(K, plain[current.number], tree, false);
        }
        else if(current.endP) // query on only one side of a beam
        {
            // cerr << query(plain[current.number], tree) << endl;
            crossed[current.number] = query(plain[current.number], tree);
        }
        // else cerr << "v s" << endl;
    }
}


//#############################################################################
int main()
{
    ios_base::sync_with_stdio(false);
    int z; cin >> z;
    while(z--)
    {
        /* ===variables=== */
        /* n - total beams count 
        (K+1, K+1) - bottom right corner of the plain */
        int n, K; cin >> n >> K;

        /* plain on beams on it */
        beaM plain[n+1];

        /*crossed_[i] - how many beams crosses beam i */
        int crossed[n+1] = {0};


        /* =====input===== */
        for(int i=1; i<=n; i++)
        {
            /* 4 ints: start(x, y), end(x, y) */
            cin >> plain[i].start.x >> plain[i].start.y;
            cin >> plain[i].end.x >> plain[i].end.y; 

            /* filling the poinT struct */
            plain[i].start.number = i;
            plain[i].end.number = i;

            plain[i].start.endP = false;
            plain[i].end.endP = true;

            /* checking if its vertical or horizontal */
            if(plain[i].start.x == plain[i].end.x)
            {
                plain[i].start.type = true;
                plain[i].end.type = true;
                if(plain[i].start.y > plain[i].end.y)
                {
                    plain[i].start.endP = true;
                    plain[i].end.endP = false;
                    poinT helper = plain[i].start;
                    plain[i].start = plain[i].end;
                    plain[i].end = helper;
                }
            }   
            if(plain[i].start.y == plain[i].end.y)
            {
                plain[i].start.type = false;
                plain[i].end.type = false;
                if(plain[i].start.x > plain[i].end.x)
                {
                    plain[i].start.endP = true;
                    plain[i].end.endP = false;
                    poinT helper = plain[i].start;
                    plain[i].start = plain[i].end;
                    plain[i].end = helper;
                }
            }   
        }

        
        /* ===algorithm=== */
        sweepLR(n, K, plain, crossed, true);
        changeDirection(n, K, plain);
        // cerr << "---------" << endl;
        sweepUD(n, K, plain, crossed, false);


        /* =====output==== */
        for(int i=1; i<=n; i++)
        {
            cout << crossed[i] << endl;
        }
    }  

    return 0;  
}

/*
example:

0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 | | 0 | 0
| 0 0 0 0 | | 0 | 0
| 0 0 0 0 | | 0 | 0
| 0 0 0 0 | 0 0 | 0
| 0 --====+==---+--
| --- 0 0 | 0 0 | 0
0 0 0 0 0 | 0 0 | 0
0 0 0 0 0 | 0 0 | 0
*/