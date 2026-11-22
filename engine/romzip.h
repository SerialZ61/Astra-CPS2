#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int romzip_prepare(const char *path, int requested_game, char *error, size_t capacity);
int romzip_load(unsigned char *destination, int *written, int index);
typedef void (*RomChunk)(void *context, unsigned offset, const unsigned char *data, unsigned size);
int romzip_stream(int index, RomChunk consume, void *context);
const char *romzip_error(void);
void romzip_release(void);

#ifdef __cplusplus
}
#endif
