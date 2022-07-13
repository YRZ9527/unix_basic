#include"iostream"
using namespace std;

class Tree{
    int height;
public:
    Tree(int height);
    ~Tree();
    void grow(int years);
    void printsize();
};
Tree::Tree(int initialHeight)
{
    height = initialHeight;
}
Tree::~Tree() {
    cout <<"Tree destructor" << endl;
    printsize();
}


void Tree::grow(int years) {
    height += years;
}


void Tree::printsize() {
    cout<<"size ="<<height<<endl;

}

int main() {
    cout<<"before constructor"<< endl;
    Tree t(12);
    cout<<"after constructor"<< endl;
    t.printsize();
    t.grow(4);
    cout<<"before closing brace"<<endl;
    cout<<"after Tree creation"<<endl;
    
}