#include "AList.h"
#include <stdlib.h>

iv_alist *iv_alinit(uint32_t size) {
    iv_alist *alist = malloc(sizeof(iv_alist));

    alist->maxsize = size;
    alist->length = 0;
    alist->items = malloc(sizeof(void *) * size);

    return alist;
}

void iv_alfree(iv_alist *alist) {
    free(alist->items);
    free(alist);
}

void *iv_alget(iv_alist *alist, uint32_t index) {
    if (index >= alist->length) {
        return NULL;
    }

    return alist->items[index];
}

void iv_alput(iv_alist *alist, void *item, uint32_t index) {
    if (index < alist->length) {
        alist->items[index] = item;
    }
}

void iv_aladd(iv_alist *alist, void *item, uint32_t index) {
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

    void *itm = alist->items[index];
    alist->items[index] = item;

    for (int i = index + 1; i < alist->length; i++) {
        void *tmp = alist->items[i];
        alist->items[i] = itm;
        itm = alist->items[i];
    }
}

void iv_alappend(iv_alist *alist, void *item) {
    iv_aladd(alist, item, alist->length);
}

void *iv_alremove(iv_alist *alist, uint32_t index) {
    if (alist->length >= index) {
        return NULL;
    }

    void *remel; 
    remel = alist->items[index];
    for (int i = index; i < alist->length - 1; i++) {
        alist->items[i] = alist->items[i + 1];
    }
    alist->length -= 1;
     
    return remel;
}

void **_iv_alist_resize(void **items, uint32_t old_size,
                            uint32_t size) {
    void **newitems = malloc(sizeof(void **) * size);
    for (int i = 0; i < old_size; i++) {
        newitems[i] = items[i];
    }

    free(items);

    return newitems;
}
