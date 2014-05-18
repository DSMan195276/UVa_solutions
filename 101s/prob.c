#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int box_total;
int box_count[25];
int boxes[25][25] = {{0}};

void find_pos (int num, int *row, int *col) {
    int i, k;
    for (i = 0; i < box_total; i++) {
        for (k = 0; k < box_count[i]; k++) {
            if (boxes[i][k] == num) {
                *row = i;
                *col = k;
                return ;
            }
        }
    }
}

void add_block (int row, int num) {
    boxes[row][box_count[row]] = num;
    box_count[row]++;
}

void remove_blocks(int row, int col) {
    int i;
    for (i = box_count[row] - 1; i > col; i--) {
        add_block(boxes[row][i], boxes[row][i]);
        box_count[row]--;
    }
}

int main() {
    int i, k;
    char move[5], op[5];
    scanf("%d\n", &box_total);
    for (i = 0; i < box_total; i++) {
        box_count[i] = 1;
        boxes[i][0] = i;
    }

    while (scanf("%s", move) != EOF && move[0] != 'q' ) {
        int p1r, p1c, p2r, p2c;
        int a, b;
        int box_c;

        scanf("%d %s %d\n", &a, op, &b);
        find_pos(a, &p1r, &p1c);
        find_pos(b, &p2r, &p2c);
        if (a == b)
            continue;
        if (p1r == p2r)
            continue;
        if (a > box_total || b > box_total)
            continue;

        if (move[0] == 'm')
            remove_blocks(p1r, p1c);

        if (op[1] == 'n') {
            remove_blocks(p2r, p2c);
            find_pos(a, &p1r, &p1c);
            find_pos(b, &p2r, &p2c);
        }

        if (move[0] == 'm') {
            find_pos(b, &p2r, &p2c);
            add_block(p2r, boxes[p1r][p1c]);
            box_count[p1r]--;
        } else {
            box_c = box_count[p1r] - p1c;
            memcpy(boxes[p2r] + box_count[p2r], boxes[p1r] + p1c, box_c * sizeof(int));
            box_count[p1r] -= box_c;
            box_count[p2r] += box_c;
        }
    }

    for (i = 0; i < box_total; i++) {
        printf("%d:", i);
        for (k = 0; k < box_count[i]; k++)
            printf(" %d", boxes[i][k]);

        putchar('\n');
    }

    return 0;
}

