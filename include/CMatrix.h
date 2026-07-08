#ifndef __CMATRIX_H__
#define __CMATRIX_H__
#include "util.h"

template<typename T>
class CMatrix {
    TI m_rows;
    TI m_cols;
    T* m_data;

public:
    CMatrix() : m_rows(0), m_cols(0), m_data(nullptr) {}

    CMatrix(TI rows, TI cols) : m_rows(rows), m_cols(cols) {
        m_data = new T[rows * cols]();
    }

    CMatrix(const CMatrix& other) {
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_data = new T[m_rows * m_cols];
        for (TI i = 0; i < m_rows * m_cols; ++i)
            m_data[i] = other.m_data[i];
    }

    CMatrix(CMatrix&& other) noexcept {
        m_rows = exchange(other.m_rows, 0);
        m_cols = exchange(other.m_cols, 0);
        m_data = exchange(other.m_data, nullptr);
    }

    CMatrix& operator=(const CMatrix& other) {
        if (this != &other) {
            delete[] m_data;
            m_rows = other.m_rows;
            m_cols = other.m_cols;
            m_data = new T[m_rows * m_cols];
            for (TI i = 0; i < m_rows * m_cols; ++i)
                m_data[i] = other.m_data[i];
        }
        return *this;
    }

    CMatrix& operator=(CMatrix&& other) noexcept {
        if (this != &other) {
            delete[] m_data;
            m_rows = exchange(other.m_rows, 0);
            m_cols = exchange(other.m_cols, 0);
            m_data = exchange(other.m_data, nullptr);
        }
        return *this;
    }

    ~CMatrix() {
        delete[] m_data;
    }

    void CreateMatrix(TI rows, TI cols) {
        delete[] m_data;
        m_rows = rows;
        m_cols = cols;
        m_data = new T[rows * cols]();
    }

    T& operator()(TI row, TI col) { return m_data[row * m_cols + col]; }
    const T& operator()(TI row, TI col) const { return m_data[row * m_cols + col]; }

    TI GetRows() const { return m_rows; }
    TI GetCols() const { return m_cols; }
};

#endif