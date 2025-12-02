#pragma once
#include <iostream>
#include <stdexcept>

template <class T>
class TStack {
protected:
    T* pMem;
    int memSize;
    int topIndex;

public:
    TStack(int _size = 100) {
        if (_size > 0)
            memSize = _size;
        else
            memSize = 100;

        pMem = new T[memSize];
        topIndex = -1;
    }

    TStack(const TStack& s) {
        memSize = s.memSize;
        topIndex = s.topIndex;
        pMem = new T[memSize];
        for (int i = 0; i <= topIndex; i++) {
            pMem[i] = s.pMem[i];
        }
    }

    ~TStack() {
        delete[] pMem;
    }

    void Push(const T& val) {
        if (IsFull()) {
            T* tmp = new T[memSize * 2];
            for (int i = 0; i < memSize; i++) {
                tmp[i] = pMem[i];
            }
            delete[] pMem;
            pMem = tmp;
            memSize *= 2;
        }
        topIndex++;
        pMem[topIndex] = val;
    }

    T Pop() {
        if (IsEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        T res = pMem[topIndex];
        topIndex--;
        return res;
    }

    T Top() {
        if (IsEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return pMem[topIndex];
    }

    bool IsEmpty() const {
        return topIndex == -1;
    }

    bool IsFull() const {
        return topIndex == memSize - 1;
    }

    void Clear() {
        topIndex = -1;
    }
};