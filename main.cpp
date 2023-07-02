#include "widget.h"
#include"AI.h"
#include <QApplication>
#include <string>
#include <fstream>
#include <iostream>
#include <QDebug>
#include <ctime>
#include <thread>
#include <AI_small.h>
using namespace std;

string path( "C:\\1.txt") ;

void restart(AI w)
{
    while (1) {
        if(w.chaincount==0){
            fstream file;
            file.open( path, ios::out );
                if (!file)
                {
                    cout << "Failed to create file...\n";
                    //return false;
                }
                file.close();
            //std::this_thread::sleep_for (chrono::seconds(1));
            //w = new AI();
        }
    }

}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    AI w ;

        //thread t(restart, w);
        //t.detach();  

    Widget b;
  //  b.show();
    b.setWindowTitle("对战平台");
    w.setWindowTitle("巨人肩膀");
    w.setFixedSize(750,630);
    w.show();

    return a.exec();
}
