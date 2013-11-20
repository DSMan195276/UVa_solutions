#include <stdio.h>
#include <string.h>

int grid[1025][1025] = {0};

int main()
{
    int scount;
    int bstrength, rat_count;
    int x, y, size;
    int i, j;
    int max, xmax, ymax;

    scanf("%d\n", &scount);
    for (; scount; scount--) {
        memset(grid, 0, 1025 * 1025 * sizeof(int));
        scanf("%d\n%d\n", &bstrength, &rat_count);

        for (; rat_count; rat_count--) {
            scanf("%d %d %d\n", &x, &y, &size);
            for (i = -bstrength; i <= bstrength; i++)
                for (j = -bstrength; j <= bstrength; j++)
                    if (i + x > 0 && i + x < 1024 && j + y > 0 && j + y < 1024)
                        grid[i+x][j+y]+=size;
        }
        max = grid[0][0];
        xmax = 0;
        ymax = 0;
        for (i = 0; i < 1024; i++) {
            for (j = 0; j < 1024; j++) {
                if (grid[i][j] > max) {
                    max = grid[i][j];
                    xmax = i;
                    ymax = j;
                }
            }
        }
        printf("%d %d %d\n", xmax, ymax, max);
    }

    return 0;
}

