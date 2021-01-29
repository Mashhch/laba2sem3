
#include <cstdlib>
#include <fstream>
#include <chrono>
#include "SparseVector.h"
#include "histogram.h"
#include "AlphabetIndex.h"
#include <iostream>
#include <string>
#include "tests.h"

using namespace std;





Person enterPerson()
{
    string a = "";
    string b = "";
    string c = "";
    int d = 0;
    cout << "FIRST NAME: ";
    cin >> a;
    cout << endl;
    cout << "MIDDLE NAME: ";
    cin >> b;
    cout << endl;
    cout << "LAST NAME:";
    cin >> c;
    cout << endl;
    cout << "BIRTH YEAR: ";
    cin >> d;
    cout << endl;
    return Person(a, b, c, d);
}

void interface() {
    int switcher = 1;
    while (switcher) {
        cout << "1. create histogram" << endl
            << "2. create sparce vector" << endl
            << "3. Building an alphabetical index" << endl
            << "0. Exit" << endl;

        cin >> switcher;
        if (switcher == 1) { //histogram Histogram(ArraySequence<Person>* seq, int gap)
            string FirstNames[13]{ "Maria", "Tolya", "Lera", "Alexey", "Sonya", "Ivan", "Vasiliy", "Stepan", "Egor", "Elizaveta", "Daria", "Liza", "Michael" };
            string MiddleNames[13]{ "Chernova", "Frolov", "Nikiforenko", "Kutnyi", "Pavlova", "Korotkov", "Ershov", "Romanov", "Demidenko", "Kalashnikova", "Ivanchenko", "Murmur", "Krivorotov" };
            string LastNames[13]{ "Pavlovna", "Alexeevich", "Ivanovna", "Vasilievich", "Igorevna", "Pavlovich", "Olegovich", "Vladimirovich", "Alexandrovich", "Michaelovna", "Mihailovna", "Ignatievna", "Stasovna" };

            Person Person_;
            int gap = 0;
            int amount = 0;
            int option = 0;
            Histogram* histogramofpersons;
            Sequence<Person>* seq = new ArraySequence<Person>();
            cout << "Select option" << endl;
            cout << "1 - auto generating sequence" << endl;
            cout << "2 - enter sequence yourself" << endl;
            cin >> option;
            switch (option) {

            case 1:
                cout << "Amount of persons: ";
                srand(time(0));
                amount = 5 + rand() % 10;
                cout << amount << endl;
                cout << "Persons:" << endl;
                for (int i = 0; i < amount; i++) {
                    Person_ = Person(FirstNames[(rand() + i) % 13], MiddleNames[(rand() + i) % 13], LastNames[(rand() + i) % 13], 1950 + (rand() + i) % 70);
                    seq->Append(Person_);
                    cout << Person_.getFIO() << " ";
                    cout << Person_.getBirthYear() << endl;
                }
                cout << "Gap: ";
                gap = 5 + rand() % 20;
                cout << gap << endl;
                histogramofpersons= new Histogram(seq, gap);
                cout << "Category - Amount: " << endl;
                histogramofpersons->print();
                break;
            case 2:            
                cout << "Enter amount of persons" << endl;
                cin >> amount;
                for (int i = 0; i < amount; i++) {
                    Person_ = enterPerson();
                    seq->Append(Person_);
                }
                cout << "Enter gap: ";
                cin >> gap;
                histogramofpersons = new Histogram(seq, gap);
                cout << "Key - category; Element - Amount" << endl;
                histogramofpersons->print();
                break;
            }
        }

        else if (switcher == 2) {   //  sparce vector
            int option = 0;
            int amount = 0;
            int* vect;
            int value = 0;
            SparceVector<int>* Sparce_Vector;
            cout << "Select option" << endl;
            cout << "1 - auto generating a vector" << endl;
            cout << "2 - enter the vector yourself" << endl;
            cin >> option;
            switch (option) {
            case 1:
                cout << "Amount of the elements in the vector: " << endl;
                srand(time(0));
                amount = 1 + rand() % 30;
                vect = new int[amount];
                for (int i = 0; i < amount; i++) {
                    value = (rand() + i * 16) % 50;
                    if (i%10 == 0) value = 0;
                    cout << i << ". " << value << endl;
                    vect[i] = value;
                }
                Sparce_Vector = new SparceVector<int>(vect, amount);
                cout << "size of vector is: " << Sparce_Vector->getSize() << endl;
                cout << "vector:" << endl;
                cout << "index - value" << endl;
                Sparce_Vector->Print();
                cout << endl;
                break;
            case 2:

                cout << "Enter amount of the elements in the vector: " << endl;
                cin >> amount;
                vect = new int[amount];
                for (int i = 0; i < amount; i++) {
                    value = 0;
                    cout << i << ". ";
                    cin >> value;
                    vect[i] = value;
                }
                Sparce_Vector = new SparceVector<int>(vect, amount);
                cout << "size of vector is: " << Sparce_Vector->getSize() << endl;
                cout << "vector:" << endl;
                cout << "index - value" << endl;
                Sparce_Vector->Print();
                cout << endl;
                break;
            }
        }

        else if (switcher == 3) {

            const string letters = " abc defghi jklm nopqrstu vwxyz ";
            int option = 0;
            int sizeOfString = 0;
            string String;
            int SizePageInLetters;
            Split_into_pages* Collection;
            cout << "Select option" << endl;
            cout << "1 - auto string" << endl;
            cout << "2 - enter the string yourself" << endl;
            cin >> option;
            switch (option) {
            case 1:
                srand(time(0));
                sizeOfString = 1+ rand() % 40;
                for (int i = 0; i < sizeOfString; i++) {
                    String = String + letters[(rand()+i) % letters.size()];
                }
                cout << "String: " << String<< endl;
                srand(time(0));
                SizePageInLetters= 10 + rand() % 30;
                cout << "Size of Page: " << SizePageInLetters << endl;
                Collection = new Split_into_pages(String, SizePageInLetters);
                cout << "Number of Pages" << Collection->GetNumberOfPages() << endl;
                cout << "Word - Page" << endl;
                Collection->PrintWordsWithIndex();
                break;
            case 2:
                cout << "enter string: " << endl;
                cin.ignore();
                std::getline(std::cin, String);
                cout << "enter Size of Page In Letters: " << endl;
                cin >> SizePageInLetters;

                Collection = new Split_into_pages(String, SizePageInLetters);
                cout << "Number of Pages" << Collection->GetNumberOfPages() << endl;
                cout << "Word - Page" << endl;
                Collection->PrintWordsWithIndex();
                break;
            }
        }
    }
}
int main(){
    alltests();
    interface();
    return 0;
}