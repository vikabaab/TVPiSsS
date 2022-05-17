//
// Created by Viktoria on 14.05.2022.
//

#ifndef TVPIS_STACK_HPP
#define TVPIS_STACK_HPP
namespace ft {

#include "List.hpp"

    template <typename T, typename Container = ft::List<T> >
    class Stack {
    protected:
        Container container_;
    public:
        typedef Container container_type;


        explicit Stack(const Container &cont = Container()): container_(cont) {
        }
        Stack(const Stack &other): container_(other.container_) {
        }
        Stack &operator=(const Stack &other) {
            if (this != &other) {
                container_ = other.container_;
            }
            return *this;
        }
        ~Stack() {
        }
        bool empty() const {
            return container_.empty();
        }

        T top() {
            return container_.back();
        }

        void push(const T &value) {
            container_.push_back(value);
        }

        void pop() {
            container_.pop_back();
        }

        template<typename T_, typename Container_>
        friend bool operator==(const Stack<T_, Container_> &lhs, const Stack<T_, Container_> &rhs);

        template<typename T_, typename Container_>
        friend bool operator<(const Stack<T_, Container_> &lhs, const Stack<T_, Container_> &rhs);
    };

    template<typename T, typename Container>
    bool operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
        return lhs.container_ == rhs.container_;
    }

    template<typename T, typename Container>
    bool operator!=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
        return !(lhs == rhs);
    }

    template<typename T, typename Container>
    bool operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
        return lhs < rhs;
    }

    template<typename T, typename Container>
    bool operator>(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
        return rhs < lhs;
    }

    template<typename T, typename Container>
    bool operator<=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
        return !(rhs < lhs);
    }

    template<typename T, typename Container>
    bool operator>=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
        return !(lhs < rhs);
    }

}
#endif //TVPIS_STACK_HPP
