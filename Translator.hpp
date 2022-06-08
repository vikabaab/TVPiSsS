//
// Created by Viktoria on 04.06.2022.
//

#ifndef TVPIS_TRANSLATOR_HPP
#define TVPIS_TRANSLATOR_HPP
#include "poliz.hpp"
#include "Lexer.hpp"
#include "RecursiveParser.hpp"
using namespace std;

class Translator{
private:
    std::map<string, int> int_id;
    std::map<string, double> double_id;
    Lexer l = Lexer();
    Executor e = Executor(int_id, double_id);

public:
    void Translate(string s, ft::HashTable<string> ht_service, ft::HashTable<string> ht_id){

        try {
            vector <Lex> lexems = l.lex_analyze(s, ht_service, ht_id);
            l.debug_lexems_states(ht_service, ht_id);
            RecursiveParser rp = RecursiveParser(lexems);
            if (rp.parse() == 0) {
                e.Execute(lexems);
            }
        }
        catch (const char* c) {
            cout << c;
            return;
        }
        findId("S");
    }

    void findId(string s){
        auto searchd = e.double_id.find(s);
        auto searchi = e.int_id.find(s);
        if (searchd != e.double_id.end()) {
            std::cout << endl << "Found " << searchd->first << " " << searchd->second << '\n';
        }
        else if (searchi != e.int_id.end()) {
            std::cout << endl << "Found " << searchi->first << " " << searchi->second << '\n';
        }
        else {
            std::cout << endl << "Not found\n";
        }
    }
};

#endif //TVPIS_TRANSLATOR_HPP
