#define mid (l + r) >> 1
#define lid id << 1
#define rid lid | 1

struct Data
{
public:
    ll data;
    Data() {}
    Data(int data_) { data = data_; }
};

struct Lazy
{
public:
    ll prop;
    Lazy() {}
    Lazy(int prop_) { prop = prop_; }
};
int n;

struct LazySegTree
{
    Data seg[mxn * 4];
    Lazy lazy[mxn * 4];

    Data merge(Data l, Data r)
    {
        return Data(l.data + r.data);
    }

    void relax(int id, Lazy x, int l)
    {
        seg[id].data += x.prop * l;
        lazy[id].prop += x.prop;
    }

    void relaxT(int l, int r, int id)
    {
        int MID = (l + r) / 2;
        relax(2 * id, lazy[id], MID - l);
        relax(2 * id + 1, lazy[id], r - MID);
        lazy[id].prop = 0;
    }

    void build(int l = 0, int r = n, int id = 1)
    {
        if (l + 1 == r)
        {
            seg[id] = 0;
            return;
        }

        build(l, mid, lid);
        build(mid, r, rid);

        seg[id] = merge(seg[lid], seg[rid]);
    }

    Data get(int s, int t, int l = 0, int r = n, int id = 1)
    {
        if (l >= s && r <= t)
            return seg[id];

        relaxT(l, r, id);

        if (t <= mid)
            return get(s, t, l, mid, lid);

        if (s >= mid)
            return get(s, t, mid, r, rid);

        return merge(get(s, t, l, mid, lid), get(s, t, mid, r, rid));
    }

    void upd(int v, int s, int t, int l = 0, int r = n, int id = 1)
    {
        if (l >= s and r <= t)
        {
            relax(id, Lazy(v), r - l);
            return;
        }

        relaxT(l, r, id);

        if (t <= mid)
            upd(v, s, t, l, mid, lid);
        else if (s >= mid)
            upd(v, s, t, mid, r, rid);
        else
            upd(v, s, t, l, mid, lid), upd(v, s, t, mid, r, rid);

        seg[id] = merge(seg[lid], seg[rid]);
    }
};
