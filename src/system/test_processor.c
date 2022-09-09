#include <stdio.h>
#include <assert.h>
#include "memory.h"
#include "processor.h"

#define alert_test(x) do { printf("Test %d: ", x); fflush(stdout); } while(0)

int main(int, char**);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    memory_instantiate();
    load_rom(argv[1]);
    processor_instantiate();


    for(int i = 0; i < 16; i++) {
        alert_test(i);
        processor_set_register(i, 3 * i);
        assert(processor_get_register(i) == 3 * i);
        printf("Passed\n\n\n");
    }

    alert_test(16);
    push_word(0x123);
    assert(memory_get_word(MAX_STACK - 2) == 0x123);
    printf("Passed\n\n\n");

    alert_test(17);
    assert(pop_word() == 0x123);
    printf("Passed\n\n\n");

    memory_destroy();

    return 0;
}
