//
// Created by Viktoria on 14.05.2022.
//

#ifndef TVPIS_DEQUE_HPP
#define TVPIS_DEQUE_HPP

#include "List.hpp"

namespace ft {
    template<typename T, typename Container = ft::List<T> >
    class Deque {
    protected:
        Container container_;
    public:

        explicit Deque(const Container &cont = Container()) : container_(cont) {
        }
        Deque(const Deque &other) : container_(other.container_) {
        }
        Deque &operator=(const Deque &other) {
            if (this != &other) {
                container_ = other.container_;
            }
            return *this;
        }
        ~Deque() {
        }

        T front() {
            return container_.front();
        }

        bool empty() const {
            return container_.empty();
        }

        void push_back(const T &value) {
            container_.push_back(value);
        }

        void push_front(const T &value) {
            container_.push_front(value);
        }

        void pop_back() {
            container_.pop_back();
        }

        void pop_front() {
            container_.pop_front();
        }

        T back() {
            return container_.back();
        }


    };
}

#endif //TVPIS_DEQUE_HPP
