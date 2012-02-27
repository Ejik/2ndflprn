#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QTextCodec>

static const QChar kPageBreak(0x0C);

static const QString kHead = ":/sections/res/head_20101117.txt";
static const QString kBody = ":/sections/res/body_20111206.txt";
static const QString kBodyPage2 = ":/sections/res/body_page2_20111206.txt";

//static const QString k_body = "c:\\qt\\projects\\2ndflprn\\res\\body_20111206.txt";
//static const QString k_body_page2 = "c:\\Projects\\other\\2ndflprn\\res\\body_page2_20111206.txt";

static QString OEMtoUnicode(const QString string)
{
    QTextCodec *codec = QTextCodec::codecForName("IBM 866");
    return codec->toUnicode(string.toLocal8Bit());
}

static QString WINtoUnicode(const QString string)
{
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    return codec->toUnicode(string.toAscii());
}

static QString UTFtoUnicode(const QString string)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    return codec->toUnicode(string.toAscii());
}

#endif // COMMON_H
