//
// Created by Viktoria on 14.05.2022.
//

#ifndef TVPIS_LISTNODE_HPP
#define TVPIS_LISTNODE_HPP
#include "include.hpp"

namespace ft {

    template<typename T>
    struct List_node {
        ClientMemoryBlock<List_node> prev;
        ClientMemoryBlock<List_node> next;
        T data;
    };

}
#endif //TVPIS_LISTNODE_HPP
