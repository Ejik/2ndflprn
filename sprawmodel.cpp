#include "common.h"
#include "sprawmodel.h"

SprawModel::SprawModel() {

}

void SprawModel::Append(int page_num, const QString value) {

    pages_[page_num].append(value);

}

void SprawModel::SplitPages() {   

    QMutableStringListIterator i(page1_);
    QString line;

    while (i.hasNext() ) {

        line = i.next();
        if (line[0] == kPageBreak) {

            while (i.hasNext()) {

                line = i.next();
                page2_ << line;

                i.remove();
            }
        }
    }
}

int SprawModel::PagesCount() const {

    return pages_.count();

}

QStringList SprawModel::page1() {

    return page1_;

}

QStringList SprawModel::page2() {

    return page2_;

}

QString SprawModel::GetParam(const QString param_name) {

    return params_.value(param_name);

}
void SprawModel::SetParam(const QString param_name, const QString value) {

    params_[param_name] = value;
}

QList<QString> SprawModel::GetParamKeys() {

    return params_.keys();

}

QList<QStringList> SprawModel::tbl(int tbl_index) {

    return tables_.value(tbl_index);

}

void SprawModel::set_tbl(int tbl_index, const QList<QStringList> value) {

    tables_[tbl_index] = value;

}

QStringList SprawModel::para4() {

    return para4_;
}

void SprawModel::set_para4(QStringList value) {

    para4_ = value;
}

QList<QStringList> SprawModel::para5(int para_num) {

    return para5_.value(para_num);
}

void SprawModel::set_para5(int para_num, const QList<QStringList> value) {

    para5_[para_num] = value;

}

QMap<int, QStringList> SprawModel::pages() {

    return pages_;

}
