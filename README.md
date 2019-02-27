# words-analyzer
A C ++ implementation of an engine that parses text files representing literary works by well-known authors and determines the adaptation of a literary work by an unknown author to one of the authors.

This is done by vectorizing frequent words so that the number of appearances of each word in each file is represented by a coordinate in the vector.

A simple calculation of the angle between representative vectors is then performed for each word file and the file with the smallest angle determines the writer
