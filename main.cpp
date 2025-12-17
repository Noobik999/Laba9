#include <iostream>
//Функции для заданий
char* CopyString(const char* str) {
    int i = 0;
    while (str[i] != '\0') i++;
    char* coppied_string = new char[i+1];
    for (int ind = 0; ind < i; ind++) {
        coppied_string[ind] = str[ind];
    }
    coppied_string[i] = '\0';
    return coppied_string;

}
char* ConcatinateStrings(const char* a, const char* b) {
    int i = 0;
    int j = 0;
    while (a[i] != '\0') i++;
    while (b[j] != '\0') j++;
    char* sovmeshennaya_string = new char[i+j];
    for (int ind = 0; ind < i; ind++) {
        sovmeshennaya_string[ind] = a[ind];
    }
    for (int ind = i; ind < j+i; ind++) {
        sovmeshennaya_string[ind] = b[ind-i]; //Так как мы берём ind от i он выходит за рамки строки b => нужно вычесть i, чтобы вставился нужный символ
    }
    sovmeshennaya_string[i+j] = '\0';
    return sovmeshennaya_string;
}


//Второе задание
struct Matrix {
    // двумерный массив с данными.
    int** data_ = nullptr;
    // количество столбцов
    size_t n_ = 0u;
    // количество строк
    size_t m_ = 0u;
};

// Создает заполненную нулями матрицу n x m.
void Construct(Matrix& out, size_t n, size_t m) {
    out.n_ = n;
    out.m_ = m;
    out.data_ = new int*[m];
    for (size_t i = 0; i < m; i++) {
        out.data_[i] = new int[n]();
    }
}

// Освобождает выделенную память.
void Destruct(Matrix& in) {
    if (in.data_ != nullptr) {
        for (size_t i = 0; i < in.m_; i++) {
            delete[] in.data_[i];
        }
        delete[] in.data_;
        in.data_ = nullptr;
    }
    in.n_ = 0;
    in.m_ = 0;
    }

// Создает копию матрицы |matrix|.
Matrix Copy(const Matrix& matrix) {
    Matrix coppied;
    Construct(coppied, matrix.n_, matrix.m_);
    for (size_t i = 0; i < coppied.m_; i++) {
        for (size_t j = 0; j < coppied.n_; j++) {
            coppied.data_[i][j] = matrix.data_[i][j];
        }
    }
    return coppied;
}
// Возвращает сумму двух матриц.
// Если операция невозможна - вернуть пустую матрицу
Matrix Add(const Matrix& a, const Matrix& b, int minus) {//Я добавил ещё одну переменную, так как суммирование и вычитание матриц почти одинаковые операции, чтобы не писать одинаковый код я модернизировал предыдущюю функцию, надеюсь ничего страшного;
    Matrix summ;
    if (a.m_ == b.m_ and a.n_ == b.n_) {
        Construct(summ, a.n_,b.m_);
        for (size_t i = 0; i < a.m_; i++) {
            for (size_t j = 0; j < b.n_; j++) {
                summ.data_[i][j] = a.data_[i][j] + b.data_[i][j] * minus;
            }
        }
    }
    else {
        std::cout<<"Размер матриц не одинаковый => их нельзя суммировать и нельзя найти их разность";
        return summ;
    }
    return summ;
}

// Возвращает разницу двух матриц.
// Если операция невозможна - вернуть пустую матрицу
Matrix Sub(const Matrix& a, const Matrix& b) {
    return Add(a,b,-1); //Сумма матриц с умножением значения второй на минус будет равна разности
}
// Возвращает произведение двух матриц.
// Если операция невозможна - вернуть пустую матрицу
Matrix Mult(const Matrix& a, const Matrix& b) {
    Matrix mult;
    Construct(mult, a.n_, b.m_);
    if (a.n_ == b.m_) {
        for (size_t i = 0; i < a.m_; i++) {
            for (size_t j = 0; j < b.n_; j++) {
                mult.data_[i][j] = 0;
                for (size_t k = 0; k < a.m_; k++) {
                    mult.data_[i][j] += a.data_[i][k] * b.data_[k][j];}
            }
        }
    }
    else {
        std::cout<<"Число столбцов в первой матрице не равно числу строк во второй матрице => Умножение невозможно"<<std::endl;
        return mult;
    }
    return mult;
}

// Транспонирование матрицы.
void Transposition(Matrix& matrix) {
    Matrix transporated;
    Construct(transporated, matrix.m_, matrix.n_);
    for (size_t i = 0; i < transporated.m_; i++) {
        for (size_t j = 0; j < transporated.n_; j++) {
            transporated.data_[i][j] = matrix.data_[j][i];
            }
        }
    Destruct(matrix);
    Construct(matrix, transporated.n_, transporated.m_);
    matrix = Copy(transporated);
    Destruct(transporated);
    }

// Сравнение двух матриц.
bool operator==(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.n_ or a.m_ != b.m_) {
        return false;
    }
    for (size_t i = 0; i < a.m_; i++) {
        for (size_t j = 0; j < a.n_; j++) {
            if (a.data_[i][j] != b.data_[i][j]) {
                return false;
            }
        }
    }
    return true;
};

//Вывод матрицы на экран
void PrintMatrix(const Matrix& matrix) {
    for (size_t i = 0; i < matrix.m_; i++) {
        for (size_t j = 0; j < matrix.m_; j++) {
            std::cout<<matrix.data_[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}
int main() {

    //Певрое задание
    char* stringa = "Сто одёжек, и все без пуговиц на распашку рубаха рваная!";
    char* Second_string = " Гром салюта с вечерней улицы от души поздравляю с праздником!";
    char* copy = CopyString(stringa);
    std::cout<<"Ваша оригинальная строка: "<<stringa<<'\n';
    std::cout<<"Копия вашей строки: "<<copy<<'\n';
    delete copy; //Удаляем динамическую переменную

    char* new_str = ConcatinateStrings(stringa, Second_string);
    std::cout<<"Ваши оригинальные строки: "<<stringa<<" и "<<Second_string<<'\n';
    std::cout<<"Ваша совмещённая строка: "<<new_str<<std::endl<<std::endl;
    delete new_str;

    //Создание 2 матриц
    Matrix matrica1, matrica2;
    Construct(matrica1, 3,3);
    Construct(matrica2, 3,3);
    matrica1.data_[0][0] = 1; matrica1.data_[0][1] = 2; matrica1.data_[0][2] = 3;
    matrica1.data_[1][0] = 4; matrica1.data_[1][1] = 5; matrica1.data_[1][2] = 6;
    matrica1.data_[2][0] = 7; matrica1.data_[2][1] = 8; matrica1.data_[2][2] = 9;

    matrica2.data_[0][0] = 1; matrica2.data_[0][1] = 7; matrica2.data_[0][2] = 4;
    matrica2.data_[1][0] = 2; matrica2.data_[1][1] = 8; matrica2.data_[1][2] = 5;
    matrica2.data_[2][0] = 3; matrica2.data_[2][1] = 9; matrica2.data_[2][2] = 6;

    //Махинации с матрицами
    std::cout<<"Сумма 2 матриц: "<<std::endl;
    PrintMatrix(Add(matrica1, matrica2,1));
    std::cout<<std::endl;
    std::cout<<"Разность 2 матриц: "<<std::endl;
    PrintMatrix(Sub(matrica1, matrica2));
    std::cout<<std::endl;
    std::cout<<"Произведение 2 матриц: "<<std::endl;
    Matrix mult = Mult(matrica1, matrica2);
    PrintMatrix(mult);
    std::cout<<std::endl;
    std::cout<<"Транспонирование матрицы1: "<<std::endl;
    Transposition(matrica1);
    PrintMatrix(matrica1);
    std::cout<<std::endl;
    Transposition(matrica1); //Возврат матрицы 1 в первоначальный вид
    if (matrica1 == matrica2) std::cout<<"Матрицы 1 и 2 равны";
    else std::cout<<"Матрицы 1 и 2 не равны";
    return 0;}
