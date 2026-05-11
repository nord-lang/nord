#ifndef NORD_RUNTIME_H
#define NORD_RUNTIME_H

#include <stddef.h>

typedef struct {
    void* memory;
    size_t capacity;
    size_t offset;
} Arena;

void noreturn runtime_panic(const char* msg);
void* arena_alloc(Arena* a, size_t size);
Arena* arena_create(size_t initial);
void arena_reset(Arena* a);

#endif