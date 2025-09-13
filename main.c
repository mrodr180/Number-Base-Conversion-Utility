#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void div_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);
void sub_convert(uint32_t n, int base, char *out);

int main() {
        char assignment[] = "CS 3505 Assignment 1 - Number Base Conversion";
        char author[] = "Miguel Rodriguez";
        char description[] = "For our first assignment for cs 3503 we were tasked with creating a number base converter using division and subtraction algorithm as well as a print table";
        char buffer[65];

        printf("%s\n\n"
            "# Author \n%s\n\n"
            "# Description\n%s\n\n",assignment, author, description);

     FILE *file = fopen("C:\\Users\\migue\\Downloads\\a1_test_file.txt", "r"); //copy filepath
        if (file == NULL) {
            printf("Error: Could not open file\n");
            return 1;
        }

    FILE *outFile = fopen("output.txt", "w");
    if (!outFile) {
        printf("Error\n");
        return 1;
    }

        char line[256], function[32], expected[65], output[65];
        int lineNumber = 0;
        unsigned int input1, input2;

        while (fgets(line, sizeof(line), file) != NULL) {
            int parse = sscanf(line,"%31s %u %u %64s", function, &input1, &input2, expected);

            if (parse == 4) {
                if (strcmp(function, "div_convert") == 0)
                    div_convert(input1, input2, output);
                else if (strcmp(function, "sub_convert") == 0)
                    sub_convert(input1, input2, output);
                sprintf(line, "Test %d: %s(%u, %u) --> expected: %s, got %s  [%s]\n", lineNumber, function, input1, input2, expected, output,
                strcmp(output, expected) == 0 ? "pass" : "fail");
                printf("%s", line);
                fprintf(outFile, "Test %d: %s(%u, %u) --> expected: %s, got %s  [%s]\n", lineNumber, function, input1, input2, expected, output,
                strcmp(output, expected) == 0 ? "pass" : "fail");
                fprintf(outFile, "%s", line);
                lineNumber++;

            }
            else if (parse ==2 && strcmp(function, "print_tables") == 0) {
                sprintf(line, "Test %d: %s(%u) --> [ FORMATTED OUTPUT CHECK ] ", lineNumber, function, input1);
                fprintf(outFile,"Test %d: %s(%u) --> [ FORMATTED OUTPUT CHECK ] ", lineNumber, function, input1);
                print_tables(input1);
                fprintf(outFile, "%s", line);
                printf("%s", line);
                lineNumber++;
            }
        }
    fclose(file);
    fclose(outFile);
        return 0;
}
