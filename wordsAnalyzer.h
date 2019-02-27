//
// Created by master-yoda on 12/31/18.
//

#ifndef CPP_EX2_WORDSANALYZER_H
#define CPP_EX2_WORDSANALYZER_H

#define FREQWORD_FILE_ARG 1
#define UNKNOWN_FILE_ARG 2

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>

#include "boost/algorithm/string.hpp"
#include "boost/tokenizer.hpp"

//#include "boost/filesystem.hpp"


using namespace std;
using namespace boost;

typedef set<string> stringVector;
typedef unordered_map<string, int> wordsCounter;

/** words analyzor class */
class wordsAnalyzer
{

public:
    /** paths vector constructor */
    explicit wordsAnalyzer(const vector<string> &filePaths);


    /** author data class */
    class author
    {
    public:
        /** defaut constructor */
        author();

        /** constructor */
        author(const string &filePath, const stringVector &freqWordsSet);

        /** author data class */
        author(const wordsAnalyzer::author &);

        friend class wordsAnalyzer;

        /** defines as the angle between the given author vector */
        double operator|(const wordsAnalyzer::author &a) const;

    private:
        /** count the words accorfing to given frequent words set */
        void _countWords(const stringVector &freqWordsSet);

        /** fill the author vector according to the given frequent words set */
        void _getVector(const stringVector &freqWordsSet);

        string name;
        ifstream file;
        vector<double> authVector;
        wordsCounter counter;
    };


    friend class wordsAnalyzer::author;

    /** analyze the given text files */
    void analyze() const;

private:
    /** default constructor */
    wordsAnalyzer() = default;

    /** fill the frequent words set */
    stringVector _getFrequentWordTable(ifstream &freqWordFile);

    /** calculate the distances between the unknown author text(authors[0]) with the known authors text */
    void _calcDistances() const;

    stringVector freqWordsSet;
    vector<author> authors;


};


#endif //CPP_EX2_WORDSANALYZER_H
