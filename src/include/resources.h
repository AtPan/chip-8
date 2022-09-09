#pragma once

#define RESOURCE_MEMORY 0
#define RESOURCE_SCREEN 1
#define RESOURCE_CPU 2
#define RESOURCE_SPEAKER 3

void save_resource(int, void *);
void *get_resource(int);
