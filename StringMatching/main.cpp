#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <ctime>
using namespace std;
vector<int> trivial(string text, string pattern);
vector<int> rabinKarpSearch(string text, string pattern, int primeNumber);
int main(int argc, char* argv[])
{
    std::cout << "Hello, World!" << std::endl;
    fstream input;
    char* temp;
    input.open(argv[1], ios::in);


    if(!input)
    {
        cout << "Not opened";
    }
    ifstream ifs(argv[1]);
    string text( (std::istreambuf_iterator<char>(ifs) ),
                 (std::istreambuf_iterator<char>()    ) );
    std::clock_t start;
    start = std::clock();
    vector<int> triv = trivial(text, "the");
    std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
    char* cstr = new char[text.length() + 1];
    strcpy(cstr, text.c_str());
    char* a = "the";


    start = std::clock();
    vector<int> RK = rabinKarpSearch(text, "the", 101);
    std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
    cout << "Trivial: " << triv.size() << endl;
    cout << "Rabin-Karp: " << RK.size() << endl;
//    while(!input.eof())
//    {
//        input.getline(temp, 2000);
//    }

    return 0;
}

vector<int> trivial(string text, string pattern)
{
    vector<int> indexOfMatches;
    int patLength = pattern.length();
    for(int i= 0; i < text.length() - patLength + 1; i++)
    {
        if(text.substr(i, patLength) == pattern)
        {
            cout << "Poggers" << endl;
            indexOfMatches.push_back(i);
        }
    }

    return indexOfMatches;
}

vector<int> rabinKarpSearch(string text, string pattern, int primeNumber)
{
    vector<int> patternMatches;
    int chars = 256;
    int pHashVal = 0;
    int subStringHashVal = 0;
    int hash = 1;

    for (int i = 0; i < pattern.length() -1; i++)
    {
        hash = (hash *chars) % primeNumber;
    }

    for(int i = 0; i < pattern.length(); i++)
    {
        pHashVal = (chars * pHashVal + pattern.at(i)) % primeNumber;//determing pattern hash val
        subStringHashVal = (chars * subStringHashVal +  text.at(i)) % primeNumber; //d/etermine prime read hash val
    }

    for(int i = 0; i <= text.length() - pattern.length(); i++)
    {
        if(pHashVal == subStringHashVal)
        {
            if (text.substr(i, pattern.length()) == pattern)
            {
                patternMatches.push_back(i);
            }
        }

        if(i < text.length() - pattern.length())
        {
            subStringHashVal = ((chars * (subStringHashVal - text.at(i) * hash) + text.at(i + pattern.length()) )% primeNumber);

            if(subStringHashVal < 0)
            {
                subStringHashVal += primeNumber;
            }
        }
    }

    return patternMatches;
}
