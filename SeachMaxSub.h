#pragma once
#include <iostream>
#include <string>
#include "binary_tree.h"
#include "sequence.h"
#include <utility>
#include "ArraySequence.h"
#include "dictionary.h"
#include <vector>

using namespace std;

template <class T>
bool frstmin(T a, T b)
{
    return a <= b;
}

void print_seq(Sequence<pair<string, int>>* seq) {
    for (int i = 0; i < seq->GetSize(); i++) {
        cout << "string: " << seq->Get(i).first << " - amount: " << seq->Get(i).second << endl;
    }
}


class Search_often_sub {
private:
    Dictionary<string, int>* dict;
    int min, max;
    string max_string;
    int max_count = 0;
    vector <string> keys;
public:
    Search_often_sub(Sequence<char>* seq, int min, int max) {
        dict = new Dictionary<string, int>();
        this->min = min;
        this->max = max;


        for (int i = 0; i < seq->GetSize(); i++) {
            Sequence<char>* sub;
            for (int j = min; i + j <= seq->GetSize() && j <= max; j++) {
                 sub = seq->GetSubsequence(i, i + j);
                string sub_string = "";
                for (int i = 0; i < sub->GetSize(); i++) {
                    sub_string.append(1, sub->Get(i));
                }

                if (!dict->containsKey(sub_string)) {
                    int count = 1;
                    dict->add(sub_string, count);
                    keys.push_back(sub_string);
                    if (max_count < count) {
                        max_count = count;
                        max_string = sub_string;
                    }
                }
                else {
                    int count = dict->get(sub_string);
                    count++;
                    dict->changeElem(sub_string, count);
                    if (max_count < count) {
                        max_count = count;
                        max_string = sub_string;
                    }
                }
            }
        }
    }

    void print()
    {
        for (auto& elem : keys) {
            cout << "string: " << elem << " - amount: " << dict->get(elem) << endl;
        }
    }

    ~Search_often_sub() {
        delete dict;
    }

    int GetCountOfString(string sub) {
        return dict->get(sub);
    }

    void GetInfoAboutMaxString() {
        cout << "string: " << max_string << " - amount: " << max_count << endl;
    }

    string GetMaxString(){
        return max_string;
    }

    int Get_max_count() {
        return max_count;
    }
};
