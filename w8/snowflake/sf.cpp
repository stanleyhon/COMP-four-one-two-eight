#include <iostream>
#include <stdio.h>

struct snowflake {
    int arr[6];
    struct snowflake * next;
};

#define PRIME 94949

snowflake* hash[PRIME];

typedef struct snowflake snowflake;

bool match (snowflake * s1, snowflake * s2) {
    for (int offset = 0; offset < 6; offset++) {
        // try match with an offset of zero
        int matched;
        for (matched = 0; matched < 6; matched++) {
            int offsetIndex = (offset + matched) % 6;
            if (s1->arr[offsetIndex] != s2->arr[matched]) {
                break;
            }
        }

        if (matched == 6) { // we matched entirely! return true;
            return true;
        }

        // No? Try reversing that shit as well and trying
        for (matched = 0; matched < 6; matched++) {
            int offsetIndex = (offset + matched) % 6;
            if (s1->arr[offsetIndex] != s2->arr[5-matched]) {
                break;
            }
        }
        
        if (matched == 6) { // we matched entirely! return true;
            return true;
        }

    }
    return false;
}

bool hashThatShit (int temp[6]) {
    snowflake * add = new struct snowflake;
    add->next = NULL;

    int sum = 0;
    for (int i = 0; i < 6; i++) {
        sum += temp[i] % PRIME;
        add->arr[i] = temp[i];
    }
    sum = sum % PRIME;

    if (hash[sum] == NULL) { // no possibility of match yet just push
        hash[sum] = add;
    } else if (hash[sum] != NULL) { // possibility of match
        snowflake * current = hash[sum];
        if (match (current, add) == true) {
            return true;
        }
        while (current->next != NULL) {
            current = current->next;

            if (match (current, add) == true) {
                return true;
            }
        }

        current->next = add;
    }
    return false;
}

int main (void) {
    int numSnowflakes;
    scanf ("%d", &numSnowflakes);
    while (numSnowflakes--) {
        int temp[6];
        scanf ("%d %d %d %d %d %d", temp, temp + 1, temp + 2, temp + 3, temp + 4, temp + 5);

        if (hashThatShit (temp) == true) {
            printf ("Twin snowflakes found.\n");
            return 0;
        }
    }

    printf ("No two snowflakes are alike.\n");
    return 0;
}


        

