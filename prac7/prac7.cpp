#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string calculate(int sum, std::vector<int>& moneys) {
    std::string temp = "";
    while (sum != 0) {
        for (int i = moneys.size() - 1; i >= 0; i--) {
            if (moneys[i] <= sum) {
                temp += std::to_string(moneys[i]) + " ";
                sum -= moneys[i];
                break;
            }
        }
    }
    return temp;
}

void prac7() {
    setlocale(LC_ALL, "");
    int sum{};
    int n{};
    std::vector<int> moneys = {1};
    std::cout << "Введите количество монет: ";
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int temp;
        std::cin >> temp;
        moneys.push_back(temp);
    }
    std::sort(moneys.begin(), moneys.end());
    std::cout << "Монеты: " << calculate(31, moneys);
}