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

void dv_resize(DynamicVector *dv)
{
    dv->capacity *= 2;
    uint8_t *old_data = dv->data;
    dv->data = malloc(sizeof(uint8_t) * dv->capacity);
    for(int i = 0; i < dv->size; i++)
    {
        dv->data[i] = old_data[i];
    }
    free(old_data);
}

void dv_push_back(DynamicVector *dv, uint8_t data_val)
{
    if(dv->size == dv->capacity)
    {
        printf("Vector Full, Resizing\n");
        dv_resize(dv);
    }
    printf("Adding %d to index:%d\n", data_val, dv->size);
    dv->data[dv->size++] = data_val;
}

uint8_t dv_get(DynamicVector *dv, int index)
{
    if(index >= dv->size)
        return 0xFF;
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