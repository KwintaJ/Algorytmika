//#########################//
//                         //
//      Jan Kwinta 3E      //
//                         //
//    Problem K01: Ławka   //
//                         //
//    Satori status: RTE   //
//                         //
//#########################//

#include <bits/stdc++.h>
using namespace std;

struct criminal
{
    int ID = -1;
    int photos = -1;
    int startTime = -1;
    int endTime = -1;
    int phOnStart = -1;
    criminal(int i, int p, int s, int e)
    {
        ID = i;
        photos = p;
        startTime = s;
        endTime = e;
    }
};

struct poinT
{
    int id = -1;
    int time = -1;
    bool end = false;
    poinT(int i, int t, bool e) 
    {
        id = i;
        time = t;
        end = e;
    }   
};

bool operator<(const poinT &A, const poinT &B)
{
    if(A.time == B.time)
    {
        if(!A.end && B.end)
            return true;
        else if(A.end && !B.end)
            return false;
        else
            return A.id < B.id;
    }

    return A.time < B.time;
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
        int num;
        vector<criminal> bench;
        vector<poinT> timeline;
        int counter = 0;

        /* =====input===== */
        cin >> num;
        for(int i = 0; i < num ; i++)
        {
            int p, s, e;
            cin >> s >> e >> p;
            bench.push_back(criminal(i, p, s, e));
            timeline.push_back(poinT(i, s, false));
            timeline.push_back(poinT(i, e, true));
        }

        /* ===algorithm=== */
        sort(timeline.begin(), timeline.end());

        for(poinT x : timeline)
        {
            if(x.end)
            {
                int shoot = bench[x.id].photos - (counter - bench[x.id].phOnStart);
                if(shoot > 0) 
                    counter += shoot;
            }
            else
                bench[x.id].phOnStart = counter;
        }

        /* =====output==== */
        cout << counter << endl;
    }
}
