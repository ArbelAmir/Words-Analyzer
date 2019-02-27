#include <numeric>

#include <cmath>
#include "wordsAnalyzer.h"

/** implementation of the header file */
void wordsAnalyzer::analyze() const
{
    _calcDistances();
}

stringVector wordsAnalyzer::_getFrequentWordTable(ifstream &freqWordFile)
{
    typedef tokenizer<char_separator<char>> tokenizer;
    string data((istreambuf_iterator<char>(freqWordFile)), (istreambuf_iterator<char>()));
    tokenizer tok(data, char_separator<char>(" \n, \"\r ;:!"));
    freqWordsSet.insert(tok.begin(), tok.end());
    return freqWordsSet;
}

wordsAnalyzer::wordsAnalyzer(const vector<string> &filePaths)
{
    ifstream freqWordFile(filePaths[FREQWORD_FILE_ARG - 1]);
    _getFrequentWordTable(freqWordFile);

    author unknownAuthor(filePaths[UNKNOWN_FILE_ARG - 1], freqWordsSet);
    authors.push_back(unknownAuthor);
    for (size_t i = 2; i < filePaths.size(); i++)
    {
        author a(filePaths[i], freqWordsSet);
        authors.push_back(a);
    }
}

void wordsAnalyzer::_calcDistances() const
{
    string max_name = "NO FILES";
    double max = 0;
    double tempRes = 0;
    for (auto it = authors.begin() + 1; it != authors.end(); it++)
    {
        tempRes = authors[0] | *it;
        cout << it->name << ' ' << tempRes << endl;
        if (tempRes > max)
        {
            max = tempRes;
            max_name = it->name;
        }
    }
    cout << max_name << ' ' << max << endl;
}


wordsAnalyzer::author::author(const string &filePath, const stringVector &freqWordsSet) : file(filePath)
{
    name = filePath;
    _countWords(freqWordsSet);
    _getVector(freqWordsSet);
    file.close();
}

void wordsAnalyzer::author::_getVector(const stringVector &freqWordsSet)
{
    for (auto &word : freqWordsSet)
    {
        authVector.emplace_back(counter[word]);
    }
}

void wordsAnalyzer::author::_countWords(const stringVector &freqWordsSet)
{
    typedef tokenizer<char_separator<char>> tokenizer;
    string data((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    tokenizer tok(data, char_separator<char>("\t \n,;:!\r"));
    for (const string &word : tok)
    {
        string lowerWord = boost::algorithm::to_lower_copy(word);
        if (freqWordsSet.count(lowerWord) != 0)
        {
            counter[lowerWord]++;
        }
    }
}

wordsAnalyzer::author::author(const wordsAnalyzer::author &a) : file(a.name)
{
    name = a.name;
    authVector = a.authVector;
    counter = a.counter;
}

double wordsAnalyzer::author::operator|(const wordsAnalyzer::author &a) const
{
    double product = inner_product(authVector.begin(), authVector.end(), a.authVector.begin(), 0.0);
    double norm0 = sqrt(inner_product(authVector.begin(), authVector.end(), authVector.begin(), 0.0));
    double norm1 = sqrt(inner_product(a.authVector.begin(), a.authVector.end(), a.authVector.begin(), 0.0));
    return product / (norm0 * norm1);
}
