#include "nord_runtime.h"
#include <stdio.h>
#include <stdlib.h>

void noreturn runtime_panic(const char* msg) {
    fprintf(stderr, "PANIC: %s\n", msg);
    exit(1);
}

void* arena_alloc(Arena* a, size_t size) {
    if (a->offset + size > a->capacity) {
        size_t new_cap = a->capacity * 2;
        while (new_cap < a->offset + size) new_cap *= 2;
        a->memory = realloc(a->memory, new_cap);
        a->capacity = new_cap;
    }
    void* ptr = (char*)a->memory + a->offset;
    a->offset += size;
    return ptr;
}

Arena* arena_create(size_t initial) {
    Arena* a = malloc(sizeof(Arena));
    a->memory = malloc(initial);
    a->capacity = initial;
    a->offset = 0;
    return a;
}

void arena_reset(Arena* a) {
    a->offset = 0;
}