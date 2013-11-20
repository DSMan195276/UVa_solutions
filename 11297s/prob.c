#include <stdio.h>
#include <ctype.h>

int size;
int map[501][501];

int main()
{
    int i, j, querys, x, y, v;
    int xmin, xmax, ymin, ymax, min, max;
    char cmd;
    scanf("%d %d\n", &size, &size);
    for (i = 1; i <= size; i++) {
        for (j = 1; j <= size; j++) {
            scanf("%d", &(map[i][j]));
        }
    }

    scanf("%d\n", &querys);

    for (i = 0; i < querys; i++) {
        scanf("%c", &cmd);
        if (cmd == 'q') {
            scanf("%d %d %d %d\n", &ymin, &xmin, &ymax, &xmax);
            min = map[ymin][xmin];
            max = map[ymin][xmin];
            for (y = ymin; y <= ymax; y++) {
                for (x = xmin; x <= xmax; x++) {
                    if (map[y][x] < min)
                        min = map[y][x];
                    if (map[y][x] > max)
                        max = map[y][x];
                }
            }
            printf("%d %d\n", max, min);
        } else if (cmd == 'c') {
            scanf("%d %d %d\n", &y, &x, &v);
            map[y][x] = v;
        }
    }

    return 0;
}

