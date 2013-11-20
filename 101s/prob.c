#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int box_total;
int box_count[25];
int boxes[25][25] = {0};

struct pos {
    int row;
    int col;
};

struct pos find_pos (int num) {
    struct pos p;
    int i, k;
    for (i = 0; i < box_total; i++) {
        for (k = 0; k < box_count[i]; k++) {
            if (boxes[i][k] == num) {
                p.row = i;
                p.col = k;
                return p;
            }
        }
    }
}

void add_block (int row, int num) {
    boxes[row][box_count[row]] = num;
    box_count[row]++;
}

void print_arr(int box_total)
{
    int i, k;
    for (i = 0; i < box_total; i++) {
        printf("%d:", i);
        for (k = 0; k < box_count[i]; k++)
            printf(" %d", boxes[i][k]);

        putchar('\n');
    }
}

#define REMOVE_BLOCKS(pos) \
    do { \
        int i; \
        for (i = box_count[pos.row] - 1; i > pos.col; i--) { \
            add_block(boxes[pos.row][i], boxes[pos.row][i]); \
            box_count[pos.row]--; \
        } \
    } while (0)

int main() {
    int i, k;
    char move[5], op[5];
    scanf("%d", &box_total);
    getchar();
    for (i = 0; i < box_total; i++) {
        box_count[i] = 1;
        boxes[i][0] = i;
    }

    while (scanf("%s", move) != EOF && move[0] != 'q' ) {
        struct pos p1, p2;
        int a, b;
        int box_c;

        getchar();
        scanf("%d %s %d", &a, op, &b);
        p1 = find_pos(a);
        p2 = find_pos(b);
        if (a == b)
            continue;
        if (p1.row == p2.row)
            continue;
        if (a > box_total || b > box_total)
            continue;

        switch(move[0]) {
        case 'm':
            REMOVE_BLOCKS(p1);
            switch(op[1]) {
            case 'n':
                REMOVE_BLOCKS(p2);
                p1 = find_pos(a);
                break;
            }
            p2 = find_pos(b);
            add_block(p2.row, boxes[p1.row][p1.col]);
            box_count[p1.row]--;
            break;
        case 'p':
            switch(op[1]) {
            case 'n':
                REMOVE_BLOCKS(p2);
                p2 = find_pos(b);
                break;
            }
            box_c = box_count[p1.row] - p1.col;
            memcpy(boxes[p2.row] + box_count[p2.row], boxes[p1.row] + p1.col, box_c * sizeof(long long));
            box_count[p1.row] -= box_c;
            box_count[p2.row] += box_c;
            break;
        }
    }

    print_arr(box_total);

    return 0;
}

