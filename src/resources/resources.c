#include <stdio.h>
#include "chip8.h"
#include "resources.h"

static unsigned char *resources[4] = {NULL, NULL, NULL, NULL};

void save_resource(int resource, void * restrict p) {
    resources[resource] = (unsigned char *)p;
}

void *get_resource(int resource) {
    return resources[resource];
}
