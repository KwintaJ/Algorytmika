//###########################//
//                           //
//       Jan Kwinta 2E       //
//                           //
// Problem E08: Triangulacja //
//                           //
//     Satori status: TLE    //
//                           //
//###########################//

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
 
using namespace std;
 
struct point // pair<long long, long long> tylko taka fajna
{
    long long x;
    long long y;
};
 
struct outcome //struktura do spamiętywania wyników
{
    long long result;
    long long _a;
    long long _b;
    long long _c;
};
 
long long distance(long long n, point polygon[], long long a, long long b) // odleglosc pomiedzy a i b (0 jesli a=b-1 v a=b+1)
{
    if(a==b+1 || a==b-1 || (a==0 && b==n-1) || (a==n-1 && b==0))
    {
            return 0;
    }
 
    long long o1=(polygon[a].x - polygon[b].x)*(polygon[a].x - polygon[b].x);
    long long o2=(polygon[a].y - polygon[b].y)*(polygon[a].y - polygon[b].y);
    return o1+o2;
}
 
void rem_set(long long n, vector<vector<outcome>> &rem)
{
    if(!rem.empty())
    {
        rem.clear();
    }
 
    vector<outcome> xx;
    for(int j=0; j<n; j++)
    {
        outcome xx2;
        xx2.result=-1;
        xx2._a=-2;
        xx2._b=-2;
        xx2._c=-2;
        xx.push_back(xx2);
    }

    for(int i=0; i<n; i++)
    {
        rem.push_back(xx);
    }
}
 
void diagonals(long long n, point polygon[], vector<vector<long long>> &cost) //koszt każdej przekątnej
{
    for(int i=0; i<n; i++)
    {
        vector<long long> d;
        for(int j=0; j<n; j++)
        {
            d.push_back(distance(n, polygon, i, j));
        }
        cost.push_back(d);
    }
}
 
 
outcome triangulation(long long n, point polygon[],  vector<vector<outcome>> &rem, vector<vector<long long>> &cost, long long i, long long j) // triangulacja
{
    // cerr<<"."<<endl;
    outcome T;
    T.result=0;
 
    if(rem[i][j].result!=-1)
    {
        // cerr<<"known for int" j: "<<j<<endl;
        return rem[i][j];
    }
 
    if(i==j+1 || i==j-1)
    {
        rem[i][j]=T;
        rem[i][j]._a=-2;
        rem[i][j]._b=-2;
        rem[i][j]._c=-2;
        // cerr<<"i: "<<i<<" j: "<<j<<" T: "<<T.result<<endl;
        return T;
    }
 
    T.result=cost[i][i+1]+cost[i+1][j]+(triangulation(n, polygon, rem, cost, i+1, j)).result;
    T._a=i;
    T._b=i+1;
    T._c=j;
    for(int k=i+2; k<j; k++)
    {
        long long x=cost[i][k]+cost[k][j]+(triangulation(n, polygon, rem, cost, i, k)).result+(triangulation(n, polygon, rem, cost, k, j)).result;
        if(x<T.result)
        {
            T.result=x;
            T._a=i;
            T._b=k;
            T._c=j;
        }
    }
 
    rem[i][j]=T;
    // cerr<<"i: "<<i<<" j: "<<j<<" T: "<<T.result<<endl;
    return T;
}
 
void second(vector<vector<outcome>> &rem, long long i, long long k, long long j)
{
    if(i+1==k && k+1==j)
    {
        return;
    }
    if(i+1<k)
    {
        cout<<i<<" "<<k<<" ";
        second(rem, rem[i][k]._a, rem[i][k]._b, rem[i][k]._c);
    }
    if(k<j-1)
    {
        cout<<k<<" "<<j<<" ";
        second(rem, rem[k][j]._a, rem[k][j]._b, rem[k][j]._c);
    }
    return;
}
 
int main()
{
    long long z; cin>>z;
    while(z--)
    {
        long long n; cin>>n; // n
        point polygon[n]; // współrzędne wierzchołków
        for(int i=0; i<n; i++)
        {
            cin>>polygon[i].x>>polygon[i].y;
        }
 
        vector<vector<outcome>> rem; // spamiętywanie
        rem_set(n, rem);
 
        vector<vector<long long>> cost; // koszt każdego odcinka
        diagonals(n, polygon, cost);
 
        //cerr<<cost[2][0];
 
        outcome X_OUT; //OSTATECZNY WYNIK
 
        // cerr<<"A"<<endl;
        outcome one_OUT=triangulation(n, polygon, rem, cost, 0, n-1);
        // rem_set(n, rem);
 
        // cerr<<"B"<<endl;
        // outcome two_OUT=triangulation(n, polygon, rem, cost, 1, n-1);
 
        // cerr<<"1: "<<one_OUT.result<<" 2: "<<two_OUT.result+cost[1][n-1]<<endl;
 
        /* if(one_OUT.result > two_OUT.result+cost[1][n-1])
        {
            // cerr<<"two"<<endl;
            X_OUT.result=two_OUT.result+cost[1][n-1];
            cout<<X_OUT.result<<" ";
            if(two_OUT.result)
            {
                X_OUT._a=two_OUT._a;
                X_OUT._b=two_OUT._b;
                X_OUT._c=two_OUT._c;
                // cerr<<two_OUT._a<<" "<<two_OUT._b<<endl;
                second(rem, two_OUT._a, two_OUT._b, two_OUT._c);
            }
        }
        else
        { */
            // cerr<<"one"<<endl;
            X_OUT=one_OUT;
            cout<<X_OUT.result<<" ";
            if(one_OUT.result)
            {
                // cerr<<one_OUT._a<<" "<<one_OUT._b<<endl;
                second(rem, one_OUT._a, one_OUT._b, one_OUT._c);
            }
        // }
        cout<<endl;
    }
}