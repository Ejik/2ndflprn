//#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QtGui/QFileDialog>
#include "importer.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    QString filename = QFileDialog::getOpenFileName(NULL,
                                                    QObject::tr("�������� ���� ������� 2����"), "", QObject::tr("LST (2ndfl*.lst)"));

    Importer importer(filename);



    return a.exec();
}
