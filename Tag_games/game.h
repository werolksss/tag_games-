#pragma once
#include <string>

// создание и заполнение поля
void sozdaniePolya(int pole[4][4], int razmer);

// ручной ввод поля
void vvodPolya(int pole[4][4], int razmer);

// проверка корректности ввода
bool proverkaVvoda(int pole[4][4], int razmer);

// проверка решаемости
bool proverkaReshaemosti(int pole[4][4], int razmer);

// поиск пустой клетки
void naytiNol(int pole[4][4], int razmer, int& r, int& c);

// проверка победы
bool proverkaPobedy(int pole[4][4], int razmer);

// перемешивание поля
void peremeshatPole(int pole[4][4], int razmer);

// вывод поля
void pechatPolya(int pole[4][4], int razmer);

// игра компьютера
void kompyuterIgraet(int pole[4][4], int razmer);

// сохранение результатов
void sohranitRezultat(int razmer, int hody, int time, const std::string& rezhim);

// вывод результатов
void pokazatRezultaty();

// очистка результатов
void ochistitRezultaty();
