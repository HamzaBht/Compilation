#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct DataItem *hashArray[SIZE];
struct DataItem *dummyItem;
struct DataItem *item;

// struct DataItem *delete (struct DataItem *item)
// {
//     int hashindx = item->key;

//     //move in array until an empty
//     while (hashArray[hashindx] != NULL)
//     {

//         if (hashArray[hashindx]->key == hashindx)
//         {
//             struct DataItem *temp = hashArray[hashindx];

//             //assign a dummy item at deleted position
//             hashArray[hashindx] = dummyItem;
//             return temp;
//         }

//         //go to next cell
//         ++hashindx;

//         //wrap around the table
//         hashindx %= SIZE;
//     }

//     return NULL;
// }

