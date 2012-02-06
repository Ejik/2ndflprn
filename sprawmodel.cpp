#include "sprawmodel.h"

SprawModel::SprawModel() {

}

void SprawModel::Append(int page_num, const QString value) {

    if (page_num == 1) {
        page1_.append(value);
    } else if (page_num == 2) {
        page2_.append(value);
    }
}

void SprawModel::SplitPages() {

    QChar pagebreak(0x0C);    

    QMutableStringListIterator i(page1_);
    QString line;

    while (i.hasNext() ) {

        line = i.next();
        if (line[0] == pagebreak) {

            while (i.hasNext()) {

                line = i.next();
                page2_ << line;

                i.remove();
            }
        }
    }
}

int SprawModel::PageCount() const {

    return page2_.count() > 0 ? 2 : 1 ;
}

QStringList SprawModel::page1() {

    return page1_;

}

QStringList SprawModel::page2() {

    return page2_;

}

QString SprawModel::GetParam(const QString param_name) {

    return params_[param_name];

}

QList<QString> SprawModel::GetParamKeys() {

    return params_.keys();
}

void SprawModel::SetParam(const QString paramname, const QString value) {

    params_[paramname] = value;
}

QList<QStringList> SprawModel::tbl(int tbl_num) {

    if (tbl_num == 1)
        return tbl1_;

    return tbl2_;
}

void SprawModel::set_tbl(int tbl_num, const QList<QStringList> value) {

    if (tbl_num == 1)
        tbl1_ = value;
    else
        tbl2_ = value;
}

QStringList SprawModel::para4() {

    return para4_;
}

void SprawModel::set_para4(QStringList value) {

    para4_ = value;
}

QList<QStringList> SprawModel::para5(int para_num) {

    if (para_num == 1)
        return para5_1_;

    return para5_2_;
}

void SprawModel::set_para5(int para_num, const QList<QStringList> value) {

    if (para_num == 1)
        para5_1_ = value;
    else
        para5_2_ = value;

}
