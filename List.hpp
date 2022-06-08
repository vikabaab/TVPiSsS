//
// Created by Viktoria on 14.05.2022.
//

#ifndef TVPIS_LIST_HPP
#define TVPIS_LIST_HPP

#include "ListNode.hpp"
#include "Utils.hpp"
#include "include.hpp"

namespace ft {
    template<typename T>
    class List {
    public:
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

    protected:
        typedef List_node<T> _Node;
        typedef ClientMemoryBlock<_Node> _Node_pointer;

        size_type size_;
        ::Allocator allocator_;

        _Node_pointer node_;

        _Node_pointer allocate_node(const value_type &x = {}) {
            auto ptr = allocator_.Allocate<List_node<T>>(sizeof(List_node<T>));
            ptr.GetObject()->data = x;

            return ptr;
        }

        _Node_pointer create_node(const value_type &x) {
            _Node_pointer ptr = allocate_node(x);

            ++size_;
            return ptr;
        }
        void destroy_node(_Node_pointer node) {
            allocator_.Free(node);

            --size_;
        }
        void make_connection(_Node_pointer prev, _Node_pointer next) {
            prev.GetObject()->next = next;
            next.GetObject()->prev = prev;
        }
        void make_connection(_Node_pointer prev, _Node_pointer to_insert, _Node_pointer next) {
            make_connection(prev, to_insert);
            make_connection(to_insert, next);
        }
    public:
        // Constructor and destructors
        List() : size_(0), allocator_(Allocator()) {
            node_ = allocate_node(T{});
            node_.GetObject()->next = node_;
            node_.GetObject()->prev = node_;
        }

        List(const List &other) :
                size_(0), allocator_(Allocator()) {
            node_ = allocate_node(T{});
            node_.GetObject()->next = node_;
            node_.GetObject()->prev = node_;

            _Node_pointer tmp = other.node_.GetObject()->next;
            while (tmp != other.node_) {
                push_back(tmp.GetObject()->data);

                tmp = tmp.GetObject()->next;
            }
        }

        ~List() {
            clear();
            allocator_.Free(node_);
        }

        // Element access
        T front() {
            return (node_.GetObject()->next).GetObject()->data;
        }

        T back() {
            return (node_.GetObject()->prev).GetObject()->data;
        }

        // Capacity functions
        [[nodiscard]] bool empty() const {
            return !size_;
        }

        [[nodiscard]] size_type size() const {
            return size_;
        }

        // Modifiers
        void clear() {
            _Node_pointer ptr = node_.GetObject()->next;
            while (ptr != node_) {
                _Node_pointer tmp = ptr.GetObject()->next;
                destroy_node(ptr);
                ptr = tmp;
            }

            node_.GetObject()->next = node_;
            node_.GetObject()->prev = node_;
        }

        _Node_pointer getNode(int pos) const {
            auto tmpNode = this->node_;
            while (pos-- >= 0) {
                tmpNode = tmpNode.GetObject()->next;
            }

            return tmpNode;
        }

        void erase(int pos) {
            _Node_pointer ptr = getNode(pos);
            make_connection(ptr.GetObject()->prev, ptr.GetObject()->next);
            destroy_node(ptr);
        }

        T operator[](size_type pos) const {
            return getNode(pos).GetObject()->data;
        }

        void push_back(const T &value) {
            _Node_pointer tmp = create_node(value);
            make_connection(node_.GetObject()->prev, tmp, node_);
        }

        void pop_back() {
            _Node_pointer tmp = node_.GetObject()->prev;
            make_connection(tmp.GetObject()->prev, node_);
            destroy_node(tmp);
        }

        void push_front(const T &value) {
            _Node_pointer tmp = create_node(value);
            make_connection(node_, tmp, node_.GetObject()->next);
        }

        void pop_front() {
            _Node_pointer tmp = node_.GetObject()->next;
            make_connection(node_, tmp.GetObject()->next);
            destroy_node(tmp);
        }
        void resize(size_type count, T value = T()) {
            if (count > size_) {
                while (count > size_) {
                    push_back(value);
                }
            } else if (count < size_) {
                while (count < size_) {
                    pop_back();
                }
            }
        }

        List &operator=(const List &other) {
            if (this != &other) {
                clear();

                size_ = 0;

                for (auto i = 0; i != other.size_; ++i) {
                    push_back(other[i]);
                }
            }

            return *this;
        }
    };



}

#endif //TVPIS_LIST_HPP
