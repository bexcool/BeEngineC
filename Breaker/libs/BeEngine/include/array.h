#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdio.h>

// Type definitions
typedef struct Array {
    void* data;
    size_t size;
} Array;

// Macros
#define REG_GAMEOBJECT(gameObject) \
    _engineCore_registerGameObject(gameObject)

#define UNREG_GAMEOBJECT(id) \
    _engineCore_registerGameObject(id)

/**
 * Allocate a new array struct.
 * 
 * Uses malloc to allocate memory.
 *
 * \param type array data type
 * \param size size of array
 */
#define NEW_ARRAY(_type, _size) \
    ((Array) { .data = (_type*)malloc(sizeof(_type) * _size), .size = _size })

/**
 * Declare a new array struct.
 *
 * \param type array data type
 * \param size size of array
 */
#define ARRAY(_data, _size) \
    ((Array) { .data = _data, .size = _size })

/**
 * Allocate a new array struct with new item in it.
 * 
 * Uses malloc to allocate memory.
 *
 * \param array array struct
 * \param item item to add
 */
#define ARRAY_ADD(array, type, item) { \
    (Array*)array->size += 1; \
    (Array*)array->data = (type*)realloc(array, sizeof(type) * (array->size + 1)); \
}

#define ARRAY_FREE(array) \
    free((Array*)array->data); \
    (Array*)array->data = NULL;

#endif