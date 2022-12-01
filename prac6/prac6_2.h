//
// Created by Влад on 01.12.2022.
//

#ifndef SIAOD_PRAC6_2_H
#define SIAOD_PRAC6_2_H

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <Windows.h>
#include <vector>
#include <algorithm>

void decode(std::vector<std::pair<char, std::string>>& code, std::string str) {
    std::string result = "";
    std::map< std::string, char> decode_table;
    for (int i = 0; i < code.size(); i++) {
        decode_table[code[i].second] = code[i].first;
    }
    std::string symb = "";
    for (int i = 0; i < str.length(); i++) {
        symb += str[i];
        if (decode_table.find(symb) != decode_table.end()) {
            result += decode_table.find(symb)->second;
            symb = "";
        }
    }
    std::cout << result;
}

std::string codeStr(std::vector<std::pair<char, std::string>>& code, std::string str) {
    std::string result = "";
    std::map<char, std::string> decode_table;
    for (int i = 0; i < code.size(); i++) {
        decode_table[code[i].first] = code[i].second;
    }
    for (int i = 0; i < str.length(); i++) {
        char symbol = str[i];
        if (int(symbol) >= 'А' and int(symbol) <= 'Я') {
            symbol = char(int(symbol) + 32);
        }
        result += decode_table[symbol];
    }
    return result;
}


std::vector<std::pair<char, double>> getMap(std::string str) {
    std::map<char, int> counter;
    for (int i = 0; i < str.length(); i++) { // если символа нет в контейнере
        char symbol = str[i];
        if (int(symbol) >= 'А' and int(symbol) <= 'Я') {
            symbol = char(int(symbol) + 32);
        }

        if (counter.find(symbol) == counter.end()) {
            counter[symbol] = 1;
        }
        else {
            counter[symbol]++;
        }
    }

    // создаем пустой vector пар
    std::vector<std::pair<char, double>> vec;

    for (std::map<char, int>::iterator it = counter.begin(); it != counter.end(); it++) {
        std::pair<char, double> temp = { it->first, double(it->second) / double(str.length()) };
        vec.push_back(temp);
    }

    // сортируем vector по возрастанию второго значения его пары
    // если второе значение равно, упорядочить по первому значению пары
    std::sort(vec.begin(), vec.end(),
              [](const std::pair<char, int>& l, const std::pair<char, int>& r)
              {
                  if (l.second != r.second) {
                      return l.second > r.second;
                  }

                  return l.first > r.first;
              });

    return vec;
}

std::map<char, std::string> codeSymbols(std::vector<std::pair<char, double>> vec) {
    std::map<char, std::string> code_table;
    std::string temp = "";
    temp += vec[vec.size() - 1].first;
    double p = vec[vec.size() - 1].second;
    vec.pop_back();
    while (vec.size() != 1) {
        std::pair<char, double> new_pair = vec[vec.size() - 1];
        vec.pop_back();
        char symbol_first = '0';
        char symbol_second = '1';
        if (new_pair.second >= p) {
            symbol_first = '1';
            symbol_second = '0';
        }
        code_table[new_pair.first] = symbol_first + code_table[new_pair.first];
        for (int i = 0; i < temp.length(); i++) {
            code_table[temp[i]] = symbol_second + code_table[temp[i]];
        }
        temp += new_pair.first;
        p = new_pair.second;
    }
    if (vec[0].second > p) {
        code_table[vec[0].first] = '1' + code_table[vec[0].first];
        for (int i = 0; i < temp.length(); i++) {
            code_table[temp[i]] = '0' + code_table[temp[i]];
        }
    }
    else {
        code_table[vec[0].first] = '0' + code_table[vec[0].first];
        for (int i = 0; i < temp.length(); i++) {
            code_table[temp[i]] = '1' + code_table[temp[i]];
        }
    }
    return code_table;
}



void prac6_2() {
    //setlocale(LC_ALL, "");
    std::system("chcp 1251");
    std::string str;
    std::getline(std::cin, str);
    std::vector<std::pair<char, double>> vector = getMap(str);
    std::map<char, std::string> code_table = codeSymbols(vector);
    std::map<char, std::string> ::iterator it = code_table.begin();
    int counter{};
    for (; it != code_table.end(); it++) {
        std::cout << it->first << " " << it->second << std::endl;
        counter += it->second.length();
    }
    std::cout << "Количество бит: " << counter;
}

// Тише, мыши, тише, кот на крыше
// Плыл по морю чемодан, В чемодане был диван, На диване ехал слон. Кто не верит ? выйди вон!
#endif //SIAOD_PRAC6_2_H
