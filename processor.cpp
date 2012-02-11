#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include "processor.h"

Processor::Processor(const QString filename)
{
    input_file_ = filename;
}

void Processor::debug(const QString line, QChar symb)
{
    QFile file1("1251.txt");
    if (!file1.open(QFile::WriteOnly | QFile::Truncate))
        return;
    QTextStream out(&file1);
    out.setCodec("UTF-8");
    out << "line0 " << line[0].unicode() << " " << symb.unicode();
    file1.close();
}

QString Processor::input_file() {

    return input_file_;
\
}

int Processor::spraw_count() const {

    return spraw_list_.count();

}

SprawModel Processor::spraw(int index) {

    return spraw_list_.at(index);

}
