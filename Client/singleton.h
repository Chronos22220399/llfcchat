#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>       // shared_ptr enable_shared_from_this
#include <mutex>        // call_once once_flag
#include <iostream>


/*********************************************************************
 * @file         singleton.h
 * @brief        单例模式模版
 *
 * @author       Ess
 * @date         2024/10/01
 * @history
 **********************************************************************/

template <typename T>
class SingleTon {
protected:
    SingleTon() = default;      // SingleTon() should be in protected area, because the subclass need to use this constructor
    SingleTon(const SingleTon &) = delete;
    SingleTon& operator= (const SingleTon &) = delete;

    static std::shared_ptr<T> _instance;
public:
    static std::shared_ptr<T> Getinstance() {
        // in fact, since c++11, we could use this 'phrase'
        // static T _instance;
        // return _instance;
        // instead below
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            _instance = std::shared_ptr<T>(new T);
        });
        return _instance;
    }

    void PrintAddress() {
        std::cout << _instance.get() << std::endl;
    }

    ~SingleTon() {
        std::cout << "this is singleton destruct" << std::endl;
    }
};


template <typename T>
// std::shared_ptr<T> SingleTon<T>::_instance = std::shared_ptr<T>(new T);
std::shared_ptr<T> SingleTon<T>::_instance = nullptr;

#endif // SINGLETON_H
