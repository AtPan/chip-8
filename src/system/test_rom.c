#include <stdio.h>
#include "memory.h"

int main(int, char**);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        return 1;
    }

    memory_instantiate();

    printf("Loading rom... ");
    fflush(stdout);
    load_rom(argv[1]);
    printf("Loaded\n\n\n");





    memory_destroy();

    return 0;
}
