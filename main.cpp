#include "figure.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "pentagon.h"
#include "array.h"

#include <iostream>
#include <iomanip>
#include <memory>


template<Number T>
double total_area(const Array<std::shared_ptr<Figure<T>>>& arr) {
    double sum = 0.0;
    for (size_t i = 0; i < arr.size(); ++i) {
        sum += static_cast<double>(*arr[i]); 
    }
    return sum;
}


int main() {
    std::cout << std::fixed << std::setprecision(4);

    std::cout << "=== ВВОД ФИГУР === " << std::endl;
    std::cout << "0.Стоп, 1.Трапеция, 2.Ромб, 3.Пятиугольник" << std::endl;

    Array<std::shared_ptr<Figure<double>>> figures;
    int choice;
    std::cin >> choice;
    while (choice) {
        std::shared_ptr<Figure<double>> fig = nullptr;

        if (choice == 1) {
            std::cout << "cx_bottom, cy_bottom, bottom, top, h (<double>)" << std::endl;
            fig = std::make_shared<Trapezoid<double>>();
        } else if (choice == 2) {
            std::cout << "cx, cy, d1, d2 (<double>)" << std::endl;
            fig = std::make_shared<Rhombus<double>>();
        } else if (choice == 3) {
            std::cout << "cx, cy, R описанной окружности (<double>)" << std::endl;
            fig = std::make_shared<Pentagon<double>>();
        } else {
            std::cout << "Попробуйте другой тип" << std::endl;
            continue;
        }

        std::cin >> *fig;
        figures.push_back(fig);

        std::cin >> choice;
    }
    std::cout << std::endl;

    std::cout << "=== ИНФОРМАЦИЯ О ФИГУРАХ ===" << std::endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Индекс фигуры " << i << ":\n";
        std::cout << *figures[i];
        auto center = figures[i]->center();
        std::cout << "Центр: (" << center.x << ", " << center.y << ")\n";
        double area = static_cast<double>(*figures[i]);
        std::cout << "Площадь: " << area << "\n\n";
    }

    std::cout << "Общая площадь: " << total_area(figures) << "\n";

    if (figures.size() > 0) {
        std::cout << "Введите индекс фигуры для удаления (0-" << figures.size() - 1 << "): ";
        size_t index;
        std::cin >> index;
        if (index < figures.size()) {
            figures.remove(index); 
            std::cout << "Фигура удалена. Новая общая площадь: " << total_area(figures) << "\n";
        } else {
            std::cout << "Неверный индекс.\n";
        }
    }


    std::cout << "\n=== Array<Pentagon<int>> ===\n";
    Array<Pentagon<int>> pentagon_array;

    Pentagon<int> p1(1, 1, 3); 
    Pentagon<int> p2(2, 2, 4); 

    pentagon_array.push_back(std::move(p1));
    pentagon_array.push_back(std::move(p2));    


    std::cout << "Pentagon 0: ";
    pentagon_array[0].print(std::cout);
    std::cout << "Площадь: " << static_cast<double>(pentagon_array[0]) << "\n";

    std::cout << "Pentagon 1: ";
    pentagon_array[1].print(std::cout);
    std::cout << "Площадь: " << static_cast<double>(pentagon_array[1]) << "\n";

    return 0;
}