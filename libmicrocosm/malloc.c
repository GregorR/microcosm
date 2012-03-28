#include <stdio.h>
#include <stdlib.h>

#include "abi.h"
#include "visibility.h"

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
