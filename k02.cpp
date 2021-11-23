//#########################//
//                         //
//      Jan Kwinta 3E      //
//                         //
// Problem K02: Wyprzedaż  //
//                         //
//    Satori status: OK    //
//                         //
//#########################//

#include <bits/stdc++.h>
using namespace std;

struct shoP
{
    int ID = -1;
    int coins = -1;
    int startTime = -1;
    int endTime = -1;
    shoP(int i, int s, int e, int c)
    {
        ID = i;
        coins = c;
        startTime = s;
        endTime = e;
    }
};

bool sortByValue(const shoP &A, const shoP &B)
{
    if(A.coins == B.coins)
    {
        if(A.startTime == B.startTime)
            return A.ID < B.ID;
        return A.startTime < B.startTime;
    }
    return A.coins > B.coins;
}

bool sortByStart(const shoP &A, const shoP &B)
{
    if(A.startTime == B.startTime)
    {
        if(A.coins == B.coins)
            return A.ID < B.ID;
        return A.coins > B.coins;
    }
    return A.startTime < B.startTime;
}

bool checkTimes(vector<shoP> shops)
{
    sort(shops.begin(), shops.end(), sortByStart);

    multiset<int> closings;
    int actual = shops[0].startTime;
    int nowId = 0;

    while(nowId < shops.size() || !closings.empty())
    {
        while(shops[nowId].startTime == actual && nowId < shops.size())
        {
            closings.emplace(shops[nowId].endTime);
            nowId++;
        }

        if(!closings.empty())
        {
            if(*closings.begin() <= actual)
                return false;

            actual++;
            closings.erase(closings.begin());
        }
        else
            actual = shops[nowId].startTime;
    }

    return true;
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
        vector<shoP> mall;
        int counter = 0;

        /* =====input===== */
        cin >> num;
        for(int i = 0; i < num ; i++)
        {
            int s, e, c;
            cin >> s >> e >> c;
            mall.push_back(shoP(i, s, e, c));
        }

        /* ===algorithm=== */
        sort(mall.begin(), mall.end(), sortByValue);

        vector<shoP> visit;
        for(auto s : mall)
        {
            visit.push_back(s);
            if(checkTimes(visit))
                counter += s.coins;
            else
                visit.erase((visit.end()--));
        }

        /* =====output==== */
        cout << counter << endl;
    }
}
