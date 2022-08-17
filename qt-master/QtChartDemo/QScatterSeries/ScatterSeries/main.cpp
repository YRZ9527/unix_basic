#include "widget.h"
#include <QApplication>
#include <vector>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
//    std::vector<int> tmp;
//    tmp.push_back(88);
//    for(auto i : tmp)
//    {
//        QDebug()<<",hll";
//    }


    return a.exec();
}
