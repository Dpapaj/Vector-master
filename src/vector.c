/*!
 * \file       vector.c
 * \author     Horak, Jurena
 * \date       2019.6
 * \brief      Implementation of function.h header file
 * ******************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
/* Includes --------------------------------------------------------------------------------------*/
#include "vector.h"

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
#define UNUSED(x) (void)x

/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/
Vector_t *Vector_Create(size_t initial_size, size_t alloc_step)
{
  // Allocate memory for the vector struct
  Vector_t *vector = malloc(sizeof(Vector_t));
  if (vector == NULL) {
    return NULL;
  }

  // Allocate memory for the items array
  vector->items = malloc(sizeof(Vector_DataType_t) * initial_size);
  if (vector->items == NULL) {
    free(vector);
    return NULL;
  }

  // Set the initial size, next pointer, and allocation step
  vector->size = initial_size;
  vector->next = vector->items;
  vector->alloc_step = alloc_step;

  return vector;
}


Vector_t *Vector_Copy(const Vector_t *const original)
{
  if (original == NULL) {
    return NULL;
  }
  Vector_t *copy = Vector_Create(original->size, original->alloc_step);
  if (copy == NULL) {
    return NULL;
  }
  memcpy(copy->items, original->items, original->size * sizeof(Vector_DataType_t));
  copy->size = original->size;
  copy->next = copy->items + (original->next - original->items);
  return copy;
}

void Vector_Clear(Vector_t *const vector)
{
    if(vector == NULL)
    {
        return;
    }
  // Set the size to zero and the next pointer to the beginning of the items array
  {
  // Free the allocated memory
  free(vector->items);

  // Reset the vector fields
  vector->items = NULL;
  vector->size = 0;
  vector->next = NULL;
}
}

size_t Vector_Length(const Vector_t *const vector)
{
  if (vector == NULL) {
    return SIZE_MAX;
  }

  return vector->next - vector->items;
}

bool Vector_At(const Vector_t *const vector, size_t position, Vector_DataType_t *const value)
{
    if (vector == NULL || position >= Vector_Length(vector)) {
        return false;
    }
    *value = *(vector->items + position);
    return true;
}
bool Vector_Remove(Vector_t *const vector, size_t position)
{
    if (vector == NULL || position >= Vector_Length(vector)) {
        return false;
    }

    // Move elements after the position to the left
    for (size_t i = position; i < Vector_Length(vector) - 1; i++) {
        *(vector->items + i) = *(vector->items + i + 1);
    }

    vector->next--;

    return true;
}

size_t Vector_Append(Vector_t *vector, Vector_DataType_t value)
{
  if (vector == NULL) {
    return SIZE_MAX;
  }

  if (vector->next == vector->items + vector->size) {
    size_t new_size = vector->size + vector->alloc_step;
    Vector_DataType_t *new_items = (Vector_DataType_t *)realloc(vector->items, new_size * sizeof(Vector_DataType_t));

    if (new_items == NULL) {
      return SIZE_MAX;
    }

    vector->items = new_items;
    vector->next = new_items + vector->size;
    vector->size = new_size;
  }

  *vector->next++ = value;
  return vector->next - vector->items - 1;
}
void Vector_Set(Vector_t *const vector, size_t position, Vector_DataType_t value)
{
  if (vector == NULL || position >= vector->size) {
    return;
  }

  if (position < Vector_Length(vector)) {
    vector->items[position] = value;
  }
}

bool Vector_Contains(const Vector_t *const vector, Vector_DataType_t value)
{
   if(vector == 0 || value == 0)
    {
        return false;
    }
  // Iterate over the elements of the vector and check if the value exists
  for (size_t i = 0; i < vector->size; i++) {
    if (vector->items[i] == value) {
      return true;
    }
  }

  return false;
}

size_t Vector_IndexOf(const Vector_t *const vector, Vector_DataType_t value, size_t from)
{
  if(vector == NULL || vector->items == NULL || from >= vector->size)
    {
        return -1;
    }
  // Check if from is within the range of the vector
  if (from >= vector->size) {
    return SIZE_MAX;
  }

  // Iterate over the elements of the vector from the specified position and return the index of the first occurrence of the value
  for (size_t i = from; i < vector->size; i++) {
    if (vector->items[i] == value) {
      return i;
    }
  }

  return SIZE_MAX;
}



void Vector_Fill(const Vector_t *const vector,
                 Vector_DataType_t value,
                 size_t start_position,
                 size_t end_position)
 {
    // Determine the actual range of elements to fill
    size_t length = Vector_Length(vector);
    if (start_position >= length) {
        return;
    }
    if (end_position >= length) {
        end_position = length - 1;
    }

    // Fill the elements with the specified value
    for (size_t i = start_position; i <= end_position; ++i) {
        Vector_Set((Vector_t *)vector, i, value);
    }
}
void Vector_Destroy(Vector_t **const vector)
{
    if (vector == NULL || *vector == NULL) {
        return;
    }
    
    // Deallocate the memory used by the vector.
    free((*vector)->items);
    free(*vector);
    *vector = NULL;;
}

/* Private function definitions ------------------------------------------------------------------*/
