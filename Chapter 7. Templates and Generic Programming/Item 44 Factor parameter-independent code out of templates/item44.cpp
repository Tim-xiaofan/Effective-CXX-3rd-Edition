#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>    // std::swap
#include <exception>
#include <assert.h>     //c lib
#include <functional>
#include <list>
#include <cstring>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;
using std::function;
using std::bind;

template<typename T, std::size_t n>
class SquareMatrix
{
    public:
        void invert(){cout << n << endl;}
};

template<typename T>
class SquareMatrixBase
{
    protected:
        void invert(std::size_t matrixSize){}
};

template<typename T, std::size_t n>
class SquareMatrixBoost : private SquareMatrixBase<T>
{//problem:how does it know where the data for a particular matrix is
    private:
        using SquareMatrixBase<T>::invert;
    public:
        void invert(){this->invert(n);}
};

template<typename T>
class SquareMatrixBase1
{
    protected:
        SquareMatrixBase1(std::size_t n, T *pMem)
            :size(n), pData(pMem){}
        void setDataPtr(T * ptr){ pData = ptr;}
        void invert(void){cout << size << endl;}
    private:
        std::size_t size;
        T *pData;
};

template<typename T, std::size_t n>
class SquareMatrix1: private SquareMatrixBase1<T>
{
    public:
        SquareMatrix1():SquareMatrixBase1<T>(n, data){}
        void invert(void){SquareMatrixBase1<T>::invert();}
    private:
        T data[n * n];//problem:the objects themselves could be very large
};

template<typename T, std::size_t n>
class SquareMatrix2: private SquareMatrixBase1<T>
{
    public:
        SquareMatrix2()
            :SquareMatrixBase1<T>(n, nullptr), data(new T[n * n])
        {
            this->setDataPtr(data);
        }
        void invert(void){SquareMatrixBase1<T>::invert();}
    private:
        T *data;
};

int main(int argc, char *argv[])
{
    SquareMatrix<double, 5> sm1;
    sm1.invert();
    SquareMatrix<double, 10> sm2;
    sm2.invert();

    SquareMatrix1<int, 15> sm3;
    sm3.invert();
    SquareMatrix2<int, 20> sm4;
    sm4.invert();
	return 0;
}
