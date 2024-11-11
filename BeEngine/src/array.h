#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdio.h>
#include <stdlib.h>

// Macros

/**
 * Typedef a new array struct.
 * 
 * Enter item type without the array pointer. Item type of "char" will automatically become "char*" array.
 * Using pointers as items "char*" will result in a "char**" array.
 *
 * \param name name of the array
 * \param itemType type of the items
 */
#define PREPARE_ARRAY(name, itemType) \
    typedef struct name { \
        itemType* items; \
        size_t size; \
        size_t _capacity; \
    } name;

#define ARRAY_INIT(arrayStruct) \
    arrayStruct.size = 0; \
    arrayStruct._capacity = 0;

/**
 * Allocate a new array struct.
 * 
 * Uses malloc to allocate memory.
 *
 * \param type array data type
 * \param size size of array
 */
#define ARRAY_NEW(arrayStruct, itemType, _size) \
    arrayStruct.items = (itemType*)malloc(sizeof(itemType) * size * 2); \
    arrayStruct.size = _size; \
    arrayStruct._capacity = _size * 2;

#define ARRAY_ADD(arrayStruct, itemType, itemToAdd) \
    if (arrayStruct.size + 1 > arrayStruct._capacity) { \
        if (arrayStruct._capacity == 0) arrayStruct._capacity = 1; \
        arrayStruct._capacity *= 2; \
        arrayStruct.items = (itemType*)realloc(arrayStruct.items, sizeof(itemType) * arrayStruct._capacity); \
    } \
    arrayStruct.items[arrayStruct.size++] = itemToAdd;

#define ARRAY_CLEAN(arrayStruct) \
    free(arrayStruct.items); \
    arrayStruct.items = NULL;

#endif