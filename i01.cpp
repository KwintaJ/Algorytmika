//#########################//
//                         //
//      Jan Kwinta 2E      //
//                         //
// Problem I01: The Dragon //
//      and the knights    //
//                         //
//    Satori status: OK    //
//                         //
//#########################//
 
#include <bits/stdc++.h>
using namespace std;
 
struct linE
{
    long long A;
    long long B;
    long long C;
};
 
struct poinT
{
    long long x;
    long long y;
};
 
//##################################################################
int main()
{
    long long z; cin>>z;
    while(z--)
    {
        /* ===variables=== */
        long long riversNum, knightsNum;
        cin >> riversNum >> knightsNum;
        linE riversMap[riversNum];
        poinT knightsMap[knightsNum];
        long long allDistrictsNum = 1;
        long long protectedDistrictsNum = 0;
 
        /* =====input===== */
        for(long long i=0; i<riversNum; i++)
        {
            linE inRiver;
            cin >> inRiver.A >> inRiver.B >> inRiver.C;
            if(inRiver.A < 0 || (inRiver.A == 0 && inRiver.B < 0))
            {
                inRiver.A *= -1;
                inRiver.B *= -1;
                inRiver.C *= -1;
            }
 
            riversMap[i] = inRiver;
        }
 
        for(long long i=0; i<knightsNum; i++)
        {
            cin >> knightsMap[i].x >> knightsMap[i].y;
        }
 
        /* =counting all districts= */
        for(long long i=0; i<riversNum; i++)
        {
            long long notParallelCount = 1;
            for(long long j=0; j<i; j++)
            {
                if(riversMap[i].A * riversMap[j].B != riversMap[j].A * riversMap[i].B)
                    notParallelCount++;
            }
            allDistrictsNum += notParallelCount;
        }
        // cerr << allDistrictsNum << endl;
 
        /* =counting protected districts= */
        unordered_set<string> knightsPos; // position of Knights
        for(long long i=0; i<knightsNum; i++)
        {
            poinT ithK = knightsMap[i]; // i-th Knight
            string ithPos=" "; // mask = position of i-th Knight
            for(long long j=0; j<riversNum; j++)
            {
                linE jthR = riversMap[j]; //j-th River
                long long equation = (jthR.A * ithK.x + jthR.B * ithK.y + jthR.C);
                if(equation > 0)
                    ithPos += '1';
 
                if(equation < 0)
                    ithPos += '0';
            }
 
            knightsPos.insert(ithPos);
        }
 
        protectedDistrictsNum = knightsPos.size();
        // cerr << endl << protectedDistrictsNum << endl;
 
        /* =====output==== */
        if(allDistrictsNum == protectedDistrictsNum)
            cout << "PROTECTED" << endl;
        else
            cout << "VULNERABLE" << endl;
    }
}
