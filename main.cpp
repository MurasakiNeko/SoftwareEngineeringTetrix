#include <QtGui>
#include <QApplication>
#include "tetrixwindow.h"
#include "tetrixwindowZZY.h"
#include "tetrixwindowLKT.h"
#include "tetrixwindowWWK.h"
#include "tetrixwindowYCF.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TetrixWindow window;
	//TetrixWindowZZY window;
	//TetrixWindowLKT window;
	//TetrixWindowWWK window;
	//TetrixWindowYCF window;
    window.show();
    return a.exec();
}
