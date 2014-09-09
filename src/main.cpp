#include "ide.h"

int main(int argc, char *argv[])
{
    QApplication qtApp(argc, argv);
    IDE ide;
    ide.show();
    return qtApp.exec();
}
