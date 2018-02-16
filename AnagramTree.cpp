
#include "AnagramTree.h"

AnagramTree::AnagramTree()
{
    root = nullptr;
    this->count = 0;
}

AnagramTree::AnagramTree(string &w, string &bag, int &len)
{
    root = nullptr;
    count = 0;
    addIter(w,bag,len);
}

AnagramTree::~AnagramTree()
{
    clear(root);
}

void AnagramTree::clear(Node * &r)
{
    if(r == nullptr) return;
    clear(r->left);
    clear(r->right);
    delete r;
    count--;
    r = nullptr;
}

int AnagramTree::partition(string &word, int first, int last)
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

void AnagramTree::quickSort(string &word, int start, int end)
{
    if(start >= end) return;
    int mid = partition(word, start, end);
    quickSort(word, start, mid - 1);
    quickSort(word, mid + 1, end);
}

void AnagramTree::add(string &w)
{
    string bag = w;
    int len = w.length();
    quickSort(bag,0,len - 1);
    addIter(w,bag,len);
}

void AnagramTree::addIter(string &w, string &bag, int &len)
{
    if(count == 0)
    {
        Node * t = new Node();
        t->left = t->right = nullptr;
        t->word = w;
        t->lbag = bag;
        t->wlength = len;
        root = t;
        count++;
        return;
    }
    Node * temp = root;
    Node * prev = nullptr;

    while(temp != nullptr)
    {
        prev = temp;
        if(w > temp->word)
            temp = temp->right;
        else if(w < temp->word)
            temp = temp->left;
        else
            return;
    }
    if(w > prev->word)
    {
        prev->right = new Node();
        prev->right->left = prev->right->right = nullptr;
        prev->right->word = w;
        prev->right->lbag = bag;
        prev->right->wlength = len;
    }
    else
    {
        prev->left = new Node();
        prev->left->left = prev->left->right = nullptr;
        prev->left->word = w;
        prev->right->lbag = bag;
        prev->left->wlength = len;
    }
    count++;
}

bool AnagramTree::rem(string &w)
{
    if(!find(w))
        return false;
    return removeHelper(root,root,w);
}

bool AnagramTree::removeHelper(Node * cur, Node * parent, string & w)
{
    if(cur == nullptr)
        return false;
    if(cur->word == w)
    {
        //case 1. No children
        if(cur->left == nullptr && cur->right == nullptr)
        {
            if(parent->left == cur)
                parent->left = nullptr;
            else
                parent->right = nullptr;

            cur->left = cur->right = nullptr;
            delete cur;
            count--;
            return true;
        }

        //case 2. Only one child
        else if(cur->left == nullptr || cur->right == nullptr)
        {
            if(cur == parent->left)
            {
                parent->left = cur->left == nullptr? cur->right : cur->left;
            }
            else
                parent->right = cur->left == nullptr? cur->right : cur->left;

            delete cur;
            count--;
            return true;
        }

        //case 3. Two children
        else
        {
            string t = minValue(cur->right);
            rem(t);
            cur->word = t;
            return true;
        }
    }
    else if(cur->word < w)
        return removeHelper(cur->right,cur,w);
    else
        return removeHelper(cur->left, cur, w);
}

bool AnagramTree::find(string &w)
{
    Node * t = root;

    while(t != nullptr)
    {
        if(t->word == w)
            return true;
        else if(t->word < w)
            t = t->right;
        else if(t->word > w)
            t = t->left;
    }
    return false;
}

string AnagramTree::getWord(string &w) const
{
    Node * t = root;
    while(t != nullptr)
    {
        if(t->word < w)
            t = t->right;
        else if(t->word > w)
            t = t->left;
        else if(t->word == w)
            return t->word;
        else
            return "NO MATCH";
    }
}

string AnagramTree::minValue(Node * r)
{
    if(r->left == nullptr)
        return r->word;
    return minValue(r->left);
}

//Print all words of size s
void AnagramTree::printOne(ostream & out, Node * r, int &s)
{
    if(r == nullptr) return;
    printOne(out,r->left,s);
    if(r->wlength == s) out << r->word << endl;
    printOne(out,r->right,s);
}

//Print all words of size s, starting with letter(s) x
void AnagramTree::printTwo(ostream & out, Node * r, int &s, string &x)
{
    if(r == nullptr) return;
    printTwo(out,r->left,s,x);
    if(r->wlength == s && x.length() <= r->wlength)
    {
        bool match = true;
        for(int i = 0; i < x.length(); i++)
        {
            if(r->word[i] != x[i])
                match = false;
        }
        if(match)
            out << r->word << endl;
    }
    printTwo(out,r->right,s,x);
}

//Print all words of size s, containing each character in string str
void AnagramTree::printThree(ostream & out, Node * r, int &s, string &str)
{
    if(r == nullptr) return;
    printThree(out,r->left,s,str);
    if(r->wlength == s)
    {
        int x = r->word.find(str[0]), i = 1;
        while(x != -1 && i < str.length())
        {
            x = r->word.find(str[i]);
            i++;
        }
        if(x >= 0)
            out << r->word << endl;
    }
    printThree(out,r->right,s,str);
}

void AnagramTree::printFour(ostream & out, Node *r, string &str)
{
    if(r == nullptr) return;
    printFour(out,r->left,str);
    if(r->lbag == str)
        out << r->word << endl;
    printFour(out,r->right,str);
}

void AnagramTree::inOrder(ostream& out, Node * r)
{
    if(r == nullptr) return;

    inOrder(out, r->left);
    out << r->word << endl;
    inOrder(out, r->right);
}

istream& operator >> (istream& in, AnagramTree & obj)
{
    string w;
    in >> w;
    obj.add(w);
    return in;
}

ostream& operator<< (ostream& out, AnagramTree& obj)
{
    obj.inOrder(out,obj.getHead());
    return out;
}

