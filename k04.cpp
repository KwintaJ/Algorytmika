//#########################//
//                         //
//      Jan Kwinta 3E      //
//                         //
//    Problem K04: Elfy    //
//        i orkowie        //
//                         //
//    Satori status: ANS   //
//                         //
//#########################//

#include <bits/stdc++.h>
using namespace std;

//#####################################
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int z; cin>>z;
    while(z--)
    {
        /* ===variables=== */
        int fightsNum;
        vector<int> orcs;
        vector<int> elves;
        int counter = 0;

        /* =====input===== */
        cin >> fightsNum;
        for(int i = 0; i < fightsNum; i++)
        {
            int s; 
            cin >> s;
            orcs.push_back(s);
        }
        for(int i = 0; i < fightsNum; i++)
        {
            int s; 
            cin >> s;
            elves.push_back(s);
        }

        /* ===algorithm=== */
        sort(orcs.begin(), orcs.end(), greater<int>());
        sort(elves.begin(), elves.end(), greater<int>());

        int o = 0;
        int e = 0;
        while(o < orcs.size())
        {
            if(orcs[o] > elves[e])
            {
                counter++;
                o++;
                e++;
            }
            else if(orcs.back() > elves.back())
            {
                counter++;
                orcs.pop_back();
                elves.pop_back();
            }
            else
            {
                if(orcs.back() < elves[e])
                    counter--;
                orcs.pop_back();
                e++;
            }            
        }
        
        /* =====output==== */
        cout << counter * 200 << endl;
    }
}
