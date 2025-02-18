#include "InvertedIndex.h"
#include <fstream>
#include <iostream>

InvertedIndex::InvertedIndex() {
}

InvertedIndex::InvertedIndex(const InvertedIndex &obj) {
    this->invertedIndex = obj.invertedIndex;
}

InvertedIndex::~InvertedIndex() {
}

TreeMap<std::string, std::vector<int> >& InvertedIndex::getInvertedIndex() {
    return invertedIndex;
}

InvertedIndex& InvertedIndex::addDocument(const std::string &documentName, int docid) {
    std::ifstream file(documentName.c_str());
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << documentName << std::endl;
        return *this;
    }

    std::string word;
    while (file >> word) {
        if (invertedIndex.containsKey(word)) {
            std::vector<int>& docIds = invertedIndex[word];
            
            bool found = false;
            for (std::vector<int>::iterator it = docIds.begin(); it != docIds.end(); ++it) {
                if (*it == docid) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                docIds.push_back(docid);
            }
        }
        else {
            std::vector<int> newDocIds;
            newDocIds.push_back(docid);
            invertedIndex.put(word, newDocIds);
        }
    }

    file.close();
    return *this;
}

std::vector<int> InvertedIndex::search(const std::string &query) {

    std::vector<std::string> words;
    std::string currentWord = "";

    for (int i = 0; i < query.size(); i++) 
    {
        if (query[i] == ' ') 
        {
            if (!currentWord.empty()) 
            {
                words.push_back(currentWord);
                currentWord = "";
            }
        } 
        else 
        {
            currentWord += query[i];
        }
    }

    if (!currentWord.empty()) 
    {
        words.push_back(currentWord);
    }

    std::vector<int> result;
    
    std::vector<std::string>::iterator wordIt = words.begin();
    for (; wordIt != words.end(); wordIt++)
    {
        std::vector<int> currentDocIds;

        if (!invertedIndex.containsKey(*wordIt)) 
        {
            continue; 
        }
        
        try 
        {
            currentDocIds = invertedIndex.get(*wordIt); 
        }
        catch (NoSuchItemException) 
        { 
            continue;
        }

        std::vector<int> mergedResult;
        std::vector<int>::iterator result_it = result.begin();
        std::vector<int>::iterator ID_it = currentDocIds.begin();

        while (result_it != result.end() && ID_it != currentDocIds.end()) 
        {
            if (*result_it == *ID_it) 
            {
                mergedResult.push_back(*result_it);
                result_it++;
                ID_it++;
            } 
            else if (*result_it < *ID_it) 
            {
                mergedResult.push_back(*result_it);
                result_it++;
            } 
            else if(*ID_it<*result_it)
            {
                mergedResult.push_back(*ID_it);
                ID_it++;
            }
        }

        while (result_it != result.end()) {
            mergedResult.push_back(*result_it);
            result_it++;
        }

        while (ID_it != currentDocIds.end()) {
            mergedResult.push_back(*ID_it);
            ID_it++;
        }

        result = mergedResult;
    }

    return result;
}


InvertedIndex& InvertedIndex::printInvertedIndex() const {
    invertedIndex.print();
    return const_cast<InvertedIndex&>(*this);
}

InvertedIndex& InvertedIndex::operator=(const InvertedIndex &rhs) {
    this->invertedIndex = rhs.invertedIndex;
    return *this;
}