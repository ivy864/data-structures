#include "AList.h"
#include <stdlib.h>

iv_alist *iv_alinit(uint32_t size) {
    iv_alist *alist = malloc(sizeof(iv_alist));

    alist->maxsize = size;
    alist->length = 0;
    alist->items = malloc(sizeof(iv_alitem) * size);

    return alist;
}

void iv_alfree(iv_alist *alist) {
    free(alist->items);
    free(alist);
}

iv_alitem iv_alget(iv_alist *alist, uint32_t index) {
    if (index >= alist->length) {
        return (iv_alitem)NULL;
    }

    return alist->items[index];
}

void iv_alput(iv_alist *alist, iv_alitem item, uint32_t index) {
    if (index < alist->length) {
        alist->items[index] = item;
    }
}

void _iv_aladd(iv_alist *alist, iv_alitem item, uint32_t index) {
    if (index > alist->length) {
        return;
    }

    alist->length += 1;

    // perform resize if necicary
    if (alist->length > alist->maxsize) {
        alist->items =
            _iv_alist_resize(alist->items, alist->maxsize, alist->maxsize * 2);
        alist->maxsize *= 2;
    }

    iv_alitem itm = alist->items[index];
    alist->items[index] = item;

    for (int i = index + 1; i < alist->length; i++) {
        iv_alitem tmp = alist->items[i];
        alist->items[i] = itm;
        itm = alist->items[i];
    }
}

iv_alitem *_iv_alist_resize(iv_alitem *items, uint32_t old_size,
                            uint32_t size) {
    iv_alitem *newitems = malloc(sizeof(iv_alitem) * size);
    for (int i = 0; i < old_size; i++) {
        newitems[i] = items[i];
    }

    free(items);

    return newitems;
}
