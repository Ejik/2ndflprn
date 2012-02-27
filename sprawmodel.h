#ifndef SPRAWMODEL_H
#define SPRAWMODEL_H

#include <QStringList>
 #include <QMap>

class SprawModel
{
public:
    SprawModel();
    void Append(int page_num, const QString value);
    void SplitPages();
    int PagesCount() const;
    QStringList page1();
    QStringList page2();
    QString GetParam(const QString param_name);
    QList<QString> GetParamKeys();
    void SetParam(const QString paramname, const QString value);

    QList<QStringList> tbl(int tbl_index);
    void set_tbl(int tbl_index, const QList<QStringList> value);
    QStringList para4();
    void set_para4(QStringList value);
    QList<QStringList> para5(int para_num);
    void set_para5(int para_num, const QList<QStringList> value);
    QMap<int, QStringList> pages();

private:
    QMap<int, QStringList> pages_;
    QMap<int, QList<QStringList> > tables_;
    QMap<int, QList<QStringList> > para5_;
    QStringList page1_;
    QStringList page2_;
    QMap<QString, QString> params_;
    QList<QStringList> tbl1_;
    QList<QStringList> tbl2_;
    QStringList para4_;
    QList<QStringList> para5_1_;
    QList<QStringList> para5_2_;
};

#endif // SPRAWMODEL_H
