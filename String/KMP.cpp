struct KMP
{
    str s, t;
    int n, m, k;
    vi p, c, ans;

    KMP(str s_, str t_)
    {
        s = s_, t = t_, n = sz(s), m = sz(t), p.assign(m + 1, 0), d.assign(m + 1, 0);
    }

    void fill_p()
    {
        c[0]++, p[0] = -1, k = 0;
        for (int i = 2; i <= m; i++)
        {
            while (k != -1 and t[k] != t[i - 1])
                k = p[k];
            p[i] = ++k;
            c[p[i]]++;
        }
    }

    void match()
    {
        fill_p();
        k = 0;
        for (int i = 0; i < n; i++)
        {
            while (k != -1 and t[k] != s[i])
                k = p[k];
            k++;
            if (k == m)
                ans.pb(i - m + 1), k = p[k];
        }
    }
};
