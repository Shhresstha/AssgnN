#include "json_writer.h"
#include <stdio.h>
#include <stdarg.h>

void json_init(json_writer_t *w, char *buf, size_t size) {
    w->buffer = buf;
    w->size   = size;
    w->used   = 0;
    if (size > 0) {
        buf[0] = '\0';
    }
}

bool json_write(json_writer_t *w, const char *fmt, ...) {
    if (w->used >= w->size) {
        return false;
    }

    va_list args;
    va_start(args, fmt);

    int written = vsnprintf(
        &w->buffer[w->used],
        w->size - w->used,
        fmt,
        args
    );

    va_end(args);

    if (written < 0 || (size_t)written >= (w->size - w->used)) {
        return false;
    }

    w->used += (size_t)written;
    return true;
}
