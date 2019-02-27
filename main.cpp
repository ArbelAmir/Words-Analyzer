#include "wordsAnalyzer.h"

/** main function */
int main(int argc, char *argv[])
{
    vector<string> authFilePaths(argv + 1, argv + argc);
    if (!(ends_with(authFilePaths[0], "frequent_words.txt") and ends_with(authFilePaths[1], "unknown.txt") and
          (argc > 3)))
    {
        cerr << "invalide input." << endl;
        exit(EXIT_FAILURE);
    }

    wordsAnalyzer analyzer(authFilePaths);
    analyzer.analyze();

    return 0;
}

