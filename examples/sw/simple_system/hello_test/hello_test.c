// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include "simple_system_common.h"

int main(int argc, char **argv) {
	int a = 12;
    int b = 34;
    int result;

    asm volatile (
        ".insn r 0x0B, 0x0, 0x00, %0, %1, %2"
        : "=r"(result)        // output
        : "r"(a), "r"(b)      // inputs
    );

    char buf[32];

    int temp = result;
    int idx = 0;
    if (temp == 0) {
        buf[idx++] = '0';
    } else {
        if (temp < 0) {
            putchar('-');
            temp = -temp;
        }
        char rev[16];
        int ridx = 0;
        while (temp > 0) {
            rev[ridx++] = '0' + (temp % 10);
            temp /= 10;
        }
        while (ridx > 0) {
            buf[idx++] = rev[--ridx];
        }
    }
    buf[idx] = '\0';

    puts("ALU_ADD32 result:\n");
    puts(buf);
    putchar('\n');

  return 0;
}
