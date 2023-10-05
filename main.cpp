#include <iostream>
#include <clocale>
#include <ctime>
#include <cstdlib>

enum Cell
{
    None    = 0,
    Cross   = 1,
    Circle  = 2,
};

Cell field[9];

void printField()
{
    for (size_t i = 0; i < 9; i++)
    {
        char c;
        switch (field[i])
        {
            case Cross:
                c = 'X';
                break;
            case Circle:
                c = 'O';
                break;
            case None:
                c = ' ';
                break;
            default:
                c = '-';
                break;
        }
        std::cout
            << '\t'
            << i
            << '['
            << c
            << ']';
        
        if ( i % 3 == 2)
            std::cout << '\n';
    }
    
}

bool check()
{
    for (size_t i = 0; i < 3; i++)
    {
        if (
            field[i*3+0] != None &&
            field[i*3+0] == field[i*3+1] &&
            field[i*3+1] == field[i*3+2]
        )
            return true;
    }
    for (size_t i = 0; i < 3; i++)
    {
        if (
            field[i+0] != None &&
            field[i+0] == field[i+3] &&
            field[i+3] == field[i+6]
        )
            return true;
    }
    if (
        field[0] != None &&
        field[0] == field[4] &&
        field[4] == field[8]
    )
        return true;
    if (
        field[2] != None &&
        field[2] == field[4] &&
        field[4] == field[6]
    )
        return true;
    return false;
}

bool isFull()
{
    for (size_t i = 0; i < 9; i++)
    {
        if (field[i] == None)
            return false;
    }
    return true;
    
}
int main(int, char**)
{
    setlocale(LC_ALL, "ru_RU.UTF-8\0");
    time_t seed;
    time((time_t * const)&seed);
    srand((long)seed);
    std::cout
        << "Seed: "
        << seed
        << '\n';

    for (size_t i = 0; i < 9; i++)
        field[i] = None;
    int pos = -1;
    Cell cur = rand() % 2 == 0 ? Cross : Circle;

    while (!check() && !isFull())
    {
        printField();
        std::cout
            <<  "Ход игрока: " 
            << (
                cur == Cross ? "Крестик" :
                cur == Circle ? "Нолик" :
                    "Ошибка"
            )
            << '\n';
        while ( pos < 0 || pos >= 9 || field[pos] != None )
        {
            std::cout << "Введите номер ячейки для хода: ";
            std::cin >> pos;
        }
        field[pos] = cur;
        cur = cur == Cross ? Circle : Cross;
    }
    cur = cur == Cross ? Circle : Cross;
    
    printField();
    if (isFull())
    {
        std::cout << "Ничья\n";
        return 0;
    }

    std::cout
        << "Выиграл игрок: "
        <<(
            cur == Cross ? "Крестик" :
            cur == Circle ? "Нолик" :
                "Ошибка"
        )
        << '\n';
}
