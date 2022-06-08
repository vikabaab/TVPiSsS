//
// Created by Viktoria on 04.06.2022.
//

#ifndef TVPIS_POLIZ_HPP
#define TVPIS_POLIZ_HPP
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Executor {
private:
    std::vector<Lex> result;
    std::vector<Lex> lexems;
    string type;

    Lex numbertolex(Lex lex) {
        if (int_id.count(lex.lexem) > 0) {
            lex.state = State_Number;
            lex.lexem = std::to_string(int_id.find(lex.lexem)->second);
        }
        else if (double_id.count(lex.lexem) > 0) {
            lex.state = State_RealNumber;
            lex.lexem = std::to_string(double_id.find(lex.lexem)->second);
        }
        else {
            throw "Использование неинициализованной переменной";
        }
        return lex;
    }

    void calculate() {
        std::stack<Lex> st;
        for (int i = 0; i < result.size(); i++) {
            if (result[i].state == State_Number || result[i].state == State_RealNumber || result[i].state == State_Word) {
                st.push(result[i]);
            }
            else if (result[i].state == State_Operator) {
                Lex secondlex = st.top();
                st.pop();
                if (result[i].lexem != "=") {
                    Lex firstlex = st.top();
                    st.pop();
                    Lex lex;
                    if (firstlex.state == State_Word) {
                        firstlex = numbertolex(firstlex);
                    }
                    if (secondlex.state == State_Word) {
                        secondlex = numbertolex(secondlex);
                    }
                    if (firstlex.state == State_Number && secondlex.state == State_Number) {
                        lex.state = State_Number;
                    }
                    else {
                        lex.state = State_RealNumber;
                    }
                    double first = std::stod(firstlex.lexem);
                    double second = std::stod(secondlex.lexem);
                    switch (result[i].lexem[0]) {
                        case '+':
                            lex.lexem = std::to_string(first + second);
                            st.push(lex);
                            break;
                        case '-':
                            lex.lexem = std::to_string(first - second);
                            st.push(lex);
                            break;
                        case '*':
                            lex.lexem = std::to_string(first * second);
                            st.push(lex);
                            break;
                        case '/':
                            lex.lexem = std::to_string(first / second);
                            st.push(lex);
                            break;
                    }
                }
                else {
                    if (lexems[0].id[1] == '1') {
                        int_id[st.top().lexem] = stoi(secondlex.lexem);
                    }
                    else if (lexems[0].id[1] == '2') {
                        double_id[st.top().lexem] = stod(secondlex.lexem);
                    }
                }
            }
        }
    }

    void poliz() {
        std::stack<Lex> st;
        std::map<string, int> operation_priority = { {"O3", 3}, {"O4", 3}, {"O1", 2}, {"O2", 2}, {"B1", 1}, {"A2", 0} };
        if (lexems[0].state != State_Service && lexems[0].id[0] != 'T') {
            throw "Не указан тип переменной";
        }
        for (int i = 1; i < lexems.size(); i++) {
            if (lexems[i].state == State_Number || lexems[i].state == State_RealNumber || lexems[i].state == State_Word) {
                result.push_back(lexems[i]);
            }
            else if (lexems[i].state == State_Operator) {
                if (st.empty() || operation_priority[st.top().id] < operation_priority[lexems[i].id]) {
                    st.push(lexems[i]);
                }
                else {
                    while (!st.empty() && operation_priority[st.top().id] >= operation_priority[lexems[i].id]) {
                        result.push_back(st.top());
                        st.pop();
                    }
                    st.push(lexems[i]);
                }
            }
            else if (lexems[i].id == "B1") {
                st.push(lexems[i]);
            }
            else if (lexems[i].id == "B2") {
                while (!st.empty() && st.top().lexem != "(") {
                    result.push_back(st.top());
                    st.pop();
                }
                //удаляем последнюю скобку
                st.pop();
            }
        }
        while (!st.empty()) {
            result.push_back(st.top());
            st.pop();
        }
//        for (int i = 0; i < result.size(); i++) {
//            std::cout << result[i].lexem;
//        }
    }

public:
    std::map<string, int> int_id;
    std::map<string, double> double_id;
    Executor(std::map<string, int> _int_id, std::map<string, double> _double_id) {
        int_id = _int_id;
        double_id = _double_id;
    }

    void Execute(std::vector<Lex> _lexems) {
        lexems = _lexems;
        poliz();
        calculate();
        lexems.clear();
        result.clear();
    }
};


#endif //TVPIS_POLIZ_HPP
