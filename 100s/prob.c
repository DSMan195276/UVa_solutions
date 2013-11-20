#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HIGH_VALUE 1000000

struct nplus {
    long long count;
    long long parent;
};

/*struct nplus table[LARGEST_VALUE] = {0};*/

long long table[HIGH_VALUE] = {0};

void calc_values()
{
    long long i;
    long long highest = 0;
   
    table[1] = 1;
    for (i = 2; i < HIGH_VALUE; i++) {
        long long ans = 0; 
        long long tmp = i;
        if (table[i] != 0)
            continue;

        while (tmp != 1) {
            if (tmp % 2 == 0) {
                tmp /= 2;
                ans++;
            } else {
                tmp = (tmp * 3 + 1);
                ans++;
            }
            if (tmp > highest)
                highest = tmp;
        }
        table[i] = ans;

        for (tmp = i; tmp < HIGH_VALUE; tmp *= 2) {
            ans++;
            table[tmp] = ans;
        }
    }
}

int main(int argc, char **argv)
{
    unsigned int low, high, cur;
    unsigned long long highest = 0;
    unsigned long long i;

    calc_values();

    while (scanf("%d %d", &low, &high) != EOF) {
        unsigned int llow, lhigh;
        getchar();
        if (low > high) {
            llow = high;
            lhigh = low;
        } else {
            llow = low;
            lhigh = high;
        }


        highest = 0;
        for (cur = llow; cur <= lhigh; cur++) {
            register long long count = table[cur];
            if (count > highest)
                highest = count;
        }
        printf("%d %d %d\n", low, high, highest);
    }

    return 0;
}

