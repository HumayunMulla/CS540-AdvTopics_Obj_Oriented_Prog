/* Using Include Guards */
#ifndef _MAP_HPP_
#define _MAP_HPP_

/*  headers are included as there are needed
    for certain operations down the line */
#include <iostream>
#include <stdlib.h>
#include <utility>

/*  namespace cs540 - abstract container created to hold 
    a logical grouping of unique identifiers. */
namespace cs540 
{
    /*  forward declarations of template for Class Map */
    template<typename Key_T, typename Mapped_T>
    class Map;

    /*  forward declarations of template for Class SkipList */
    template<typename Key_T, typename Mapped_T>
    class SkipList;

    /*  forward declarations of template for Class Skiplist_Node */
    template<typename Key_T, typename Mapped_T>
    class Skiplist_Node;
    
    /*  type alias template */
    template<typename Key_T, typename Mapped_T>
    class Skiplist
    {
        /*  This is the base class of SkipList, there
            would be another class extending this class
            to develop SkipList */
        private:
            /*  private data members would be declared here */
        public:
            /*  Constructor */
            Skiplist(int);

            /*  To get the height of the node*/
            int height;
            /*  To handle the sentinel node */
            int sentinel;

            /*  Pointer for handling the frontend and
                backend nodes of the Skiplist */
            Skiplist<Key_T, Mapped_T> **frontend_node;
            Skiplist<Key_T, Mapped_T> **backend_node;

            /*  Destructor */
            ~Skiplist();

    }; /* End of Skiplist Class */

    /*  forward declarations of template for Class SkipList */
    template<typename Key_T, typename Mapped_T>
    class SkipList
    {
        /*  This class would be extending Skiplist for creating
            pairs using std::pairs */
        private:
            /*  private data members would be declared here */
            /*  current height of the list */
            int current_height; 
            /*  maximum height of the nodes in list */
            int maximum_height; 
            /*  probability to build subsequent layers of linked lists */
            float probability;
            /*  Header and Tail pointers */
            Skiplist<Key_T, Mapped_T> *head_node_pointer;
            Skiplist<Key_T, Mapped_T> *tail_node_pointer;
        public:
            /*  Constructor */
            SkipList();

            /*  Pointing to the Header and Tail Node */
            Skiplist<Key_T, Mapped_T> *get_head_node() const;
            Skiplist<Key_T, Mapped_T> *get_tail_node() const;

            /*  Search function to search on keys given */
            Skiplist<Key_T, Mapped_T> *search(const Key_T) const;
            
            /*  insert function to insert key and value */
            std::pair<Skiplist<Key_T, Mapped_T>*, bool> insert(const Key_T, Mapped_T, int);
            
            /*  Deterministically adjusting pointer location is costly. Skip lists fix
                this problem by using randomness to randomly determine where
                pointers go */
            int 
            RandomNumberGenerator()
            {
                int temporary_height = 0;
                /*  Generate a Random float value and divide it by RAND_MAX 
                    (32767 on any standard library implementation) comparing less than probability 
                    AND temporary_height should be less than than the maximum height of the list */
                while((((float)rand()) / RAND_MAX < probability) && (temporary_height < (maximum_height-1))) {
                    /* If its TRUE increament the temporary_height by 1 */
                    temporary_height++;
                }
                /* Returning temporary_height calculated */
                return temporary_height;
            } /* End of RandomNumberGenerator Function */

            /*  function to remove node from list */
            bool remove_node(const Key_T);

            /*  Destructor */
            ~SkipList();
        
    };/* End of SkipList Class */

    template< typename Key_T, typename Mapped_T>
    class Skiplist_Node : public Skiplist<Key_T, Mapped_T> 
    {
        typedef std::pair<const Key_T, Mapped_T> ValueType;
        public:
            /*  Parametrized Constructor */
            Skiplist_Node(const Key_T, Mapped_T, int);
            
            /*  node_pair for key and value pair */
            ValueType node_pair;

            /*  Pointer for handling the frontend and
                    backend nodes of the Skiplist */
            Skiplist<Key_T, Mapped_T>** frontend_node;
            Skiplist<Key_T, Mapped_T>** backend_node;

            /*  Destructor */
            ~Skiplist_Node();

    };/* End of Skiplist_Node */

    /*  type alias template */
    template<typename Key_T, typename Mapped_T>
    class Map
    {
        /*  This class would be used to create the std::map
            and its associated functions */
        private:
            /*  private data members would be declared here */
            size_t map_size;
            SkipList<Key_T, Mapped_T> map_list;
        public:
            /*  Default Constructor */
            Map();

            /*  Copy Constructor */
            Map(const Map &);

            /*  typedef - creates an alias that can be used anywhere in 
                place of a (possibly complex) type name */
            typedef std::pair<const Key_T, Mapped_T> ValueType;

            /* Copy Assignment Operator */
            Map &operator=(const Map &);
            
            /* Initizalizer's list constructor */
            Map(std::initializer_list<ValueType>);

            /*  size of list datatype size_t */
            size_t size() const;

            /*  check if the list is empty */
            bool empty() const;

            /*  Forward Declarations of Classes
                to be developed and used later
                on in the program */
            class ConstIterator;
            class Iterator;
            class ReverseIterator;

            /*  Map Template for ConstIterator Class */
            Map<Key_T, Mapped_T>::ConstIterator begin() const;
            Map<Key_T, Mapped_T>::ConstIterator end() const;
            Map<Key_T, Mapped_T>::ConstIterator find(const Key_T &) const;

            /*  Map Template for Iterator Class */
            Map<Key_T, Mapped_T>::Iterator begin();
            Map<Key_T, Mapped_T>::Iterator end();
            Map<Key_T, Mapped_T>::Iterator find(const Key_T &);

            /*  Map Template for ReverseIterator Class */
            Map<Key_T, Mapped_T>::ReverseIterator rbegin();
            Map<Key_T, Mapped_T>::ReverseIterator rend();
            
            /*  Element access - at access specified element with bounds checking */
            Mapped_T &at(const Key_T &);
            const Mapped_T &at(const Key_T &) const;

            /*  Element access - operator[] access or insert specified element */
            Mapped_T &operator[](const Key_T &);
            
            /*  Member functions - insert - clears the contents */
            void clear();

            /*  Member functions - insert - inserts elements or nodes (since C++17) */
            std::pair<Map<Key_T, Mapped_T>::Iterator, bool> insert(const ValueType &);
            template <typename ITERATOR_T>
            void insert(ITERATOR_T begin_range, ITERATOR_T end_range);

            /*  Member functions -erase - erases elements */
            void erase(Map<Key_T, Mapped_T>::Iterator position);
            void erase(const Key_T &);
            
            /*  Method to get the list of map, it will 
                return map_list to the called function */
            SkipList<Key_T, Mapped_T> get_map_list() const;

            class ConstIterator
            {
                private:
                    /*  private data members would be declared here */
                    /*  Trying to work like Member type const_pointer */
			        Skiplist<Key_T, Mapped_T> *constant_node_pointer;
                public:
                    ConstIterator(Skiplist<Key_T, Mapped_T>*);
                    
                    /*  Copy Constructor */
                    ConstIterator(const ConstIterator &);
                    ConstIterator(const Iterator &);

                    /*  Non-member functions */
                    const ValueType &operator*() const;
                    const ValueType *operator->() const;
                    /*  Pre-increament */
                    ConstIterator &operator++();
                    /*  Post-increament */
                    ConstIterator operator++(int);
                    /*  Pre-decreament */
                    ConstIterator &operator--();
                    /*  Post-decreament */
                    ConstIterator operator--(int);
                    /*  Copy Assignment */
                    ConstIterator &operator=(const ConstIterator &);

                    /*  Point to the constant node pointer */
                    Skiplist<Key_T, Mapped_T> *get_const_node_pointer() const;
                    
                    /*  resetting the const_node_pointer */
                    void set_const_node_pointer(Skiplist<Key_T, Mapped_T>*);

                    /* Making it friend so that the functions can be accessed from the same class*/
                    friend bool
                    operator==(const typename Map<Key_T, Mapped_T>::ConstIterator &I1, const typename Map<Key_T, Mapped_T>::ConstIterator &I2) 
                    {
                            if(I1.get_const_node_pointer() == NULL || I2.get_const_node_pointer() == NULL) 
                                return false;
                            else if(I1.get_const_node_pointer() == I2.get_const_node_pointer())	 
                                return true;
                            else 
                                return false;
                    }
                    friend bool
                    operator==(const typename Map<Key_T, Mapped_T>::ConstIterator &I1, const typename Map<Key_T, Mapped_T>::Iterator &I2) 
                    {
                            if(I1.get_const_node_pointer() == NULL || I2.get_node_pointer() == NULL) 
                                return false;
                            else if(I1.get_const_node_pointer() == I2.get_node_pointer()) 
                                return true;
                            else 
                                return false;
                    }
                    friend bool
                    operator!=(const typename Map<Key_T, Mapped_T>::ConstIterator &I1, const typename Map<Key_T, Mapped_T>::ConstIterator &I2)
                    {
                        if(I1 == I2) 
                                return false;
                            else 
                                return true;
                    }
                    friend bool
                    operator!=(const typename Map<Key_T, Mapped_T>::ConstIterator &I1, const typename Map<Key_T, Mapped_T>::Iterator &I2)
                    {
                        if(I1 == I2) 
                                return false;
                            else 
                                return true;
                    }

                    /*  Destructor */
                    ~ConstIterator();
            }; /* End of ConstIterator Class */

            class Iterator
            {
                private:
                    /*  private data members would be declared here */
                    Skiplist<Key_T, Mapped_T> *node_pointer;
                public:
                    Iterator(Skiplist<Key_T, Mapped_T>*);

                    /*  Copy Constructor */
                    Iterator(const Iterator &);
                    
                    /*  assigns values to the container */
                    Iterator& operator=(const Iterator &);

                    /*  Non-member functions */
                    /*  Pre-increament */
                    Iterator &operator++();
                    /*  Post-increament */
                    Iterator operator++(int);
                    /*  Pre-decreament */
                    Iterator &operator--();
                    /*  Post-decreament */
                    Iterator operator--(int);

                    ValueType &operator*() const;
                    ValueType *operator->() const;
                    
                    /*  Point to the node pointer to be used in the operatiosn */
                    Skiplist<Key_T, Mapped_T>* get_node_pointer() const;
                    
                    /*  resetting the node_pointer */
                    void set_node_pointer(Skiplist<Key_T, Mapped_T>*);

                    /* Making it friend so that the functions can be accessed from the same class*/
                    friend bool
                    operator==(const typename Map<Key_T, Mapped_T>::Iterator &I1, const typename Map<Key_T, Mapped_T>::Iterator &I2) 
                    {
                        if(I1.get_node_pointer() == NULL || I2.get_node_pointer() == NULL) 
                            return false;
        		        else if(I1.get_node_pointer() == I2.get_node_pointer())	 
                            return true;
        		        else 
                            return false;
                    }
                    friend bool 
                    operator==(const typename Map<Key_T, Mapped_T>::Iterator &I1, const typename Map<Key_T, Mapped_T>::ConstIterator &I2)
                    {
                        if(I1.get_node_pointer() == NULL || I2.get_const_node_pointer() == NULL) 
                            return false;
        		        else if(I1.get_node_pointer() == I2.get_const_node_pointer())	 
                            return true;
        		        else 
                            return false;
                    }
                    friend bool 
                    operator!=(const typename Map<Key_T, Mapped_T>::Iterator &I1, const typename Map<Key_T, Mapped_T>::Iterator &I2)
                    {
                        if(I1 == I2) return false;
        		        else return true;
                    }

                    friend bool 
                    operator!=(const typename Map<Key_T, Mapped_T>::Iterator &I1, const typename Map<Key_T, Mapped_T>::ConstIterator &I2)
                    {
                        if(I1 == I2) 
                            return false;
        		        else
                            return true;
                    }
           
                    /*  Destructor */
                    ~Iterator();
            }; /* End of Iterator Class */

            class ReverseIterator
            {
                private:
                    /*  private data members would be declared here */
			        Skiplist<Key_T, Mapped_T>* reverse_node_pointer;
                public:
                    ReverseIterator(Skiplist<Key_T, Mapped_T>*);

                    /*  Copy Constructor */
                    ReverseIterator(const ReverseIterator &);

                    ReverseIterator& operator=(const ReverseIterator &);

                    /*  Non-member functions */
                    /*  Pre-increament */
                    ReverseIterator &operator++();
                    /*  Post-increament */
                    ReverseIterator operator++(int);
                    /*  Pre-decreament */
                    ReverseIterator &operator--();
                    /*  Post-decreament */
                    ReverseIterator operator--(int);
                    
                    ValueType &operator*() const;
                    ValueType *operator->() const;
                    
                    /*  Point to the reverse node to be used in the operatiosn */
                    Skiplist<Key_T, Mapped_T>* get_reverse_node_pointer() const;
                    
                    /*  resetting the reverse_node_pointer */
                    void set_reverse_node_pointer(Skiplist<Key_T, Mapped_T>*);

                    /* Making it friend so that the functions can be accessed from the same class*/
                    friend bool
                    operator==(const typename Map<Key_T, Mapped_T>::ReverseIterator &I1, const typename Map<Key_T, Mapped_T>::ReverseIterator &I2)
                    {
                        if(I1.get_reverse_node_pointer() == NULL || I2.get_reverse_node_pointer() == NULL) 
                            return false;
                        else if(I1.get_reverse_node_pointer() == I2.get_reverse_node_pointer()) 
                            return true;
                        else 
                            return false;
                    }
                    friend bool
                    operator!=(const typename Map<Key_T, Mapped_T>::ReverseIterator &I1, const typename Map<Key_T, Mapped_T>::ReverseIterator &I2)
                    {
                        if(I1 == I2) 
                            return false;
                        else
                            return true;
                    }
                    
                    /*  Destructor */
                    ~ReverseIterator();	
		    }; /* End of ReverseIterator Class */

            /* Making it friend so that the functions can be accessed from the same class*/
            friend bool
            operator==(const Map<Key_T, Mapped_T> &map_1, const Map<Key_T, Mapped_T> &map_2)
            {
                /*  Compare the Members Passed! */
        	    if(map_1.size() == map_2.size()) {
    			    if(map_1.size() == 0)
                        /*  since the size is 0 return a true */
                        return true;

                    /*  Pointing to the beginning */
    			    typename Map<Key_T, Mapped_T>::ConstIterator iteration_1 = map_1.begin();
    			    typename Map<Key_T, Mapped_T>::ConstIterator iteration_2 = map_2.begin();

                    /*  Iterate and check the node pairs */
    			    for(; iteration_1 != map_1.end(); ++iteration_1, ++iteration_2) {
    				    Skiplist_Node<Key_T, Mapped_T>* temporary_1 = (static_cast<Skiplist_Node<Key_T, Mapped_T>*>( iteration_1.get_const_node_pointer() ) );
    				    Skiplist_Node<Key_T, Mapped_T>* temporary_2 = (static_cast<Skiplist_Node<Key_T, Mapped_T>*>( iteration_2.get_const_node_pointer() ) );
    				    if (temporary_1->node_pair != temporary_2->node_pair) 
                            /*  If the temporary pointing node pair are not equal
                                return false */
                           return false;
    			    }
    			    return true;
    		    }
    		    else
                    /* default case return */
                    return false;
            }
            friend bool
            operator!=(const Map<Key_T, Mapped_T> &map_1, const Map<Key_T, Mapped_T> &map_2)
            {
                /*  Check if both the members are equal or no */
                if(map_1 == map_2)
                    return false;
    		    else
                    return true;
            }
            friend bool
            operator<(const Map<Key_T, Mapped_T> &map_1, const Map<Key_T, Mapped_T> &map_2)
            {
                /*  Initialize to the beginning */
                typename Map<Key_T, Mapped_T>::ConstIterator iteration_1 = map_1.begin();
                typename Map<Key_T, Mapped_T>::ConstIterator iteration_2 = map_2.begin();

                if(iteration_1.get_const_node_pointer() == NULL && iteration_2.get_const_node_pointer() != NULL) 
                    return true;
                else if(iteration_1.get_const_node_pointer() != NULL && iteration_2.get_const_node_pointer() == NULL) 
                    return false;
                else if(iteration_1.get_const_node_pointer() == NULL && iteration_2.get_const_node_pointer() == NULL) 
                    return false;
                else {
                    if(map_1.size() < map_2.size()) {
                        /*  If map_1 is smaller in size than map_2 */
                        for(; iteration_1 != map_1.end(); ++iteration_1, ++iteration_2) {
                            Skiplist_Node<Key_T, Mapped_T>* temporary_1 = (static_cast<Skiplist_Node<Key_T, Mapped_T>*>(iteration_1.get_const_node_pointer()));
                            Skiplist_Node<Key_T, Mapped_T>* temporary_2 = (static_cast<Skiplist_Node<Key_T, Mapped_T>*>(iteration_2.get_const_node_pointer()));
                            if(temporary_1->node_pair < temporary_2->node_pair) 
                                return true;
                            else if(temporary_1->node_pair > temporary_2->node_pair) 
                                return false;
                        }
                        /* If the size of map_1 is less than Member 2 and each element is same */
                        return true;   
                    }
                    else {
                        /* The size of both the maps are same */
                        for(; iteration_2 != map_2.end(); ++iteration_2, ++iteration_1) {
                            Skiplist_Node<Key_T, Mapped_T>* temporary_1 = (static_cast<Skiplist_Node<Key_T, Mapped_T>*>(iteration_1.get_const_node_pointer()));
                            Skiplist_Node<Key_T, Mapped_T>* temporary_2 = (static_cast<Skiplist_Node<Key_T, Mapped_T>*>(iteration_2.get_const_node_pointer()));
                            if(temporary_1->node_pair < temporary_2->node_pair) return true;
                        }
                        return false;
                    }
                }
    	    }


        /*  Destructor */
        ~Map();
    };/* End of Map Class */

    /*  Inheritance for *CLASS* Skiplist_Node, i.e. extending class Skiplist */
    template<typename Key_T, typename Mapped_T>
    Skiplist_Node<Key_T, Mapped_T> :: Skiplist_Node(const Key_T key, Mapped_T object_1, int height) : Skiplist<Key_T, Mapped_T>(height), node_pair(key,object_1)
    {
        this->sentinel = 0;
    }
    
    /* Desctructor Defination for Skiplist_Node */
    template<typename Key_T, typename Mapped_T>
    Skiplist_Node<Key_T, Mapped_T>::~Skiplist_Node()
    {
        /*  delete all the pointer contents 
            and free memory */
        delete [] frontend_node;
        delete [] backend_node;
    } /*    End of Skiplist_Node() ctor */

    /* Defining Constructor for Skiplist */
    template<typename Key_T, typename Mapped_T>
    Skiplist<Key_T, Mapped_T> :: Skiplist(int x)
    {
        /*  Check the height of the list */
        if(x == 0) 
            height = 0;
        else 
            height = x-1;

        /*  initialization of frontend and backend pointer */
        frontend_node = new Skiplist<Key_T, Mapped_T>* [x];
        backend_node = new Skiplist<Key_T, Mapped_T>* [x];

        for(int i = 0; i < x; i++) {
            frontend_node[i] = NULL;
            backend_node[i] = NULL;
        }
        /*  set the sentinel to 1 */
        sentinel = 1;
    } /* End of Skiplist() ctor */

    /* Desctructor Defination for Skiplist */
    template<typename Key_T, typename Mapped_T>
    Skiplist<Key_T, Mapped_T> :: ~Skiplist()
    {
        /*  delete all the pointer contents 
            and free memory */
        delete [] frontend_node;
        delete [] backend_node;
    } /*    End of ~Skiplist() method */

    /* Defining Constructor for SkipList */
    template<typename Key_T, typename Mapped_T>
    SkipList<Key_T, Mapped_T>::SkipList()
    {
        /*  reset SRAND to NULL */
        srand(time(NULL));

        /* Parameters of private in SkipList */
        maximum_height = 32;
        current_height = 0;
        probability = 0.5;

        /*  Reset pointers */
        head_node_pointer = new Skiplist<Key_T, Mapped_T>(maximum_height);
        tail_node_pointer = new Skiplist<Key_T, Mapped_T>(maximum_height);
        for(int i = 0; i < maximum_height; i++){
            head_node_pointer->frontend_node[i] = tail_node_pointer;
            tail_node_pointer->backend_node[i] = head_node_pointer;
        }
    }

    /*  Defination of get_head_node which return head_node_pointer */
    template<typename Key_T, typename Mapped_T>
    Skiplist<Key_T, Mapped_T>* SkipList<Key_T, Mapped_T> :: get_head_node() const
    {
            return head_node_pointer;
    } /*    End of get_head_node() method */

    /*  Defination of get_tail_node which return tail_node_pointer */
    template<typename Key_T, typename Mapped_T>
    Skiplist<Key_T, Mapped_T>* SkipList<Key_T, Mapped_T> :: get_tail_node() const
    {
            return tail_node_pointer;
    } /*    End of get_tail_node() method */

    /* insert Func - SkipList to insert elements into the Skiplist */
    template<typename Key_T, typename Mapped_T>
  	std::pair<Skiplist<Key_T, Mapped_T>*, bool> SkipList<Key_T, Mapped_T> :: insert(const Key_T key, Mapped_T object, int correct_height)
    {
        /*  Default Initialization of level and height of list */
        int level = 0;
        int height = 0;

        /*  create a value_pair variable */
        std::pair<Skiplist<Key_T, Mapped_T>*, bool> value_pair;

        /*  instantiate a new list called update_list */
		Skiplist<Key_T, Mapped_T> **update_list = new Skiplist<Key_T, Mapped_T>*[maximum_height];
        Skiplist<Key_T, Mapped_T> *temporary = head_node_pointer;
        
        /*  Create a const pointer comparison key variable */
        const Key_T *compare_key;

        /*  Until all the heights of lists are travered */
        for (height = current_height; height >= 0; height--) {
            if((temporary->frontend_node[height] != NULL) && (temporary->frontend_node[height]->sentinel == 0)) {
                /*  static cast the node_pair.first */
                compare_key = &(static_cast<Skiplist_Node<Key_T, Mapped_T>*>(temporary->frontend_node[height])->node_pair.first);
            }
            else
                /*  since both the conditions failed instantiate 
                    compare_key to null */ 
                compare_key = NULL;
            
            /*  Until compare_key reaches null */
            while((compare_key != NULL) && (*compare_key < key)) {
                /*  update temporary to current frontend_node's height */
                temporary = temporary->frontend_node[height];
                /*  Now again try comparing */
                if( (temporary->frontend_node[height] != NULL) && (temporary->frontend_node[height]->sentinel == 0)) {
                    /*  static cast the node_pair.first */
                    compare_key = &(static_cast<Skiplist_Node<Key_T, Mapped_T>*>(temporary->frontend_node[height])->node_pair.first);
                }
                else 
                    compare_key = NULL;
            }
            /* Update the list */
            update_list[height] = temporary;
        }
        /*  Once that's done now for the final try */
        temporary = temporary->frontend_node[0];
        /*  Now again try comparing if temporary is NULL 
            or sentinel has become 0 */
        if( (temporary != NULL)  && (temporary->sentinel == 0) ) {
            /*  static cast the node_pair.first */
            compare_key = &(static_cast<Skiplist_Node<Key_T, Mapped_T>*>(temporary)->node_pair.first);
        }
        else
            compare_key = NULL;
		
        if(compare_key != NULL && *compare_key == key) {
            /*  delete the update_list created at the beginning */
            delete [] update_list;
            
            /*  resetting the first, second and return value_pair */
			value_pair.first = temporary;
			value_pair.second = false;
			return value_pair;
        }
        else {
            /*  Now get the level using RandomNumber 
                Generator function call */
            if(correct_height == -1) 
                level = RandomNumberGenerator();
            else 
                level = correct_height;

            /*  check if the level is smaller than current_height */
            if(level > current_height) {
                for(int i = current_height+1; i <= level; i++) {
                    /*  update the current list to the head_node_pointer */
                    update_list[i] = head_node_pointer;
                }
                /*  update the current_height with the level 
                    calculated with the random generated function */
                current_height = level;
            }

            /*  Instantitate temporary with new Skiplist */
            temporary = new Skiplist_Node<Key_T, Mapped_T>(key, object, level+1);

            for(int i = 0; i <= level; i++) {
                /*  Reset all the pointers */
                temporary->frontend_node[i] = update_list[i]->frontend_node[i];
                update_list[i]->frontend_node[i]->backend_node[i] = temporary;
                update_list[i]->frontend_node[i] = temporary;
                temporary->backend_node[i] = update_list[i];
            }
        }
        
        /*  delete the update_list created at the beginning */
        delete[] update_list;

        /*  Reset the the first and second of the value_pair */
        value_pair.first = temporary;
		value_pair.second = true;
        
        /* Return with value_pair */
        return value_pair;
    } /*    End of insert() method */

    /* search Func - SkipList to search elements in the Skiplist */
    template<typename Key_T, typename Mapped_T>
    Skiplist<Key_T, Mapped_T>* SkipList<Key_T, Mapped_T> :: search(const Key_T key) const 
    {
        /*  resetting height to 0 */
        int height = 0;
        
        /*  instantiate a new list called update_list */
        Skiplist<Key_T, Mapped_T>** update_list = new Skiplist<Key_T, Mapped_T>*[maximum_height];
        Skiplist<Key_T, Mapped_T>* temporary = head_node_pointer;
        
        /*  Create a const pointer comparison key variable */
        const Key_T* compare_key;

        for (height = current_height; height >= 0; height--) {
            if ((temporary->frontend_node[height] != NULL) &&  (temporary->frontend_node[height]->sentinel == 0)) {
                /*  static cast the node_pair.first */
                compare_key = &(static_cast<Skiplist_Node<Key_T, Mapped_T>*>(temporary->frontend_node[height])->node_pair.first);
            }
            else 
                compare_key = NULL;
            
            /*  Until compare_key reaches null */
            while ((compare_key != NULL) && (*compare_key < key)) {
                /*  point temporary to the height of frontend_node */
                temporary = temporary->frontend_node[height];
                if ((temporary->frontend_node[height] != NULL)  && (temporary->frontend_node[height]->sentinel == 0)) {
                    /*  static cast the node_pair.first */
                    compare_key = &(static_cast<Skiplist_Node<Key_T, Mapped_T>*>(temporary->frontend_node[height])->node_pair.first);
                }
                else compare_key = NULL;
            }
            update_list[height] = temporary;
        }

        /* Reset to point to frontend_node's 0th position */
        temporary = temporary->frontend_node[0];
        
        /*  check if the 0th position node is not NULL or 0 */
        if ((temporary != NULL) && (temporary->sentinel == 0)) {
            /*  static cast the node_pair.first */
            compare_key = &(static_cast<Skiplist_Node<Key_T, Mapped_T>*>(temporary)->node_pair.first);
        }
        else 
            /*  If its NULL or 0 return compare_key as NULL */
            compare_key = NULL;

        /*  delete the update_list created at the beginning */
        delete[] update_list;

        /*  Check now has the compare_key got NULL */
        if (compare_key == NULL) 
            return NULL;
        else if (*compare_key == key) {
            /*  The compare_key itself is the search key */
            return temporary;
        }
        else
            /*  If nothing found after all search then return NULL */ 
            return NULL;
        /*  Return back the search key const */
    } /*    End of search() method for SkipList */

    /* remove_node Func - SkipList to search elements in the Skiplist */
    template<typename Key_T, typename Mapped_T>
    bool SkipList<Key_T, Mapped_T> :: remove_node(const Key_T key) 
    {
        /*  instantiate a new list called update_list */
        Skiplist<Key_T, Mapped_T>** update_list = new Skiplist<Key_T, Mapped_T>* [maximum_height];
        Skiplist<Key_T, Mapped_T>* temporary = head_node_pointer;

        /*  Create a const pointer comparison key variable */
        const Key_T* compare_key;

        /*  Start searching for removing the node */
        for (int i = current_height; i >= 0; i--) {
            /*  check if it is NULL or 0 */
            if ((temporary->frontend_node[i] != NULL)  &&  (temporary->frontend_node[i]->sentinel == 0)) {
                /*  static cast the node_pair.first */
                compare_key = &(static_cast<Skiplist_Node<Key_T, Mapped_T>*>(temporary->frontend_node[i])->node_pair.first);
            }
            else 
                compare_key = NULL;
            
             /*  Until compare_key reaches null */
            while ((compare_key != NULL) && (*compare_key < key) ){
                temporary = temporary->frontend_node[i];
                if ((temporary->frontend_node[i] != NULL) &&  (temporary->frontend_node[i]->sentinel == 0)) {
                    /*  static cast the node_pair.first */
                    compare_key = &(static_cast<Skiplist_Node<Key_T, Mapped_T>*>(temporary->frontend_node[i])->node_pair.first);
                }
                else compare_key = NULL;
            }
            /*  Append the temporary node to the 
                update_list at the ith position */
            update_list[i] = temporary;
        }
        temporary = temporary->frontend_node[0];
        if ((temporary != NULL)  && (temporary->sentinel == 0) ) {
            /*  static cast the node_pair.first */
            compare_key = &(static_cast<Skiplist_Node<Key_T, Mapped_T>*>(temporary)->node_pair.first);
        }
        else
            compare_key = NULL;
        
        /*  Now if the keys match, what to do ! */
        if ((compare_key != NULL) && (*compare_key == key)) {
            /*  iterate through all the lists until 
                the curent_height is reached */
            for(int i = 0; i <= current_height; i++) {
                /*  first check if the update_list and 
                    frontend_node are equal to temporary pointer */
                if (update_list[i]->frontend_node[i] != temporary) 
                    break;
                /*  Otherwise now update for the next traversal */
                update_list[i]->frontend_node[i] = temporary->frontend_node[i];
                update_list[i]->frontend_node[i]->backend_node[i] = update_list[i];
            }

            /*  Delete the temporary instance */
            delete temporary;
            
            /*  Keep on decreasing the height until you find the new tallest node */
            while ((current_height > 0) && (head_node_pointer->frontend_node[current_height]->sentinel == 1)) {
                current_height--;
            }

            /*  As the keys have been successfully found and removed 
                delete the update_list created and return TRUE */
            delete [] update_list;
            return true;
        }
        else { 
            /*  As keys have not matched delete the 
                update list and return false */
            delete [] update_list;
            return false;
        }
    } /*    End of remove_node() method of SkipList class */
    
    /* Desctructor Defination for SkipList */
    template<typename Key_T, typename Mapped_T>
    SkipList<Key_T, Mapped_T> :: ~SkipList()
    {
        /*  Initialize to defaults */
        Skiplist<Key_T, Mapped_T> *temporary;
        Skiplist<Key_T, Mapped_T> *next_node_pointer;
        temporary = head_node_pointer;

        /*  Until empty delete all pointings*/
        while (temporary) {
            next_node_pointer = temporary->frontend_node[0];
            delete temporary;
            temporary = next_node_pointer;
        }
    } /*    End of ~SkipList() */

    /*  ReverseIterator Class inheritance */
    template<typename Key_T, typename Mapped_T>
	Map<Key_T, Mapped_T>::ReverseIterator :: ReverseIterator(Skiplist<Key_T, Mapped_T> *temporary) 
    {
        /*  Check if temporary is NULL then set reverse_node_pointer 
            to also NULL, else set it to the temporary */
		if (temporary == NULL) 
            reverse_node_pointer = NULL;
		else 
            reverse_node_pointer = temporary;
	} /* End of ReverseIterator Skiplist method */

    /*  ReverseIterator passed by reference of iteration 1 */
    template<typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T>::ReverseIterator::ReverseIterator(const Map<Key_T,Mapped_T>::ReverseIterator &iteration_1)
    {
        /*  If the iteration's reverse_node_pointer is NULL 
            then return reverse_node_pointer as NULL */
        if (iteration_1.reverse_node_pointer == NULL) 
            reverse_node_pointer = NULL;
        /*  Otherwise return the iteration's reverse_node_pointer */
        else 
            reverse_node_pointer = iteration_1.reverse_node_pointer;
    } /*    End of ReverseIterator passed by reference of iteration 1 */

    /* ReverseIterator Class operator= */
    template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T> :: ReverseIterator &Map<Key_T, Mapped_T> :: ReverseIterator :: operator=(const ReverseIterator &iteration_1)
    {
        /*  If the iteration's reverse_node_pointer is NULL 
            then return reverse_node_pointer as NULL */
        if (iteration_1.reverse_node_pointer == NULL) 
            reverse_node_pointer = NULL;
        /*  Otherwise return the iteration's reverse_node_pointer */
		else {
			reverse_node_pointer = iteration_1.reverse_node_pointer;
		}
        return (*this);
	} /*   End of ReverseIterator Class operator= */

    /*  ReverseIterator Class operator++() */
    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T> :: ReverseIterator& Map<Key_T, Mapped_T> :: ReverseIterator :: operator++()
    {
        if (reverse_node_pointer == NULL)
            /*  If it's NULL return this pointer */
            return (*this);
        else {
            /*  Otherwise find the backend_node's 0th element and return it */
            reverse_node_pointer = reverse_node_pointer->backend_node[0];
            return (*this);
        }
    } /*  End of ReverseIterator Class operator++() */

    /*  ReverseIterator Class operator++(int) */
    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T> :: ReverseIterator Map<Key_T, Mapped_T> :: ReverseIterator :: operator++(int) 
    {
        /*  Instantiate iteration(*this) operator */
        Map<Key_T, Mapped_T> :: ReverseIterator iteration(*this);

        /*  since its not NULL point to the 
            frontend_node of 0th position */
        if (reverse_node_pointer != NULL) {
            reverse_node_pointer = reverse_node_pointer->frontend_node[0];
        }
        
        /*  Return iteration pointer */
        return iteration;
    } /*  End of ReverseIterator Class operator++(int) */

    /*  ReverseIterator Class operator--() */
    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T> :: ReverseIterator &Map<Key_T, Mapped_T> :: ReverseIterator :: operator--()
    {
        /*  If its NULL then return this pointer */
        if (reverse_node_pointer == NULL) 
            return (*this);
        else {
            /*  since its not NULL point to the 
            frontend_node of 0th position */
            reverse_node_pointer = reverse_node_pointer->frontend_node[0];

            /*  return this pointer */
            return (*this);
        }
    } /*  End of ReverseIterator Class operator--() */

    /*  ReverseIterator Class operator--(int) */
    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T> :: ReverseIterator Map<Key_T, Mapped_T> :: ReverseIterator :: operator--(int)
    {
        /*  Instantiate iteration(*this) operator */
        Map<Key_T, Mapped_T> :: ReverseIterator iteration(*this);

        /*  since its not NULL point to the 
            frontend_node of 0th position */
        if (reverse_node_pointer != NULL) {
            reverse_node_pointer = reverse_node_pointer->frontend_node[0];
        }

        /*  Return iteration pointer */
        return iteration;
    } /*  End of ReverseIterator Class operator--(int) */

    /*  ReverseIterator Class operator*() const */
    template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T> :: ValueType &Map<Key_T, Mapped_T> :: ReverseIterator :: operator*() const
    {
        /*  Return node_pair pointer */
		return (static_cast<Skiplist_Node<Key_T, Mapped_T>*>(reverse_node_pointer)->node_pair);
	} /* End of ReverseIterator Class operator*() const */

    /*  ReverseIterator Class operator->() const */
    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T> :: ValueType *Map<Key_T, Mapped_T> :: ReverseIterator :: operator->() const
    {
		/*  Return node_pair pointer */
		return &(static_cast<Skiplist_Node<Key_T, Mapped_T>*>(reverse_node_pointer)->node_pair);
	} /* End of ReverseIterator Class operator->() const */

    /*  ReverseIterator Class get_reverse_node_pointer() */
    template<typename Key_T, typename Mapped_T>
	Skiplist<Key_T, Mapped_T> *Map<Key_T, Mapped_T> :: ReverseIterator :: get_reverse_node_pointer() const
    {
        /*  And now return the reverse_node_pointer */
		return reverse_node_pointer;
	} /*    End of ReverseIterator Class get_reverse_node_pointer() */

    /*  ReverseIterator Class get_reverse_node_pointer() */
	template<typename Key_T, typename Mapped_T>
	void Map<Key_T, Mapped_T> :: ReverseIterator :: set_reverse_node_pointer(Skiplist<Key_T, Mapped_T> *temporary)
    {
        /*  Return the temporary instance of the pointer */
		reverse_node_pointer = temporary;
	} /*    End of ReverseIterator Class get_reverse_node_pointer() */

    /* Desctructor Defination for ReverseIterator */
	template<typename Key_T, typename Mapped_T>
	Map<Key_T, Mapped_T> :: ReverseIterator :: ~ReverseIterator()
    {
	}/*    End of ~ReverseIterator() */

    /* ConstIterator Class *temporary > constant_node_pointer */
    template<typename Key_T, typename Mapped_T>
	Map<Key_T, Mapped_T> :: ConstIterator :: ConstIterator(Skiplist<Key_T, Mapped_T> *temporary)
    {
        /*  Check if temporary is NULL then 
            constant_node_pointer is NULL */
		if(temporary == NULL) {
            constant_node_pointer = NULL;
        }
		else {
            /*  If not NULL then return temporary */
            constant_node_pointer = temporary;
        }
	} /*    End of ConstIterator Class *temporary > constant_node_pointer */

    /* ConstIterator Class ConstIterator(const Map<Key_T,Mapped_T> :: ConstIterator &iteration_1) */
    template<typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T> :: ConstIterator :: ConstIterator(const Map<Key_T,Mapped_T> :: ConstIterator &iteration_1)
    {
        /*  Check if iteration_1 constant pointer is NULL then 
            constant_node_pointer is NULL */
        if (iteration_1.constant_node_pointer == NULL) {
            constant_node_pointer = NULL;
        }
        else {
            /*  If not NULL then return iteration_1.constant_node_pointer */
            constant_node_pointer = iteration_1.constant_node_pointer;
        }
    } /* End of ConstIterator Class ConstIterator(const Map<Key_T,Mapped_T> :: ConstIterator &iteration_1) */
    
    /* ConstIterator Class ConstIterator(const Map<Key_T,Mapped_T> :: Iterator &iteration_1) */
    template<typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T> :: ConstIterator :: ConstIterator(const Map<Key_T,Mapped_T> :: Iterator &iteration_1)
    {
        /*  Check if iteration_1 constant pointer is NULL then 
            constant_node_pointer is NULL */
        if (iteration_1.get_node_pointer() == NULL) {
            constant_node_pointer = NULL;
        }
        else {
            /*  If not NULL then return iteration_1.constant_node_pointer */
            constant_node_pointer = iteration_1.get_node_pointer();
        }
    } /* End of ConstIterator Class ConstIterator(const Map<Key_T,Mapped_T> :: Iterator &iteration_1) */

    /*  ConstIterator Class get_const_node_pointer() */
    template<typename Key_T, typename Mapped_T>
   	Skiplist<Key_T, Mapped_T> *Map<Key_T, Mapped_T> :: ConstIterator :: get_const_node_pointer() const
    {
        /*  return constant_node_pointer location */
		return constant_node_pointer;
	} /*    End of ConstIterator Class get_const_node_pointer() */

    /*  ConstIterator Class set_const_node_pointer() */
	template<typename Key_T, typename Mapped_T>
	void Map<Key_T, Mapped_T> :: ConstIterator :: set_const_node_pointer(Skiplist<Key_T, Mapped_T> *temporary)
    {
        /*  return constant_node_pointer temporary */
		constant_node_pointer = temporary;
	} /*    End of ConstIterator Class set_const_node_pointer() */

    /*  ConstIterator Class operator= ()
        changed after Piazza post from TA */
    template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T> :: ConstIterator &Map<Key_T, Mapped_T> :: ConstIterator :: operator=(const ConstIterator &iteration_1)
    {
        /*  check if it's NULL then return constant_node_pointer */
	 	if (iteration_1.constant_node_pointer == NULL) {
            constant_node_pointer = NULL;
        }
		else {
            /*  Otherwise return the iteration_1's constant pointer */ 
			constant_node_pointer = iteration_1.constant_node_pointer;
		}
        /*  return this pointer */
        return (*this);
	} /*   End of ConstIterator Class operator= () */

    /*  ConstIterator Class operator++() */
    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T> :: ConstIterator &Map<Key_T, Mapped_T> :: ConstIterator :: operator++()
    {
        /*  check if it's NULL then return this pointer */
        if (constant_node_pointer == NULL) {
            return (*this);
        }
        else {
            /*  Otherwise return the 
                constant_node_pointer->frontend_node location */ 
            constant_node_pointer = constant_node_pointer->frontend_node[0];
            /*  Now return this pointer */
            return (*this);
        }
    } /*    End of ConstIterator Class operator++() */

    /*  ConstIterator Class operator++(int) */
    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T> :: ConstIterator Map<Key_T, Mapped_T> :: ConstIterator :: operator++(int)
    {
        /*  instantiate this pointer */
        Map<Key_T, Mapped_T> :: ConstIterator iteration(*this);

        /*  Now find the constant_node_pointer location */
        if(constant_node_pointer != NULL) {
            constant_node_pointer = constant_node_pointer->frontend_node[0];
        }
        /*  Now return iteration pointer */
        return iteration;
    } /*  End of ConstIterator Class operator++(int) */

    /*  ConstIterator Class operator--() */
    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T> :: ConstIterator &Map<Key_T, Mapped_T> :: ConstIterator :: operator--()
    {
        /*  check if it's NULL then return this pointer */
        if (constant_node_pointer == NULL) {
            return (*this);
        }
        else {
            /*  Otherwise return the 
                constant_node_pointer->backend_node location */ 
            constant_node_pointer = constant_node_pointer->backend_node[0];
            return (*this);
        }
    } /*    End of ConstIterator Class operator--() */

    /*  ConstIterator Class operator--(int) */
    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T> :: ConstIterator Map<Key_T, Mapped_T> :: ConstIterator :: operator--(int)
    {
        /*  instantiate ConstIterator iteration */
        Map<Key_T, Mapped_T> :: ConstIterator iteration(*this);

        /*  check if it's NULL then return this pointer */
        if (constant_node_pointer != NULL) {
            constant_node_pointer = constant_node_pointer->backend_node[0];
        }
        
        /*  return the iteration pointer */
        return iteration;
    } /*    End of ConstIterator Class operator--(int) */

    /*  ConstIterator Class operator*() const */
    template<typename Key_T, typename Mapped_T>
	const typename Map<Key_T, Mapped_T> :: ValueType &Map<Key_T, Mapped_T> :: ConstIterator :: operator*() const
    {
        /*  cast and return the node_pair */
		return (static_cast<Skiplist_Node<Key_T, Mapped_T>*>(constant_node_pointer)->node_pair);
	} /*  End of ConstIterator Class operator*() const */
    
    /*  ConstIterator Class operator->() const */
    template<typename Key_T, typename Mapped_T>
    const typename Map<Key_T, Mapped_T>::ValueType* Map<Key_T, Mapped_T>::ConstIterator::operator->() const
    {
        /*  return static_cast */
		return &(static_cast<Skiplist_Node<Key_T, Mapped_T>*>(constant_node_pointer)->node_pair);
	} /*    End of ConstIterator Class operator->() const */

    /* Desctructor Defination for ConstIterator */
    template<typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T>::ConstIterator::~ConstIterator()
    {
   	} /*    End of Desctructor for ConstIterator */

    /*  Iterator Class temporary pass by */
    template<typename Key_T, typename Mapped_T>
	Map<Key_T, Mapped_T> :: Iterator :: Iterator(Skiplist<Key_T, Mapped_T> *temporary)
    {
        /*  if temporary then NULL now node_pointer is NULL */
		if (temporary == NULL) {
            node_pointer = NULL;
        }
		else {
            /*  node_pointer is temporary */
            node_pointer = temporary;
        }
	} /*    End of Iterator Class temporary pass by */

    /*  Iterator Class Iterator iteration_1 */
    template<typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T> :: Iterator :: Iterator(const Map<Key_T,Mapped_T> :: Iterator &iteration_1)
    {
        /*  if iteration_1.node_pointer then NULL now node_pointer is NULL */
        if (iteration_1.node_pointer == NULL) {
            node_pointer = NULL;
        }
        else {
            /*  node_pointer is iteration_1.node_pointer */
            node_pointer = iteration_1.node_pointer;
        }
    } /*    End of Iterator Class Iterator iteration_1 */

    /* changes done after TA's piazza post */
    /*  Iterator Class Iterator operator=() */
    template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T> :: Iterator &Map<Key_T, Mapped_T> :: Iterator :: operator=(const Iterator &iteration_1)
    {
	 	if (iteration_1.node_pointer == NULL) {
             /* Found NULL so initialize to NULL */
             node_pointer = NULL;
        }
		else {
            /*  As it is not null return iteration_1.node_pointer */
			node_pointer = iteration_1.node_pointer;
		}
        /*  Now return the this pointer */
        return (*this);
	} /*    End of Iterator Class Iterator operator=() */

    /*  Iterator Class Iterator operator++() */
    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T> :: Iterator &Map<Key_T, Mapped_T> :: Iterator :: operator++()
    {
        /*  if node_pointer is NULL then return this pointer */
        if(node_pointer == NULL) {
            return (*this);
        }
        else {
            /*  node_pointer is frontend_node */
            node_pointer = node_pointer->frontend_node[0];
            return (*this);
        }
    } /*    End of Iterator Class Iterator operator++() */

    /*  Iterator Class Iterator operator++(int) */
    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T> :: Iterator Map<Key_T, Mapped_T> :: Iterator :: operator++(int)
    {
        /*  instantiate iteration(*this) pointer */
        Map<Key_T, Mapped_T> :: Iterator iteration(*this);

        if(node_pointer != NULL) {
            /*  since node_pointer is not NULL 
                then frontend_node[0] */
            node_pointer = node_pointer->frontend_node[0];
        }

        /*  return iteration value */
        return iteration;
    } /*    End of Iterator Class Iterator operator++(int) */

    /*  Iterator Class Iterator operator--() */
    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T> :: Iterator &Map<Key_T, Mapped_T> :: Iterator :: operator--()
    {
        /*  if node_pointer is NULL then return this pointer */
        if (node_pointer == NULL) {
            return (*this);
        }
        else {
            /*  since node_pointer is not NULL 
                then backend_node[0] */
            node_pointer = node_pointer->backend_node[0];
            return (*this);
        }
    } /*    End of Iterator Class Iterator operator--()  */

    /*  Iterator Class Iterator operator--(int) */
    template<typename Key_T, typename Mapped_T>
    typename Map<Key_T, Mapped_T> :: Iterator Map<Key_T, Mapped_T> :: Iterator :: operator--(int)
    {
        /*  instantiate iteration(*this) pointer */
        Map<Key_T, Mapped_T>::Iterator iteration(*this);

        if(node_pointer != NULL) {
            /*  since node_pointer is not NULL 
                then backend_node[0] */
            node_pointer = node_pointer->backend_node[0];
        }

        /*  return iteration value */
        return iteration;
    } /*    End of Iterator Class Iterator operator--(int) */

    /*  Iterator Class set_node_pointer() */
    template<typename Key_T, typename Mapped_T>
	void Map<Key_T, Mapped_T> :: Iterator :: set_node_pointer(Skiplist<Key_T, Mapped_T> *temporary)
    {
        /*  return the temporary pointer location */
		node_pointer = temporary;
	} /*    End of Iterator Class set_node_pointer() */

    /*  Iterator Class get_node_pointer() */
    template<typename Key_T, typename Mapped_T>
	Skiplist<Key_T, Mapped_T> *Map<Key_T, Mapped_T> :: Iterator :: get_node_pointer() const
    {
        /*  return node_pointer's location */
		return node_pointer;
	} /*    End of Iterator Class get_node_pointer() */

    /*  Iterator Class Iterator operator*() */
    template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T> :: ValueType &Map<Key_T, Mapped_T> :: Iterator :: operator*() const
    {
        /*  return node_pair location, could have done using 
            Map<Key_T, Mapped_T>::ValueType but that would cause a reference error 
            updated after Professor's November 11, 2020	Lecture*/
		return (static_cast<Skiplist_Node<Key_T, Mapped_T>*>(node_pointer)->node_pair);
	} /*    End of Iterator Class Iterator operator*() */

    /*  Iterator Class Iterator operator->() */
	template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T> :: ValueType *Map<Key_T, Mapped_T> :: Iterator :: operator->() const
    {
        /* return the casting node_pair pointer value */
		return &(static_cast<Skiplist_Node<Key_T, Mapped_T>*>(node_pointer)->node_pair);
	} /*    End of Iterator Class Iterator operator->() */

    /*  Desctructor Defination for Iterator */
    template<typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T> :: Iterator :: ~Iterator()
    {

    } /*    End of Desctructor Defination for Iterator */

    /*  Funpart begins ;-) */
    /*  Map Class Default ctor */
    template<typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T> :: Map()
    {
        /*  initialize the size to 0 
            for every instantiation */
        map_size = 0;
    } /*    End of Map Class Default ctor */

    /*  Map Class ctor for initiating ConstIterator iteration */
    template< typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T> :: Map(const Map<Key_T, Mapped_T> &map_1)
    {
		if (map_1.map_size == 0) {
            /* Since its an empty map */
            map_size = 0;
        }
		else {
            /*  start by initializing map_size to 0 */
			map_size = 0;

            /*  instantiate ConstIterator iteration to begin() */
			Map<Key_T, Mapped_T> :: ConstIterator iteration = map_1.begin();

            /*  until it reaches the end of map iterate and insert */
			for (; iteration != map_1.end(); ++iteration) {
				Skiplist_Node<Key_T, Mapped_T> *temporary = static_cast<Skiplist_Node<Key_T, Mapped_T>*>(iteration.get_const_node_pointer());
                /*  if for Performance Test [test-scaling.cpp] 
                    insertion fails handle it smartly */
                try {
                    /*  Easy for Debugging-1 */
				    map_list.insert(temporary->node_pair.first, temporary->node_pair.second, -1);
                }
                catch (const std::exception& e) { 
                    /*  if the insert operation fails print the error */
                    std::cout << "map_list.insert failed for Map(const Map<Key_T, Mapped_T> &map_1)!" << std::endl;
                    std::cout << e.what(); 
                }
                /*  as insert is successfull increament map_size */
				map_size++;
			}
		}
	} /*    End of Map Class ctor ConstIterator iteration */

    /*  Member Functions and Comparison Operators of Map */

    /*  Map Class operator=() */
    template<typename Key_T, typename Mapped_T>
	Map<Key_T, Mapped_T> &Map<Key_T, Mapped_T> :: operator=(const Map &map_1)
    {
		if ((*this) != map_1) {
            /*  check and see if the map_1 is empty with size 0 */
			if(map_1.map_size == 0) {
                map_size = 0;
            }
            /*  Delete all the existing nodes */
			else {     
                this->clear();
                /*  start by initializing map_size to 0 */
                map_size = 0;

                /*  instantiate ConstIterator iteration to begin() */
				Map<Key_T, Mapped_T> :: ConstIterator iteration = map_1.begin();

                /*  until it reaches the end of map iterate and insert */
				for(; iteration != map_1.end(); iteration++){
					Skiplist_Node<Key_T, Mapped_T> *temporary = static_cast<Skiplist_Node<Key_T, Mapped_T>*> (iteration.get_const_node_pointer());
                    /*  if for Performance Test [test-scaling.cpp] insertion fails handle it smartly */
                    try {
                        /*  Easy for Debugging-2 with gdb */
                        map_list.insert(temporary->node_pair.first, temporary->node_pair.second, -1);
                    }
                    catch (const std::exception& e) { 
                        /*  if the insert operation fails print the error */
                        std::cout << "map_list.insert failed for operator=!" << std::endl;
                        std::cout << e.what(); 
                    }
					map_size++;
				}
			}
		}
        /*  return this pointer */
		return (*this);
	} /*    End of Map Class operator=() */

    /*  Map Class Initizalizer's list constructor */
    template< typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T> :: Map(std::initializer_list<ValueType> init_list)
    {
        /*  initialize the 'it' iterator */
        typename std::initializer_list<ValueType>::iterator it;

        /*  resize the map to 0 */
        map_size = 0;

        /*  initlize the list from beginning to end */
        for (it = init_list.begin(); it != init_list.end(); it++) {
            if( &(it->first) != NULL && &(it->second) != NULL ) {
                map_list.insert(it->first, it->second, -1);
                map_size++;
            }
        }
    }   /*     End of Map Class Initizalizer's list constructor */

    /*  Map Class Basic Function - size() */
    template<typename Key_T, typename Mapped_T>
    size_t Map<Key_T, Mapped_T>::size() const{
        return map_size;
    } /*   End of Map Class Basic Function - size() */

    /*  Map Class Basic Function - empty() */
    template< typename Key_T, typename Mapped_T>
    bool Map<Key_T, Mapped_T> :: empty() const
    {
        /*  Check if the size of map is 0 
            and return TRUE or FALSE */
        if (map_size == 0) {
            return true;
        }
        else 
            return false;
    }  /*   End of Map Class Basic Function - empty() */

    /*  SkipList Class Basic Function - get_map_list() */
    template< typename Key_T, typename Mapped_T>
    SkipList<Key_T, Mapped_T> Map<Key_T, Mapped_T> :: get_map_list() const
    {
        /*  Just return the map_list */
        return map_list;
    } /*   End of SkipList Class Basic Function - get_map_list() */

    /*  std::pair Map insert(value_pair) */
    template< typename Key_T, typename Mapped_T>
	std::pair<typename Map<Key_T, Mapped_T> :: Iterator, bool> Map<Key_T, Mapped_T> :: insert(const ValueType& value_pair)
    {
        /*  instantiate insert_pair object from std::pair */
		std::pair<Skiplist<Key_T, Mapped_T>*, bool> insert_pair;

        /*  if for Performance Test [test-scaling.cpp] insertion fails handle it smartly */
        try {
            /*  Easy for Debugging-2 with gdb */
            insert_pair = map_list.insert(value_pair.first, value_pair.second, -1);
        }
        catch (const std::exception& e) { 
            /*  if the insert operation fails print the error */
            std::cout << "map_list.insert failed for insert(value_pair)" << std::endl;
            std::cout << e.what(); 
        }

        /* Iterator Class ctor along with Skiplist Class pointer creation */
		Map<Key_T, Mapped_T>::Iterator temp_iterator(insert_pair.first);  

        /*   update the size of map */
		if(insert_pair.second) 
            map_size++;

        /*  binding the return_pair with make_pair */
        std::pair<Map<Key_T, Mapped_T>::Iterator, bool> return_pair = std::make_pair(temp_iterator, insert_pair.second);

        /*  return the pair formed */
		return return_pair;
	} /* End of std::pair Map insert(value_pair) */

    /* Map Class begin() Iterator */
    template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T> :: Iterator Map<Key_T, Mapped_T> :: begin()
    {
        /*  instantiate pointer to frontend node of head node using the
            map_list's get_head_node function */
		Skiplist<Key_T, Mapped_T> *temporary = map_list.get_head_node()->frontend_node[0];

		if (temporary == map_list.get_tail_node()) {
            /*  Default to NULL */ 
            Iterator iteration_1(temporary);
            return iteration_1;
        }
        else {
            /*  otherwise return the Map with Iterator */
            Map<Key_T, Mapped_T>::Iterator iteration_1(temporary);
            return iteration_1;
        }
	} /* End of Map Class begin() Iterator */

    /* Map Class begin() ConstIterator */
    template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T> :: ConstIterator Map<Key_T, Mapped_T> :: begin() const
    {
        /*  instantiate pointer to frontend node of head node using the
            map_list's get_head_node function */
		Skiplist<Key_T, Mapped_T> *temporary = map_list.get_head_node()->frontend_node[0];

		if (temporary == map_list.get_tail_node()) {
            /*  Default to NULL */ 
            Map<Key_T, Mapped_T>::ConstIterator iteration_1(temporary);
            return iteration_1;
        }
		else {
            /*  otherwise return the Map with Iterator */
            Map<Key_T, Mapped_T>::ConstIterator iteration_1(temporary);
            return iteration_1;
        }
	} /* End of Map Class begin() ConstIterator */

    /*  Map Class template<typename IT_T> */
    template<typename Key_T, typename Mapped_T>
	template<typename IT_T>
	void Map<Key_T, Mapped_T> :: insert(IT_T begin_range, IT_T end_range)
    {
        /*  instantiate IT_T */
		IT_T iteration;

        /*  from the beginning to the end of range iterate and insert */
		for (iteration = begin_range; iteration != end_range; iteration++) {
            
            /*  instantiate temporary to first and second */
			ValueType temporary(iteration->first, iteration->second);

            /*  if for Performance Test [test-scaling.cpp] insertion fails handle it smartly */
            try {
                /*  Easy for Debugging-2 with gdb */
                this->insert(temporary);
            }
            catch (const std::exception& e) { 
                /*  if the insert operation fails print the error */
                std::cout << "insert(temporary) failed for insert(IT_T begin_range, IT_T end_range)" << std::endl;
                std::cout << e.what(); 
            }
			
            /*  update the Map size */
            map_size++;
		}
	} /* End of Map Class template<typename IT_T> */
    
    /*  Map Class Mapped_T &operator[](const Key_T &) */
    template<typename Key_T, typename Mapped_T>
	Mapped_T& Map<Key_T, Mapped_T> :: operator[](const Key_T& key)
    {
        /* 	If key is in the map, return a reference to the corresponding mapped object. 
            If it is not, value initialize a mapped object 
            for that key and returns a reference to it (after insert). 
            This operator may not be used for a Mapped_T class type that does not support default construction. */
		Skiplist<Key_T, Mapped_T> *temporary = map_list.search(key);

		if (temporary == NULL) {
            /*  Empty Map key, value(map)*/
			Mapped_T map{};

            /*  make a pair for insertion */
			ValueType temporary_pair = std::make_pair(key,map);
            
            /*  insert and return */
            std::pair<Map<Key_T, Mapped_T>::Iterator, bool> return_pair = this->insert(temporary_pair);
            
            /*  return the static case of node_pair */
            return (static_cast<Skiplist_Node<Key_T, Mapped_T>*>(return_pair.first.get_node_pointer())->node_pair.second);
		}
		else {
            /*  if temporary is has contents then return 
                temporary pointing node */
			return ( (static_cast<Skiplist_Node<Key_T, Mapped_T>*>(temporary)->node_pair.second) );
		}
	} /* End of Map Class Mapped_T &operator[](const Key_T &) */

    /*  Map Class erase method with key */
    template<typename Key_T, typename Mapped_T>
	void Map<Key_T, Mapped_T> :: erase(const Key_T &key)
    {
        /*  search the key given for the map */
		Skiplist<Key_T, Mapped_T> *temporary = map_list.search(key);

        /*  if the key is not found then throw and exception */
		if (temporary == NULL) 
            throw std::out_of_range("Element does not exists in MAP!");
		else {
            /*  if the key exists in the map then remove it */
			map_list.remove_node( (static_cast<Skiplist_Node<Key_T, Mapped_T>*>(temporary)->node_pair.first) );

            /*  resize the map */
			map_size--;
		}
	} /*    End of Map Class erase method with key */

    /*  Map Class erase method with key's position */
    template<typename Key_T, typename Mapped_T>
	void Map<Key_T, Mapped_T> :: erase(typename Map<Key_T, Mapped_T>::Iterator position)
    {
        /*  Removes the given object from the map. The object may be indicated by iterator, 
            or by key. If given by key, throws std::out_of_range if the key is not in the Map */
		if ((position.get_node_pointer() != NULL) && (position.get_node_pointer()->sentinel)!= 1) {

            /*  The position of the key is found
                so now remove that node */
			map_list.remove_node((static_cast<Skiplist_Node<Key_T, Mapped_T>*>(position.get_node_pointer())->node_pair.first));

            /*  resize the map */
			map_size--;
		}
	} /*    End of Map Class erase method with key's position */

    /*  Map Class clear() */
    template<typename Key_T, typename Mapped_T>
	void Map<Key_T, Mapped_T> :: clear() 
    {
        /*  MAP Modifier - Removes all elements from the map. */
		if(map_size != 0) {  
            /*  map_size is greater than 0 means elements exists in map */
            Skiplist<Key_T, Mapped_T> *foo = map_list.get_head_node();
            
            /*  point to the head node */
            foo = map_list.get_head_node();

            /*  create a copy of it */
            Skiplist<Key_T, Mapped_T>* boo = foo;

            /*  until the element in deleted repeat operation */
        	while(boo) {
        		if(boo->sentinel == 1){
                    boo = boo->frontend_node[0];
        		}
        		else {
                    /*  create a copy of it */
                    foo = boo;
                    /*  point to the frontend_node */
                    boo = boo->frontend_node[0];
        			
                    /*  if for Performance Test [test-scaling.cpp] removal fails handle it smartly */
                    try {
                        /*  Easy for Debugging-2 with gdb */
                        map_list.remove_node(static_cast<cs540::Skiplist_Node<Key_T,Mapped_T>*>(foo)->node_pair.first);
                    }
                    catch (const std::exception& e) { 
                        /*  if the remove_node operation fails print the error */
                        std::cout << "remove_node() failed for clear()" << std::endl;
                        std::cout << e.what(); 
                    }
                    
                    /*  resize the map */
                    map_size--;
        		}
        	}
		}
	} /* End of Map Class clear() */

    /*  Map class end() for Iterator */
    template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T> :: Iterator Map<Key_T, Mapped_T> :: end()
    {
        /*  instantiate tail node for Iterator */
		Map<Key_T, Mapped_T>::Iterator iteration_1(map_list.get_tail_node());
		return iteration_1;
	} /*  End of Map class end() for Iterator */

    /*  Map class end() for ConstIterator */
    template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T> :: ConstIterator Map<Key_T, Mapped_T> :: end() const
    {
        /*  instantiate tail node for Iterator */
		Map<Key_T, Mapped_T> :: Iterator iteration_1(map_list.get_tail_node());
		return iteration_1;
	} /*    End of Map class end() for ConstIterator */

    /*  Map class rbegin() for ReverseIterator */
    template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T>::ReverseIterator Map<Key_T, Mapped_T>::rbegin()
    {
        /*  Returns an ReverseIterator to the first element in reverse order, 
            which is the last element in normal order. */
		Skiplist<Key_T, Mapped_T> *temporary = map_list.get_tail_node()->backend_node[0];

		if (temporary == map_list.get_head_node()) {
            /*  if is the first head node */
            Map<Key_T, Mapped_T>::ReverseIterator iteration_1(temporary);
            return iteration_1;
        }
		else {
            Map<Key_T, Mapped_T>::ReverseIterator iteration_1(temporary);
            return iteration_1;
        }
	} /* End of Map class rbegin() for ReverseIterator */

    /*  Map class rend() for ReverseIterator */
	template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T> :: ReverseIterator Map<Key_T, Mapped_T> :: rend()
    {
        /*  Returns an ReverseIterator pointing to one past the last element 
            in reverse order, which is one before the first element in normal order.*/
		Map<Key_T, Mapped_T>::ReverseIterator iteration_1(map_list.get_head_node());
        return iteration_1;
	} /* End of Map class rend() for ReverseIterator */

    /* Map class find() for Iterator using key */
    template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T> :: Iterator Map<Key_T, Mapped_T> :: find(const Key_T &key)
    {
        /*  Returns an iterator to the given key. If the key is not found, 
            these functions return the end() iterator. */

        /*  Lookout for the key given */
		Skiplist<Key_T, Mapped_T> *temporary = map_list.search(key);

		if (temporary != NULL) {
            /*  if it is found then return */
            Map<Key_T, Mapped_T>::Iterator iteration_1(temporary);
            return iteration_1;
        }
        else {
            /*  If that does not exists */
            Map<Key_T, Mapped_T>::Iterator iteration_1(this->end());
            return iteration_1;
        }
	} /* End of Map class find() for Iterator using key */

    /* Map class find() for ConstIterator using key */
	template<typename Key_T, typename Mapped_T>
	typename Map<Key_T, Mapped_T> :: ConstIterator Map<Key_T, Mapped_T> :: find(const Key_T &key) const
    {
        /*  Returns an iterator to the given key. If the key is not found, 
            these functions return the end() iterator. */

        /*  Lookout for the key given */
		Skiplist<Key_T, Mapped_T> *temporary = map_list.search(key);

		if (temporary != NULL) {
            /*  if it is found then return */
            Map<Key_T, Mapped_T>::ConstIterator iteration_1(temporary);
            return iteration_1;
        }
        else {
            /*  If that does not exists */
            Map<Key_T, Mapped_T>::ConstIterator iteration_1(this->end());
            return iteration_1;
        }
	} /* End of Map class find() for ConstIterator using key */

    /* Map class at() using key */
    template<typename Key_T, typename Mapped_T>
	Mapped_T&  Map<Key_T, Mapped_T> :: at(const Key_T &find_key)
    {
        /*  Returns a reference to the mapped object at the specified key. 
            If the key is not in the Map, throws std::out_of_range. */

        /* First check to see if that key exists in the map */
		Skiplist<Key_T, Mapped_T>* temporary = map_list.search(find_key);
        
		if (temporary == NULL) {
            /*  As it does not exists then return 
            out of range exception */
			throw std::out_of_range("Element does not exists in MAP!");
		}
		else {
            /*  Since it exists now return the value */
            return (static_cast<Skiplist_Node<Key_T, Mapped_T>*>(temporary)->node_pair.second);

        }
	} /* End of Map class at() using key */

    /* Map class at() using key const */
	template<typename Key_T, typename Mapped_T>
	const Mapped_T&  Map<Key_T, Mapped_T> :: at(const Key_T &find_key) const
    {
        /*  Returns a const reference to the mapped object at the specified key. 
            If the key is not in the map, throws std::out_of_range. */

        /* First check to see if that key exists in the map */
		Skiplist<Key_T, Mapped_T> *temporary = map_list.search(find_key);
        
		if (temporary == NULL) {
            /*  As it does not exists then return 
            out of range exception */
			throw std::out_of_range("Element does not exists in MAP!");
		}
		else {
            /*  Since it exists now return the value */
            return (static_cast<Skiplist_Node<Key_T, Mapped_T>*>(temporary)->node_pair.second);
        }
	} /* End of Map class at() using key const */

    /*  Map class Destructor */
    template< typename Key_T, typename Mapped_T>
    Map<Key_T, Mapped_T> :: ~Map()
    {
    } /* End of Map class Destructor */

} /* End of Namespace cs540 */

#endif /* End of Include Guards */