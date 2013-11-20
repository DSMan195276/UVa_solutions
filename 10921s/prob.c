#include <stdio.h>
#include <ctype.h>

char char_map[26] = {
    '2','2','2',
    '3','3','3',
    '4','4','4',
    '5','5','5',
    '6','6','6',
    '7','7','7','7',
    '8','8','8',
    '9','9','9','9'
};

int main()
{
    char buf[31];
    char *cur;

    while (scanf("%s", buf) != EOF) {
        for (cur = buf; *cur != '\0'; cur++) {
            if (*cur >= 'A' && *cur <= 'Z'
                || *cur >= 'a' && *cur <= 'z') {
                *cur = char_map[(*cur & 0xDF) - 'A'];
            }
        }
        printf("%s\n", buf);
    }
    return 0;
}

