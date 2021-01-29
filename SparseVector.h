
#pragma once
#include "dictionary.h"

template <class T>
class SparceVector {
private:
    Dictionary<int, T>* dict;
    int size = 0;
public:
    SparceVector(T* vector, int size) {
        int i = 0;
        while (vector[i] == 0) {
            i++;
        }
        dict = new Dictionary<int, int>(i, vector[i]);
        this->size++;
        for (i++; i < size; i++) {
            if (vector[i] != 0) {
                dict->add(i, vector[i]);
                this->size++;
            }
        }
    }

    ~SparceVector() {
        delete dict;
    }

    void addElem(int index, T elem) {
        if (elem != T(0)) {
            dict->add(index, elem);
            this->size++;
        }


    }

    T getElem(int index) {
        return dict->get(index);
    }

    void changeElem(int index, T elem) {
        dict->changeElem(index, elem);
    }

    T* getSparceVector() {
        T* get_vector = new T[size];
        for (int i = 0; i < size; i++) {
            if (dict->containsKey(i))
                get_vector[i] = dict->get(i);
            else
                get_vector[i] = 0;
        }
        return get_vector;
    }

    int getSize() {
        return size;
    }

    Dictionary<int, T>* GetDictionary() {
        return this->dict;
    }

    void Print() {
        dict->print();
    }

};
