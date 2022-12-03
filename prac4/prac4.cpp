//
// Created by Влад on 03.12.2022.
//

#include "Tree.h"

void prac4()
{
    setlocale(LC_ALL, "");
    std::string value;
    //std::cout << "Введите значение: ";
    //std::cin >> value;
    Tree tree("6");
    tree.insert("1");
    tree.insert("4");
    tree.insert("5");
    tree.insert("3");
    tree.insert("7");
    tree.insert("8");
    tree.print();
    tree.inOrder();
    /*int kommand{};
    while (1)
    {
        std::cout << "Список комманд: \n" << "0 - выход из программы\n" << "1 - вставка значения\n" << "2 - вывод суммы узлов\n" << "3 - вывод глубины дерева\n" << "4 - вывод дерва\n" << "Введите комманду: ";
        std::cin >> kommand;
        switch (kommand) {
        case 0:
            return 0;
            break;
        case 1:
            std::cout << "Введите значение: ";
            std::cin >> value;
            tree.insert(value);
            break;
        case 2:
            std::cout << "Сумма значений: " << tree.sum() << std::endl;
            break;
        case 3:
            std::cout << "Глубина дерева: " << tree.depth() << std::endl;
            break;
        case 4:
            std::cout << "Дерево: ";
            tree.print();
            std::cout << std::endl;
        }
    }*/
}
