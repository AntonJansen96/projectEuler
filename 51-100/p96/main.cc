#include "main.ih"

size_t Nthreads = 0;

void compute(Sudoku &sudoku)
{
        ++Nthreads;
        sudoku.solve();
        cout << sudoku;
        Nthreads--;
}

int main()
{
    vector<Sudoku> sudokus(import("sudoku1.txt"));
    vector<thread> threads;
    
    for (Sudoku &sudoku : sudokus)
    {
        while (Nthreads == thread::hardware_concurrency())
            sleep_for(nanoseconds(1));
        
        threads.push_back(thread(compute, ref(sudoku)));

        sleep_for(milliseconds(1));
    }
    
    for (thread &thr : threads)
        thr.join();

    int sum = 0;
    for (Sudoku const &sudoku : sudokus)
        sum += sudoku.topleftnum();
    
    cout << sum << '\n';
}

///////////////////////////////////////////////////////////////////////////////

// Single thread            1m25s
// Original multithread     28.8s
// Newest multithread       26.2s
// Solver optimalizations   0.8 a 0.9s.

///////////////////////////////////////////////////////////////////////////////

// #pragma GCC optimize(2)
// #pragma GCC optimize(3)
// #pragma GCC optimize(4)

// #include <iostream>
// #include <cstring>          // For memcpy.

// using namespace std;

// const int N = 11;
// int mp[N][N], st[N][N], sum = 0;
// char s[N][N], t[N];
// int ans = 0;

// void initialize()
// {
//     for (int i = 1; i <= 9; ++i)
//     {
//         for (int j = 1; j <= 9; ++j)
//         {
//             mp[i][j] = 0;
//             st[i][j] = 0;
//         }
//     }
//     sum = 0;
// }

// void add(int x, int  y, int a)
// {
//     mp[x][y] = a;
//     ++sum;

//     for (int i = 1; i <= 9; ++i)
//     {
//         st[i][y] |= 1 << (a - 1);
//         st[x][i] |= 1 << (a - 1);
//     }
    
//     int xx = (x + 2) / 3;
//     int yy = (y + 2) / 3;
    
//     for (int i = (xx - 1) * 3 + 1; i <= xx * 3; ++i)
//         for (int j = (yy - 1) * 3 + 1; j <= yy * 3; ++j)
//             st[i][j] |= 1 << (a - 1);


// }

// void topleftnum()
// {
//     ans += (100 * mp[1][1] + 10 * mp[1][2] + mp[1][3]);
// }

// bool depthFirstSearch()
// {
//     if(sum == 81)
//     {
//         topleftnum();
//         return true;
//     }
    
//     for (int i = 1; i <= 9; ++i)
//         for (int j = 1; j <= 9; ++j)
//         {
//             if (mp[i][j])
//                 continue;
            
//             int cnt = 0, a;
//             for (int k = 0; k < 9; ++k)
//             {
//                 if (!(st[i][j] & (1 << k)))
//                 {
//                     ++cnt;
//                     a = k + 1;
//                 }
                    
//                 if(cnt > 1)
//                     break;
//             }
            
//             if (!cnt)
//                 return false;
            
//             if (cnt == 1)
//                 add(i, j, a);
//         }

//     for (int i = 1; i <= 9; ++i)
//         for (int k = 0; k < 9; ++k)
//         {
//             int cnt1 = 0, cnt2 = 0, x, y;
            
//             for (int j = 1; j <= 9; ++j)
//             {
//                 if(!(st[i][j]&(1<<k))) cnt1++, x = i, y = j;
//                 if(mp[i][j] == k+1) cnt2++;
//                 if(cnt2 > 1) return false;
//             }
//             if(!cnt1 && !cnt2) return false;
//             if(!cnt2 && cnt1 == 1) add(x, y, k+1);
//         }

//     for (int j = 1; j <= 9; ++j) {
//         for (int k = 0; k < 9; ++k) {
//             int cnt1 = 0, cnt2 = 0, x, y;
//             for (int i = 1; i <= 9; ++i) {
//                 if(!(st[i][j]&(1<<k))) cnt1++, x = i, y = j;
//                 if(mp[i][j] == k+1) cnt2++;
//                 if(cnt2 > 1) return false;
//             }
//             if(!cnt1 && !cnt2) return false;
//             if(!cnt2 && cnt1 == 1) add(x, y, k+1);
//         }
//     }
//     for (int x = 1; x <= 3; ++x) {
//         for (int y = 1; y <= 3; ++y) {
//             for (int k = 0; k < 9; ++k) {
//                 int cnt1 = 0, cnt2 = 0, xx, yy;
//                 for (int i = (x-1)*3+1; i <= x*3; ++i) {
//                     for (int j = (y-1)*3+1; j <= y*3; ++j) {
//                         if(!(st[i][j]&(1<<k))) cnt1++, xx = i, yy = j;
//                         if(mp[i][j] == k+1) cnt2++;
//                         if(cnt2 > 1) return false;
//                     }
//                 }
//                 if(!cnt1 && !cnt2) return false;
//                 if(!cnt2 && cnt1 == 1) add(xx, yy, k+1);
//             }
//         }
//     }
    
//     if(sum == 81)
//     {
//         topleftnum();
//         return true;
//     }
    
//     int mn = N, x, y;

//     for (int i = 1; i <= 9; ++i)
//         for (int j = 1; j <= 9; ++j)
//         {
//             if(mp[i][j])
//                 continue;
            
//             int cnt = 0;
            
//             for (int k = 0; k < 9; ++k)
//             {
//                 if (! (st[i][j] & (1 << k)))
//                     ++cnt;
                
//                 if (cnt >= mn)
//                     break;
//             }

//             if (cnt < mn)
//             {
//                 mn = cnt;
//                 x = i;
//                 y = j;
//             }
//         }

//     int tmp[N][N], tst[N][N], tsum = sum;
    
//     memcpy(tmp, mp, sizeof(mp));
//     memcpy(tst, st, sizeof(st));
    
//     for (int k = 0; k < 9; ++k)
//         if(!(st[x][y] & (1 << k)))
//         {
//             add(x, y, k + 1);
//             bool f = depthFirstSearch();
            
//             if (f)
//                 return true;
//             else
//             {
//                 memcpy(mp, tmp, sizeof(mp));
//                 memcpy(st, tst, sizeof(st));
//                 sum = tsum;
//             }
//         }

//     return false;
// }

// int main()
// {
//     freopen("sudoku1.txt", "r", stdin);

//     for (int cs = 1; cs <= 50; ++cs)
//     {
//         scanf("%s", t);
//         scanf("%d", &cs);
        
//         for (int i = 1; i <= 9; ++i)
//             scanf("%s", s[i] + 1);
        
//         initialize();
        
//         for (int i = 1; i != 10; ++i)
//             for (int j = 1; j != 10; ++j)
//                 if (s[i][j] != '0')
//                     add(i, j, s[i][j] - '0');

//         depthFirstSearch();
//     }
    
//     cout << ans << '\n';
// }
