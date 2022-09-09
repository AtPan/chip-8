#include <stdlib.h>
#include <stdio.h>
#include "processor.h"
#include "screen.h"
#include "memory.h"
#include "error.h"
#include "resources.h"

void fatal_error(ERROR msg, unsigned int code) {
    fprintf(stderr, "FATAL: %s\n", (const char *)msg);
    exit_prog(code);
}

void exit_prog(int code) {
    screen_destroy();

    void *p;

    if((p = get_resource(RESOURCE_MEMORY)) != NULL) {
        memory_destroy((unsigned char *)p);
    }
    if((p = get_resource(RESOURCE_CPU)) != NULL) {
        processor_destroy((struct cpu_t *)p);
    }
    if((p = get_resource(RESOURCE_SCREEN)) != NULL) {
        screen_destroy();
    }
    if((p = get_resource(RESOURCE_SPEAKER)) != NULL) {

    }

    exit(code);
}
