#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include "sprawmodel.h"

class Processor : public QObject
{
public:
    Processor(const QString filename);
    virtual int Import() = 0;
    virtual int ParseData() = 0;

    QString input_file();
    int spraw_count() const;
    SprawModel spraw(int index);

protected:       
    void debug(const QString line, QChar symb);

    QString input_file_;    
    QList<SprawModel> spraw_list_;
};

#endif // PROCESSOR_H
