#include "AnagramTree.h"
#include <fstream>
#include <unordered_map>

#define QUIT 9
#define NUM_MAPS 12
#define SPECIAL 11
#define INDEX(len) (((len < 4) || (len > 14)) ? (SPECIAL) : (len - 3))
#define BREAK   cout << "\n\n\n";

struct U_MAP
{
    unordered_map<string,AnagramTree> mymap;
};

void Read(int &count, istream &input, U_MAP maps[]);
void printMap3(U_MAP &map, int search_size, string str);
void printMap(U_MAP &map, int search_size);
void printMap2(U_MAP &map, int search_size, string str);
void printMap4(U_MAP &map, string str);
void quickSort(string &word, int start, int end);
int partition(string &word, int first, int last);

int main(int argc, char * argv[])
{
    ifstream fin;
    ofstream fout;

    U_MAP maps [NUM_MAPS];

    string w, bag, str;
    int opt = 0, index, search_size, count = 0;
    char search_char;

    if(argc == 3)
    {
        fin.open(argv[1]);
        fout.open(argv[2]);
    }
    else if(argc == 2)
    {
        fin.open(argv[1]);
    }
    else
    {
        fin.open("words_big.txt");
        //fin.open("en-US.dic");
        fout.open("words.txt");
    }

    Read(count,fin,maps);

    while(opt != QUIT)
    {
        cout << "Select an option:\n"
             << "1. Number of words\n"
             << "2. Add new words\n"
             << "3. View all words\n"
             << "4. View words with specific size\n"
             << "5. View words with specific size & starting letter\n"
             << "6. View words with specific size, containing letter(s)\n"
             << "7. View anagrams of the word\n"
             << "8. Find a Word\n"
             << "9. Exit\n" << endl;

        cout << "Select an option (1 - 9): " << flush;
        cin >> opt;
        switch(opt)
        {
        case 1:
            cout << count << endl;
            break;
        case 4:
            cout << "Enter the desired size: " << flush;
            cin >> search_size;
            BREAK
            printMap(maps[INDEX(search_size)],search_size);
            BREAK
            break;
        case 5:
            cout << "Enter the desired size: " << flush;
            cin >> search_size;
            cout << "Enter the starting letter(s): " << flush;
            cin >> str;
            BREAK
            printMap2(maps[INDEX(search_size)],search_size,str);
            BREAK
            break;
        case 6:
            cout << "Enter the desired size: " << flush;
            cin >> search_size;
            cout << "Enter the required character(s): " << flush;
            cin >> str;
            BREAK
            printMap3(maps[INDEX(search_size)],search_size,str);
            BREAK
            break;
        case 7:
            cout << "Enter the anagram to search: " << flush;
            cin >> str;
            BREAK
            quickSort(str,0,str.length()-1);
            printMap4(maps[INDEX(str.length())],str);
            BREAK
            break;
        case 8:
            cout << "Enter the word you wish to find: " << flush;
            cin >> str;
            BREAK
            cout << maps[INDEX(str.length())].mymap[str].getWord(str);
            BREAK

        }
    }


    return 0;
}

void Read(int &count,istream &input, U_MAP maps[])
{
    string word;

    while(input)
    {
        input >> word;
        maps[INDEX(word.length())].mymap[word].add(word);
        count++;
    }
}


void printMap3(U_MAP &map, int search_size, string str)
{
    for(auto it = map.mymap.begin(); it != map.mymap.end(); ++it)
    {
        it->second.printThree(cout, it->second.getHead(),search_size,str);
    }
}

void printMap2(U_MAP & map, int search_size, string str)
{
    for(auto it = map.mymap.begin(); it != map.mymap.end(); ++it)
    {
        it->second.printTwo(cout, it->second.getHead(),search_size,str);
    }
}

void printMap(U_MAP &map, int search_size)
{
    for(auto it = map.mymap.begin(); it != map.mymap.end(); ++it)
    {
        it->second.printOne(cout, it->second.getHead(),search_size);
    }
}

void printMap4(U_MAP & map, string str)
{
    for(auto it = map.mymap.begin(); it != map.mymap.end(); ++it)
    {
        it->second.printFour(cout, it->second.getHead(),str);
    }
}

int partition(string &word, int first, int last)
{
    char ch = word[last];
    while(first < last)
    {
        while(word[first] < ch)
            first++;
        while(word[last] > ch)
            last--;
        if (word[first] == word[last])
            first++;
        else if (first < last){
            char temp = word[first];
            word[first] = word[last];
            word[last] = temp;
        }
    }

    return last;
}

void quickSort(string &word, int start, int end)
{
    if(start >= end) return;
    int mid = partition(word, start, end);
    quickSort(word, start, mid - 1);
    quickSort(word, mid + 1, end);
}
