/*
    g++ -std=c++11 Deque_without_macro_MyClass.cpp -o test -ldl
    ** Do not forget to use -ldl while compilation.
    */

/*  Header files taken from test.cpp program
    given by Prof. Kenneth Chiu 
    */
#include <dlfcn.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <random>
#include <unistd.h>
#include <string.h>
#include <algorithm>
#include <typeinfo>
#include <iostream>

// May assume memcpy()-able.
// May assume = operator.

/*
 * Track memory allocation.
 */

// This functions like an assert(), but is careful not to do anything that
// calls malloc(), so can be used before malloc has been initialized.
#define xyzzy_check(e) do {                                                    \
    if (!(e)) {                                                                \
        const char s[] = #e "\n";                                              \
        write(2, s, sizeof s);                                                 \
        abort();                                                               \
    }                                                                          \
} while (0)

size_t alloc_call_count;
size_t total_bytes_allocated;

namespace {
    bool initialized;
    void *(*default_malloc)(size_t);
    void *(*default_realloc)(void *, size_t);
    void *(*default_calloc)(size_t, size_t);
    void
    alloc_init() {
        if (!initialized) {
            // Cast through int to avoid warnings on some versions of g++.
            default_malloc = (void*(*)(size_t)) (uintptr_t) dlsym(RTLD_NEXT, "malloc"); xyzzy_check(default_malloc != nullptr);
            default_realloc = (void*(*)(void*,size_t)) (uintptr_t) dlsym(RTLD_NEXT, "realloc"); xyzzy_check(default_realloc != nullptr);
            default_calloc = (void*(*)(size_t,size_t)) (uintptr_t) dlsym(RTLD_NEXT, "calloc"); xyzzy_check(default_calloc != nullptr);
            initialized = true;
        }
    }
}

void *
malloc(size_t size) {
    alloc_init();
    void *ptr = default_malloc(size);
    alloc_call_count++;
    total_bytes_allocated += size;
    return ptr;
}

void *
realloc(void *p, size_t size) {
    alloc_init();
    void *ptr = default_realloc(p, size);
    alloc_call_count++;
    total_bytes_allocated += size;
    return ptr;
}

void *
calloc(size_t num, size_t size) {
    alloc_init();
    void *ptr = default_calloc(num, size);
    alloc_call_count++;
    total_bytes_allocated += num*size;
    return ptr;
}

/*  Default Initial Capacity which would be
    used when allocating memory in malloc
    */
#define MAGNITUTE 1000

/*  struct of MyClass */
struct
MyClass
{
    int id;
    char name[10];
};

/* Forward Declarations of structures */
struct Deque_MyClass_Iterator;
struct Deque_MyClass_Data_Element;
struct Deque_MyClass;

/*  MyClass Iterator structure to traverse
    in deque using iterator */
struct 
Deque_MyClass_Iterator 
{
    size_t index;
    Deque_MyClass *deque;

    /*  Not changing the function names as the same names
        belong in the test.cpp file */
    MyClass &(*deref)(Deque_MyClass_Iterator * iterator);
    void (*inc)(Deque_MyClass_Iterator * iterator);
    void (*dec)(Deque_MyClass_Iterator * iterator);
};

/*  MyClass Data Elements structure containing
    elements in the deque */
struct
Deque_MyClass_Data_Element 
{
    MyClass item;
    bool (*is_less_than)(const MyClass &, const MyClass &);
};  

struct 
Deque_MyClass 
{
    /*  Size variables */
    size_t deque_length;
    size_t capacity;
    
    /*  index pointers to point beginning and end of deque */
    size_t begin_index;
    size_t end_index;

    Deque_MyClass_Data_Element *data_array;
    char type_name[sizeof("Deque_MyClass")] = "Deque_MyClass";

    /*  Boolean fucntion to compare */
    bool (*is_less_than)(const MyClass &, const MyClass &);
    
    /** DEQUE - Element access 
        front - access the first element
        back - access the last element
        at - access specified element with bounds checking
        */
    MyClass &(*front)(Deque_MyClass *deque);
    MyClass &(*back)(Deque_MyClass *deque);
    MyClass &(*at)(Deque_MyClass *deque, size_t index);

    /** DEQUE - Capacity 
        size - returns the number of elements
        empty - checks whether the container is empty
        */
    size_t (*size)(Deque_MyClass *deque);
    bool (*empty)(Deque_MyClass *deque);

    /** DEQUE - Modifiers 
     *  push_back - adds an element to the end
     *  pop_back - removes the last element
     *  push_front - inserts an element to the beginning
     *  pop_front - removes the first element
     *  resize - changes the number of elements stored
     *  clear - clears the contents
     *  */
    void (*clear)(Deque_MyClass *deque);
    void (*push_back)(Deque_MyClass *deque, MyClass);
    void (*push_front)(Deque_MyClass *deque, MyClass);
    void (*pop_front)(Deque_MyClass *deque);
    void (*pop_back)(Deque_MyClass *deque);

    /** DEQUE - Destructor to clear all the memory */
    void (*dtor)(Deque_MyClass *deque);
    
    /** DEQUE - Comparison function to compare two objects */
    int (*compare_MyClass)(const void *item_1_ptr, const void *item_2_ptr);
    
    /** DEQUE - sort() Func to sort the elements & handle Professor's 
     *  new Test.cpp conditions 
     * */
    void (*sort)(Deque_MyClass * deque, Deque_MyClass_Iterator start, Deque_MyClass_Iterator last);

    /** DEQUE - Iterators 
        begin - returns an iterator to the beginning
        end - returns an iterator to the end
        */
    Deque_MyClass_Iterator (*begin)(Deque_MyClass * deque);
    Deque_MyClass_Iterator (*end)(Deque_MyClass * deque);
};

/*  Forward Declarations of functions */
void Deque_MyClass_Iterator_ctor(Deque_MyClass_Iterator *iterator, Deque_MyClass *deque);
bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator iterator_1, Deque_MyClass_Iterator iterator_2);
int compare_MyClass(const void *item_1_ptr, const void *item_2_ptr);
void clear(Deque_MyClass *deque);
void dtor(Deque_MyClass *deque);
void sort(Deque_MyClass *deque, Deque_MyClass_Iterator start, Deque_MyClass_Iterator last);
int compare_MyClass(const void *item_1_ptr, const void *item_2_ptr);
MyClass &deref(Deque_MyClass_Iterator *iterator);
void inc(Deque_MyClass_Iterator *iterator);
void dec(Deque_MyClass_Iterator *iterator);

/*  size() Func - returns the size of deque. Earlier I had used
    int but after Professor's & TA's feedback changed to size_t
    as Test.cpp has an assertion condition to check with size_t */
size_t 
size(Deque_MyClass *deque) 
{ 
    return deque->deque_length; 
}  

/*  Resize() Func - This is very critical function as I was getting 
    valgrind issues when the memory was not allocated correctly, 
    therefore I have made changes using memcpy() to handle Professor's
    Test.cpp rigourous testing */
void 
resize(Deque_MyClass *deque) 
{
    Deque_MyClass_Data_Element *data_array_new = (Deque_MyClass_Data_Element *)
        malloc(sizeof(Deque_MyClass_Data_Element) * deque->capacity * 2);
    
    /*  memcpy() function, here is where the magic is */
    if (deque->begin_index < deque->end_index) {
        memcpy(data_array_new, deque->data_array + deque->begin_index,
            (deque->end_index - deque->begin_index) * sizeof(Deque_MyClass_Data_Element));
    }
    else {
        memcpy(data_array_new, deque->data_array + deque->begin_index,
            (deque->capacity - deque->begin_index) * sizeof(Deque_MyClass_Data_Element));
        memcpy(data_array_new + (deque->capacity - deque->begin_index), deque->data_array,
            deque->end_index * sizeof(Deque_MyClass_Data_Element));
    }
    /*  Reset all the variables supposedly if the function
        is called again to resuse and to pass the rigorous 
        test.cpp */
    deque->begin_index = 0;
    deque->end_index = deque->capacity - 1;
    deque->capacity = deque->capacity * 2;
    free(deque->data_array);
    deque->data_array = data_array_new;
}

/** DEQUE - Modifiers 
    push_back() - adds an element to the end */
void 
push_back(Deque_MyClass *deque, const MyClass item) 
{
    /*  Instantiate the Data Element Struct */
    Deque_MyClass_Data_Element element;
    element.item = item;
    element.is_less_than = deque->is_less_than;

    /* Check the capacity, if required resize the deque */
    if (deque->capacity - 1 == deque->deque_length) {
        resize(deque);
    }
    *(deque->data_array + deque->end_index) = element;
    deque->end_index = (deque->end_index + 1) % deque->capacity;

    /*  Increament the size of deque_length object after 
        push_back operation */
    ++deque->deque_length;
}

/** DEQUE - Modifiers 
 *  push_front - inserts an element to the beginning */
void 
push_front(Deque_MyClass *deque, const MyClass item)
{
    Deque_MyClass_Data_Element element;
    element.item = item;        
    element.is_less_than = deque->is_less_than;

    /* Check the capacity, if required resize the deque */
    if (deque->capacity - 1 == deque->deque_length) {
        resize(deque);              
    }
    /*  Changing the beginning index, if element and point
        accordingly */
    if (deque->begin_index == 0) {
        deque->begin_index = deque->capacity - 1;      
    } 
    else
        deque->begin_index = deque->begin_index - 1;   
    
    *(deque->data_array + deque->begin_index) = element;  
    
    /*  Increament the size of deque_length object after 
        push_front operation */
    ++deque->deque_length;        
}

/** DEQUE - Modifiers 
    pop_front - removes the first element.
    Adjusting the index and dec the deque_length
    solves the purpose, do not use resize()
    */
void 
pop_front(Deque_MyClass *deque) 
{
    /*  Decreament the size of deque_length object after 
        pop_front operation */
    --deque->deque_length;

    /* Adjust the front index after element is popped */
    deque->begin_index = (deque->begin_index + 1) % deque->capacity;
}                               

/** DEQUE - Modifiers 
    pop_back - removes the last element
    */
void 
pop_back(Deque_MyClass *deque) 
{
    /*  Decreament the size of deque_length object after 
        pop_front operation */
    --deque->deque_length;

    /* Adjust the end index after element is popped */
    if(deque->end_index == 0)
        deque->end_index = deque->capacity - 1;
    else
        deque->end_index = deque->end_index - 1;
}

/** DEQUE - Element access 
    front - access the first element
    */
MyClass
&front(Deque_MyClass *deque)
{
    return (deque->data_array + deque->begin_index)->item;
}

/** DEQUE - Element access 
    back - access the last element
    */
MyClass
&back(Deque_MyClass *deque)
{
    return (deque->data_array + deque->end_index - 1)->item;
}

/** DEQUE - Capacity 
    empty - checks whether the container is empty
    */
bool
empty(Deque_MyClass *deque) 
{
    return deque->deque_length == 0;
}

/** DEQUE - Element access 
    at - access specified element with bounds checking
    */
MyClass
&at(Deque_MyClass *deque, size_t index)
{
    return (deque->data_array + ((index + deque->begin_index) % deque->capacity))->item; 
}

/*  Deque_MyClass_Iterator Constructor Initialization*/
void 
Deque_MyClass_Iterator_ctor (Deque_MyClass_Iterator *iterator, Deque_MyClass *deque) 
{
    iterator->deref = deref;                                                        
    iterator->inc = inc;                                                            
    iterator->dec = dec;                                                            
    iterator->deque = deque;                                                            
}

/** DEQUE - Iterators 
    begin - returns an iterator to the beginning
    */
Deque_MyClass_Iterator 
begin(Deque_MyClass *deque) 
{
    Deque_MyClass_Iterator iterator;
    Deque_MyClass_Iterator_ctor(&iterator, deque);
    iterator.index = deque->begin_index;
    return iterator;
}

/** DEQUE - Iterators 
    end - returns an iterator to the end
    */
Deque_MyClass_Iterator 
end(Deque_MyClass *deque)
{
    Deque_MyClass_Iterator iterator;                      
    Deque_MyClass_Iterator_ctor(&iterator, deque);
    iterator.index = deque->end_index;
    return iterator;
}

/*  Deque_MyClass Constructor Initialization*/
void
Deque_MyClass_ctor(Deque_MyClass *deque, bool (*is_less_than)(const MyClass &, const MyClass &))
{
    deque->is_less_than = is_less_than;
    deque->deque_length = 0;
    deque->begin_index = 0;
    deque->end_index = 0;
    deque->data_array = (Deque_MyClass_Data_Element *)malloc(sizeof(Deque_MyClass_Data_Element) * MAGNITUTE);
    deque->capacity = MAGNITUTE;
    deque->push_back = push_back;
    deque->push_front = push_front;
    deque->pop_back = pop_back;
    deque->pop_front = pop_front;
    deque->front = front;
    deque->back = back;
    deque->size = size;
    deque->empty = empty;
    deque->clear = clear;
    deque->dtor = dtor;
    deque->begin = begin;
    deque->end = end;
    deque->at = at;
    deque->sort = sort;
    deque->compare_MyClass = compare_MyClass;
}

/** DEQUE - Modifiers 
    clear - clears the contents
    */
void
clear(Deque_MyClass *deque) 
{
    deque->begin_index = 0;
    deque->end_index = 0;
    deque->deque_length = 0;
}

/** DEQUE - Destructor to clear all the memory */
void
dtor(Deque_MyClass *deque) 
{
    free(deque->data_array);
    deque->data_array = NULL;
    deque->capacity = 0;
    deque->clear(deque);          
}

/*  sort() Func to call the std::qsort [Standard Template Quick Sort] */
void 
sort(Deque_MyClass *deque, Deque_MyClass_Iterator start, Deque_MyClass_Iterator last)
{ 
    if (start.index > last.index) {
        Deque_MyClass_Data_Element *data_array_new = (Deque_MyClass_Data_Element *)malloc(
            sizeof(Deque_MyClass_Data_Element) * deque->capacity);
        memcpy(data_array_new, deque->data_array + deque->begin_index,
            (deque->capacity - deque->begin_index) * sizeof(Deque_MyClass_Data_Element));
        memcpy(data_array_new + (deque->capacity - deque->begin_index), 
            deque->data_array, deque->end_index * sizeof(Deque_MyClass_Data_Element));

        start.index = start.index - deque->begin_index;
        last.index = ((deque->capacity - 1) - deque->begin_index) + last.index; 
        deque->begin_index = 0;
        deque->end_index = ((deque->capacity - 1) - deque->begin_index) + deque->end_index;
        free(deque->data_array);
        deque->data_array = data_array_new;
    }

    /* Calling quick sort */                                                         
    qsort(deque->data_array + deque->begin_index + start.index,
            last.index - start.index, sizeof(Deque_MyClass_Data_Element), deque->compare_MyClass);           
} 

int 
compare_MyClass(const void *item_1_ptr, const void *item_2_ptr)
{
    Deque_MyClass_Data_Element element_1 = *((Deque_MyClass_Data_Element *)item_1_ptr);
    Deque_MyClass_Data_Element element_2 = *((Deque_MyClass_Data_Element *)item_2_ptr);
    
    /* Compare the element objects and return state */
    if (element_1.is_less_than(element_1.item, element_2.item)) {
        return -1;
    }
    if (element_1.is_less_than(element_2.item, element_1.item)) {
        return 1;
    }                                                          
    return 0;
}

/*  Deque_MyClass_equal - compare two deques
    and return the status either true or false */
bool 
Deque_MyClass_equal(Deque_MyClass deque1, Deque_MyClass deque2)
{
    if (deque1.deque_length == deque2.deque_length) {
        Deque_MyClass_Iterator iterator1 = deque1.begin(&deque1);
        Deque_MyClass_Iterator iterator2 = deque2.begin(&deque2);
        
        /* Compare and check if the deque1 and deque2 are same */
        while (!Deque_MyClass_Iterator_equal(iterator1, deque1.end(&deque1)) &&
                !Deque_MyClass_Iterator_equal(iterator2, deque2.end(&deque2))) {
                if (deque1.is_less_than(iterator1.deref(&iterator1), iterator2.deref(&iterator2)) ||
                    deque1.is_less_than(iterator2.deref(&iterator2), iterator1.deref(&iterator1))) {   
                    return false;
        }

        iterator1.inc(&iterator1);
        iterator2.inc(&iterator2);
      }                                 
      return true;
    }                                                 
    return false;
}

/* Printing the Deque on Screen for verification */
void 
PrintQueue(Deque_MyClass *deque) 
{
    std::cout << "--------- Print DEQUE --------- " << std::endl;
    std::cout << "Capacity: " << deque->capacity << std::endl;  
    std::cout << "Begin_Index: " << deque->begin_index << std::endl;
    std::cout << "End_Index: " << deque->end_index << std::endl; 
    std::cout << "Deque_Length: " << deque->deque_length << std::endl;
    std::cout << "Size: " << deque->deque_length << std::endl;
    std::cout << "Empty: " << deque->empty(deque) << std::endl;       
}

/* Deference the Deque_MyClass_Iterator */
MyClass 
&deref(Deque_MyClass_Iterator *iterator) 
{
    return (iterator->deque->data_array + (iterator->index % iterator->deque->capacity))->item;
}

/* inc() Function to increament the Deque_MyClass_Iterator */
void 
inc(Deque_MyClass_Iterator *iterator) 
{
    iterator->index = (iterator->index + 1) % iterator->deque->capacity;          
}

/* dec() Function to decreament the Deque_MyClass_Iterator */ 
void 
dec(Deque_MyClass_Iterator *iterator) 
{
    if (iterator->index == 0)
        iterator->index = iterator->deque->capacity - 1;                      
    else
        iterator->index = iterator->index - 1;
}                                                           

/*  Deque_MyClass_Iterator_equal function to check if the iterators 
    are equal */                                          
bool 
Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator iterator1, Deque_MyClass_Iterator iterator2) 
{
    return iterator1.index == iterator2.index;
}

/* Testing Function given in Test.cpp */
bool
MyClass_less_by_id(const MyClass &o1, const MyClass &o2) {
    return o1.id < o2.id;
}

bool
MyClass_less_by_name(const MyClass &o1, const MyClass &o2) {
    return strcmp(o1.name, o2.name) < 0;
}

void
MyClass_print(const MyClass *o) {
    printf("%d\n", o->id);
    printf("%s\n", o->name);
}


/*  Main() Func */
int
main (void)
{
    FILE *devnull = fopen("/dev/null", "w");
    assert(devnull != 0);
    {
        Deque_MyClass deq;
        Deque_MyClass_ctor(&deq, MyClass_less_by_id);

        assert(deq.size(&deq) == 0);
        // size() should return a size_t.
        assert(typeid(std::size_t) == typeid(decltype(deq.size(&deq))));
        assert(deq.empty(&deq));

        // Should print "---- Deque_MyClass, 14".
        printf("---- %s, %d\n", deq.type_name, (int) sizeof(deq.type_name));
        // std::cout << "---- " << deq.type_name << ", " << sizeof(deq.type_name) << std::endl;
        assert(sizeof deq.type_name == 14);

        deq.push_back(&deq, MyClass{1, "Joe"});
        deq.push_back(&deq, MyClass{2, "Mary"});
        deq.push_back(&deq, MyClass{3, "Tom"});
        deq.push_front(&deq, MyClass{0, "Mike"});
        deq.push_front(&deq, MyClass{-1, "Mary"});

        MyClass_print(&deq.front(&deq));
        MyClass_print(&deq.back(&deq));
        assert(deq.front(&deq).id == -1);
        assert(deq.back(&deq).id == 3);

        deq.pop_front(&deq);
        deq.pop_back(&deq);
        assert(deq.front(&deq).id == 0);
        assert(deq.back(&deq).id == 2);

        assert(deq.size(&deq) == 3);

        for (Deque_MyClass_Iterator it = deq.begin(&deq);
         !Deque_MyClass_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
            MyClass_print(&it.deref(&it));
        }

        // Multiple iterators?
        for (Deque_MyClass_Iterator it1 = deq.begin(&deq);
         !Deque_MyClass_Iterator_equal(it1, deq.end(&deq)); it1.inc(&it1)) {
            MyClass_print(&it1.deref(&it1));
            for (Deque_MyClass_Iterator it2 = deq.begin(&deq);
             !Deque_MyClass_Iterator_equal(it2, deq.end(&deq)); it2.inc(&it2)) {
                MyClass_print(&it2.deref(&it2));
                for (Deque_MyClass_Iterator it3 = deq.begin(&deq);
                 !Deque_MyClass_Iterator_equal(it3, deq.end(&deq)); it3.inc(&it3)) {
                    MyClass_print(&it3.deref(&it3));
                }
            }
        }

        // Test decrement of end.
        {
            auto it = deq.end(&deq);
            it.dec(&it);
            assert(it.deref(&it).id == 2);
        }

        // printf("Using at.\n");

        for (size_t i = 0; i < 3; i++) {
            MyClass_print(&deq.at(&deq, i));
        }

        // Test that front(), back(), at(), and deref() are returning a reference.
        // Change via at().
        assert(deq.at(&deq, 0).id == 0);
        deq.at(&deq, 0).id = 100;
        assert(deq.at(&deq, 0).id == 100);
        // Change via front().
        assert(deq.front(&deq).id == 100);
        deq.front(&deq).id = 0;
        assert(deq.front(&deq).id == 0);
        assert(deq.at(&deq, 0).id == 0); // Verify with at() also.
        {
            auto it = deq.end(&deq);
            it.dec(&it);
            assert(it.deref(&it).id == 2);
            it.deref(&it).id = 200;
            assert(it.deref(&it).id == 200);
            // Change using back().
            assert(deq.back(&deq).id == 200);
            deq.back(&deq).id = 2;
            assert(deq.back(&deq).id == 2);
            assert(it.deref(&it).id == 2); // Verify with iterator also.
        }

        deq.clear(&deq);

        deq.dtor(&deq);

        // Test equality.  Two deques compare equal if they are of the same
        // length and all the elements compare equal.  It is undefined behavior
        // if the two deques were constructed with different comparison
        // functions.
        {
            Deque_MyClass deq1, deq2;
            Deque_MyClass_ctor(&deq1, MyClass_less_by_id);
            Deque_MyClass_ctor(&deq2, MyClass_less_by_id);

            deq1.push_back(&deq1, MyClass{1, "Joe"});
            deq1.push_back(&deq1, MyClass{2, "Jane"});
            deq1.push_back(&deq1, MyClass{3, "Mary"});
            deq2.push_back(&deq2, MyClass{1, "Joe"});
            deq2.push_back(&deq2, MyClass{2, "Jane"});
            deq2.push_back(&deq2, MyClass{3, "Mary"});

            assert(Deque_MyClass_equal(deq1, deq2));

            deq1.pop_back(&deq1);
            assert(!Deque_MyClass_equal(deq1, deq2));
            deq1.push_back(&deq1, MyClass{4, "Mary"});
            assert(!Deque_MyClass_equal(deq1, deq2));

            deq1.dtor(&deq1);
            deq2.dtor(&deq2);
        }
        PrintQueue(&deq);

    }
}