#include <iostream>
#include <exception>
#include "List.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "Deque.hpp"
#include "HashTable.hpp"
using namespace std;
int main() {
//ft::List<int> l = ft::List<int>();
//
//  for (int i = 1; i < 1000; ++i) {
//    l.push_back(i);
//  }
//
//
//  std::cout << l.back() << " " << l.front();

//    ft::Deque<int> q = ft::Deque<int>();
//    q.push_back(5);
//
//    std::cout << q.back();
//
//    q.push_front(10);
//
//    std::cout << q.front();
//
//    q.pop_back();
//    std::cout <<  q.front();

    //cout<< "Hello";
    ft::HashTable<int> ht = ft::HashTable<int>();
    string key = "клюшка";
    int value = 5;
    ht.insert(key, value);
    ht.insert("1", 1);
    ht.insert("ebane45", 10);
    ht.insert("tema",234);
    ht.insert("Vika",564);
    ht.insert("Sergey",782);
    ht.insert("Kolya",3627);
    ht.insert("Kirill",674332);
    ht.ebalvrot();
    //ht.insert(key, 7);
//    cout << ht.find(key);
//    cout << ht.find("1");
//    ht.ebalvrot();
//    ht.resize();
//    cout << "\n" << "new";
//    ht.ebalvrot();
//    cout << ht.find(key);
//    ht.remove(key);
//    cout << "\n";
//    ht.ebalvrot();
    return 0;
}