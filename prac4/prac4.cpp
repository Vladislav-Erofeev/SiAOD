//
// Created by ���� on 03.12.2022.
//

#include "Tree.h"

void prac4()
{
    setlocale(LC_ALL, "");
    std::string value;
    //std::cout << "������ ���祭��: ";
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
        std::cout << "���᮪ �������: \n" << "0 - ��室 �� �ணࠬ��\n" << "1 - ��⠢�� ���祭��\n" << "2 - �뢮� �㬬� 㧫��\n" << "3 - �뢮� ��㡨�� ��ॢ�\n" << "4 - �뢮� ��ࢠ\n" << "������ ��������: ";
        std::cin >> kommand;
        switch (kommand) {
        case 0:
            return 0;
            break;
        case 1:
            std::cout << "������ ���祭��: ";
            std::cin >> value;
            tree.insert(value);
            break;
        case 2:
            std::cout << "�㬬� ���祭��: " << tree.sum() << std::endl;
            break;
        case 3:
            std::cout << "��㡨�� ��ॢ�: " << tree.depth() << std::endl;
            break;
        case 4:
            std::cout << "��ॢ�: ";
            tree.print();
            std::cout << std::endl;
        }
    }*/
}
