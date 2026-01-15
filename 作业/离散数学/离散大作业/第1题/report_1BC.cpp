#include <iostream>
#include <cstring>
#include <cmath>
#include <conio.h>
using namespace std;

const int N = 50;

void panduan(int b[N], int f);
int tkh(char sz[N], char ccu[N], int icu[N], int h0);
int fkh(char sz[N], char ccu[N], int icu[N], int h0);

int main()
{
    int i1, i2, d = 1, icu[N], kh = 0, jg, j = 0, h0;
    int bj = 0, hq[N], h = 0, x = 0, xq[N];
    char sz[N], ccu[N], sz0[N];

    hq[0] = -1;
    xq[0] = -1;

    cout << "***************************************" << endl;
    cout << "**                                   **" << endl;
    cout << "**         欢迎进入逻辑运算软件      **" << endl;
    cout << "**   (可运算真值表,主范式,支持括号)  **" << endl;
    cout << "**                                   **" << endl;
    cout << "**              用!表示非            **" << endl;
    cout << "**              用&表示与            **" << endl;
    cout << "**              用|表示或            **" << endl;
    cout << "**             用^表示蕴含           **" << endl;
    cout << "**             用~表示等值           **" << endl;
    cout << "**                                   **" << endl;
    cout << "***************************************" << endl << endl;
    cout << "请输入一个合法的命题公式:" << endl;

    cin.getline(sz, N);
    strcpy_s(sz0, sz);

    for (i1 = 0; i1 < (int)strlen(sz); i1++)
    {
        if (sz[i1] == ')' || sz[i1] == '(')
            kh++;
        if ((sz[i1] >= 'a' && sz[i1] <= 'z') || (sz[i1] >= 'A' && sz[i1] <= 'Z'))
        {
            for (i2 = 0; i2 < j; i2++)
                if (ccu[i2] == sz[i1])
                    d = 0;
            if (d == 1)
            {
                ccu[j] = sz[i1];
                j++;
            }
            d = 1;
        }
    }

    cout << endl << "该式子中的变量个数为:" << j << endl;
    h0 = j;
    cout << endl << "输出真值表如下:" << endl << " " << endl;

    for (i1 = 0; i1 < h0; i1++)
        cout << " " << ccu[i1] << " ";
    cout << "    ";
    cout << sz;
    cout << endl;

    for (i1 = 0; i1 < j; i1++)
        icu[i1] = 0;

    for (i2 = 0; i2 < j; i2++)
        cout << " " << icu[i2] << " ";

    jg = tkh(sz, ccu, icu, h0);
    if (jg == 0)
        hq[h++] = bj;
    else
        xq[x++] = bj;
    cout << "    " << jg << endl;

    strcpy_s(sz, sz0);
    int totalRows = (int)pow(2.0, j) - 1;

    for (i1 = 0; i1 < totalRows; i1++)
    {
        ++bj;
        panduan(icu, j - 1);
        jg = tkh(sz, ccu, icu, h0);
        if (jg == 0)
            hq[h++] = bj;
        else
            xq[x++] = bj;
        strcpy_s(sz, sz0);

        for (i2 = 0; i2 < j; i2++)
            cout << " " << icu[i2] << " ";
        cout << "    " << jg << endl;
    }

    if (hq[0] == -1)
        cout << endl << "该命题公式不存在主合取范式." << endl;
    else
    {
        cout << endl << "该命题公式的主合取范式:" << endl << "\t";
        for (i1 = 0; i1 < h; i1++)
        {
            if (i1 > 0)
                cout << "\\/";
            cout << "M(" << hq[i1] << ")";
        }
    }

    if (xq[0] == -1)
        cout << endl << "该命题公式不存在主析取范式." << endl;
    else
    {
        cout << endl << endl << "该命题公式的主析取范式:" << endl << "\t";
        for (i1 = 0; i1 < x; i1++)
        {
            if (i1 > 0)
                cout << "/\\";
            cout << "m(" << xq[i1] << ")";
        }
    }

    cout << endl;
    cout << endl << "欢迎下次再次使用!" << endl;
   
    return 0;
}

void panduan(int b[N], int f)
{
    if (b[f] == 0)
        b[f] = 1;
    else
    {
        b[f] = 0;
        if (f > 0)
            panduan(b, f - 1);
    }
}

int tkh(char sz[N], char ccu[N], int icu[N], int h0)
{
    int i, j, h, s, kh = 0, wz[N], a;
    char xs1[N], ckh[N];

    s = strlen(sz);
    for (i = 0; i < s; i++)
        if (sz[i] == '(' || sz[i] == ')')
        {
            wz[kh] = i;
            ckh[kh] = sz[i];
            kh++;
        }

    if (kh == 0)
        return fkh(sz, ccu, icu, h0);
    else
    {
        for (i = 0; i < kh; i++)
            if (ckh[i] == ')')
                break;

        for (j = wz[i - 1] + 1, h = 0; j < wz[i]; j++, h++)
            xs1[h] = sz[j];
        xs1[h] = '\0';

        a = fkh(xs1, ccu, icu, h0);
        if (a == 1)
            sz[wz[i - 1]] = 1;
        else
            sz[wz[i - 1]] = -2;

        for (j = wz[i - 1] + 1; j < s + wz[i - 1] - wz[i]; j++)
            sz[j] = sz[j + wz[i] - wz[i - 1]];
        sz[j] = '\0';

        return tkh(sz, ccu, icu, h0);
    }
}

int fkh(char sz[N], char ccu[N], int icu[N], int h0)
{
    int i, j = 0, j1 = 0, j2 = 0, j3 = 0, j4 = 0, j5 = 0, i1, i2, p1, p2, s;
    char dt[N] = {'0'};

    s = strlen(sz);
    if (s == 1)
    {
        if (sz[0] == -2)
            return 0;
        else
            return 1;
    }

    // 处理非运算
    for (i = 0; i < s - j; i++)
    {
        if (sz[i] == '!')
        {
            p1 = -1;
            for (i1 = 0; i1 < h0; i1++)
                if (sz[i + 1] == ccu[i1])
                    p1 = icu[i1];
            if (sz[i + 1] == -2)
                p1 = 0;
            if (p1 == -1)
                p1 = sz[i + 1];

            dt[j + 2] = !p1;
            sz[i] = j + 2;
            j++;

            for (i1 = i + 1; i1 < s - j; i1++)
                sz[i1] = sz[i1 + 1];
            sz[s - j] = '\0';
            i--;
        }
    }

    j1 = j;

    // 处理与运算
    for (i = 0; i < s - j1 - 2 * j2; i++)
    {
        if (sz[i] == '&')
        {
            p1 = -1; p2 = -1;
            for (i1 = 0; i1 < h0; i1++)
            {
                if (sz[i - 1] == ccu[i1])
                    p1 = icu[i1];
                if (sz[i + 1] == ccu[i1])
                    p2 = icu[i1];
            }
            for (i2 = 2; i2 < j + 2; i2++)
            {
                if (sz[i - 1] == i2)
                    p1 = dt[i2];
                if (sz[i + 1] == i2)
                    p2 = dt[i2];
            }
            if (sz[i - 1] == -2)
                p1 = 0;
            if (sz[i + 1] == -2)
                p2 = 0;
            if (p1 == -1)
                p1 = sz[i - 1];
            if (p2 == -1)
                p2 = sz[i + 1];

            dt[j + 2] = p1 && p2;
            sz[i - 1] = j + 2;
            j++;
            j2++;

            for (i1 = i; i1 < s - j1 - 2 * j2; i1++)
                sz[i1] = sz[i1 + 2];
            sz[s - j1 - 2 * j2] = '\0';
            i -= 2;
        }
    }

    // 处理或运算
    for (i = 0; i < s - j1 - 2 * j2 - 2 * j3; i++)
    {
        if (sz[i] == '|')
        {
            p1 = -1; p2 = -1;
            for (i1 = 0; i1 < h0; i1++)
            {
                if (sz[i - 1] == ccu[i1])
                    p1 = icu[i1];
                if (sz[i + 1] == ccu[i1])
                    p2 = icu[i1];
            }
            for (i2 = 2; i2 < j + 2; i2++)
            {
                if (sz[i - 1] == i2)
                    p1 = dt[i2];
                if (sz[i + 1] == i2)
                    p2 = dt[i2];
            }
            if (sz[i - 1] == -2)
                p1 = 0;
            if (sz[i + 1] == -2)
                p2 = 0;
            if (p1 == -1)
                p1 = sz[i - 1];
            if (p2 == -1)
                p2 = sz[i + 1];

            dt[j + 2] = p1 || p2;
            sz[i - 1] = j + 2;
            j++;
            j3++;

            for (i1 = i; i1 < s - j1 - 2 * j2 - 2 * j3; i1++)
                sz[i1] = sz[i1 + 2];
            sz[s - j1 - 2 * j2 - 2 * j3] = '\0';
            i -= 2;
        }
    }

    // 处理蕴含运算
    for (i = 0; i < s - j1 - 2 * j2 - 2 * j3 - 2 * j4; i++)
    {
        if (sz[i] == '^')
        {
            p1 = -1; p2 = -1;
            for (i1 = 0; i1 < h0; i1++)
            {
                if (sz[i - 1] == ccu[i1])
                    p1 = icu[i1];
                if (sz[i + 1] == ccu[i1])
                    p2 = icu[i1];
            }
            for (i2 = 2; i2 < j + 2; i2++)
            {
                if (sz[i - 1] == i2)
                    p1 = dt[i2];
                if (sz[i + 1] == i2)
                    p2 = dt[i2];
            }
            if (sz[i - 1] == -2)
                p1 = 0;
            if (sz[i + 1] == -2)
                p2 = 0;
            if (p1 == -1)
                p1 = sz[i - 1];
            if (p2 == -1)
                p2 = sz[i + 1];

            dt[j + 2] = !p1 || p2;
            sz[i - 1] = j + 2;
            j++;
            j4++;

            for (i1 = i; i1 < s - j1 - 2 * j2 - 2 * j3 - 2 * j4; i1++)
                sz[i1] = sz[i1 + 2];
            sz[s - j1 - 2 * j2 - 2 * j3 - 2 * j4] = '\0';
            i -= 2;
        }
    }

    // 处理等值运算
    for (i = 0; i < s - j1 - 2 * j2 - 2 * j3 - 2 * j4 - 2 * j5; i++)
    {
        if (sz[i] == '~')
        {
            p1 = -1; p2 = -1;
            for (i1 = 0; i1 < h0; i1++)
            {
                if (sz[i - 1] == ccu[i1])
                    p1 = icu[i1];
                if (sz[i + 1] == ccu[i1])
                    p2 = icu[i1];
            }
            for (i2 = 2; i2 < j + 2; i2++)
            {
                if (sz[i - 1] == i2)
                    p1 = dt[i2];
                if (sz[i + 1] == i2)
                    p2 = dt[i2];
            }
            if (sz[i - 1] == -2)
                p1 = 0;
            if (sz[i + 1] == -2)
                p2 = 0;
            if (p1 == -1)
                p1 = sz[i - 1];
            if (p2 == -1)
                p2 = sz[i + 1];

            dt[j + 2] = (!p1 || p2) && (!p2 || p1);
            sz[i - 1] = j + 2;
            j++;
            j5++;

            for (i1 = i; i1 < s - j1 - 2 * j2 - 2 * j3 - 2 * j4 - 2 * j5; i1++)
                sz[i1] = sz[i1 + 2];
            sz[s - j1 - 2 * j2 - 2 * j3 - 2 * j4 - 2 * j5] = '\0';
            i -= 2;
        }
    }

    return dt[j + 1];
}