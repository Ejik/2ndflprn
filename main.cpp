//#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QtGui/QFileDialog>
#include <QTextCodec>
#include "importer.h"
#include "exporter.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("WINDOWS-1251"));

    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    QString filename = QFileDialog::getOpenFileName(NULL,
                                                    QObject::tr("�������� ���� ������� 2����"), "", QObject::tr("LST (2ndfl*.lst)"));

    Importer importer(filename);
    importer.parse();

    Exporter exporter(&importer);
    exporter.exportToExcel();

    //return a.exec();
}
