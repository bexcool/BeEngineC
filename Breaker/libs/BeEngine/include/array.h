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
#define DEFINE_ARRAY(name, itemType) \
    typedef struct name {            \
        itemType* items;             \
        size_t size;                 \
        size_t _capacity;            \
    } name;

#define ARRAY_INIT(arrayStruct)    \
    {                              \
        arrayStruct.size = 0;      \
        arrayStruct._capacity = 0; \
        arrayStruct.items = NULL;  \
    }

/**
 * Allocate a new array struct.
 *
 * Uses malloc to allocate memory.
 *
 * \param type array data type
 * \param size size of array
 */
#define ARRAY_NEW(arrayStruct, itemType, _size)                             \
    {                                                                       \
        arrayStruct.items = (itemType*)malloc(sizeof(itemType) * size * 2); \
        arrayStruct.size = _size;                                           \
        arrayStruct._capacity = _size * 2;                                  \
    }

#define ARRAY_ADD(arrayStruct, itemType, itemToAdd)                                                              \
    {                                                                                                            \
        if (arrayStruct.size + 1 > arrayStruct._capacity) {                                                      \
            if (arrayStruct._capacity == 0) arrayStruct._capacity = 1;                                           \
            arrayStruct._capacity *= 2;                                                                          \
            arrayStruct.items = (itemType*)realloc(arrayStruct.items, sizeof(itemType) * arrayStruct._capacity); \
        }                                                                                                        \
        arrayStruct.items[arrayStruct.size++] = itemToAdd;                                                       \
    }

#define ARRAY_REMOVE(arrayStruct, itemType, itemIndex)                                                           \
    {                                                                                                            \
        for (size_t i = itemIndex; i < arrayStruct.size - 1; i++) {                                              \
            arrayStruct.items[i] = arrayStruct.items[i + 1];                                                     \
        }                                                                                                        \
        arrayStruct.size -= 1;                                                                                   \
        if (arrayStruct._capacity / 2 >= arrayStruct.size) {                                                     \
            arrayStruct._capacity /= 2;                                                                          \
            arrayStruct.items = (itemType*)realloc(arrayStruct.items, sizeof(itemType) * arrayStruct._capacity); \
        }                                                                                                        \
    }

#define ARRAY_REMOVE_CLEAN(arrayStruct, itemType, itemIndex)                                                     \
    {                                                                                                            \
        free(arrayStruct.items[itemIndex]);                                                                      \
        arrayStruct.items[itemIndex] = NULL;                                                                     \
        for (size_t i = itemIndex; i < arrayStruct.size - 1; i++) {                                              \
            arrayStruct.items[i] = arrayStruct.items[i + 1];                                                     \
        }                                                                                                        \
        arrayStruct.size -= 1;                                                                                   \
        if (arrayStruct._capacity / 2 >= arrayStruct.size) {                                                     \
            arrayStruct._capacity /= 2;                                                                          \
            arrayStruct.items = (itemType*)realloc(arrayStruct.items, sizeof(itemType) * arrayStruct._capacity); \
        }                                                                                                        \
    }

#define ARRAY_CONTAINS(arrayStruct, itemType, propertyToCheck, valueToCheck) ({ \
    int result = 0;                                                             \
    for (size_t i = 0; i < arrayStruct.size; i++) {                             \
        if (arrayStruct.items[i] propertyToCheck == valueToCheck) {             \
            result = 1;                                                         \
            break;                                                              \
        }                                                                       \
    }                                                                           \
    result;                                                                     \
})

#define ARRAY_FIND_INDEX(arrayStruct, itemType, propertyToCheck, valueToCheck) ({ \
    size_t index = -1;                                                            \
    for (size_t i = 0; i < arrayStruct.size; i++) {                               \
        if (arrayStruct.items[i] propertyToCheck == valueToCheck) {               \
            index = i;                                                            \
            break;                                                                \
        }                                                                         \
    }                                                                             \
    index;                                                                        \
})

#define ARRAY_CLEAN(arrayStruct)  \
    {                             \
        free(arrayStruct.items);  \
        arrayStruct.items = NULL; \
    }

#endif