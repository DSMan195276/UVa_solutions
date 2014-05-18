#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int r;
    int c;
    int len;
} rc;

typedef struct edge {
    struct edge *next;
    int len;
    int target;
} edge;

typedef struct {
    int r;
    int c;

    int usedFlag;

    int edgeCount;
    char bitmap[101];
    edge edges[101];
} alien;

edge *queueStart;

int alienCount = 0;
alien ai[101];

char grid[50][50];

void push_edges(edge *e, int ecount)
{
    edge *j, *p;
    edge *end = e + ecount;
    for (; e != end; e++) {
        for (j = queueStart, p = NULL; j != NULL; p = j, j = j->next) {
            if (e->len < j->len) {
                if (p)
                    p->next = e;
                else
                    queueStart = e;
                e->next = j;
                break;
            }
        }
        if (!j) {
            if (p)
                p->next = e;
            else
                queueStart = e;
        }
    }
}

edge *get_smallest_edge(void)
{
    edge *q;

    while (1) {
        q = queueStart;
        queueStart = queueStart->next;
        if (!ai[q->target].usedFlag) {
            ai[q->target].usedFlag = 1;
            return q;
        }
    }
}

int find_steps(void)
{
    alien *current = ai;
    edge *e;
    int len = 0, i = 0;

    current->usedFlag = 1;
    for (i = 1; i < alienCount; i++) {
        push_edges(current->edges, current->edgeCount);
        e = get_smallest_edge();

        len += e->len;
        current = ai + e->target;
    }

    return len;
}

int find_shortest_path(int r1, int c1, int r2, int c2)
{
    int queueSize = 0;
    int flag[50][50] = {{ 0 }};
    rc edgequeue[2501];
    rc *first = edgequeue;
    rc current = { r1, c1, 0 };

    do {
        if (current.r == r2 && current.c == c2)
            return current.len;

        if (grid[current.r + 1][current.c] != '#' && !flag[current.r + 1][current.c]) {
            edgequeue[queueSize++] = (rc) { current.r + 1, current.c, current.len + 1 };
            flag[current.r + 1][current.c] = 1;
        }
        if (grid[current.r - 1][current.c] != '#' && !flag[current.r - 1][current.c]) {
            edgequeue[queueSize++] = (rc) { current.r - 1, current.c, current.len + 1 };
            flag[current.r - 1][current.c] = 1;
        }
        if (grid[current.r][current.c + 1] != '#' && !flag[current.r][current.c + 1]) {
            edgequeue[queueSize++] = (rc) { current.r, current.c + 1, current.len + 1 };
            flag[current.r][current.c + 1] = 1;
        }
        if (grid[current.r][current.c - 1] != '#' && !flag[current.r][current.c - 1]) {
            edgequeue[queueSize++] = (rc) { current.r, current.c - 1, current.len + 1 };
            flag[current.r][current.c - 1] = 1;
        }

        current = *first;
        first++;
    } while ((first - edgequeue) <= queueSize);

    return 0;
}

int main()
{
    char buf[52];
    int cases, n, r, c, a, a2;
    int nrows, ncols, result;

    scanf("%d\n", &cases);
    for (n = 0; n < cases; n++) {
        alienCount = 0;
        queueStart = NULL;
        memset(grid, 0, 50 * 50);

        scanf("%d %d\n", &ncols, &nrows);
        for (r = 0; r < nrows; r++) {
            memset(buf, 0, 50);
            fgets(buf, 52, stdin);
            memcpy(grid[r], buf, 50);
        }

        for (r = 0; r < nrows; r++) {
            for (c = 0; c < ncols; c++) {
                if (grid[r][c] == 'S' || grid[r][c] == 'A') {
                    memset(ai + alienCount, 0, sizeof *ai);
                    ai[alienCount].r = r;
                    ai[alienCount].c = c;
                    ai[alienCount].edgeCount = 0;
                    alienCount++;
                }
            }
        }

        for (a = 0; a < alienCount; a++) {
            for (a2 = 0; a2 < alienCount; a2++) {
                if (a == a2 || ai[a].bitmap[a2])
                    continue;
                int e = ai[a].edgeCount;
                int len = find_shortest_path(ai[a].r, ai[a].c, ai[a2].r, ai[a2].c);
                ai[a].edges[e].target = a2;
                ai[a].edges[e].len = len;
                ai[a].edgeCount++;

                e = ai[a2].edgeCount;
                ai[a2].edges[e].target = a;
                ai[a2].edges[e].len = len;
                ai[a2].edgeCount++;

                ai[a].bitmap[a2] = 1;
                ai[a2].bitmap[a] = 1;
            }
        }

        result = find_steps();

        printf("%d\n", result);
    }
    return 0;
}

