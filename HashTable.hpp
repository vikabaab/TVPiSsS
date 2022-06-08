//
// Created by Viktoria on 14.05.2022.
//

#ifndef TVPIS_HASHTABLE_HPP
#define TVPIS_HASHTABLE_HPP
using namespace std;
#include "List.hpp"
#include "Utils.hpp"
#include "include.hpp"
namespace ft {
    template<typename T>
    struct HashTableElement {
        std::string key;
        T value;
    };

    template<typename T>
    class HashTable {
    private:
        static const int default_size = 8;

        ClientMemoryBlock<List<HashTableElement<T> > > _Array_list;

        int size;
        int buffer_size;
        constexpr static const double rehash_size = 0.75;

        ::Allocator allocator_;
    public:
        HashTable() : allocator_(Allocator()) {
            _Array_list = allocator_.Allocate<List<HashTableElement<T>>>(
                    sizeof(List<HashTableElement<T>>) * default_size);

            buffer_size = default_size;
            size = 0;
            for (int i = 0; i < buffer_size; i++) {
                _Array_list.PutObjectInArray(i);
            }

        }

        int hash_function(std::string s) // Хеш-функция
        {
            const int p = 31;
            long long hash = 0, p_pow = 1;

            for (char i : s) {
                hash += int(i - '0') * p_pow;
                p_pow *= p;
            }

            return abs(hash % buffer_size);
        }

        int get_size(){
            return this->size;
        }

        //Вставка элемента в хеш-таблицу
        void insert(std::string _key, T _value) {
            size++;
            if (float(size) / float(buffer_size) >= rehash_size) {
                this->resize();
            }
            HashTableElement<T> Element;
            Element.key = _key;
            Element.value = _value;

            _Array_list.GetObject()[hash_function(_key)].push_back(Element);
        }

        //Поиск элемента по ключу
        T find(std::string _key) {
            int index = hash_function(_key);

            if (!_Array_list.GetObject()[index].empty()) {
                auto list = _Array_list.GetObject()[index];
                for (auto iter = 0; iter != list.size(); iter++) {
                    if (_key == (list[iter]).key) {
                        return (list[iter]).value;
                    }
                }

            }
            T empt;
            return empt;
//              return _Array_list.GetObject()[index].front().value;
        }

        // Удаление элемента по ключу
        void remove(std::string _key) {
            int index = hash_function(_key);
            bool isFind = false;
            int number;

            if (_Array_list.GetObject()[index].empty()) {
                return;
            }

            int i = 0;
            for (auto iter = 0; iter != _Array_list.GetObject()[index].size(); iter++) {
                if (_key == (_Array_list.GetObject()[index][iter].key)) {

                    _Array_list.GetObject()[index].erase(iter);
                    break;
                }
                i++;
            }
        }

        //Проверка
        void debugList() {
            for (int i = 0; i < buffer_size; i++) {
                std::cout << i << " ";
                if (!_Array_list.GetObject()[i].empty()) {
                    auto list = _Array_list.GetObject()[i];
                    for (auto iter = 0; iter != list.size(); iter++) {
                        std:: cout << list[iter].key << " " <<
                            list[iter].value << " ";

                    }
                }
                std::cout << "\n";
            }
        }

        //Расширение хеш-таблицы
        void resize() {
            int past_buffer_size = buffer_size;
            buffer_size *= 2;
            size = 0;

            auto pastArrayList = allocator_.template Allocate<List<HashTableElement<T>>>(
                    sizeof(List<HashTableElement<T>>) * buffer_size);
            for (int i = 0; i < buffer_size; i++) {
                pastArrayList.PutObjectInArray(i);
            }
            auto t = _Array_list;
            _Array_list = pastArrayList;
            pastArrayList = t;
            for (int i = 0; i < past_buffer_size; i++) {
                if (!pastArrayList.GetObject()[i].empty()) {
                    auto list = pastArrayList.GetObject()[i];
                    for (auto iter = 0; iter != list.size(); iter++) {
                        this->insert(list[iter].key, list[iter].value);
                    }
                }
            }
//
//            for (int i = 0; i < past_buffer_size; i++) {
//                newArrayList.GetObject()[i] = _Array_list.GetObject()[i];
//            }
//
//            _Array_list = newArrayList;
        }

    };
}
#endif //TVPIS_HASHTABLE_HPP
