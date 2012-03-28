#define _POSIX_C_SOURCE 200112L /* for posix_memalign */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>

#include "microcosmabi.h"

VISIBLE MC_ABI void microcosm__free(void *ptr)
{
    free(ptr);
}

VISIBLE MC_ABI void *microcosm__malloc(size_t size)
{
    return malloc(size);
}

VISIBLE MC_ABI void *microcosm__calloc(size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

VISIBLE MC_ABI void *microcosm__realloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}

VISIBLE MC_ABI int microcosm__posix_memalign(void **memptr, size_t alignment, size_t size)
{
    return posix_memalign(memptr, alignment, size);
}
