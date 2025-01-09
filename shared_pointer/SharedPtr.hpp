/* Using Include Guards */
#ifndef _SHARED_PTR__HPP_
#define _SHARED_PTR__HPP_

#include <iostream>
#include <mutex> /* using the STL mutex */
#include <cstddef>

namespace cs540 {

    /* create the mutex variable */
    std::mutex mutex;

    /*  I am going to make a Base Class called 
        Reference_Counting_Parent which would 
        be used for Reference Counting given in 
        the test case by professor. */

    struct Reference_Counting_Parent 
    {

        /*  declaring a count variable 
            with size_t data type */
        std::size_t counter;

         /*  having a reference counter initialized 
            to 1 as a part of constructor */
        Reference_Counting_Parent() : counter{1} {}

        /*  Trying to implement locking the 
            way professor taught in 12/1 lecture */

        /*  increament_refernce_counter - method to 
            increament the reference counter */
        void 
        increament_refernce_counter() 
        { 
            /* instantiate a unique lock on the mutex */
            std::unique_lock<std::mutex> lock(mutex);

            /* once the lock is achieved increament now */
            counter = counter + 1;
        } /* End of increament_refernce_counter method */

        /*  decreament_refernce_counter - method to 
            decreament the reference counter */
        void 
        decreament_refernce_counter() 
        {
            /* instantiate a unique lock on the mutex */
            std::unique_lock<std::mutex> lock(mutex);
            
            /* once the lock is achieved increament now */
            counter = counter - 1;

            /*  what if the counter is 0, 
                then delete it */
            if (counter==0) {
                delete this;
            }

        } /* End of decreament_refernce_counter method */

        /*  defining the desctructor as virtual because 
            I might need to delete an instance of a 
            child/derived class through a pointer of this class */
        virtual ~Reference_Counting_Parent() {}   

    };/* End of Reference_Counting_Parent Class */

    /*  Now, I wil be creating Reference_Counting_Child as 
        Child class parent of Reference Counting class */
    template<class U> 
    struct Reference_Counting_Child:public Reference_Counting_Parent 
    {
        private:
            U* pointer;
            /* using what is given in the test.cpp */
        public:
            
            /* instantiating the contructor with parent class and pointer */
            Reference_Counting_Child(U *p) : Reference_Counting_Parent{}, pointer(p) {}

            /* Desctructor for Reference_Counting_Parent */
            ~Reference_Counting_Child() { 
                /* delete the pointer variable */
                delete pointer; 
            } /* End of desctructor */

    }; /* End of Reference_Counting_Child Class */

    /*  funtime over main class of SharedPtr 
        given in the test file */

    /*  The smart pointer points to an object of 
        type T. T may refer to a const-qualified type. */
    template <typename T> 
    class SharedPtr 
    {
        /*  This class is developed referring the 
            way test cases are given in test.cpp */

        public:
            /*  creating two object 
                Typename T and Reference Parent Class */
            T *pointer;
            Reference_Counting_Parent *reference;

            /*  Default Copy Constructor
                Constructs a smart pointer that_one points to null. */
            SharedPtr() : pointer(nullptr), reference(nullptr) {}

            /*  Constructs a smart pointer that_one points to the given object. 
                The reference count is initialized to one. */
            template <typename U>
            explicit SharedPtr(U *ptr_p) : pointer{ptr_p}, reference
            {
                new Reference_Counting_Child<U>(ptr_p)
            } {}

            /* increament the reference counter */
            SharedPtr(const SharedPtr &my_pointer):pointer{my_pointer.pointer}, reference{my_pointer.reference} 
            {
                if(reference) {
                    reference->increament_refernce_counter();
                }
            }

            /* Copy Constructor with a Template flavour */
            template <typename U>
            SharedPtr(const SharedPtr<U> &my_pointer):pointer{static_cast<T *>(my_pointer.pointer)}, reference{my_pointer.reference} 
            {
                if(reference) {
                    reference->increament_refernce_counter();
                }
            } /* End Copy Constructor with a Template flavour */

            /* Setting it to default */
            SharedPtr(SharedPtr &&my_pointer):pointer{my_pointer.pointer}, reference{my_pointer.reference} 
            {
                my_pointer.pointer = nullptr;
                my_pointer.reference = nullptr;
            }

            /* Setting it to default [Template] */
            template <typename U>
            SharedPtr(SharedPtr<U> &&my_pointer):pointer{static_cast<T *>(my_pointer.pointer)}, reference{my_pointer.reference} 
            {
                my_pointer.pointer = nullptr;
                my_pointer.reference = nullptr;
            }

             /*  For safety handling casting of 
                custom created constructors */
            template <typename U>
            SharedPtr(const SharedPtr<U> &sp_ptr, T *ptr_p):pointer{ptr_p}, reference{sp_ptr.reference} 
            {
                if(reference)  {
                    reference->increament_refernce_counter();
                }
            }

            /*  COPY Assignment Operator 
                Copy assignment. Must handle self assignment. Decrement 
                reference count of current object, if any, and increment 
                reference count of the given object. If U * is not implicitly 
                convertible to T *, this will result in a syntax error. */
            SharedPtr &operator=(const SharedPtr &my_pointer) 
            {
                /*  first check if that_one and this one are same */
                if(my_pointer == *this) {
                    /* simply return this one */
                    return *this;
                }

                /* Now decreament refernce counter */
                if(reference) {
                    reference->decreament_refernce_counter();
                }

                 /* Assign it to the T's pointer */
                pointer = my_pointer.pointer;

                /*  If the assignment is successful 
                    increament the reference count */
                reference = my_pointer.reference;
                if(reference) {
                    reference->increament_refernce_counter();
                }

                /* Return this pointer */
                return *this;
            } /* End of COPY Assignment Operator */

            /*  COPY Assignment Operator [Template]
                Copy assignment. Must handle self assignment. Decrement 
                reference count of current object, if any, and increment 
                reference count of the given object. If U * is not implicitly 
                convertible to T *, this will result in a syntax error. */
            template <typename U>
            SharedPtr<T> &operator=(const SharedPtr<U> &my_pointer) 
            {
                /*  first check if that_one and this one are same */
                if(my_pointer == *this) {
                    /* simply return this one */
                    return *this;
                }

                /* Now decreament refernce counter */
                if(reference) {
                    reference->decreament_refernce_counter();
                }

                 /* Assign it to the T's pointer */
                pointer = my_pointer.pointer;

                /*  If the assignment is successful 
                    increament the reference count */
                reference = my_pointer.reference;
                if(reference) {
                    reference->increament_refernce_counter();
                }

                /* Return this pointer */
                return *this;
            } /* End of COPY Assignment Operator [Template] */

            /* MOVE Assignment Operator */
            SharedPtr &operator=(SharedPtr &&my_pointer) 
            {
                /* move that one's T pointer to pointer T */
                pointer = my_pointer.pointer;

                /* copy that to reference */
                reference = my_pointer.reference;

                /* making both of them null */
                my_pointer.pointer = nullptr;
                my_pointer.reference = nullptr;
                
                /* return this one now */
                return *this;
            } /* End of MOVE Assignment Operator */

            /* MOVE Assignment Operator [Template] */
            template <typename U>
            SharedPtr &operator=(SharedPtr<U> &&my_pointer) 
            {
                 /* move that one's T pointer to pointer T */
                pointer = my_pointer.pointer;

                /* copy that to reference */
                reference = my_pointer.reference;

                /* making both of them null */
                my_pointer.pointer = nullptr;
                my_pointer.reference = nullptr;
                
                /* return this one now */
                return *this;
            } /* End of MOVE Assignment Operator [Template] */

            /* Observers */

            /*  Returns a pointer to the owned object. Note 
                my_pointer this will be a pointer-to-const if T 
                is a const-qualified type. */
            T *get() const 
            { 
                return pointer; 
            }

            /*  A reference to the pointed-to object is 
                returned. Note my_pointer this will be a 
                const-reference if T is a const-qualified type. */
            T &operator*() const 
            { 
                return *this->get(); 
            }

            /*  The pointer is returned. Note my_pointer 
                this will be a pointer-to-const if T is a 
                const-qualified type. */
            T *operator->() const 
            { 
                return this->get(); 
            }

            /* Returns true if the SharedPtr is not null. */
            explicit operator bool() const 
            { 
                return pointer != nullptr; 
            }
            
            /* Modifiers */

            /*  The smart pointer is set to point to the null pointer. 
                The reference count for the currently pointed to object, 
                if any, is decremented. */
            void 
            reset() 
            {
                if(reference) {
                    reference->decreament_refernce_counter();
                }

                pointer = nullptr;
                reference = nullptr;
            }

            /*  Replace owned resource with another pointer. If the 
                owned resource has no other references, it is deleted. 
                If p has been associated with some other smart pointer, 
                the behavior is undefined. */
            template <typename U> 
            void 
            reset(U *ptr_p)
            {
                if(reference) {
                    reference->decreament_refernce_counter();
                }
                pointer = ptr_p;
                reference = new Reference_Counting_Child<U>(ptr_p);
            }

            /*  Destructor 
                Decrement reference count of managed object. 
                If the reference count is zero, delete the object.*/
            ~SharedPtr() {
                if(reference) {
                    /* If reference contains some values */
                    reference->decreament_refernce_counter();
                }
            } /* End of Destructor */

    }; /* End of SharedPtr Class */

    /*  Returns true if the two smart pointers point to the 
        same object or if they are both null. Note that 
        implicit conversions may be applied. */
    template <typename T1, typename T2>
    bool operator==(const SharedPtr<T1> &left_hand_side, const SharedPtr<T2> &right_hand_side) 
    {
        return left_hand_side.get() == right_hand_side.get();
    }

    /*  Compare the SharedPtr against nullptr. */
    template <typename T>
    bool operator==(const SharedPtr<T> &left_hand_side, std::nullptr_t) {
        return !left_hand_side;
    }

    /*  Compare the SharedPtr against nullptr. */
    template <typename T>
    bool operator==(std::nullptr_t, const SharedPtr<T> &right_hand_side) 
    {
        return !right_hand_side;
    }

    /*  True if the SharedPtrs point to different 
        objects, or one points to null while the 
        other does not. */
    template <typename T1, typename T2>
    bool operator!=(const SharedPtr<T1> &left_hand_side, const SharedPtr<T2> &right_hand_side) 
    {
        return !(left_hand_side == right_hand_side);
    }

    /*  Compare the SharedPtr against nullptr. */
    template <typename T>
    bool operator!=(const SharedPtr<T> &left_hand_side, std::nullptr_t) 
    {
        return left_hand_side;
    }

    /*  Compare the SharedPtr against nullptr. */
    template <typename T>
    bool operator!=(std::nullptr_t, const SharedPtr<T> &right_hand_side) 
    {
        return right_hand_side;
    }
    
    /*  Convert sp by using static_cast to cast the contained pointer. 
        It will result in a syntax error if static_cast cannot be 
        applied to the relevant types. */
    template <typename T, typename U>
    SharedPtr<T> static_pointer_cast(const SharedPtr<U> &sp) 
    {
        return SharedPtr<T>(sp, static_cast<T *>(sp.get()));
    }

    /*  Convert sp by using dynamic_cast to cast the contained pointer. 
        It will result in a syntax error if dynamic_cast cannot be applied 
        to the relevant types, and will result in a smart pointer to null 
        if the dynamic type of the pointer in sp is not T *. */
    template <typename T, typename U>
    SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U> &sp) 
    {
        return SharedPtr<T>(sp, dynamic_cast<T *>(sp.get()));
    }

} /* End of namespace cs540 */

#endif /* End of Include Guards */