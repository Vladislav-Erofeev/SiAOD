#include <iostream>
#include <string>
#include <stdio.h>
#include <exception>
#include <string.h>
#include <windows.h>

void add(int* &arr, int& length, int value)
{
    int* temp_array = new int[length + 1];
    for (int i = 0; i < length; i++)
    {
        temp_array[i] = arr[i];
    }
    temp_array[length] = value;
    delete[] arr;
    arr = temp_array;
    length++;
}

bool isInteger(char* str)
{
    try {
        float temp_float = std::stof(str);
        int temp_integer = std::stoi(str);
        return (temp_float - temp_integer == 0) ? (true) : (false);
    }
    catch (std::invalid_argument e)
    {
        return false;
    }
}

int separate(std::string input, int*& arr)
{
    char delimiters[] = " ";
    arr = new int[0];
    int length = 0;
    char* str = _strdup(input.c_str());
    char* temp = strtok_s(str, delimiters, &str);;
    do
    {
        if (isInteger(temp))
        {
            add(arr, length, std::stoi(temp));
        }
        temp = strtok_s(str, delimiters, &str);
    } while (temp != NULL);
    return length;
}
int main()
{
    std::string input;
    int* arr = nullptr;
    std::cout << "Enter a string: ";
    std::getline(std::cin, input);
    int length = separate(input, arr);
    std::cout << "Array: ";
    for (int i = 0; i < length; i++)
    {
        std::cout << arr[i] << " ";
    }
    // Hello
}