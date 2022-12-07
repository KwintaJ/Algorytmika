#include <iostream>
#include <algorithm>
 
using namespace std;
 
int las(int A[], int n, int max_of_A)
{
      //cerr<<"max_of_A: "<<max_of_A<<endl;
      int LCS[n][max_of_A+1];
      int max_of_LCS=0;
 
      for(int i=0; i<n; i++)
      {
              for(int j=0; j<=max_of_A; j++)
              {
                      LCS[i][j]=0;
                      //cerr<<". ";
              }
              //cerr<<endl;
      }
 
      for(int i=0; i<n; i++)
      {
              for(int j=0; j<=max_of_A; j++)
              {
                      if(i==0 && j==0)
                      {
                              LCS[0][0]=0;
                      }
                      else if(i==0)
                      {
                              if(A[i]<=j && LCS[i][j-1]==0)
                              {
                                      LCS[i][j]=LCS[i][j-1]+1;
                                      //cerr<<"A[i]: "<<A[i]<<" j: "<<j<<endl;
                              }
                              else
                              {
                                      LCS[i][j]=LCS[i][j-1];
                              }
                      }
                      else if(j==0)
                      {
                              LCS[i][0]=0;
                      }
                      else if(j==1)
                      {
                              if(A[i]<=j)
                              {
                                      LCS[i][j]=LCS[i-1][j]+1;
                              }
                              else
                              {
                                      LCS[i][j]=LCS[i-1][j];
                              }
                      }
                      else
                      {
                              if(A[i]!=j)
                              {
                                      //cerr<<"A[i]: "<<A[i]<<" j: "<<j<<" "<<LCS[i-1][j-1]+1<<endl;
                                      LCS[i][j]=max(LCS[i-1][j], LCS[i][j-1]);
                              }
                              else
                              {
                                      //cerr<<"A[i]: "<<A[i]<<" j: "<<j<<" "<<LCS[i-1][j-1]+1<<endl;
                                      LCS[i][j]=LCS[i-1][j-1]+1;
                              }
                      }
              }
      }
 
      for(int i=0; i<n; i++)
      {
              for(int j=0; j<=max_of_A; j++)
              {
                      if(max_of_LCS<LCS[i][j])
                      {
                              max_of_LCS=LCS[i][j];
                      }
                      //cerr<<LCS[i][j]<<" ";
              }
              //cerr<<endl;
      }
 
      return max_of_LCS;
}
 
int main()
{
      int z; cin>>z;
      while(z--)
      {
              int n; cin>>n;
              int A[n];
              int max_of_A=0;
 
              for(int i=0; i<n; i++)
              {
                      cin>>A[i];
                      if(max_of_A<A[i])
                      {
                              max_of_A=A[i];
                      }
              }
 
              int out=(n-las(A, n, max_of_A));
              cout<<out<<endl;
      }
}
 
/*
 
 
 
- 0 1 2 3 4 5 6 7 8
2 0 0 1
4 0 0 1
1 0 1 2
6 0 1 2
5 0 1 2
8 0 1 2
 
 
 
 
 
 
*/