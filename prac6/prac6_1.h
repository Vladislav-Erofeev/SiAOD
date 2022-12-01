//
// Created by Влад on 01.12.2022.
//

#ifndef SIAOD_PRAC6_1_H
#define SIAOD_PRAC6_1_H

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <Windows.h>
#include <vector>
#include <algorithm>


std::vector<std::pair<char, int>> getMap(std::string str) {
    std::map<char, int> counter;
    for (int i = 0; i < str.length(); i++) { // если символа нет в контейнере
        char symbol = str[i];
        if (int(symbol) >= 'А' and int(symbol) <= 'Я') {
            symbol = char(int(symbol) + 32);
        }

        if (counter.find(symbol) == counter.end()) {
            counter[symbol] =  1;
        }
        else {
            counter[symbol]++;
        }
    }

    // создаем пустой vector пар
    std::vector<std::pair<char, int>> vec;

    for (std::map<char, int>::iterator it = counter.begin(); it != counter.end(); it++) {
        std::pair<char, int> temp = { it->first, it->second };
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

int separate(std::vector<std::pair<char, int>> vector, int start, int end) {
    int count_of_symbols{};
    for (int i = start; i < end; i++)
        count_of_symbols += vector[i].second;
    int index{};
    int mindif = count_of_symbols;
    for (int i = 1; i < end-start; i++) {
        int sum{};
        for (size_t j = start; j < i+start; j++)
        {
            sum += vector[j].second;
        }
        if (sum == count_of_symbols / 2) {
            return i;
        }

        if (abs(sum - (count_of_symbols-sum)) < mindif) {
            index = i;
            mindif = abs(sum - (count_of_symbols - sum));
        }
    }
    return index;
}

void codeArr(std::vector<std::pair<char, int>> vector, std::vector<std::pair<char, std::string>>& code, int start, int end) {
    if (start > end) {
        std::cout << "Error: " << start << "  " << end;
        exit(0);
    }
    if (start + 1 == end) {
        return;
    }
    int ind = separate(vector, start, end);
    for (int i = start; i < start + ind; i++) {
        code[i].second = code[i].second + '0';
    }
    for (int i = start + ind; i < end; i++) {
        code[i].second = code[i].second + '1';
    }
    codeArr(vector, code, start, start + ind);
    codeArr(vector, code, start + ind, end);
}

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

void prac6_1() {
    //setlocale(LC_ALL, "");
    std::system("chcp 1251");
    std::string str;
    std::getline(std::cin, str);
    std::vector<std::pair<char, int>> vector = getMap(str);
    std::vector<std::pair<char, std::string>> code;
    for(int i = 0; i < vector.size(); i++) {
        std::pair<char, std::string> temp = { vector[i].first, ""};
        code.push_back(temp);
    }
    codeArr(vector, code, 0, vector.size());
    //for (int i = 0; i < code.size(); i++) {
    //	std::cout << code[i].first << "  " << code[i].second << std::endl;
    //}

    int count_of_bits{};
    std::string str_code = codeStr(code, str);
    for (int i = 0; i < code.size(); i++) {
        count_of_bits += code[i].second.length() * vector[i].second;
    }
    std::cout << str_code << std::endl;
    decode(code, str_code);
    std::cout << "\nКоличество бит: " << count_of_bits;
}

// Тише, мыши, тише, кот на крыше
// Плыл по морю чемодан, В чемодане был диван, На диване ехал слон. Кто не верит ? выйди вон!

#endif //SIAOD_PRAC6_1_H
