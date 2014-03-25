#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define d double

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    point p1;
    point p2;
} rec;

rec align_r(rec r)
{
    rec ret;
    if (r.p1.x < r.p2.x) {
        ret.p1 = r.p1;
        ret.p2 = r.p2;
    } else {
        ret.p1 = r.p2;
        ret.p2 = r.p1;
    }
    return ret;
}

int get_intersect(rec r1, rec r2, d *x, d *y)
{
    rec tmp;
    int v = 0;

    if (r1.p1.x == r1.p2.x)
        v = 1;

    if (r2.p1.x == r2.p2.x) {
        v = 1;
        tmp = r1;
        r1 = r2;
        r2 = tmp;
    }
    
    d s1 = ((d)(r1.p2.y - r1.p1.y) / (d)(r1.p2.x - r1.p1.x));
    d s2 = ((d)(r2.p2.y - r2.p1.y) / (d)(r2.p2.x - r2.p1.x));

    if (v) {
        if (r2.p1.x == r2.p2.x)
            return 0;

        *x = r1.p1.x;
        *y = s2 * (r1.p1.x - r2.p1.x) + r2.p1.y;
        return 1;
    }

    if (s2 == s1)
        return 0;

    *x = (r1.p1.y - r2.p1.y + s2 * r2.p1.x - s1 * r1.p1.x) / (s2 - s1);
    *y = s2 * (*x - r2.p1.x) + r2.p1.y;

    return 1;
}

int do_seg_intersect(rec r1p, rec r2p)
{
    rec r1 = {0};
    rec r2 = {0};

    r1 = align_r(r1p);
    r2 = align_r(r2p);

    d x, y;
    int c = 1;

    if (!get_intersect(r1, r2, &x, &y))
        return 0;

    if (!(r1.p1.x <= x && r1.p2.x >= x))
        c = 0;

    if (!(r2.p1.x <= x && r2.p2.x >= x))
        c = 0;

    if (!((r1.p1.y <= r1.p2.y) ? (r1.p1.y <= y && r1.p2.y >= y) : (r1.p1.y >= y && r1.p2.y <= y)))
        c = 0;

    if (!((r2.p1.y <= r2.p2.y) ? (r2.p1.y <= y && r2.p2.y >= y) : (r2.p1.y >= y && r2.p2.y <= y)))
        c = 0;

    return c;
}

int main(void)
{
    int test = 0;

    while (1) {
        test++;

        int nob;
        scanf("%d\n", &nob);
        if (nob == 0)
            return 0;

        rec b[nob];

        for (int i = 0; i < nob; i++)
            scanf("%d %d %d %d\n", &b[i].p1.x, &b[i].p1.y, &b[i].p2.x, &b[i].p2.y);

        int children;
        scanf("%d\n", &children);

        point c[children];
        for (int i = 0; i < children; i++)
            scanf("%d %d\n", &c[i].x, &c[i].y);

        int parent;
        scanf("%d\n", &parent);

        point p[parent];
        for (int i = 0; i < parent; i++)
            scanf("%d %d\n", &p[i].x, &p[i].y);

        for (int i = 0; i < parent; i++) {
            int children_s = 0;
            for (int j = 0; j < children; j++) {
                int flag = 0;
                for (int k = 0; k < nob; k++) {
                    rec r1;
                    r1.p1 = p[i];
                    r1.p2 = c[j];
                    if (do_seg_intersect(r1, b[k]))
                        flag = 1;
                }
                if (flag == 0)
                    children_s++;
            }
            printf("Case %d, Position %d: Children seen: %d\n", test, i + 1, children_s);
        }
        printf("\n");
    }
}

