#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H
#include "dMatrix.h"
#include "cmath"
#endif // MATRIX_TEST_H
typedef std::vector<std::vector<double>> double_vector;
typedef std::vector<std::vector<int>> int_vector;
typedef std::vector<std::vector<float>> fl_vec;

bool test_1();
bool test_2();
bool test_3();
bool test_4();
bool test_5();
bool test_6();
bool test_7();
bool test_8();
bool test_9();
bool test_10();
bool test_11();
bool test_12();
bool test_13();
bool test_14();
bool test_15();

void tests(){
    bool test_result = test_1()*test_2()*test_3()*test_4()*test_5()
                       *test_6()*test_7()*test_8()
                       *test_9()*test_10()*test_11()*test_12()*test_13()*test_14()*test_15();
    if(test_result){
        std::cout << "Tests passed" << std::endl;
    }
    else{
        std::cout << "Tests didn't passed" << std::endl;
    }
}


bool test_double_matrix(Matrix<double> matrix_difference,double epsilon){
    for (int i = 0; i < matrix_difference.getRows(); ++i) {
        for (int j = 0; j < matrix_difference.getColumns(); ++j) {
            if (matrix_difference[i][j] > epsilon || matrix_difference[i][j] < -epsilon) {
                return false;
            }
        }
    }
    return true;
}


bool test_1(){
    try{
       double_vector test_matrix_1_test = {{2,4},{1,3}};
       double_vector test_matrix_2_test = {{5,1},{0,2}};
       Matrix test_matrix_2(test_matrix_2_test);
       Matrix test_matrix_1(test_matrix_1_test);
       Matrix result_test_1 = test_matrix_2 + test_matrix_1;
       if(result_test_1[0][0] == 7 && result_test_1[0][1] == 5 && result_test_1[1][0] == 1 && result_test_1[1][1] == 5){
           return true;
       }
    }
    catch(...){
        throw "Error in test";
    }
    std::cout << "test_1 was failed\n";
    return false;
}

bool  test_2(){
    try{
        double_vector test_matrix_1_test = {{1,2},{3,4}};
        double_vector test_matrix_2_test = {{5,6},{7,8}};
        Matrix test_matrix_2(test_matrix_2_test);
        Matrix test_matrix_1(test_matrix_1_test);
        Matrix result_test_1 = test_matrix_1*test_matrix_2;
        if(result_test_1[0][0] == 19 && result_test_1[0][1] == 22 && result_test_1[1][0] == 43 && result_test_1[1][1] == 50){
            return true;
        }
    }
    catch(...){
        throw "Error in test";
    }
    std::cout << "test_2 was failed\n";
    return false;
}

bool  test_3(){
    try{
        double_vector test_matrix_1_test = {{6,8},{3,7}};
        double_vector test_matrix_2_test = {{2,3},{1,4}};
        Matrix test_matrix_2(test_matrix_2_test);
        Matrix test_matrix_1(test_matrix_1_test);
        Matrix result_test_1 = test_matrix_1 - test_matrix_2;
        if(result_test_1[0][0] == 4 && result_test_1[0][1] == 5 && result_test_1[1][0] == 2 && result_test_1[1][1] == 3){
            return true;
        }
    }
    catch(...){
        throw "Error in test";
    }
    std::cout << "test_3 was failed\n";
    return false;
}


bool test_4(){
    try{
        double_vector test_matrix_1_test = {{10,20},{30,40},{50,60}};
        double_vector test_matrix_2_test = {{1,2},{3,4},{5,6}};
        Matrix test_matrix_2(test_matrix_2_test);
        Matrix test_matrix_1(test_matrix_1_test);
        Matrix result = test_matrix_1 - test_matrix_2;
        if(result[0][0] == 9 && result[0][1] == 18 &&
            result[1][0] == 27 && result[1][1] == 36 &&
            result[2][0] == 45 && result[2][1] == 54){
            return true;
        }
    }
    catch(...){
        throw "Error in test";
    }
    std::cout << "test_4 was failed\n";
    return false;
}

bool test_5(){
    try{
        double_vector test_matrix_1_test = {{1.11 ,2.22},{3.33,4.44},{5.55,6.66}};
        double_vector test_matrix_2_test = {{0.99,1.01},{2.02,3.03},{4.04,5.05}};
        double_vector test_result = {{2.1, 3.23}, {5.35, 7.47},{9.59, 11.71}};
        Matrix test_matrix_2(test_matrix_2_test);
        Matrix test_matrix_1(test_matrix_1_test);
        Matrix result = test_matrix_1 + test_matrix_2;
        Matrix right_result(test_result);
        Matrix Error_matrix = result - right_result;

        bool bool_result = test_double_matrix(Error_matrix, 0.0001);

        if(!bool_result){
            std::cout << "test_5 was failed\n";
            std::cout << "your result is\n ";
            result.Print();
            std::cout << "right result is\n ";
            right_result.Print();
        }
        return bool_result;
    }
    catch(...){
        throw "Error in test";
    }
    return false;
}

bool test_6(){
    try{
        double_vector test_matrix_1 = {{1.1,2.2,3.3},{{4.4,5.5,6.6}}};
        double_vector test_matrix_2 = {{0.5,1.0},{1.5,2.0},{2.5,3.0}};
        double_vector right_result = {{12.1,15.4},{26.95,35.2}};
        Matrix test_m_1(test_matrix_1);
        Matrix test_m_2(test_matrix_2);
        Matrix result(right_result);

        Matrix your_result = test_m_1*test_m_2;

        Matrix Error = your_result - result;

        bool bool_result = test_double_matrix(Error,0.0001);
        if(!bool_result){
            std::cout << "test_6 was failed\n";
            std::cout << "your result is\n ";
            your_result.Print();
            std::cout << "right result is\n ";
            result.Print();
        }
        return bool_result;
    }
    catch(...){
        throw "Error in test";
    }
    return false;
}

bool test_7(){
    double_vector test_matrix = {{3, 8},{4, 6}};
    Matrix test(test_matrix);
    if(fabs(test.determinant() + 14) < 0.0001){
        return true;
    }
    std::cout << "7 is failed\n" << std::endl;
    std::cout << "right result is -14\n ";
    std::cout << "your result is " + std::to_string(test.determinant()) + "\n ";
    return false;
}


bool test_8(){
    double_vector test_8 = {{3.5,8.2},{4.1,6.7}};
    Matrix test(test_8);
    if(fabs(test.determinant() + 10.17) < 0.0001){
        return true;
    }
    std::cout << "8 is failed\n" << std::endl;
    std::cout << "right result is -10.17\n ";
    std::cout << "your result is " + std::to_string(test.determinant()) + "\n ";
    return false;
}

bool test_9(){
    int_vector test_9 = {{1,2,3},{4,5,6},{7,8,9}};
    Matrix test(test_9);
    if(test.determinant() == 0){
        return true;
    }
    std::cout << "9 is failed\n" << std::endl;
    std::cout << "right result is 0\n ";
    std::cout << "your result is " + std::to_string(test.determinant()) + "\n ";
    return false;
}

bool test_10(){
    fl_vec test_10 = {{-1.25,2.75,-3.5},{4.0, -5.125, 6.25},{-7.75,8.0,-9.875}};
    Matrix test(test_10);
    if(fabs(test.determinant() - 1.67578125) < 0.0001){
        return true;
    }
    std::cout << "10 is failed\n" << std::endl;
    std::cout << "right result is -1.67578125\n ";
    std::cout << "your result is " + std::to_string(test.determinant()) + "\n ";
    return false;
}

bool test_11(){
    double_vector test_11 = { {-1.25,2.75,-3.5,100}, {4, -5.125, 6.25, 12}, {-7.75, 8.0, -9.875, 1.2}, {40, -15, -10, 3.4} };
    Matrix test(test_11);
    if(fabs(test.determinant() + 27300.427) < 0.01){
       return true;
    }
    std::cout << "11 is failed\n" << std::endl;
    std::cout << "right result is -27300.427\n ";
    std::cout << "your result is " + std::to_string(test.determinant()) + "\n ";
    return false;
}

bool test_12(){
    double_vector test_11 = { {1,2,3,4},{-1,2,-3.7,4},{8,7,6,-5},{0.011,0.02,0.03,0.04}};
    Matrix test(test_11);
    if(fabs(test.determinant() + 0.2546) < 0.001){
        return true;
    }
    std::cout << "12 is failed\n" << std::endl;
    std::cout << "right result is -0.2546\n ";
    std::cout << "your result is " + std::to_string(test.determinant()) + "\n ";
    return false;
}


bool test_13(){
    double_vector test_13 = {{1,3,5},{4,5,10},{3,4,5}};
    double_vector test_result = {{-0.75, 0.25, 0.25},{0.5,-0.5,0.5},{0.05,0.25,-0.35}};
    Matrix test(test_13);
    Matrix right_result(test_result);
    Matrix result = test.InverseMatrix();
    Matrix Error = result - right_result;
    if(test_double_matrix(Error, 0.0001) == true){
        return true;
    }
    std::cout << "13 is failed\n" << std::endl;
    return false;
}

bool test_14(){
    double_vector test_13 = {{2, 0, 1},{0,-3,-1},{-2,4,0}};
    double_vector test_result = {{2,2,1.5},{1,1,1},{-3,-4,-3}};
    Matrix test(test_13);
    Matrix right_result(test_result);
    Matrix result = test.InverseMatrix();
    Matrix Error = result - right_result;
    if(test_double_matrix(Error, 0.0001) == true){
        return true;
    }
    std::cout << "14 is failed\n" << std::endl;
    return false;
}


bool test_15(){
    double_vector test_13 = {{1, 3, 5, 2},{4,5,10,3},{3,4,5,4},{1,3,5,5}};
    double_vector test_result = {{-(0.66666667), 0.25,0.25,-0.083333333},{1,-0.5,0.5,-0.5},{-0.133333333,0.25,-0.35,0.1833333333},{-0.3333333,0,0,0.3333333}};
    Matrix test(test_13);
    Matrix right_result(test_result);
    Matrix result = test.InverseMatrix();
    Matrix Error = result - right_result;
    if(test_double_matrix(Error, 0.0001) == true){
        return true;
    }
    std::cout << "15 is failed\n" << std::endl;
    return false;
}

