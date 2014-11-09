#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct spot {
    int len;
    char dir;
    int visited;
};

int best_len, with_swap;

struct spot swap_spot;
int swap_row, swap_col;

int map_rows, map_cols;
struct spot map[100][100];

void search(int row, int col, int cur_len, int have_swap, int s_row, int s_col) {
    int r, c, len;
    char dir;

    if (best_len < cur_len)
        return ;

    map[row][col].visited = 1;

    if (row == 0 && col == 0) {
        if (best_len > cur_len) {
            best_len = cur_len;
            if (have_swap) {
                with_swap = 1;
                swap_spot = map[s_row][s_col];
                swap_row = s_row;
                swap_col = s_col;
            } else {
                with_swap = 0;
            }
        }
        return ;
    }

    for (r = 0; r < map_rows; r++) {
        if (map[r][col].visited)
            continue;

        if (r < row) {
            len = row - r;
            dir = 'S';
        } else {
            len = r - row;
            dir = 'N';
        }

        if (map[r][col].dir == dir && map[r][col].len == len) {
            search(r, col, cur_len + 1, have_swap, s_row, s_col);
        } else if (!have_swap) {
            struct spot save_spot;
            save_spot = map[r][col];
            map[r][col].dir = dir;
            map[r][col].len = len;
            search(r, col, cur_len + 1, 1, r, col);
            map[r][col] = save_spot;
        }
    }

    for (c = 0; c < map_cols; c++) {
        if (map[row][c].visited)
            continue;

        if (c < col) {
            len = col - c;
            dir = 'E';
        } else {
            len = c - col;
            dir = 'W';
        }

        if (map[row][c].dir == dir && map[row][c].len == len) {
            search(row, c, cur_len + 1, have_swap, s_row, s_col);
        } else if (!have_swap) {
            struct spot save_spot;
            save_spot = map[row][c];
            map[row][c].dir = dir;
            map[row][c].len = len;
            search(row, c, cur_len + 1, 1, row, c);
            map[row][c] = save_spot;
        }
    }

    map[row][col].visited = 0;
}

int main() {
    int cas = 0, i, j;

    while (scanf("%d %d", &map_rows, &map_cols), map_rows != 0 && map_cols != 0) {
        cas++;

        memset(map, 0, sizeof(map));
        with_swap = 0;
        best_len = 1000000;

        for (i = 0; i < map_rows; i++) {
            for (j = 0; j < map_cols; j++) {
                if (i == map_rows - 1 && j == map_cols - 1)
                    break;

                scanf("%d%c ", &map[i][j].len, &map[i][j].dir);
            }
        }

        search(map_rows - 1, map_cols - 1, 0, 0, 0, 0);

        printf("Case %d: ", cas);

        if (best_len == 1000000)
            printf("impossible\n");
        else if (with_swap)
            printf("%d %d %d%c %d\n", swap_row, swap_col, swap_spot.len, swap_spot.dir, best_len);
        else
            printf("none %d\n", best_len);

    }

    return 0;
}

