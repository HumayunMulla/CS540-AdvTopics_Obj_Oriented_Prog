/* Using Include Guards */
#ifndef _DEQUE_HPP_
#define _DEQUE_HPP_

/*  headers are included as there are needed
    for certain operations down the line */
#include <iostream>
#include <stdlib.h>
#include <string.h>

/*  Default Initial Deque_capacity which would be
    used when allocating memory in malloc
    */
#define MAGNITUDE 1000

#define Deque_DEFINE(t)                                                                          \
/* Forward Declarations of structures */                                                         \
struct Deque_##t##_Iterator;                                                                     \
struct Deque_##t##_Data_Element;                                                                 \
struct Deque_##t;                                                                                \
/*  MyClass Iterator structure to traverse in deque using iterator */                            \
struct                                                                                           \
Deque_##t##_Iterator                                                                             \
{                                                                                                \
    size_t index;                                                                                \
    Deque_##t *deque;                                                                            \
                                                                                                 \
    /*  Not changing the function names as the same names belong in the test.cpp file */         \
    t &(*deref)(Deque_##t##_Iterator *iterator);                                                 \
    void (*inc)(Deque_##t##_Iterator *iterator);                                                 \
    void (*dec)(Deque_##t##_Iterator *iterator);                                                 \
};                                                                                               \
/*  MyClass Data Elements structure containing elements in the deque */                          \
struct                                                                                           \
Deque_##t##_Data_Element                                                                         \
{                                                                                                \
    t item;                                                                                      \
    bool (*is_less_than)(const t &, const t &);                                                  \
};                                                                                               \
/* This is token glueing operator for Deque_MyClass */                                           \
struct                                                                                           \
Deque_##t                                                                                        \
{                                                                                                \
    /*  Size variables */                                                                        \
    size_t deque_length;                                                                         \
    size_t deque_capacity;                                                                       \
                                                                                                 \
    /*  index pointers to point beginning and end of deque */                                    \
    size_t begin_index;                                                                          \
    size_t end_index;                                                                            \
                                                                                                 \
    Deque_##t##_Data_Element *data_array;                                                        \
    char type_name[sizeof("Deque_" #t)] = "Deque_" #t;                                           \
                                                                                                 \
    /*  Boolean fucntion to compare */                                                           \
    bool (*is_less_than)(const t &, const t &);                                                  \
                                                                                                 \
    /** DEQUE - Element access front - access the first element, */                              \
    /*  back - access the last element at - access specified element with bounds checking */     \
    t &(*front)(Deque_##t *deque);                                                               \
    t &(*back)(Deque_##t *deque);                                                                \
    t &(*at)(Deque_##t *deque, size_t index);                                                    \
                                                                                                 \
    /** DEQUE - Deque_capacity size - returns the number of elements */                          \
    /* empty - checks whether the container is empty  */                                         \
    size_t (*size)(Deque_##t *deque);                                                            \
    bool (*empty)(Deque_##t *deque);                                                             \
                                                                                                 \
    /** DEQUE - Modifiers */                                                                     \
    /*  push_back - adds an element to the end */                                                \
    /*  pop_back - removes the last element */                                                   \
    /*  push_front - inserts an element to the beginning */                                      \
    /*  pop_front - removes the first element */                                                 \
    /*  resize - changes the number of elements stored */                                        \
    /*  clear - clears the contents  */                                                          \
    void (*clear)(Deque_##t *deque);                                                             \
    void (*push_back)(Deque_##t *deque, const t item);                                           \
    void (*push_front)(Deque_##t *deque, const t item);                                          \
    void (*pop_front)(Deque_##t *deque);                                                         \
    void (*pop_back)(Deque_##t *deque);                                                          \
                                                                                                 \
    /** DEQUE - Destructor to clear all the memory */                                            \
    void (*dtor)(Deque_##t *deque);                                                              \
                                                                                                 \
    /** DEQUE - Comparison function to compare two objects */                                    \
    int (*compare_##t)(const void *item_1_ptr, const void *item_2_ptr);                          \
                                                                                                 \
    /** DEQUE - sort() Func to sort the elements & handle Professor's new Test.cpp conditions */ \
    void (*sort)(Deque_##t * deque, Deque_##t##_Iterator start,                                  \
                Deque_##t##_Iterator last);                                                      \
                                                                                                 \
    /** DEQUE - Iterators begin - returns an iterator to the beginning */                        \
    /*  end - returns an iterator to the end */                                                  \
    Deque_##t##_Iterator (*begin)(Deque_##t * deque);                                            \
    Deque_##t##_Iterator (*end)(Deque_##t * deque);                                              \
};                                                                                               \
                                                                                                 \
/*  Forward Declarations of functions */                                                         \
void Deque_##t##_Iterator_ctor(Deque_##t##_Iterator *iterator, Deque_##t *deque);                \
bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator iterator_1,                                 \
                                Deque_##t##_Iterator iterator_2);                                \
void clear(Deque_##t *deque);                                                                    \
void dtor(Deque_##t *deque);                                                                     \
void sort(Deque_##t *deque, Deque_##t##_Iterator start, Deque_##t##_Iterator last);              \
int compare_##t(const void *item_1_ptr, const void *item_2_ptr);                                 \
t &deref(Deque_##t##_Iterator *iterator);                                                        \
void inc(Deque_##t##_Iterator *iterator);                                                        \
void dec(Deque_##t##_Iterator *iterator);                                                        \
                                                                                                 \
/*  size() Func - returns the size of deque. Earlier I had used int but after Professor's */     \
/*  & TA's feedback changed to size_t as test.cpp has an assertion to check with size_t */       \
size_t                                                                                           \
size(Deque_##t *deque)                                                                           \
{                                                                                                \
    return deque->deque_length;                                                                  \
}                                                                                                \
                                                                                                 \
/*  Resize() Func - This is very critical function as I was getting valgrind issues */           \
/*  when the memory was not allocated correctly, therefore I have made changes using */          \
/*  memmove() to handle Professor's test.cpp rigourous testing */                                \
void                                                                                             \
resize(Deque_##t *deque)                                                                         \
{                                                                                                \
    Deque_##t##_Data_Element *data_array_new = (Deque_##t##_Data_Element *)                      \
        malloc(sizeof(Deque_##t##_Data_Element) * deque->deque_capacity * 2);                    \
                                                                                                 \
    /*  memmove() function, here is where the magic is, used instead of memcpy */                \
    /*  memmove() used to handle if the source and destination blokcs of memory overlaps */      \
    if (deque->begin_index < deque->end_index) {                                                 \
        memmove(data_array_new, deque->data_array + deque->begin_index,                          \
            (deque->end_index - deque->begin_index) * sizeof(Deque_##t##_Data_Element));         \
    }                                                                                            \
    else {                                                                                       \
        memmove(data_array_new, deque->data_array + deque->begin_index,                          \
            (deque->deque_capacity - deque->begin_index) * sizeof(Deque_##t##_Data_Element));    \
        memmove(data_array_new + (deque->deque_capacity - deque->begin_index), deque->data_array,\
            deque->end_index * sizeof(Deque_##t##_Data_Element));                                \
    }                                                                                            \
    /*  Reset all the variables supposedly if the function is called again to */                 \
    /*  resuse and to pass the rigorous test.cpp */                                              \
    deque->begin_index = 0;                                                                      \
    deque->end_index = deque->deque_capacity - 1;                                                \
    deque->deque_capacity = deque->deque_capacity * 2;                                           \
    free(deque->data_array);                                                                     \
    deque->data_array = data_array_new;                                                          \
}                                                                                                \
                                                                                                 \
/** DEQUE - Modifiers : push_back() - adds an element to the end */                              \
void                                                                                             \
push_back(Deque_##t *deque, const t item)                                                        \
{                                                                                                \
    /*  Instantiate the Data Element Struct */                                                   \
    Deque_##t##_Data_Element element;                                                            \
    element.item = item;                                                                         \
    element.is_less_than = deque->is_less_than;                                                  \
                                                                                                 \
    /* Check the deque_capacity, if required resize the deque */                                 \
    if (deque->deque_capacity - 1 == deque->deque_length) {                                      \
        resize(deque);                                                                           \
    }                                                                                            \
    *(deque->data_array + deque->end_index) = element;                                           \
    deque->end_index = (deque->end_index + 1) % deque->deque_capacity;                           \
                                                                                                 \
    /*  Increament the size of deque_length object after push_back operation */                  \
    ++deque->deque_length;                                                                       \
}                                                                                                \
                                                                                                 \
/** DEQUE - Modifiers : push_front - inserts an element to the beginning */                      \
void                                                                                             \
push_front(Deque_##t *deque, const t item)                                                       \
{                                                                                                \
    Deque_##t##_Data_Element element;                                                            \
    element.item = item;                                                                         \
    element.is_less_than = deque->is_less_than;                                                  \
                                                                                                 \
    /* Check the deque_capacity, if required resize the deque */                                 \
    if (deque->deque_capacity - 1 == deque->deque_length) {                                      \
        resize(deque);                                                                           \
    }                                                                                            \
    /*  Changing the beginning index, if element and point accordingly */                        \
    if (deque->begin_index == 0) {                                                               \
        deque->begin_index = deque->deque_capacity - 1;                                          \
    }                                                                                            \
    else                                                                                         \
        deque->begin_index = deque->begin_index - 1;                                             \
                                                                                                 \
    *(deque->data_array + deque->begin_index) = element;                                         \
                                                                                                 \
    /*  Increament the size of deque_length object after push_front operation */                 \
    ++deque->deque_length;                                                                       \
}                                                                                                \
                                                                                                 \
/** DEQUE - Modifiers : pop_front - removes the first element. Adjusting the index and dec */    \
/*  the deque_length solves the purpose, do not use resize()   */                                \
void                                                                                             \
pop_front(Deque_##t *deque)                                                                      \
{                                                                                                \
    /*  Decreament the size of deque_length object after pop_front operation */                  \
    --deque->deque_length;                                                                       \
                                                                                                 \
    /* Adjust the front index after element is popped */                                         \
    deque->begin_index = (deque->begin_index + 1) % deque->deque_capacity;                       \
}                                                                                                \
                                                                                                 \
/** DEQUE - Modifiers : pop_back - removes the last element   */                                 \
void                                                                                             \
pop_back(Deque_##t *deque)                                                                       \
{                                                                                                \
    /*  Decreament the size of deque_length object after pop_front operation */                  \
    --deque->deque_length;                                                                       \
                                                                                                 \
    /* Adjust the end index after element is popped */                                           \
    if(deque->end_index == 0)                                                                    \
        deque->end_index = deque->deque_capacity - 1;                                            \
    else                                                                                         \
        deque->end_index = deque->end_index - 1;                                                 \
}                                                                                                \
                                                                                                 \
/** DEQUE - Element access front - access the first element */                                   \
t                                                                                                \
&front(Deque_##t *deque)                                                                         \
{                                                                                                \
    return (deque->data_array + deque->begin_index)->item;                                       \
}                                                                                                \
                                                                                                 \
/** DEQUE - Element access back - access the last element   */                                   \
t                                                                                                \
&back(Deque_##t *deque)                                                                          \
{                                                                                                \
    return (deque->data_array + deque->end_index - 1)->item;                                     \
}                                                                                                \
                                                                                                 \
/** DEQUE - Deque_capacity empty - checks whether the container is empty   */                    \
bool                                                                                             \
empty(Deque_##t *deque)                                                                          \
{                                                                                                \
    return deque->deque_length == 0;                                                             \
}                                                                                                \
/** DEQUE - Element access at - access specified element with bounds checking   */               \
t                                                                                                \
&at(Deque_##t *deque, size_t index)                                                              \
{                                                                                                \
    return (deque->data_array + ((index + deque->begin_index) % deque->deque_capacity))->item;   \
}                                                                                                \
                                                                                                 \
/*  Deque_MyClass_Iterator Constructor Initialization*/                                          \
void                                                                                             \
Deque_##t##_Iterator_ctor (Deque_##t##_Iterator *iterator, Deque_##t *deque)                     \
{                                                                                                \
    iterator->deref = deref;                                                                     \
    iterator->inc = inc;                                                                         \
    iterator->dec = dec;                                                                         \
    iterator->deque = deque;                                                                     \
}                                                                                                \
                                                                                                 \
/** DEQUE - Iterators begin - returns an iterator to the beginning    */                         \
Deque_##t##_Iterator                                                                             \
begin(Deque_##t *deque)                                                                          \
{                                                                                                \
    Deque_##t##_Iterator iterator;                                                               \
    Deque_##t##_Iterator_ctor(&iterator, deque);                                                 \
    iterator.index = deque->begin_index;                                                         \
    return iterator;                                                                             \
}                                                                                                \
                                                                                                 \
/** DEQUE - Iterators end - returns an iterator to the end   */                                  \
Deque_##t##_Iterator                                                                             \
end(Deque_##t *deque)                                                                            \
{                                                                                                \
    Deque_##t##_Iterator  iterator;                                                              \
    Deque_##t##_Iterator_ctor(&iterator, deque);                                                 \
    iterator.index = deque->end_index;                                                           \
    return iterator;                                                                             \
}                                                                                                \
                                                                                                 \
/*  Deque_MyClass Constructor Initialization*/                                                   \
void                                                                                             \
Deque_##t##_ctor(Deque_##t *deque, bool (*is_less_than)(const t &, const t &))                   \
{                                                                                                \
    deque->data_array = (Deque_##t##_Data_Element *)                                             \
                        malloc(sizeof(Deque_##t##_Data_Element) * MAGNITUDE);                    \
    deque->deque_capacity = MAGNITUDE;                                                           \
    deque->is_less_than = is_less_than;                                                          \
    deque->deque_length = 0;                                                                     \
    deque->begin_index = 0;                                                                      \
    deque->end_index = 0;                                                                        \
    deque->push_back = push_back;                                                                \
    deque->push_front = push_front;                                                              \
    deque->pop_back = pop_back;                                                                  \
    deque->pop_front = pop_front;                                                                \
    deque->front = front;                                                                        \
    deque->back = back;                                                                          \
    deque->size = size;                                                                          \
    deque->empty = empty;                                                                        \
    deque->clear = clear;                                                                        \
    deque->dtor = dtor;                                                                          \
    deque->begin = begin;                                                                        \
    deque->end = end;                                                                            \
    deque->at = at;                                                                              \
    deque->sort = sort;                                                                          \
    deque->compare_##t = compare_##t;                                                            \
}                                                                                                \
                                                                                                 \
/** DEQUE - Modifiers clear - clears the contents    */                                          \
void                                                                                             \
clear(Deque_##t *deque)                                                                          \
{                                                                                                \
    deque->begin_index = 0;                                                                      \
    deque->end_index = 0;                                                                        \
    deque->deque_length = 0;                                                                     \
}                                                                                                \
                                                                                                 \
/** DEQUE - Destructor to clear all the memory */                                                \
void                                                                                             \
dtor(Deque_##t *deque)                                                                           \
{                                                                                                \
    free(deque->data_array);                                                                     \
    deque->data_array = NULL;                                                                    \
    deque->deque_capacity = 0;                                                                   \
    deque->clear(deque);                                                                         \
}                                                                                                \
                                                                                                 \
/*  sort() Func to call the std::qsort [Standard Template Quick Sort] */                         \
void                                                                                             \
sort(Deque_##t *deque, Deque_##t##_Iterator start, Deque_##t##_Iterator last)                    \
{                                                                                                \
    if (start.index > last.index) {                                                              \
        Deque_##t##_Data_Element *data_array_new = (Deque_##t##_Data_Element *)                  \
        malloc(sizeof(Deque_##t##_Data_Element) * deque->deque_capacity);                        \
        memmove(data_array_new, deque->data_array + deque->begin_index,                          \
            (deque->deque_capacity - deque->begin_index) * sizeof(Deque_##t##_Data_Element));    \
        memmove(data_array_new + (deque->deque_capacity - deque->begin_index),                   \
            deque->data_array, deque->end_index * sizeof(Deque_##t##_Data_Element));             \
                                                                                                 \
        start.index = start.index - deque->begin_index;                                          \
        last.index = ((deque->deque_capacity - 1) - deque->begin_index) + last.index;            \
        deque->begin_index = 0;                                                                  \
        deque->end_index = ((deque->deque_capacity - 1) - deque->begin_index) + deque->end_index;\
        free(deque->data_array);                                                                 \
        deque->data_array = data_array_new;                                                      \
    }                                                                                            \
                                                                                                 \
    /* Calling quick sort */                                                                     \
    qsort(deque->data_array + deque->begin_index + start.index,                                  \
            last.index - start.index, sizeof(Deque_##t##_Data_Element),                          \
            deque->compare_##t);                                                                 \
}                                                                                                \
                                                                                                 \
int                                                                                              \
compare_##t(const void *item_1_ptr, const void *item_2_ptr)                                      \
{                                                                                                \
    Deque_##t##_Data_Element element_1 = *((Deque_##t##_Data_Element *)item_1_ptr);              \
    Deque_##t##_Data_Element element_2 = *((Deque_##t##_Data_Element *)item_2_ptr);              \
                                                                                                 \
    /* Compare the element objects and return state */                                           \
    if (element_1.is_less_than(element_1.item, element_2.item)) {                                \
        return -1;                                                                               \
    }                                                                                            \
    if (element_1.is_less_than(element_2.item, element_1.item)) {                                \
        return 1;                                                                                \
    }                                                                                            \
    return 0;                                                                                    \
}                                                                                                \
                                                                                                 \
/*  Deque_MyClass_equal - compare two deques and return the status either true or false */       \
bool                                                                                             \
Deque_##t##_equal(Deque_##t  deque1, Deque_##t  deque2)                                          \
{                                                                                                \
    if (deque1.deque_length == deque2.deque_length) {                                            \
        Deque_##t##_Iterator iterator1 = deque1.begin(&deque1);                                  \
        Deque_##t##_Iterator iterator2 = deque2.begin(&deque2);                                  \
                                                                                                 \
        /* This part of program is inspired from Professor's Test.cpp '// Multiple iterators?' */\
        /* Compare and check if the deque1 and deque2 are same */                                \
        while (!Deque_##t##_Iterator_equal(iterator1, deque1.end(&deque1)) &&                    \
                !Deque_##t##_Iterator_equal(iterator2, deque2.end(&deque2))) {                   \
                if (deque1.is_less_than                                                          \
                        (iterator1.deref(&iterator1), iterator2.deref(&iterator2)) ||            \
                    deque1.is_less_than                                                          \
                        (iterator2.deref(&iterator2), iterator1.deref(&iterator1))) {            \
                            return false;                                                        \
        }                                                                                        \
                                                                                                 \
        iterator1.inc(&iterator1);                                                               \
        iterator2.inc(&iterator2);                                                               \
      }                                                                                          \
      return true;                                                                               \
    }                                                                                            \
    return false;                                                                                \
}                                                                                                \
                                                                                                 \
/* Printing the Deque on Screen for verification */                                              \
void                                                                                             \
PrintQueue(Deque_##t *deque)                                                                     \
{                                                                                                \
    std::cout << "Prints DEQUE" << std::endl;                                                    \
    std::cout << "Deque_capacity: " << deque->deque_capacity << std::endl;                       \
    std::cout << "Begin_Index: " << deque->begin_index << std::endl;                             \
    std::cout << "End_Index: " << deque->end_index << std::endl;                                 \
    std::cout << "Deque_Length: " << deque->deque_length << std::endl;                           \
    std::cout << "Size: " << deque->deque_length << std::endl;                                   \
    std::cout << "Empty: " << deque->empty(deque) << std::endl;                                  \
}                                                                                                \
                                                                                                 \
/* inc() Function to increament the Deque_MyClass_Iterator */                                    \
void                                                                                             \
inc(Deque_##t##_Iterator *iterator)                                                              \
{                                                                                                \
    iterator->index = (iterator->index + 1) % iterator->deque->deque_capacity;                   \
}                                                                                                \
                                                                                                 \
/* dec() Function to decreament the Deque_MyClass_Iterator */                                    \
void                                                                                             \
dec(Deque_##t##_Iterator *iterator)                                                              \
{                                                                                                \
    if (iterator->index == 0)                                                                    \
        iterator->index = iterator->deque->deque_capacity - 1;                                   \
    else                                                                                         \
        iterator->index = iterator->index - 1;                                                   \
}                                                                                                \
                                                                                                 \
/*  Deque_MyClass_Iterator_equal function to check if the iterators are equal */                 \
bool                                                                                             \
Deque_##t##_Iterator_equal(Deque_##t##_Iterator iterator1, Deque_##t##_Iterator iterator2)       \
{                                                                                                \
    return iterator1.index == iterator2.index;                                                   \
}                                                                                                \
                                                                                                 \
/* deref() function for deferencing the iterator pointer */                                      \
t &deref(Deque_##t##_Iterator *iterator)                                                         \
{                                                                                                \
    return (iterator->deque->data_array + (iterator->index %                                     \
        iterator->deque->deque_capacity))->item;                                                 \
}                                                                                                \
                                                                                                 \

#endif /* End of Include Guards */