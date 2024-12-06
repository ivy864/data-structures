#ifndef IV_ALIST_INCLUDED
#define IV_ALIST_INCLUDED

#include <stddef.h>
#include <stdint.h>

typedef struct iv_alist iv_alist;
struct iv_alist {
    void **items;

    uint32_t maxsize;
    uint32_t length;
};

/**
 * initialize new, empty iv_alist
 * @param size initial size of arraylist
 * @param type type stored by arraylist. Either INT_ALIST (size_t) or
 * POINTER_ALIST (void *).
 * @return pointer to the new arraylist
 */
iv_alist *iv_alinit(uint32_t size);

/**
 * free an iv_alist
 * @param alist list to be freed
 */
void iv_alfree(iv_alist *alist);

/**
 * get an item from the alist. return NULL if item is not present.
 * @param alist list to get the item from
 * @param index index of item in arraylist
 * @return item at the given index or, NULL.
 */
void *iv_alget(iv_alist *alist, uint32_t index);

/**
 * put item in alist, replacing value previously stored at given position.
 * @param alist list to insert item into
 * @param item item to be inserted
 * @param index position to insert item at. Must be less than alist length.
 */
void iv_alput(iv_alist *alist, void *item, uint32_t index);

/**
 * add an item to alist.
 * @param alist list to add item to
 * @param item item to add to alist
 * @param index position to insert item at. Must be less than or equal to alist
 * length.
 */
void iv_aladd(iv_alist *alist, void *item, uint32_t index);

/**
 * append item to end of alist
 * @param alist list to append to
 * @param item item to append
 */
void iv_alappend(iv_alist *alist, void *item);

/** remove item from alist and shift items left
 * @param alist list to remove item from
 * @param index index of item to remove
 * @return item removed from list. return NULL if list is empty
 */
void *iv_alremove(iv_alist *alist, uint32_t index);

/**
 * re-size an array of void * and free previous array.
 *
 * @param items array to be resized
 * @param size size of new array
 * @return array with new size containing all elements from items array
 */
void **_iv_alist_resize(void **items, uint32_t old_size, uint32_t size);

#endif
