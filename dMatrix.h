#include"include.hpp"


template <typename T>
class Matrix {
private:
    class MatrixRow {
    public:
        MatrixRow(T** in_matrix_arr, size_t columns) : columns(columns), matrix_arr(in_matrix_arr) {}
        T* operator[] (size_t index) {
            if (index < 0 || columns < index) {
                throw std::invalid_argument("Invalid index (MatrixRow)");
            }
            else {
                return matrix_arr[index];
            }
        }
    private:
        T** matrix_arr;
        size_t columns;
    };
public:

    Matrix(std::vector<std::vector<T>> arr_massive);

    Matrix(T** arr_massive,size_t size_rows,size_t size_columns);

    Matrix(bool identity_matrix, size_t rows, size_t columns);

    Matrix(size_t rows, size_t columns,T value);

    Matrix(const Matrix& matrix);

    Matrix(size_t rows, size_t columns);

    Matrix();

    ~Matrix();

    Matrix operator + (const Matrix& matrix) const;

    Matrix operator - (const Matrix& matrix) const;

    Matrix operator - ()const;

    Matrix operator * (const Matrix& matrix) const;

    Matrix operator* (double multi_const) const;

    bool operator == (const Matrix& matrix) const;

    Matrix& operator = (const Matrix& matrix);

    Matrix TransposeMatrix() const;

    Matrix InverseMatrix() const;

    T* operator[](size_t index);

    double determinant() const;

    void Print() const;

    size_t getRows() const{return rows;} size_t getColumns() const {return columns; }
private:

    size_t columns;

    size_t rows;

    T** matrix_arr;

    void CreateMatrixArr(size_t rows, size_t columns);

    size_t InvalidValueArray(const std::vector<std::vector<T>>& arr);

    int coeff(size_t i, size_t j) const {if((i+j)%2 == 0) return 1; else return -1;}
};



class Error;
//Constructors Matrix
template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> arr_massive)
{
    size_t rowsSize = arr_massive.size();
    size_t columnsSize = InvalidValueArray(arr_massive);
    this->rows = rowsSize; this->columns = columnsSize;
    CreateMatrixArr(rows, columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            matrix_arr[i][j] = arr_massive[i][j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(T** arr_massive, size_t size_rows, size_t size_columns):rows(size_rows), columns(size_columns){
    CreateMatrixArr(size_rows, size_columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            matrix_arr[i][j] = arr_massive[i][j];
        }
    }
}

template <typename T>
Matrix<T>::Matrix(bool identity_matrix, size_t rows, size_t columns) :rows(rows), columns(rows) {
    CreateMatrixArr(this->rows, this->columns);
    if (identity_matrix == true) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                if (i == j) {
                    matrix_arr[i][j] = 1;
                }
                else {
                    matrix_arr[i][j] = 0;
                }
            }
        }
    }
    else {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                std::cout << i << " " << j << std::endl;
                std::cin >> matrix_arr[i][j];
            }
        }
    }
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) :rows(rows), columns(columns)
{
    CreateMatrixArr(this->rows, this->columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            matrix_arr[i][j] = 0;
        }
    }
}


template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns,T value) :rows(rows), columns(columns)
{
    CreateMatrixArr(this->rows, this->columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            matrix_arr[i][j] = value;
        }
    }
}

template <typename T>
Matrix<T>::Matrix(Matrix const& matrix) :rows(matrix.rows), columns(matrix.columns)
{
    CreateMatrixArr(rows, columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            this->matrix_arr[i][j] = matrix.matrix_arr[i][j];
        }
    }
}

template <typename T>
Matrix<T>::Matrix() :rows(3), columns(3)
{
    CreateMatrixArr(this->rows, this->columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            if (i == j) {
                matrix_arr[i][j] = 1;
            }
            else {
                matrix_arr[i][j] = 0;
            }
        }
    }
}

template <typename T>
Matrix<T>::~Matrix<T>() {
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix_arr[i];
    }
    delete[] matrix_arr;
}


template <typename T>
bool Matrix<T>::operator==(const Matrix& matrix) const
{
    if(this->columns != matrix.columns || this->rows != matrix.rows){
        return false;
    }
    else{
        bool result;
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.columns; ++j) {
                if (this->matrix_arr[i][j] != matrix.matrix_arr[i][j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

//Operators Matrix
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& matrix) const
{
    if (matrix.columns != this->columns && matrix.rows != this->rows) {
        throw std::invalid_argument("Invalid size of matrix (operator+)");
    }
    else {
        Matrix result(matrix.rows, matrix.columns);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                result.matrix_arr[i][j] = this->matrix_arr[i][j] + matrix.matrix_arr[i][j];
            }
        }
        return result;
    }
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& matrix) const
{
    if (matrix.columns != this->columns && matrix.rows != this->rows) {
        throw std::invalid_argument("Invalid size of matrix(operator-)");
    }
    else {
        Matrix result(matrix.rows, matrix.columns);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                result.matrix_arr[i][j] = this->matrix_arr[i][j] - matrix.matrix_arr[i][j];
            }
        }
        return result;
    }
}

template <typename T>
Matrix<T> Matrix<T>::operator-() const
{
    Matrix result(this->rows, this->columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            result.matrix_arr[i][j] = (this->matrix_arr[i][j]) * (-1);
        }
    }
    return result;
}


template <typename T>
Matrix<T> Matrix<T>::operator*(double multip_const) const{
    Matrix result(this->rows, this->columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            result.matrix_arr[i][j] = this->matrix_arr[i][j] * multip_const;
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& matrix) const
{
    if (matrix.rows != this->columns) {
        throw std::invalid_argument("Invalid size of matrix(operator *)");
    }
    else {
        Matrix result(this->rows, matrix.columns);
        for (size_t k = 0; k < this->rows; ++k) {
            for (size_t i = 0; i < matrix.columns; ++i) {
                for (size_t j = 0; j < this->columns; ++j) {
                    result.matrix_arr[k][i] += (this->matrix_arr[k][j]) * matrix.matrix_arr[j][i];
                }
            }
        }
        return result;
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& matrix)
{
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix_arr[i];
    }
    delete[] matrix_arr;

    columns = matrix.columns;
    rows = matrix.rows;

    CreateMatrixArr(rows, columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            matrix_arr[i][j] = matrix.matrix_arr[i][j];
        }
    }
    return *this;
}

class MatrixRow;
template<typename T>
T* Matrix<T>::operator[](size_t index) {
    if (index < 0 || rows < index) {
        throw std::invalid_argument("Invalid index of rows(cons MatrixRow)");
    }
    else {
        return MatrixRow(matrix_arr, columns)[index];
    }
}

//Methods of class Matrix

template <typename T>
Matrix<T> Matrix<T>::InverseMatrix() const{
    T deter = (*this).determinant();
    if(deter == 0){
        throw std::invalid_argument("Division by zero (InverMatrix)");
    }
    else{
        Matrix temp_matrix = Matrix(*this);
        size_t rows = this->rows; size_t columns = this->columns;
        Matrix<T> result(rows, columns);
        for( size_t i = 0; i < rows; ++i){
            for(size_t j = 0; j < columns; ++j){
                Matrix<T> sub_matrix(rows - 1, columns - 1);
                size_t temp_rows = 0;
                for( size_t sub_i = 0; sub_i < rows; ++sub_i){
                    if(sub_i == i) continue;
                    size_t temp_columns = 0;
                    for(size_t sub_j = 0; sub_j < columns; ++sub_j){
                        if(sub_j == j) continue;
                        sub_matrix[temp_rows][temp_columns] = temp_matrix[sub_i][sub_j];
                        temp_columns += 1;
                    }
                    temp_rows += 1;
               }
                result[i][j] = [](size_t i, size_t j){if((i+j)%2 == 0){return 1;} else{return -1;}}(i, j) *(sub_matrix.determinant());
           }
        }
        result = (result.TransposeMatrix())*(1/deter);
        return result;
    }
}

template <typename T>
double Matrix<T>::determinant() const{
    if(this->rows != this->columns){
        std::cout << rows << columns;
        throw std::invalid_argument("Rows and columns must have the same size(determ)");
    }
    else{
        if (this->rows == 1){ return matrix_arr[0][0];}
        else if(this->rows == 2){
            return matrix_arr[0][0] * matrix_arr[1][1] - matrix_arr[0][1] * matrix_arr[1][0];
        }
        else if(this->rows == 3){
            return matrix_arr[0][0]*(matrix_arr[1][1]*matrix_arr[2][2] - matrix_arr[1][2]*matrix_arr[2][1]) -
                   matrix_arr[0][1]*(matrix_arr[1][0]* matrix_arr[2][2] - matrix_arr[1][2]*matrix_arr[2][0]) +
                   matrix_arr[0][2]*(matrix_arr[1][0]* matrix_arr[2][1] - matrix_arr[1][1]*matrix_arr[2][0]);
        }
        else{
            size_t size_rows = this->rows;
            size_t size_columns = this->columns;
            double determinant_result = 0;
            for(size_t index = 0; index < size_columns; ++index){
                std::vector<std::vector<T>> vector_arr;
                for(size_t sub_index = 1; sub_index < size_rows; ++sub_index){
                    std::vector<T> temp_vector;
                    for(size_t sub_index_2 = 0; sub_index_2 < size_columns; ++sub_index_2){
                        if(sub_index_2 != index){
                            temp_vector.push_back(matrix_arr[sub_index][sub_index_2]);
                        }
                    }
                    vector_arr.push_back(temp_vector);
                }
                determinant_result += [](size_t i){ if(i%2 == 0){return 1;} else{return -1;}}(index) * matrix_arr[0][index]*(Matrix(vector_arr).determinant());
            }
            return determinant_result;
        }
    }
}



template <typename T>
void Matrix<T>::Print() const {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            std::cout << matrix_arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template <typename T>
Matrix<T> Matrix<T>::TransposeMatrix() const
{
    Matrix temp_matrix(*this);

    size_t rows = temp_matrix.rows; size_t columns = temp_matrix.columns;
    std::vector<std::vector<T>> temp_vector;
    for(size_t i = 0; i < columns; ++i){
        std::vector<T> temp_subvector;
        for(size_t j = 0; j < rows; ++j){
            temp_subvector.push_back(temp_matrix[j][i]);
        }
        temp_vector.push_back(temp_subvector);
    }
    Matrix result(temp_vector);

    //for (int i = 0; i < rows; ++i) {
    //    delete[] matrix_arr[i];
    //}
    //delete[] matrix_arr;

    //int temp_rows = rows;

    //matrix_arr = new T * [columns];
    //for (int i = 0; i < columns; ++i) {
    //    matrix_arr[i] = new T[rows];
    //}


    //for (int i = 0; i < this->rows; ++i) {
    //    for (int j = 0; j < this->columns; ++j) {
    //        matrix_arr[j][i] = result.matrix_arr[i][j];
    //    }
    //}
    //rows = columns; columns = temp_rows;
    return result;
}

template <typename T>
void Matrix<T>::CreateMatrixArr(size_t rows, size_t columns)
{
    matrix_arr = new T * [rows];
    for (size_t i = 0; i < rows; ++i) {
        matrix_arr[i] = new T[columns];
    }
}
template <typename T>
size_t Matrix<T>::InvalidValueArray(const std::vector<std::vector<T>>& arr)
{
    size_t amountOfRows = arr.size();
    size_t currentSizeArr = 0;
    bool firstElement = true;
    for (auto rowArr : arr) {
        if (firstElement == true) {
            currentSizeArr = rowArr.size();
            firstElement = false;
        }
        else {
            if (rowArr.size() != currentSizeArr) {
                throw std::invalid_argument("Invalid index(invalidValueArr)");
                break;
            }
        }
    }
    return currentSizeArr;
}

