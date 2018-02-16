//AnagramTree.h
//
// Parfait Mwamba
// 11/07/2017
//
// Binary Search Tree class that does NOT
// allow duplicate data. Data in this program will be
// words from a file that will be sorted by length
//

#ifndef AnagramTree_H
#define AnagramTree_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class AnagramTree
{
private:
    struct Node
    {
        string word, lbag;
        int wlength;
        Node * left;
        Node * right;
    } *root;

    int count;

    int partition(string &str, int first, int last);
    void quickSort(string &str, int start, int end);
    bool removeHelper(Node *c, Node * r, string &w);
    string minValue(Node * r);
public:
    AnagramTree();
    AnagramTree(string &w, string &bag, int &len);
    ~AnagramTree();
    void clear(Node * &r);

    void add(string &w);
    void addIter(string &w, string &bag, int &len);

    bool rem(string &w);
    bool find(string &w);
    string getWord(string &w) const;

    //Print all words of a certain size s
    void printOne(ostream & out, Node * r, int &s);

    //Print all words of a certain size s, starting with letter(s) x
    void printTwo(ostream & out, Node * r, int &s, string &x);

    //Print all words of size s, containing each character in string str
    void printThree(ostream & out, Node * r, int &s, string &str);

    void printFour(ostream & out, Node * r, string &str);

    Node * getHead(){return root;}
    int getCount(){return count;}

    void inOrder(ostream& out, Node * r);

    friend istream& operator >> (istream & in, AnagramTree & obj);
    friend ostream& operator << (ostream& out, AnagramTree & obj);


};



#endif // AnagramTree_H
