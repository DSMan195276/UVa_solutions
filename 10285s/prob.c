
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct pos {
    int row;
    int column;
};

int nums_by_height_count[100];
struct pos nums_by_height[100][10000];
int map[100][100];

int largest_path[100][100];

int rows, columns;

static int check_spot(struct pos p, struct pos target, int max)
{
    int new_max = 0;

    if (target.row >= 0 && target.column >= 0 && target.row < rows && target.column < columns) {
        int val_cur = map[p.row][p.column];
        int val_spot = map[target.row][target.column];

        if (val_spot < val_cur)
            new_max = largest_path[target.row][target.column] + 1;

        if (new_max > max)
            max = new_max;
    }

    return max;
}

int main()
{
    int problems = 0;

    scanf("%d", &problems);

    int i;
    for (i = 0; i < problems; i++) {
        char name[255];
        scanf("%s %d %d", name, &rows, &columns);

        memset(nums_by_height_count, 0, sizeof(nums_by_height_count));
        memset(nums_by_height, 0, sizeof(nums_by_height));
        memset(map, 0, sizeof(map));
        memset(largest_path, 0, sizeof(largest_path));

        int j, k;
        for (j = 0; j < rows; j++) {
            for (k = 0; k < columns; k++) {
                int val;
                scanf("%d", &val);

                map[j][k] = val;

                nums_by_height[val][nums_by_height_count[val]].row = j;
                nums_by_height[val][nums_by_height_count[val]].column = k;
                nums_by_height_count[val]++;
            }
        }

        int total_max = 0;

        for (j = 0; j < 100; j++) {
            for (k = 0; k < nums_by_height_count[j]; k++) {
                struct pos p = nums_by_height[j][k];
                int max = 0;

                max = check_spot(p, (struct pos) { p.row - 1, p.column }, max);
                max = check_spot(p, (struct pos) { p.row + 1, p.column }, max);
                max = check_spot(p, (struct pos) { p.row, p.column + 1 }, max);
                max = check_spot(p, (struct pos) { p.row, p.column - 1 }, max);

                largest_path[p.row][p.column] = max;

                if (max > total_max)
                    total_max = max;
            }
        }

        printf("%s: %d\n", name, total_max + 1);
    }
}

