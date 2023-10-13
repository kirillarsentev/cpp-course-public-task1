#include "matrix.h"
#include "iostream"

// вывод матрицы на экран
void displayMatrix(Matrix m, const size_t rows, const size_t cols, std::string message)
{
    std::cout << message;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


int main()
{
    // кириллица консоли
    setlocale(LC_ALL, "RU");

    try
    {
        // размерность матрицы
        const size_t rows = 5;
        const size_t cols = 3;

        // создание объекта класса с передачей параметров
        Matrix m(rows, cols);

        // заполнение матрицы
        double value = 1;
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                m[i][j] = value++;
                std::cout << m[i][j] << " ";
            }
            std::cout << std::endl;

        }
        std::cout << std::endl;


        Matrix m2(rows, cols);
        m *= 3; // умножение на число
        m2 = m * 3; // умножение на число
        m2[1][0] = 1;

        Matrix m1(rows, cols);
        m1 = m;


        // вывод матрицы
        displayMatrix(m, rows, cols, "Matrix m:\n");
        // вывод матрицы
        displayMatrix(m2, rows, cols, "Matrix m2:\n");
        // вывод матрицы
        displayMatrix(m1, rows, cols, "Matrix m1:\n");


        if (m1 == m) std::cout << "m1 == m\n";
        else std::cout << "m1 != m\n";

        if (m != m2) std::cout << "m != m2\n";
        else std::cout << "m == m2\n";
    }

    // перехват исключений
    catch (const std::exception& exp)
    {
        std::cout << exp.what() << std::endl;
    }

    return 0;
}
