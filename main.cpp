#include <iostream>
#include <exception>
#include "List.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "Deque.hpp"
#include "HashTable.hpp"
#include "Lexer.hpp"
#include <fstream>
#include <filesystem>
#include <sstream>
#include "poliz.hpp"
#include "Translator.hpp"
#include "Reader.hpp"

using namespace std;
std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
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
//    ft::HashTable<int> ht = ft::HashTable<int>();
//    string key = "клюшка";
//    int value = 5;
//    ht.insert(key, value);
//    ht.insert("1", 1);
//    ht.insert("3",67348);
//    ht.insert("tema",234);
//    cout << "\n\nколлизии\n";
//    ht.debugList();
//
//    cout<<"\n\nfind: " << ht.find("tema");
//
//    ht.insert("Vika",564);
//    ht.insert("Sergey",782);
//    ht.insert("Kolya",3627);
//    ht.insert("Kirill",674332);
//    cout << "\n\nresize\n";
//    ht.debugList();
//
//    cout << "\n\nfind after resize: " << ht.find("tema");
//
//    cout << "\n\nremove\n";
//    ht.remove("tema");
//    ht.debugList();

//    lex_analyze("a 1  12abc = 5");
    //lex_analyze("a1==5");
    std::filesystem::path cwd = std::filesystem::current_path();

    ft::HashTable<string> ht_service = ft::HashTable<string>();
    ft::HashTable<string> ht_id = ft::HashTable<string>();
    std::string line;
    std::ifstream in(cwd.string() + "/ServiceTable.txt");

    if (in.is_open()){

        while (getline(in,line)){

            auto splitted = split(line,' ');
            ht_service.insert(splitted[0],splitted[1]);
        }
    }
    in.close();
    Reader r;
    r.reader("/input.txt",ht_service,ht_id);
    return 0;
    
}