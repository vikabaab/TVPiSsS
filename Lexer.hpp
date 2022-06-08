//
// Created by Viktoria on 26.05.2022.
//

#ifndef TVPIS_LEXER_HPP
#define TVPIS_LEXER_HPP
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include "List.hpp"
#include "HashTable.hpp"
#include <typeinfo>
using namespace std;

enum States
{
    State_Start, // 0
    State_Number, // целое число 1
    State_RealNumber, // вещественное число 2
    State_Word, // переменная 3
    State_Operator, // операторы =+-*/<> 4
    State_Equality, // операторы == += -= *= итд 5
    State_Bracket, // скобки 6
    State_Service, // служебное слово 7
    State_Er // ошибка 8
};


bool isoperator(char symb) {
    string operators = "=+-*/<>";
    for (int i = 0; i < operators.size(); i++) {
        if (symb == operators[i]) {
            return true;
        }
    }
    return false;
}

bool isbracket(char symb) {
    if (symb == '(' || symb == ')') {
        return true;
    }
    return false;
}

struct Lex{
    string lexem;
    States state;
    string id;
};

class Lexer{
private:
    vector <Lex> lexems;
    string current_lexem;
    int num_of_word = 0;
public:
    void add_lexems_states(States State, char current, ft::HashTable<string> ht_service, ft::HashTable<string> ht_id) {
        current_lexem.pop_back();
        Lex lex = Lex();
        lex.lexem = current_lexem;
        if (State == State_Word){
            if (ht_service.find(current_lexem).size() > 0){
                lex.state = State_Service;
                lex.id = ht_service.find(current_lexem);
            }
            else {
                lex.state = State_Word;
                if (ht_id.find(current_lexem).size() == 0){
                    ht_id.insert(current_lexem, current_lexem + ':' + to_string(num_of_word));
                    num_of_word++;
                }
            }
        }
        else {
            if (ht_service.find(current_lexem).size() > 0){
                lex.id = ht_service.find(current_lexem);
            }
            lex.state = State;
        }
        lexems.push_back(lex);
        current_lexem.clear();
        if (!std::isspace(current) && current != '\n') {
            current_lexem.push_back(current);
        }
    }
    vector <Lex> lex_analyze(string s, ft::HashTable<string> ht_service, ft::HashTable<string> ht_id) {
        lexems.clear();
        const size_t length = s.length();
        States state = State_Start;
        for (size_t i = 0; i != length; ++i) {
            char current = s[i];
            current_lexem.push_back(current);
            switch (state) {
                case State_Start:
                    if (std::isdigit(current)) {
                        state = State_Number;
                    }
                    else if (std::isalpha(current)) {
                        state = State_Word;
                    }
                    else if (std::isspace(current) || current == '\n') {
                        state = State_Start;
                        current_lexem.pop_back();
                    }
                    else if (isoperator(current)) {
                        state = State_Operator;
                    }
                    else if (isbracket(current)) {
                        state = State_Bracket;
                    }
                    else {
                        state = State_Er;
                    }
                    break;

                case State_Word:
                    if (std::isdigit(current) || std::isalpha(current)) {
                        state = State_Word;
                    }
                    else if (std::isspace(current)) {
                        add_lexems_states(State_Word, current, ht_service, ht_id);
                        state = State_Start;
                    }
                    else if (isoperator(current)) {
                        add_lexems_states(State_Word, current, ht_service, ht_id);
                        state = State_Operator;
                    }
                    else if (isbracket(current)) {
                        add_lexems_states(State_Word, current, ht_service, ht_id);
                        state = State_Bracket;
                    }
                    else {
                        state = State_Er;
                    }
                    break;

                case State_Number:
                    if (std::isdigit(current)) {
                        state = State_Number;
                    }
                    else if (std::isspace((current)) || current == '\n') {
                        add_lexems_states(State_Number, current, ht_service, ht_id);
                        state = State_Start;
                    }
                    else if (isoperator(current)) {
                        add_lexems_states(State_Number, current, ht_service, ht_id);
                        state = State_Operator;
                    }
                    else if (isbracket(current)) {
                        add_lexems_states(State_Number, current, ht_service, ht_id);
                        state = State_Bracket;
                    }
                    else if (current == '.') {
                        state = State_RealNumber;
                    }
                    else {
                        state = State_Er;
                    }
                    break;

                case State_RealNumber:
                    if (std::isdigit(current)) {
                        state = State_RealNumber;
                    }
                    else if (std::isspace(current) || current == '\n') {
                        add_lexems_states(State_RealNumber, current, ht_service, ht_id);
                        state = State_Start;
                    }
                    else if (isoperator(current)) {
                        add_lexems_states(State_RealNumber, current, ht_service, ht_id);
                        state = State_Operator;
                    }
                    else if (isbracket(current)) {
                        add_lexems_states(State_RealNumber, current, ht_service, ht_id);
                        state = State_Bracket;
                    }
                    else {
                        state = State_Er;
                    }
                    break;

                case State_Er:
                    throw "Лексическая ошибка";
                    if (std::isspace(current) || current == '\n') {
                        state = State_Start;
                        add_lexems_states(State_Er, current, ht_service, ht_id);
                    }
                    else if (isoperator(current)) {
                        add_lexems_states(State_Er, current, ht_service, ht_id);
                        state = State_Operator;
                    }
                    else if (isbracket(current)) {
                        add_lexems_states(State_Er, current, ht_service, ht_id);
                        state = State_Bracket;
                    }
                    else {
                        state = State_Er;
                    }
                    break;

                case State_Operator:
                    if (current == '=') {
                        state = State_Equality;
                    }
                    else {
                        add_lexems_states(State_Operator, current, ht_service, ht_id);
                        if (std::isdigit(current)) {
                            state = State_Number;
                        }
                        else if (std::isalpha(current)) {
                            state = State_Word;
                        }
                        else if (isbracket(current)) {
                            state = State_Bracket;
                        }
                        else if (isspace(current)) {
                            state = State_Start;
                        }
                        else state = State_Er;
                    }
                    break;

                case State_Equality:
                    add_lexems_states(State_Equality, current, ht_service, ht_id);
                    if (std::isdigit(current)) {
                        state = State_Number;
                    }
                    else if (std::isalpha(current)) {
                        state = State_Word;
                    }
                    else if (isbracket(current)) {
                        state = State_Bracket;
                    }
                    else state = State_Start;
                    break;

                case State_Bracket:
                    add_lexems_states(State_Bracket, current, ht_service, ht_id);
                    if (std::isalpha(current)) {
                        state = State_Word;
                    }
                    else if (std::isdigit(current)){
                        state = State_Number;
                    }
                    else if (isoperator(current)){
                        state = State_Operator;
                    }
                    else if (isbracket(current)) {
                        state = State_Bracket;
                    }
                    else state = State_Start;
                    break;
            }
            if (i == length - 1 && current != ' ') {
                Lex lex = Lex();
                lex.state = state;
                lex.lexem = current_lexem;
                current_lexem.clear();
                lexems.push_back(lex);
            }
        }
        return lexems;
    }

    void debug_lexems_states(ft::HashTable<string> ht_service, ft::HashTable<string> ht_id) {
        for (int i = 0; i < lexems.size(); i++) {
            cout << lexems[i].lexem << " " << lexems[i].state << " " << lexems[i].id << endl;
            //ht_service.find(lexems1[i].lexem) << ht_id.find(lexems1[i].lexem) << endl;
        }
    }
};




#endif //TVPIS_LEXER_HPP
