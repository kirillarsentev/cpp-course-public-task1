<<<<<<< HEAD
#include <stdexcept>
=======
>>>>>>> master
#include "matrix.h"
#include <stdexcept>
using RowMatrix = Matrix::RowMatrix;

<<<<<<< HEAD
=======

>>>>>>> master
RowMatrix::RowMatrix(double* array, size_t size) {
	this->_array = array;
	this->_size = size;
}

const double& RowMatrix::operator[] (size_t j) const {
	// вычисляем позицию необходимого элемента из одномерного массива
	size_t index = this->_size + (this->_size);
	return this->_array[index];
}

// получение значения массива по первому и второму индексам [i][j]
double& RowMatrix::operator[] (size_t j) {
	// вычисляем позицию необходимого элемента из одномерного массива
	size_t index = this->_size + j;
	return this->_array[index];
}

RowMatrix::~RowMatrix() {
	this->_size = 0;
	this->_array = NULL;
}

Matrix::Matrix() {
	this->_array = NULL;
	this->_rows = 0;
	this->_cols = 0;
}

Matrix::Matrix(size_t r, size_t c) : _rows(r), _cols(c) {
	size_t size = r * c;
	this->_array = new double[size];
	for (size_t i = 0; i < size; i++) {
		this->_array[i] = 0;
	}
}

// конструктор копирования
Matrix::Matrix(const Matrix& copy_from) {
	// необходимо копировать все члены класса срабатывает при передаче объекта
	// копирование всех членов класса
	this->_rows = copy_from._rows;
	this->_cols = copy_from._cols;
	// инициализация массива
	this->_array = new double[this->_rows * this->_cols];
	// копирование массива
	for (size_t i = 0; i < this->_rows * this->_cols; i++) {
		this->_array[i] = copy_from._array[i];
	}
}

// конструктор присваивания
Matrix& Matrix::operator=(const Matrix& move_from) {
	// проверка на самоприсваивание
	if (&move_from == this) return *this;

	this->_rows = move_from._rows;
	this->_cols = move_from._cols;
	// инициализация массива
	this->_array = new double[this->_rows * this->_cols];
	// копирование массива
	for (size_t i = 0; i < this->_rows * this->_cols; i++) {
		this->_array[i] = move_from._array[i];
	}

	// возвращаем текущий объект
	return *this;
}

// получение элемента по заданным индексам [i][j]
const RowMatrix Matrix::operator[] (size_t row_num) const {
	size_t index = row_num * this->_cols;
	if (index < 0 || index >= this->_rows * this->_cols) {
		throw std::out_of_range("[Была выявлена попытка выхода за пределы массива.]");
	}

	// передаем в проекси-класс копию массива и первый индекс [i][]
	return RowMatrix(this->_array, index);
}

// получение элемента по заданным индексам [i][j]
RowMatrix Matrix::operator[] (size_t row_num) {
	size_t index = row_num * this->_cols;
	if (index < 0 || index >= this->_rows * this->_cols) {
		throw std::out_of_range("[Была выявлена попытка выхода за пределы массива.]");
	}

	// передаем в проекси-класс копию массива и первый индекс [i][]
	return RowMatrix(this->_array, index);
}

Matrix& Matrix::operator*= (double k) {
	for (size_t i = 0; i < this->_rows * this->_cols; i++) {
		this->_array[i] *= k;
	}
	return *this;
}

Matrix Matrix::operator* (double k) {
<<<<<<< HEAD
	for (size_t i = 0; i < this->_rows * this->_cols; i++) {
		this->_array[i] *= k;
	}
	return *this;
=======
	Matrix* obj = new Matrix(this->_rows, this->_cols);
	for (size_t i = 0; i < this->_rows * this->_cols; i++) {
		obj->_array[i] = this->_array[i] * k;
	}
	return *obj;
>>>>>>> master
}

bool Matrix::operator== (Matrix& matrix) {
	if (this->_rows != matrix._rows) return false;
	if (this->_cols != matrix._cols) return false;
	for (size_t i = 0; i < this->_rows * this->_cols; i++) {
		if (this->_array[i] != matrix._array[i]) return false;
	}
	return true;
}

bool Matrix::operator!= (Matrix& matrix) {
	if (this->_rows != matrix._rows) return true;
	if (this->_cols != matrix._cols) return true;
	for (size_t i = 0; i < this->_rows * this->_cols; i++) {
		if (this->_array[i] != matrix._array[i]) return true;
	}
	return false;
}

size_t Matrix::cols() const {
	return this->_cols;
}

size_t Matrix::rows() const {
	return this->_rows;
}

Matrix::~Matrix() {
	delete[] this->_array;
	this->_rows = 0;
<<<<<<< HEAD
	this->_cols = 0;
=======
	this->_cols = 0;
}
>>>>>>> master
