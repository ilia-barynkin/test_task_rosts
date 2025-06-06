# Интерполяция на C++

Шаблонный класс `point_coll_t`, который умеет линейно интерполировать значение по заданному `x`,  
используя `std::set` для хранения отсортированных пар (x, y).

## Что делает

- Добавляешь точки через вектор аргументов и значений.
- Вызываешь `interp(xa)` — получаешь результат.
- Если точек меньше двух, или `xa` за пределами — бросает исключение.
- Есть флаг `DEBUG_TESTS`, чтобы погонять встроенные тесты.

## Зачем это всё

Доделанная линейная интерполяция через `std::set`, которую не дописал на собеседовании.

## Что поменялось

- Переделал линейный поиск в двоичный через `lower_bound`.
- Убрал лишний оператор != и переделал оператор < (чтобы не ломался контейнер STL)
- Заменил абсолютную ошибку относительной (функция almost_equal)
- Добавил тесты и ввод значений с клавиатуры.

## Как использовать

```cpp
std::vector<double> x = {1.0, 2.0, 3.0};
std::vector<double> y = {10.0, 20.0, 30.0};

point_coll_t<double, double> coll(x, y);
double res = coll.interp(2.5); // вернёт 25.0
```

## Как собрать

```sh
g++ -std=c++17 -DDEBUG_TESTS main.cpp -o interp
./interp
```

## Формат ввода (если руками)

```sh
Enter number of points:
3
Enter points as <arg val> pairs:
1 10
2 20
3 30
Enter interpolation argument xa:
1.5
Interpolated value: 15
```