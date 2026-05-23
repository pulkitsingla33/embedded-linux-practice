#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define VECTOR_SIZE_INIT 8

typedef struct dynamic_vector
{
    uint8_t *data;
    int size;
    int capacity;
} DynamicVector;


void dv_init(DynamicVector *dv)
{
    dv->size = 0;
    dv->capacity = VECTOR_SIZE_INIT;
    dv->data = malloc(sizeof(uint8_t) * dv->capacity);
}

void dv_free(DynamicVector *dv)
{
    free(dv->data);
}

int dv_resize(DynamicVector *dv)
{
    dv->capacity *= 2;
    uint8_t *temp_data = realloc(dv->data, sizeof(uint8_t) * dv->capacity);
    if(temp_data)
        dv->data = temp_data;
    else
    {
        printf("Memory Reallocation Failed\n");
        free(dv->data);
        dv->data = NULL;
        dv->size = 0;
        dv->capacity = 0;
        return -1;
    }
    return 0;
}

int dv_push_back(DynamicVector *dv, uint8_t data_val)
{
    if(dv->size == dv->capacity)
    {
        printf("Vector Full, Resizing\n");
        if(dv_resize(dv) == -1)
        {
            printf("Failed to resize vector\n");
            return -1;
        }
    }
    printf("Adding %d to index:%d\n", data_val, dv->size);
    dv->data[dv->size++] = data_val;
    return 0;
}

uint8_t dv_get(DynamicVector *dv, int index)
{
    if(index >= dv->size)
    {
        printf("Index out of bounds\n");
        return -1;
    }
    else
    {
        printf("Fetching %d from index:%d\n", dv->data[index], index);
        return (dv->data[index]);
    }
}

int main()
{
    DynamicVector dv;
    
    dv_init(&dv);

    for(int i = 0; i< 15; i++)
    {
        dv_push_back(&dv, i);
    }

    printf("\n");

    for(int i = 0; i< 15; i++)
    {
        dv_get(&dv, i);
    }

    dv_free(&dv);
    
    return 0;
}