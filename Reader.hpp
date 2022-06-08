//
// Created by Viktoria on 04.06.2022.
//

#ifndef TVPIS_READER_HPP
#define TVPIS_READER_HPP
using namespace std;
#include <iostream>
#include <exception>
#include <filesystem>
#include <sstream>
#include "Translator.hpp"
#include "HashTable.hpp"

class Reader{
public:
    void reader(string address, ft::HashTable<string> ht_service, ft::HashTable<string> ht_id){
        Translator t;
        std::filesystem::path cwd = std::filesystem::current_path();
        std::string line;
        std::ifstream in(cwd.string() + address);
        if (in.is_open()){

            while (getline(in,line)){

                t.Translate(line,ht_service,ht_id);

            }
        }
        in.close();
//        t.findId("S");
//        t.findId("R");
    }
};
#endif //TVPIS_READER_HPP
