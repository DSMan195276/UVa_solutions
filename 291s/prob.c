#include <stdio.h>

/* Valid moves */
int is_connected[6][6] = {
    /* 0, 1, 2, 3, 4, 5 */
    {  0                }, /* 0 */
    {  0, 0, 1, 1, 0, 1 }, /* 1 */
    {  0, 1, 0, 1, 0, 1 }, /* 2 */
    {  0, 1, 1, 0, 1, 1 }, /* 3 */
    {  0, 0, 0, 1, 0, 1 }, /* 4 */
    {  0, 1, 1, 1, 1, 0 }  /* 5 */
};

int cur[8] = {0}; /* Current sequence */
int arr[6][6];     /* Current paths taken */

/* 'deep' is the current link being searched for. Each recursive call
 * increments deep so that we search for the next link
 *
 * 'last' was the last value discovered in our path.
 */
void find_solutions(int deep, int last)
{
    int i;

    for (i = 1; i < 6; i++) { /* Loop over every edge */
        if (is_connected[i][last] && !arr[i][last]) { /* Check if it's adjacent and not
                                                       * already used */
            if (deep < 8) {
                cur[deep] = i; /* Add our number to the sequence */
                arr[i][last] = 1; /* Mark off our location */
                arr[last][i] = 1;
                find_solutions(deep + 1, i);
                arr[i][last] = 0; /* clear the last location */
                arr[last][i] = 0;
            } else {
                printf("%d%d%d%d%d%d%d%d%d\n", /* Print the sequence */
                        cur[0], cur[1],
                        cur[2], cur[3],
                        cur[4], cur[5],
                        cur[6], cur[7],
                        i);
            }
        }
    }
}

int main()
{
    cur[0] = 1;
    find_solutions(1, 1);
    return 0;
}
