#pragma once

#include "Sequence.h"
#include "string"
#include "Dictionary.h"
#include "LinkedListSequence.h"

using namespace std;


class Split_into_pages {
private:
	Dictionary<string, int>* WordsWithIndex = new Dictionary<string, int>();
	int SizePageInLetters = 0;
	int SizeOfString = 0; 
	int AmountOfPages = 0;

public:

	ListSequence<string>* Split_into_words(string String) {
		ListSequence<string>* Words = new ListSequence<string>();
		string letter = "";
		string word = "";
		for (int i = 0; i < String.size(); i++) {
			letter = String[i];
			//cout << "i. " << i << " " << letter<< endl;
			if (letter != " ") {
				word = word+String[i];
				if ( i == String.size() - 1)
					Words->Append(word);
			}
			else {
				if (word != "") {

					Words->Append(word);
				}
				//cout << "size" << Words->GetSize() << endl;
				//cout << word;
				word = "";
			}
		}
		
		//for (int i = 0; i < Words->GetSize(); i++) {
		//	cout << Words->Get(i);
		//}
		return Words;
	}


	Split_into_pages(string String, int SizePageInLetters_) {
		
		ListSequence<string>* words = Split_into_words(String);
		this->SizePageInLetters = SizePageInLetters_;
		int page = 1;
		this->AmountOfPages = page;
		int pointer = 0;
		this->WordsWithIndex = new Dictionary<string, int>(words->Get(0), 1);
		pointer = pointer + words->Get(0).size() + 1;
		for (int i = 1; i < words->GetSize(); i++) {
			if (page == 1) {
				this->SizePageInLetters = this->SizePageInLetters/2;
			}
			if (page%10 == 0) {
				this->SizePageInLetters = this->SizePageInLetters *3/4;
			}
			if (pointer + words->Get(i).size() < this->SizePageInLetters) {
				this->WordsWithIndex->add(words->Get(i), page);
				pointer = pointer + words->Get(i).size() + 1;
				//cout << pointer;
			}
			else {
				if (words->Get(i).size() > this->SizePageInLetters)
					throw std::out_of_range("Page smaller than word!");
				page++;
				this->AmountOfPages = page;
				pointer = words->Get(i).size() + 1;
				this->WordsWithIndex->add(words->Get(i), page);
			}
			this->SizePageInLetters = SizePageInLetters_;
		}
	}

	int GetNumberOfPages() {
		return this->AmountOfPages;
	}

	int GetPageOfString(string String) {
		return this->WordsWithIndex->get(String);
	}

	void PrintWordsWithIndex() {
		this->WordsWithIndex->print();
	}


	~Split_into_pages() {
		delete WordsWithIndex;
		this->SizePageInLetters = 0;
		this->SizeOfString = 0;
		this->AmountOfPages = 0;
	}
};