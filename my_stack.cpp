//
// Created by oleg on 11.10.2019.
//

#include "my_stack.h"
template <class T>
my_stack<T>::my_stack():
        first_canary(265),
        second_canary(265) {
    buff = (stack_buffer*) calloc(4 * 6 + 1 + 4 + 10 * sizeof(T), 1);
    buff -> first_canary = 265;
    buff -> buff_size = 10;
    buff -> size = 0;
    buff -> buff_size_copy = buff->buff_size;
    buff -> size = buff->size;
    *second_canary_ptr() = 265;
    buff -> hsh = get_hash(reinterpret_cast<char*>(&(buff->buff)), buff->size * sizeof(T));
}

template <class T>
my_stack<T>::~my_stack() {
    CHECK
    free(buff);
}

template <class T>
void my_stack<T>::dump (int err_code, const char file[], int line, const char function[]) {
    std::cout<<"Problem!!! From "<<file<<", line "<<line<<", "<<function<<std::endl;
    std::cout<<"Problem in my_stack<T> where T = ";
    const char* str = typeid(T).name();
    int pos = 0;
    while ('0' <= str[pos] && str[pos] <= '9') ++pos;
    std::cout<<str + pos;
    std::cout<<std::endl;

    if (err_code == buff_pointer_broken) {
        std::cout<<"Buffer pointer is broken"<<std::endl;
        std::cout<<"First canary = "<<first_canary;
        if (first_canary == 265) std::cout<<"(alive)."<<std::endl;
        else std::cout<<"(dead)."<<std::endl;
        std::cout<<"Second canary = "<<second_canary;
        if (second_canary == 265) std::cout<<"(alive)."<<std::endl;
        else std::cout<<"(dead)."<<std::endl;
        std::cout<<"Buffer pointer is "<<buff<<std::endl;
    }
    else if (err_code == sizes_broken) {
        std::cout<<"Sizes are broken"<<std::endl;
        std::cout<<"First buff canary = "<<buff->first_canary;
        if (buff->first_canary == 265) std::cout<<"(alive)."<<std::endl;
        else std::cout<<"(dead)."<<std::endl;
        std::cout<<"Second buff canary = "<<*(reinterpret_cast<int*>(buff) + 4 * 6 + 4 + buff->buff_size * sizeof(T));
        if (*second_canary_ptr() == 265) std::cout<<"(alive)."<<std::endl;
        else std::cout<<"(dead)."<<std::endl;
        std::cout<<"Buffer pointer is "<<buff<<std::endl;
        std::cout<<"size values:"<<std::endl;
        std::cout<<buff->size<<"(original) "<<buff->size_copy<<"(copy)"<<std::endl;
        std::cout<<"buff_size values:"<<std::endl;
        std::cout<<buff->buff_size<<"(original) "<<buff->buff_size_copy<<"(copy)"<<std::endl;
    }
    else if (err_code == buff_broken) {
        std::cout<<"Buff is broken"<<std::endl;
        std::cout<<"First buff canary = "<<buff->first_canary;
        if (buff->first_canary == 265) std::cout<<"(alive)."<<std::endl;
        else std::cout<<"(dead)."<<std::endl;
        std::cout<<"Second buff canary = "<<*(reinterpret_cast<int*>(buff) + 4 * 6 + 1+ 4 + buff->buff_size * sizeof(T));
        if (*second_canary_ptr() == 265) std::cout<<"(alive)."<<std::endl;
        else std::cout<<"(dead)."<<std::endl;
        std::cout<<"Buffer pointer is "<<buff<<std::endl;
        std::cout<<"size value:"<<std::endl;
        std::cout<<buff->size<<std::endl;
        std::cout<<"buff_size value:"<<std::endl;
        std::cout<<buff->buff_size<<std::endl;
        std::cout<<"Buffer hash last value: "<<buff->hsh<<std::endl;
        std::cout<<"Buffer hash      value: "<<get_hash(reinterpret_cast<char*>(&(buff->buff)), buff->size * sizeof(T))<<std::endl;
        std::cout<<"Buffer:"<<std::endl;
        for (int i = 0; i < buff->buff_size; ++i) {
            if (i < buff->size) std::cout<<"*";
            std::cout<<"buff["<<i<<"] = "<<buff->buff[i]<<std::endl;
        }
    }
    else std::cout<<"Unknown error"<<std::endl;
    throw std::exception();
    std::cout<<std::endl;
}

template <class T>
int my_stack<T>::check() {
    if (first_canary != 265 || second_canary != 265 || (!buff))
        return buff_pointer_broken;
    if (buff->size != buff->size_copy || buff->buff_size != buff->buff_size_copy)
        return sizes_broken;
    if (buff->size < 0 || buff->buff_size <= 0 || buff->size > buff->buff_size)
        return sizes_broken;
    if (buff->hsh != get_hash(reinterpret_cast<char*>(&(buff->buff)), buff->size * sizeof(T)) ||
        buff->first_canary != 265 ||
        *second_canary_ptr() != 265)
    {
        return buff_broken;
    }
    return ok;
}

template <class T>
int my_stack<T>::get_hash(void* start_ptr, int count) {
    if (!(DEBUG)) return 0;
    int64_t ans = 0;
    for (int i = 0; i < count; ++i) {
        ans = (ans * 257 + reinterpret_cast<char*>(start_ptr)[i] + 1) % 1000000007;
    }
    return int(ans);
}


template <class T>
bool my_stack<T>::push_back(T elem) {
    CHECK
    if (buff->size == buff->buff_size) {
        buff->buff_size *= 2;
        buff = (stack_buffer*) realloc(buff, 4 * 6 + 1 + 4 + buff->buff_size * sizeof(T));
        *second_canary_ptr() = 265;
    }
    buff->buff[buff->size] = elem;
    buff->size++;
    buff -> buff_size_copy = buff->buff_size;
    buff -> size_copy = buff->size;
    buff -> hsh = get_hash(reinterpret_cast<char*>(&(buff->buff)), buff->size * sizeof(T));
    CHECK
    return 1;
}

template <class T>
bool my_stack<T>::pop_back() {
    CHECK
    if (buff->size <= 0) return 0;
    buff->size--;
    if (buff->size * 2 >= 4 && buff->size * 4 < buff->buff_size) {
        buff->buff_size = buff->size * 2;
        buff = (stack_buffer*) realloc(buff, 4 * 6 + 1 + 4 + buff->buff_size * sizeof(T));
        *second_canary_ptr() = 265;
    }
    buff -> buff_size_copy = buff->buff_size;
    buff -> size_copy = buff->size;
    buff -> hsh = get_hash(reinterpret_cast<char*>(&(buff->buff)), buff->size * sizeof(T));
    CHECK
    return 1;
}

template <class T>
T my_stack<T>::back() {
    CHECK
    if (buff->size <= 0) return 0;
    return buff->buff[buff->size - 1];
}

template <class T>
int my_stack<T>::size() {
    CHECK
    return buff->size;

}