#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "game.h"

using namespace std;

// создание и заполнение поля
void sozdaniePolya(int pole[4][4], int razmer)
{
    int chislo = 1;

    for (int i = 0; i < razmer; i++)
        for (int j = 0; j < razmer; j++)
            pole[i][j] = chislo++;

    // последняя клетка пустая
    pole[razmer - 1][razmer - 1] = 0;
}

// проверка корректности ручного ввода 
bool proverkaVvoda(int pole[4][4], int razmer)
{
    bool used[16] = { false };
    int max = razmer * razmer - 1;
    int kolvoNuley = 0;

    for (int i = 0; i < razmer; i++)
    {
        for (int j = 0; j < razmer; j++)
        {
            int x = pole[i][j];

            // проверка диапазона
            if (x < 0 || x > max)
                return false;

            // подсчёт нулей
            if (x == 0)
                kolvoNuley++;

            // проверка повторов
            if (used[x])
                return false;

            used[x] = true;
        }
    }

    // должен быть ровно один ноль
    if (kolvoNuley != 1)
        return false;

    // проверка решаемости
    if (!proverkaReshaemosti(pole, razmer))
        return false;

    return true;
}

/// проверка решаемости
bool proverkaReshaemosti(int pole[4][4], int razmer)
{
    int mas[16];    // временный массив для чисел (без нуля)
    int k = 0;

    // копируем числа в массив (без нуля)
    for (int i = 0; i < razmer; i++)
        for (int j = 0; j < razmer; j++)
            if (pole[i][j] != 0)
                mas[k++] = pole[i][j];

    int inv = 0;

    // считаем инверсии
    for (int i = 0; i < k; i++)
        for (int j = i + 1; j < k; j++)
            if (mas[i] > mas[j])
                inv++;

    //четное число инверсий-решаемо
    if (razmer == 3)
        return inv % 2 == 0;

    //учитываем положение нуля
    int r, c;
    naytiNol(pole, razmer, r, c);
    int fromBottom = razmer - r;  // строка нуля снизу

    // для 4x4
    if (fromBottom % 2 == 0)      // ноль на четной строке снизу
        return inv % 2 == 1;      // нужны нечетные инверсии
    else                          // нуль на нечетной строке снизу
        return inv % 2 == 0;      // нужны четные инверсии
}

// ручной ввод поля пользователем
void vvodPolya(int pole[4][4], int razmer)
{
    do
    {
        cout << "Введите поле(0-пустая ячейка):\n";

        for (int i = 0; i < razmer; i++)
            for (int j = 0; j < razmer; j++)
                cin >> pole[i][j];

        if (!proverkaVvoda(pole, razmer))
            cout << "Ошибка ввода или поле нерешаемо! Повторите ввод.\n";

    } while (!proverkaVvoda(pole, razmer));
}

// поиск координат пустой клетки (0)
void naytiNol(int pole[4][4], int razmer, int& r, int& c)
{
    for (int i = 0; i < razmer; i++)
        for (int j = 0; j < razmer; j++)
            if (pole[i][j] == 0)
            {
                r = i;
                c = j;
                return;
            }
}

// проверка, собрана ли игра
bool proverkaPobedy(int pole[4][4], int razmer)
{
    int nado = 1;

    for (int i = 0; i < razmer; i++)
        for (int j = 0; j < razmer; j++)
        {
            // последняя клетка должна быть пустой
            if (i == razmer - 1 && j == razmer - 1)
                return pole[i][j] == 0;

            // проверка правильного порядка чисел
            if (pole[i][j] != nado)
                return false;

            nado++;
        }

    return true;
}

// перемешивание поля случайными корректными ходами
void peremeshatPole(int pole[4][4], int razmer)
{
    int r = razmer - 1;
    int c = razmer - 1; 

    // делаем много случайных ходов
    for (int k = 0; k < 200; k++)
    {
        int d = rand() % 4;

        int nr = r;  
        int nc = c; 

        if (d == 0) nr--; 
        if (d == 1) nr++; 
        if (d == 2) nc--; 
        if (d == 3) nc++;  
        
		if (nr >= 0 && nr < razmer && nc >= 0 && nc < razmer) //проверка границ
        {
            swap(pole[r][c], pole[nr][nc]);
            r = nr;
            c = nc;
        }
    }
}

// вывод игрового поля в консоль
void pechatPolya(int pole[4][4], int razmer)
{
    cout << "\n";

    for (int i = 0; i < razmer; i++)
    {
        for (int k = 0; k < razmer; k++)
            cout << "+----";
        cout << "+\n";

        for (int j = 0; j < razmer; j++)
        {
            cout << "|";

            if (pole[i][j] == 0)
                cout << "    ";
            else if (pole[i][j] < 10)
                cout << "  " << pole[i][j] << " ";
            else
                cout << " " << pole[i][j] << " ";
        }
        cout << "|\n";
    }

    for (int k = 0; k < razmer; k++)
        cout << "+----";
    cout << "+\n";
}

// автоматическая игра компьютера
void kompyuterIgraet(int pole[4][4], int razmer)
{
    int hod = 0;
    time_t startTime = time(0);

    // компьютер делает случайные допустимые ходы
    while (!proverkaPobedy(pole, razmer))
    {
        if (hod > 100000)
        {
            cout << "Компьютер не смог собрать поле\n";
            break;
        }

        int r, c;
        naytiNol(pole, razmer, r, c);

        int d = rand() % 4;
        int nr = r;
        int nc = c;

        if (d == 0) nr--;
        if (d == 1) nr++;
        if (d == 2) nc--;
        if (d == 3) nc++;

        if (nr >= 0 && nr < razmer &&
            nc >= 0 && nc < razmer)
        {
            swap(pole[r][c], pole[nr][nc]);
            hod++;
        }
    }

    time_t endTime = time(0);
    int seconds = difftime(endTime, startTime);

    system("cls");

    cout << "Компьютер собрал пятнашки!\n";
    pechatPolya(pole, razmer);
    cout << "Количество ходов: " << hod << endl;
    cout << "Время: " << seconds << " сек\n";

    // сохранение результата компьютера
    sohranitRezultat(razmer, hod, seconds, "компьютер");
}

// сохранение результата в файл
void sohranitRezultat(int razmer, int hody, int time, const string& rezhim)
{
    ofstream file("results.txt", ios::app);

    if (!file.is_open())
        return;

    file << "Поле: " << razmer << "x" << razmer
        << " | Режим: " << rezhim
        << " | Ходов: " << hody
        << " | Время: " << time << " сек"
        << endl;

    file.close();
}

// вывод сохранённых результатов
void pokazatRezultaty()
{
    ifstream file("results.txt");

    if (!file.is_open())
    {
        cout << "Результатов пока нет\n";
        system("pause");
        return;
    }

    string line;

    cout << "\n---Прошлые результаты---\n";

    while (getline(file, line))
        cout << line << endl;

    file.close();
    system("pause");
}

// очистка файла с результатами
void ochistitRezultaty()
{
    // перезаписываем файл
    ofstream file("results.txt");

    if (file.is_open())
        cout << "Результаты очищены.\n";

    file.close();
    system("pause");
}
