#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "game.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(0));

    int menu;

    // главное меню
    while (true)
    {
        system("cls");

        cout << "1 - Новая игра\n";
        cout << "2 - Показать прошлые результаты\n";
        cout << "3 - Очистить результаты\n";
        cout << "0 - Выход\n";
        cin >> menu;

        switch (menu)
        {
        case 0:
            // выход из программы
            return 0;

        case 1:
            // начало новой игры
            break;

        case 2:
            // показ прошлых результатов
            pokazatRezultaty();
            continue;

        case 3:
            // очистка результатов
            ochistitRezultaty();
            continue;

        default:
            cout << "Неверный выбор!\n";
            system("pause");
            continue;
        }

        // если выбрана новая игра — выходим из меню
        break;
    }

    int vibor;

    // выбор размера поля
    cout << "\nВыберите размер поля:\n";
    cout << "1 - 3х3\n";
    cout << "2 - 4х4\n";
    cin >> vibor;

    int razmer;

    switch (vibor)
    {
    case 1:
        razmer = 3;
        break;
    case 2:
        razmer = 4;
        break;
    default:
        cout << "Неверный выбор!\n";
        return 0;
    }

    // игровое поле
    int pole[4][4];

    // создание и заполнение поля
    sozdaniePolya(pole, razmer);

    int rezhim;

    // выбор режима игры
    cout << "\nВыберите режим игры:\n";
    cout << "1 - играет человек\n";
    cout << "2 - играет компьютер\n";
    cin >> rezhim;

    switch (rezhim)
    {
    case 1:
        // играет человек
        break;

    case 2:
        // играет компьютер
        break;

    default:
        cout << "Неверный режим!\n";
        return 0;
    }

    int start;

    // выбор начального размещения
    cout << "\nНачальное размещение:\n";
    cout << "1 - ввод вручную\n";
    cout << "2 - перемешать автоматически\n";
    cin >> start;

    switch (start)
    {
    case 1:
        // ручной ввод поля
        vvodPolya(pole, razmer);
        break;

    case 2:
        // автоматическое перемешивание
        peremeshatPole(pole, razmer);
        break;

    default:
        cout << "Неверный выбор!\n";
        return 0;
    }

    // если выбран режим компьютера
    if (rezhim == 2)
    {
        // компьютер играет сам и сохраняет результат
        kompyuterIgraet(pole, razmer);
        return 0;
    }

    int hod = 0; //счётчик ходов игрока
    time_t startTime = time(0); //старт таймера

    // основной игровой цикл
    while (true)
    {
        system("cls");

        // вывод поля
        pechatPolya(pole, razmer);

        // проверка победы
        if (proverkaPobedy(pole, razmer))
        {
            time_t endTime = time(0);
            int seconds = difftime(endTime, startTime);

            cout << "\nВы собрали пятнашки! \n";
            cout << "Количество ходов: " << hod << endl;
            cout << "Время: " << seconds << " сек\n";

            // сохранение результата игрока
            sohranitRezultat(razmer, hod, seconds, "игрок");
            break;
        }

        int x, y;

        // ввод координат фишки
        cout << "\nВведите координаты фишки (строка столбец, нумерация с 1)\n";
        cout << "Для выхода введите 0 0: ";
        cin >> x >> y;

        // выход из игры
        if (x == 0 && y == 0)
        {
            cout << "Выход из игры.\n";
            return 0;
        }

        // переход к индексам массива
        x--;
        y--;

        int r, c;

        // поиск пустой клетки
        naytiNol(pole, razmer, r, c);

        // проверка корректности хода
        if (x >= 0 && x < razmer &&
            y >= 0 && y < razmer &&
            pole[x][y] != 0 &&
            ((abs(x - r) == 1 && y == c) ||// выше ниже
                (abs(y - c) == 1 && x == r)))//левее правее
        {
            // обмен фишки с пустой клеткой
            swap(pole[x][y], pole[r][c]);
            hod++;
        }
        else
        {
            cout << "Ход невозможен!\n";
            system("pause");
        }
    }

    return 0;
}
