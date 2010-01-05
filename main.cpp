//#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QtGui/QFileDialog>
#include <QTextCodec>
#include <QMessageBox>
#include "importer.h"
#include "exporter.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("WINDOWS-1251"));

    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    QString filename = QFileDialog::getOpenFileName(NULL,
                                                    QObject::tr("Выберите файл справки 2НДФЛ"), "", QObject::tr("LST (2ndfl*.lst)"));
    if (filename != "")
    {
        Importer importer(filename);
        importer.parse();

        Exporter exporter(&importer);
        exporter.exportToExcel();

        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Формирование справок завершено."));
        msgBox.exec();
    }
    //return a.exec();

    return 0;
}
