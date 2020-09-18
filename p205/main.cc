#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    size_t Pwins = 0;

    for (int aa = 1; aa <= 4; ++aa)
    for (int bb = 1; bb <= 4; ++bb)
    for (int cc = 1; cc <= 4; ++cc)
    for (int dd = 1; dd <= 4; ++dd)
    for (int ee = 1; ee <= 4; ++ee)
    for (int ff = 1; ff <= 4; ++ff)
    for (int gg = 1; gg <= 4; ++gg)
    for (int hh = 1; hh <= 4; ++hh)
    for (int ii = 1; ii <= 4; ++ii)
    
    for (int qq = 1; qq <= 6; ++qq)
    for (int rr = 1; rr <= 6; ++rr)
    for (int ss = 1; ss <= 6; ++ss)
    for (int tt = 1; tt <= 6; ++tt)
    for (int uu = 1; uu <= 6; ++uu)
    for (int vv = 1; vv <= 6; ++vv)

    if (aa + bb + cc + dd + ee + ff + gg + hh + ii > qq + rr + ss + tt + uu + vv)
        ++Pwins;

    std::cout << std::setprecision(7) << Pwins / (pow(4, 9) * pow(6, 6)) << '\n';
}

