import java.util.*;
import java.lang.*;

class Main {

    static int box_total;
    static int[] box_count = new int[25];
    static int[][] boxes = new int[25][25];
    static int[] p1 = new int[2], p2 = new int[2];

    static void find_pos(int num, int[] rowcol) {
        int i, k;
        for (i = 0; i < box_total; i++) {
            for (k = 0; k < box_count[i]; k++) {
                if (boxes[i][k] == num) {
                    rowcol[0] = i;
                    rowcol[1] = k;
                    return ;
                }
            }
        }
    }

    static void add_block(int row, int num) {
        boxes[row][box_count[row]] = num;
        box_count[row]++;
    }

    static void remove_blocks(int row, int col) {
        int i;
        for (i = box_count[row] - 1; i > col; i--) {
            add_block(boxes[row][i], boxes[row][i]);
            box_count[row]--;
        }
    }

    public static void main(String args[]) {
        Scanner inp = new Scanner(System.in);
        int i, k;
        String move, op;

        box_total = inp.nextInt();
        for (i = 0; i < box_total; i++) {
            box_count[i] = 1;
            boxes[i][0] = i;
        }

        while (inp.hasNext()) {
            int a, b, box_c;
            move = inp.next();
            if (move.charAt(0) == 'q')
                break;

            a = inp.nextInt();
            op = inp.next();
            b = inp.nextInt();

            if (a == b)
                continue;

            find_pos(a, p1);
            find_pos(b, p2);

            if (p1[0] == p2[0])
                continue;
            if (a > box_total || b > box_total)
                continue;

            if (move.charAt(0) == 'm')
                remove_blocks(p1[0], p1[1]);

            if (op.charAt(1) == 'n') {
                remove_blocks(p2[0], p2[1]);
                find_pos(a, p1);
                find_pos(b, p2);
            }

            if (move.charAt(0) == 'm') {
                find_pos(b, p2);
                add_block(p2[0], boxes[p1[0]][p1[1]]);
                box_count[p1[0]]--;
            } else {
                box_c = box_count[p1[0]] - p1[1];
                System.arraycopy(boxes[p1[0]], p1[1], boxes[p2[0]], box_count[p2[0]], box_c);
                box_count[p1[0]] -= box_c;
                box_count[p2[0]] += box_c;
            }
        }

        for (i = 0; i < box_total; i++) {
            System.out.print(i + ":");
            for (k = 0; k < box_count[i]; k++)
                System.out.print(" " + boxes[i][k]);

            System.out.print("\n");
        }

        System.exit(0);
    }
}

