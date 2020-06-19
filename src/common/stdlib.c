#include <common/stdlib.h> 

void memcpy(void * dest, void * src, int bytes) {
    char * d = dest;
    char * s = src;
    for (int i = 0; i < bytes; i++) {
        *(d + i) = *(s + i);
    }
    return;
}

void bzero(void * dest, int bytes) {
    char * d = dest;
    for (int i = 0; i < bytes; i++) {
        d[i] = 0;
    }
    return;
}

char * itoa(int i) {
    int is_negative = i < 0;    
    static char int_string[16];
    bzero(int_string, 16);
    int j = 1;
    
    if (is_negative) {
        i = i * -1;
    }

    while (i > 0) {
        int_string[j] = '0' + (i % 10);
        i /= 10;
        j++;
    }

    if (is_negative) {
        int_string[j] = '-';
    }

    return int_string;
}