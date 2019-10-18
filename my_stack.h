//
// Created by oleg on 11.10.2019.
//

#ifndef STACK_MY_STACK_H
#define STACK_MY_STACK_H

#include <functional>
#include <stdint.h>
#include <iostream>

#define DEBUG true
#define CHECK if (DEBUG && check()) dump(check(), __FILE__, __LINE__, __FUNCTION__);
enum my_stack_err_code {
    ok = 0,
    sizes_broken = 1,
    buff_broken = 2,
    buff_pointer_broken = 3
};

///Stack of T
template <class T>
class my_stack {
private:
    struct stack_buffer {
        int first_canary;
        int buff_size_copy;
        int size_copy;
        int hsh;
        int size;
        int buff_size;
        T buff[1];
    };

    int first_canary;
    stack_buffer* buff;
    int second_canary;

    int* second_canary_ptr () {
        return reinterpret_cast<int*> (reinterpret_cast<char*>(buff) + 4*6 + sizeof(T) * buff->buff_size + 1);
    }
    void dump (int err_code, const char file[], int line, const char function[]);
    int check();
    int get_hash(void* start_ptr, int count);

public:
    ///Stack initializer (empty)
    /**
     *
     */
    my_stack();
    ~my_stack();
    ///Pushing back to the stack elem of T
    /**
     *
     * @param elem elem which is pushed back
     * @return success of operation
     */
    bool push_back(T elem);
    ///Pop element from the stack
    /**
     *
     * @return success of opetation
     */
    bool pop_back();
    ///Back element of stack
    /**
     *
     * @return back element of stack
     */
    T back();
    ///Size of the stack
    /**
     *
     * @return size of the stack
     */
    int size();
};

#endif //STACK_MY_STACK_H
