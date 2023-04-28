#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "interface.h"

void drawBorder(WINDOW* mainWin) {
    if(wborder(mainWin, '|', '|', '_', '_', '*','*', '*', '*' ) < 0) {
        fprintf(stderr, "Error creating border.\n");
        exit(EXIT_FAILURE);
    }
}