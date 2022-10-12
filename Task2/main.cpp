//
// Created by Влад on 12.10.2022.
//
#include <iostream>
#include <vector>

std::vector<int> suffi(std::string str)
{
    int m = str.length();
    std::vector<int> suffshift(m + 1, m);
    std::vector<int> z(m, 0);
    for (int j = 1, maxZidx = 0, maxZ = 0; j < m; ++j) {
        if (j <= maxZ) z[j] = std::min(maxZ - j + 1, z[j - maxZidx]);
        while (j + z[j] < m && str[m - 1 - z[j]] == str[m - 1 - (j + z[j])]) z[j]++;
        if (j + z[j] - 1 > maxZ) {
            maxZidx = j;
            maxZ = j + z[j] - 1;
        }
    }


    for (int j = m - 1; j > 0; j--) suffshift[m - z[j]] = j; //цикл №1
    for (int j = 1, r = 0; j <= m - 1; j++) //цикл №2
        if (j + z[j] == m)
            for (; r <= j; r++)
                if (suffshift[r] == m) suffshift[r] = j;
    return suffshift;
}

int find(std::string text, std::string str)
{
    std::vector<int> suff = suffi(str);
    for (int i = 0; i < text.length() - str.length(); i++)
    {
        int pos = str.length() - 1;
        while (str[pos] == text[pos + i])
        {
            if (pos == 0)
            {
                return i;
            }
            pos--;
        }
        i += suff[pos + 1] - 1;
    }
    return -1;
}

int task2()
{
    std::string str;
    std::string text;
    std::cout << "Enter a string: ";
    std::cin >> text;
    std::cout << "Enter a substring: ";
    std::cin >> str;
    std::cout << find(text, str);
}