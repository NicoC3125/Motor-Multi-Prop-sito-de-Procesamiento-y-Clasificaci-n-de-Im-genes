#ifndef MATRIZ_PIXELES_H
#define MATRIZ_PIXELES_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <cstring>
#include "Pixel.h"


#endif#ifndef __CMATRIX_H__
#define __CMATRIX_H__
#include <iostream>  // cout, cin, endl
#include <cstddef>   // size_t
#include "types.h"
using namespace std;

template<typename TP>
class CMatrix{
    TP   **m_pMat;
    size_t m_rows;
    size_t m_cols;

    public:
        CMatrix(size_t rows= 0, size_t cols= 0);
        CMatrix(const CMatrix<TP> &other);
        ~CMatrix();

        void CreateMatrix(size_t rows, size_t cols);
        void ReadMatrix(istream &is);
        void TransformarMatriz(void (*pFunc)(TP&));
        void PrintMatrix(ostream &os);
        void DeleteMatrix();
};

TP&operator()(size_t row, size_t col) ;
const TP&operator()(size_t row, size_t col) const;
TP* operator[](size_t row) ;
const TP* operator[](size_t row) const;

size_t GetRows() const { return m_rows; }
size_t GetCols() const { return m_cols; }
TP** getData() const { return m_pMat; }
bool isEmpty() const { return m_pMat == nullptr; }
void fill(const TP& valor) {
    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_cols; ++j)
            m_pMat[i][j] = value;
}

template<typename TP>
CMatrix<TP>::CMatrix(size_t rows, size_t cols){
    m_pMat = nullptr;
    CreateMatrix(rows, cols);
}

template<typename TP>
CMatrix<TP>::CMatrix(const CMatrix<TP> &other){
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    CreateMatrix(m_rows, m_cols);
    for(size_t i = 0 ; i < m_rows ; ++i)
        for(size_t j = 0 ; j < m_cols ; ++j)
            m_pMat[i][j] = other.m_pMat[i][j];
}

template<typename TP>
CMatrix<TP>::~CMatrix(){
    DeleteMatrix();
}

template<typename TP> 
void CMatrix<TP>::CreateMatrix(size_t rows, size_t cols){
    m_cols = cols;
    m_rows = rows;
    m_pMat = new TP*[rows];
    for (size_t i = 0; i < rows; i++)
        m_pMat[i] = new TP[cols];
}

template<typename TP> 
void CMatrix<TP>::ReadMatrix(istream &is){
    for (size_t i = 0; i < m_rows; i++)
        for (size_t j = 0; j < m_cols; j++)
            is >> m_pMat[i][j];
}

// Aqui luego vamos a generalizar mas este metoddo
template<typename TP> 
void CMatrix<TP>::TransformarMatriz(void (*pFunc)(TP&)){
    for (size_t i = 0; i < m_rows; i++)
        for (size_t j = 0; j < m_cols; j++)
            pFunc(m_pMat[i][j]);
}

template<typename TP> 
void CMatrix<TP>::PrintMatrix(ostream &os){
    os << m_rows << " " << m_cols << endl;
    for (size_t i = 0; i < m_rows; i++){
        for (size_t j = 0; j < m_cols; j++)
            os << m_pMat[i][j] << " ";
        os << endl;
    }
}

template<typename TP> 
void CMatrix<TP>::DeleteMatrix(){
    for (size_t i = 0; i < m_rows; i++)
        delete[] m_pMat[i];
    delete[] m_pMat;
    m_pMat = nullptr;
    m_rows = 0;
    m_cols = 0;
}

void DemoCMatrix1();

#endif // __CMATRIX_H__