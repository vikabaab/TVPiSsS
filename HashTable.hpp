//
// Created by Viktoria on 14.05.2022.
//

#ifndef TVPIS_HASHTABLE_HPP
#define TVPIS_HASHTABLE_HPP
using namespace std;
//#include "List.hpp"
#include "list.hpp"
#include "Utils.hpp"
namespace ft {


    template<typename T>
    struct HashTableElement{
        string key;
        T value;
    };

    template<typename T>
class HashTable{
    static const int default_size = 8;
    list<HashTableElement<T>> *_Array_list = new list<HashTableElement<T>>[default_size];
    int size;
    int buffer_size;
    constexpr static const double rehash_size = 0.75;
public:
    HashTable(){
        buffer_size = default_size;
        size = 0;
        for (int i = 0; i < buffer_size; i++){
            _Array_list[i] = list<HashTableElement<T>>();
        }
    }

    int hash_function(string s) // Хеш-функция
    {
        const int p = 31;
        long long hash = 0, p_pow = 1;
        for (int i = 0; i < s.length(); i++) {
            hash += int(s[i] - '0') * p_pow;
            p_pow *= p;
        }
        return abs(hash % buffer_size);
    }
    //Вставка элемента в хеш-таблицу
    void insert(string _key, T _value){
        size++;
        if (float(size)/float(buffer_size) >= rehash_size){
            this->resize();
        }
        HashTableElement<T> Element;
        Element.key = _key;
        Element.value = _value;
        int index = hash_function(_key);
        _Array_list[index].push_back(Element);
    }
    //Поиск элемента по ключу
    T find(string _key){
        int index = hash_function(_key);
        if (!_Array_list[index].empty()){
            for (auto iter = _Array_list[index].begin(); iter != _Array_list[index].end(); iter++){
                if (_key == (*iter).key){
                    return (*iter).value;
                }
            }
        }
        return _Array_list[index].front().value;
    }

    // Удаление элемента по ключу
    void remove(string _key){
        int index = hash_function(_key);
        bool finded = false;
        int number;
        if (!_Array_list[index].empty()){
            int i = 0;
            for (auto iter = _Array_list[index].begin(); iter != _Array_list[index].end(); iter++){
                if (_key == (*iter).key){
                    finded = true;
                    number = i;
                    break;
                }
                i++;
            }
            if (finded) {
                auto iter = _Array_list[index].begin();
                advance(iter, number);
                _Array_list[index].erase(iter);
            }
        }
    }
    //ПроверОчка
    void ebalvrot(){
        for (int i = 0; i < buffer_size; i++){
            cout << i << " ";
            if (!_Array_list[i].empty()){
                cout << _Array_list[i].front().key << " " << _Array_list[i].front().value;
            }
            cout << "\n";
        }
    }
    //Расширение хеш-таблицы
    void resize(){
        int past_buffer_size = buffer_size;
        buffer_size *= 2;
        size = 0;
        list<HashTableElement<T>> old_array_list[past_buffer_size];
        list<HashTableElement<T>> *_Array_list2 = new list<HashTableElement<T>>[buffer_size];
        for (int i = 0; i < past_buffer_size; i++) {
            old_array_list[i] = _Array_list[i];
            _Array_list[i].clear();
        }
        _Array_list = _Array_list2;
        for (int i = 0; i < past_buffer_size; i++){
            if (!old_array_list[i].empty()) {
                for (auto iter = old_array_list[i].begin(); iter != old_array_list[i].end(); iter++) {
                        this->insert((*iter).key, (*iter).value);
                    }
                }
            }
    }




};
}
#endif //TVPIS_HASHTABLE_HPP
