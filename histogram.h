#pragma once


#include "dictionary.h"
#include "binary_tree.h"
#include "sequence.h"
#include "person.h"
#include "ArraySequence.h"

using namespace std;

class Histogram
{
private:

    Dictionary<int, int>* dict;

    int HistogramParam(Person man, int gap) {
        int age = man.getAge(2020);
        if (age < 0)
            throw std::out_of_range("Age < 0");
        int category = 1;
        while ((age - gap) > 0) { //включительно
            category++;
            age = age - gap;
        }
       
        return category;
    }

public:

    Histogram(Sequence<Person>* seq, int gap) {

        int amount = 0;
        int category = HistogramParam(seq->Get(0), gap);
        this->dict = new Dictionary<int, int>(category, 1);
        for (int i = 1; i < seq->GetSize(); i++)
        {
            category = HistogramParam(seq->Get(i), gap);
            if (this->dict->containsKey(category))
            {
                amount = this->dict->get(category) + 1;
                this->dict->changeElem(category, amount);
            }
            else {
                this->dict->add(category, 1);
            }
        }
    }
    
    int getCategorysAmount(int category)//количество элементов в категории
    {
        return this->dict->get(category);
    }
    int getAmountOfCategories() // количество категорий
    {
        return this->dict->getCount();
    }

    void addElemHistogramParam(Person man, int gap) {
        int category = HistogramParam(man, gap);
        dict->changeElem(category, dict->get(category)+1);
    }
    void print()
    {
        dict->print();
    }

    ~Histogram()
    {
        delete dict;
    }
}; 
