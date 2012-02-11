//#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QtGui/QApplication>
#include <QtGui/QFileDialog>
#include <QTextCodec>
#include <QMessageBox>
#include "importer.h"
#include "exporter.h"
#include "processorlst.h"


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));

    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    QString filename = QFileDialog::getOpenFileName(NULL, QObject::tr("Выберите файл справки 2НДФЛ"), "", QObject::tr("LST (2ndfl*.lst);;Файлы справок 2-НДФЛ (*.xml)"));
    // QString filename = "c:\\projects\\other\\2ndflprn-build-desktop\\2NDFL_02.LST";
    //QString filename = "c:\\qt\\projects\\2NDFL_02.LST";

    if (!filename.isEmpty())
    {
        Processor *processor;
        if (filename.contains(".lst", Qt::CaseInsensitive)) {

            processor = new ProcessorLST(filename);

        } else {
            return 1;
        }

        processor->Import();
        processor->ParseData();

//        Importer importer(filename);
//        importer.parse();

        Exporter exporter(processor);
        exporter.export_to_html();

        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Формирование справок завершено."));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();

        delete processor;
    }
    //return a.exec();

    return 0;
}
