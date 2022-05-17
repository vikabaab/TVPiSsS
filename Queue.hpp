//
// Created by Viktoria on 14.05.2022.
//

#ifndef TVPIS_QUEUE_HPP
#define TVPIS_QUEUE_HPP

namespace ft {

#include "List.hpp"

    template<typename T, typename Container = ft::List<T> >
    class Queue {
    protected:
        Container container_;
    public:

        explicit Queue(const Container &cont = Container()) : container_(cont) {
        }
        Queue(const Queue &other) : container_(other.container_) {
        }
        Queue &operator=(const Queue &other) {
            if (this != &other) {
                container_ = other.container_;
            }
            return *this;
        }
        ~Queue() {
        }

        T front() {
            return container_.front();
        }

        bool empty() const {
            return container_.empty();
        }

        void push(const T &value) {
            container_.push_back(value);
        }
        void pop() {
            container_.pop_front();
        }
    };
}
#endif //TVPIS_QUEUE_HPP
