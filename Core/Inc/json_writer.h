#ifndef JSON_WRITER_H
#define JSON_WRITER_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    char   *buffer;
    size_t  size;
    size_t  used;
} json_writer_t;

void json_init(json_writer_t *w, char *buf, size_t size);
bool json_write(json_writer_t *w, const char *fmt, ...);

#endif
