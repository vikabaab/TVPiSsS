//
// Created by Viktoria on 04.06.2022.
//

#ifndef TVPIS_RECURSIVEPARSER_HPP
#define TVPIS_RECURSIVEPARSER_HPP
#include "Lexer.hpp"
#include <iostream>
#include <vector>
using namespace std;


class RecursiveParser {
    std::vector<Lex> lexems;
    int counter;
public:
    RecursiveParser(std::vector<Lex> _lexems) {
        lexems = _lexems;
        counter = 0;
    }

    void Declare() {
        if (lexems[counter].state == State_Service && lexems[counter].id[0] == 'T') {
            counter++;
        }
        if (counter < lexems.size() && lexems[counter].state == State_Word) {
            counter++;
        }
        if (counter < lexems.size() && lexems[counter].lexem == "=") {
            counter++;
            Expression();
        }
    }

    void Expression() {
        Term();
        if (counter < lexems.size() && (lexems[counter].lexem == "+" || lexems[counter].lexem == "-")) {
            counter++;
            Expression();
        }
//        counter++;
    }

    void Term() {
        Factor();
        if (counter < lexems.size() && (lexems[counter].lexem == "*" || lexems[counter].lexem == "/")) {
            counter++;
            Term();
        }
    }

    void Factor() {
        if (lexems[counter].state == State_Number || lexems[counter].state == State_RealNumber || lexems[counter].state == State_Word) {
            counter++;
        }
        else if (counter < lexems.size() && lexems[counter].lexem == "(") {
            counter++;
            Expression();
            if (counter < lexems.size() && lexems[counter].lexem == ")") {
                counter++;
            }
            else throw "Нет закрывающей скобки";
        }
        else throw lexems[counter].lexem;
    }

    int parse() {
            Declare();
            if (counter < lexems.size())
                throw lexems[counter].lexem;
            return 0;
//        catch (string c)
//        {
////            std::cout << "ERROR on lexeme" << " " <<  c << std::endl;
//            return 1;
//        }

    }
};
#endif //TVPIS_RECURSIVEPARSER_HPP
