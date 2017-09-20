#include <iostream>
#include "CSVFile.h"
#include "dirent.h"

using namespace std;

void printParameterHints(){

    cout <<"=========================================================================================================\n"
            "====================================Find Isomorphic Trees==========================================\n\n"
            "Version: June 15th, 2016\n"
            "Description: Find isomorphic value trees in current directory with a specific tree.\n"
            "Notes: all TreeID (the first column) in tree files must be pure text format instead of scientific notation.\n"
            "Usage: FindIsomorphy [Option Option_parameter] ...\n\n"
            "EXAMPLES:\n"
            "FindIsomorphy -F basicTreeFilename.csv\n\n"

            "OPTIONS:\n"
            "-F basic tree filename, with which program will compare all other files in current dir;\n"
            "=========================================================================================================\n";

}

int main(int argc, char** argv) {

    if (1 != argc % 2 || argc != 3) {
        printParameterHints();
        return -1;
    }

    printf("Notes: all TreeID (the first column) in tree files must be text format instead of scientific notation.\n");

    //Check input arguments
    std::string basicTreeFile;
    for (int i = 1; i < argc - 1; i = i + 2) {
        std::string argLeader(*(argv + i));

        if (0 == argLeader.compare("-F") || 0 == argLeader.compare("-f")) {
            basicTreeFile = std::string(*(argv + i + 1));
        }
        else {
            printParameterHints();
            return -2;
        }
    }
    CSVFile csvFile;
    //read basic tree file;
    Tree basicTree;
    int readFileResult = csvFile.readTreeFile(basicTreeFile,&basicTree );
    if (0 != readFileResult ) return readFileResult;

    //read other tree file in directory;
    std::vector<std::string> fileVector;
    std::vector<std::string> isomorphyVector;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (".")) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            std::string file(ent->d_name);
            if (0 == basicTreeFile.compare(file) || file.size() <= 4 ) continue;
            if (0 != file.substr(file.length()-4,4).compare(".csv")) continue;
            fileVector.push_back(file);
        }
        closedir (dir);
    }

    int const fileNum = fileVector.size();
    if (0 == fileNum) {
        printf("Can not find tree files in current directory. Exit.\n");
        return 0;
    }
    else {
        printf("Information: total read %d csv files.\n", fileNum);

    }
    //compare
    int treeFileNum = 0;
    for (int i =0; i<fileNum; ++i){
        Tree otherTree;
        readFileResult = csvFile.readTreeFile(fileVector.at(i),&otherTree);
        if (0 != readFileResult ) continue;
        if (basicTree.isIsomorphic(&otherTree)) {
           isomorphyVector.push_back(fileVector.at(i));
        }
        ++treeFileNum;
    }

    //print result
    printf("\n============================================================\n");
    printf("The below trees are isomorphic with %s : \n",basicTreeFile.c_str());
    printf("=============================================================\n");
    int isomorphicNum = isomorphyVector.size();
    for (int i=0;i< isomorphicNum;++i){
        printf("%s\n", isomorphyVector.at(i).c_str());
    }
    printf("========Total %d isomorphic trees from %d tree files.==========\n", isomorphicNum, treeFileNum);

}
