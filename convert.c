#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

    void div_convert(uint32_t n, int base, char *out){
        char temp[65]; //temp buffer
        int arrayIndex = 0;

        //for zero(0) case
        if (n == 0) {
            strcpy(out, "0");
            return;
        }

        //
        while (n > 0) {
            int remainder = n % base;
            n = n / base;
            if (remainder < 10)
                temp[arrayIndex++] = '0' + remainder;
            else
                temp[arrayIndex++] = 'A' + (remainder - 10);
        }

        //reverse list first in last out
        int outLength = 0;
        for (int i = arrayIndex - 1; i >= 0; i--) {
            out[outLength++] = temp[i];
        }
        out[outLength] = '\0';
    }

    void sub_convert(uint32_t n, int base, char *out) {
        int temp[64]; //temp buffer
        int arrayIndex = 0;

        //finding the biggest power
        uint64_t value = 1; //would overflow when assigned as int
        while (value <= n) {
            temp[arrayIndex ++] = value; //stores value in a numbered "slot" within the array
            value *= base;
        }

        int outLength = 0;
        for (int i = arrayIndex - 1; i >= 0; i-- ) {
            int arrayMove = 0;
            while (n >= temp[i]) { //goes thru arraylist
                n -= temp[i]; // subtract from n
                arrayMove++; //moves down the arraylist
            }

            if (arrayMove < 10)   // out[] is what gets spat out from the function
                out[outLength++] = '0' + arrayMove; // from numbers 0-9
            else
                out[outLength++] = 'A' + (arrayMove - 10); //from numbers a - f

        }
        out[outLength] = '\0'; //ends
    }

    void print_tables(uint32_t n) {
        char bin[33], oct[12], hex[9];

        div_convert(n, 2, bin);
        div_convert(n, 8, oct);
        div_convert(n, 16, hex);
        printf("\nOriginal binary=%s Octal=%s Decimal=%u Hex:%s\n", bin, oct, n, hex);

        uint32_t shifted = n << 3;
        div_convert(shifted, 2, bin);
        div_convert(shifted, 8, oct);
        div_convert(shifted, 16, hex);
        printf("Left shift by 3: binary=%s Octal=%s Decimal= %u Hex=%s\n", bin, oct, shifted, hex);

        uint32_t masked = n & 0xFF;
        sub_convert(masked, 2, bin);
        sub_convert(masked, 8, oct);
        sub_convert(masked, 16, hex);
        printf("And with 0xFF: binary=%s Octal=%s Decimal= %u Hex=%s\n", bin, oct, masked, hex);
    }