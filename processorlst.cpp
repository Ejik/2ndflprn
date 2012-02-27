#include <QDebug>
#include <QFile>
#include "common.h"
#include "tablemodel.h"
#include "processorlst.h"

ProcessorLST::ProcessorLST(const QString filename) : Processor(filename) {

}

// Импортируем данные в 2 страницы
int ProcessorLST::Import() {

    QFile file(input_file_);

    if (!file.open(QFile::ReadOnly))
        return -1;

    QTextStream in(&file);
    in.setCodec("IBM 866");

    SprawModel *new_spraw = new SprawModel();
    int page_index = 1;

    while (!in.atEnd()) {

        QString utf_line = in.readLine();

        if (utf_line.contains(kPageBreak)) {

            utf_line = in.readLine();
            if (utf_line.contains(UTFtoUnicode("Страница "))) {

                page_index++;

            } else {

                spraw_list_.append(*new_spraw);
                new_spraw = new SprawModel();
                page_index = 1;
            }

        }

        new_spraw->Append(page_index, utf_line);
    }

    spraw_list_.append(*new_spraw);

    return 0;
}

// Получаем данные из страниц с текстом
int ProcessorLST::ParseData() {

    QMutableListIterator<SprawModel> i(spraw_list_);

    SprawModel *current_model;
    while (i.hasNext()) {

        current_model = &i.next();

        QStringList page1 = current_model->pages().value(1);

        QString priznak = GetValue(page1, "признак", 3);
        QString ifns = GetValue(page1, "в ИФНС", 4);        
        QString title = GetTitle(page1);
        QString innkpp = GetValue(page1, "ИНН/КПП организации", 22);
        QString name = GetValue(page1, "Наименование организации", 60);
        QString okato = GetValue(page1, "Код ОКАТО", 15);
        QString tel = GetValue(page1, "Телефон", 15);
        QString inn = GetValue(page1, "2.1. ИНН", 15);
        QMap<int, QString> tbn_fio = GetTBNFIO(page1);
        QString status = GetValue(page1, "Статус налогоплательщика", 4);
        QString datarojdeniya = GetValue(page1, "Дата рождения", 15);
        QString kodstrani = GetValue(page1, "Гражданство(код)", 5);
        QString koddocumenta = GetValue(page1, "Код док-та, удост. личность -", 4);
        QString seriyanomer = GetValue(page1, "Серия, N документа", 15);
        QString index = GetValue(page1, "Почтовый индекс", 6);
        QString kodregiona = GetValue(page1, "Код региона", 3);
        QString raion = GetValue(page1, "Район", 30);
        QString gorod = GetValue(page1, "Город", 50);
        QString naspunkt = GetValue(page1, "Населенный пункт", 50);
        QString ulica = GetValue(page1, "Улица", 50);
        QString dom = GetValue(page1, " Дом", 5);
        QString korpus = GetValue(page1, " Корпус", 2);
        QString kvartira = GetValue(page1, "Квартира", 5);
        QString kodstraniprojivaniya = "";
        QString adresvstraneprojivaniya = "";
        QString stavka1 = GetValue(page1, "ОБЛАГАЕМЫЕ НАЛОГОМ ПО СТАВКЕ", 5);        
        QList<QStringList> tbl1 = GetTable(page1);
        QStringList para4 = GetPara4(page1);
        QString nomeruvedomleniya = GetValue(page1, "имущественный налог.вычет", 8);
        QString datauvedomleniya = GetValue(page1, "4.3. Дата выдачи", 15);
        QString kodifns = GetValue(page1, "Код ИФНС, выдавшей уведомление", 5);
        QString para5_text1 = GetValue(page1, "суммы дохода и налога по итогам налогового периода", 17);
        QList<QStringList> para5_1 = GetPara5(page1);
        QString agentdoljnost = GetValue(page1, "Налоговый агент", 23);
        QString agentfio = GetValue(page1, "Налоговый агент", 73);
        agentfio = agentfio.split("/")[1].trimmed();


        current_model->SetParam(UTFtoUnicode("{{ПРИЗНАК}}"), priznak);
        current_model->SetParam(UTFtoUnicode("{{ИФНС}}"), ifns);
        current_model->SetParam(UTFtoUnicode("{{ЗАГОЛОВОК}}"), title);
        current_model->SetParam(UTFtoUnicode("{{ИННКПП}}"), innkpp);
        current_model->SetParam(UTFtoUnicode("{{НАИМЕНОВАНИЕ}}"), name);
        current_model->SetParam(UTFtoUnicode("{{ОКАТО}}"), okato);
        current_model->SetParam(UTFtoUnicode("{{ТЕЛЕФОН}}"), tel);
        current_model->SetParam(UTFtoUnicode("{{ИНН}}"), inn);
        current_model->SetParam(UTFtoUnicode("{{ФИО}}"), tbn_fio[1]);
        current_model->SetParam(UTFtoUnicode("{{ТБН}}"), tbn_fio[2]);
        current_model->SetParam(UTFtoUnicode("{{СТАТУСНАЛОГОПЛАТЕЛЬЩИКА}}"), status);
        current_model->SetParam(UTFtoUnicode("{{ДАТАРОЖДЕНИЯ}}"), datarojdeniya);
        current_model->SetParam(UTFtoUnicode("{{КОДСТРАНЫ}}"), kodstrani);
        current_model->SetParam(UTFtoUnicode("{{КОДДОКУМЕНТА}}"), koddocumenta);
        current_model->SetParam(UTFtoUnicode("{{СЕРИЯНОМЕР}}"), seriyanomer);
        current_model->SetParam(UTFtoUnicode("{{ПОЧТОВЫЙИНДЕКС}}"), index);
        current_model->SetParam(UTFtoUnicode("{{КОДРЕГИОНА}}"), kodregiona);
        current_model->SetParam(UTFtoUnicode("{{РАЙОН}}"), raion);
        current_model->SetParam(UTFtoUnicode("{{ГОРОД}}"), gorod);
        current_model->SetParam(UTFtoUnicode("{{НАСЕЛЕННЫЙПУНКТ}}"), naspunkt);
        current_model->SetParam(UTFtoUnicode("{{УЛИЦА}}"), ulica);
        current_model->SetParam(UTFtoUnicode("{{ДОМ}}"), dom);
        current_model->SetParam(UTFtoUnicode("{{КОРПУС}}"), korpus);
        current_model->SetParam(UTFtoUnicode("{{КВАРТИРА}}"), kvartira);
        current_model->SetParam(UTFtoUnicode("{{КОДСТРАНЫПРОЖИВАНИЯ}}"), kodstraniprojivaniya);
        current_model->SetParam(UTFtoUnicode("{{АДРЕСВСТРАНЕПРОЖИВАНИЯ}}"), adresvstraneprojivaniya);
        current_model->SetParam(UTFtoUnicode("{{СТАВКА1}}"), stavka1);
        current_model->SetParam(UTFtoUnicode("{{ТАБЛИЦА1}}"), "");
        current_model->SetParam(UTFtoUnicode("{{ПУНКТ4.1}}"), "");
        current_model->SetParam(UTFtoUnicode("{{НОМЕРУВЕДОМЛЕНИЯ}}"), nomeruvedomleniya);
        current_model->SetParam(UTFtoUnicode("{{ДАТАУВЕДОМЛЕНИЯ}}"), datauvedomleniya);
        current_model->SetParam(UTFtoUnicode("{{КОДИФНС}}"), kodifns);
        current_model->SetParam(UTFtoUnicode("{{ПУНКТ5СТРАНИЦА1}}"), para5_text1);
        current_model->SetParam(UTFtoUnicode("{{ПУНКТЫ5СТРАНИЦА1}}"), "");
        current_model->SetParam(UTFtoUnicode("{{НАЛОГОВЫЙАГЕНТДОЛЖНОСТЬ}}"), agentdoljnost);
        current_model->SetParam(UTFtoUnicode("{{НАЛОГОВЫЙАГЕНТФИО}}"), agentfio);

        current_model->set_tbl(1, tbl1);

        current_model->set_para4(para4);
        current_model->set_para5(1, para5_1);

        // Обрабатываем остальные страницы
        for (int j = 0; j < current_model->PagesCount() - 1; j++) {

            int page_index = j + 2;
            QStringList page = current_model->pages().value(page_index);

            QString stavka = GetValue(page, "ОБЛАГАЕМЫЕ НАЛОГОМ ПО СТАВКЕ", 5);
            QList<QStringList> tbl = GetTable(page);
            QString para5_text = GetValue(page, "суммы дохода и налога по итогам налогового периода", 17);
            QList<QStringList> para5 = GetPara5(page);

            current_model->SetParam(UTFtoUnicode("{{ТАБЛИЦА" + QString::number(page_index) + "}}"), "");
            current_model->SetParam(UTFtoUnicode("{{ПУНКТ5СТРАНИЦА" + QString::number(page_index) + "}}"), para5_text);
            current_model->SetParam(UTFtoUnicode("{{ПУНКТЫ5СТРАНИЦА" + QString::number(page_index) + "}}"), "");
            current_model->SetParam(UTFtoUnicode("{{СТАВКА" + QString::number(page_index) + "}}"), stavka);
            current_model->SetParam(UTFtoUnicode("{{НОМЕРСТРАНИЦЫ" + QString::number(page_index) + "}}"), UTFtoUnicode("Страница №" + QString::number(page_index)));

            current_model->set_tbl(page_index, tbl);
            current_model->set_para5(page_index, para5);
        }

    }


    return 0;
}

// Методы парзинга уникальных данных
QString ProcessorLST::GetTitle(QStringList pagedata) {

    QString result = "";
    const QString value = UTFtoUnicode("СПРАВКА О ДОХОДАХ ФИЗИЧЕСКОГО ЛИЦА");

    QStringListIterator i(pagedata);
    QString line;

    while (i.hasNext()) {
        line = i.next();

        int position =  line.indexOf(value, 0, Qt::CaseInsensitive);
        if (position != -1) {

            line = i.next();

            QStringList title_buffer;
            title_buffer <<  line;

            QString year = GetValue(title_buffer, " за", 5);
            QString number = GetValue(title_buffer, " N", 5);
            QString date = GetValue(title_buffer, " от", 10);

            result = UTFtoUnicode("СПРАВКА О ДОХОДАХ ФИЗИЧЕСКОГО ЛИЦА за " + year + " год № " + number +
                            " от " + date);
            qDebug() << "title " << result;

            return result;

        }
    }

    return result;

}

QString ProcessorLST::GetValue(QStringList pagedata, const QString valuename, int len) {

    QString result = "";
    const QString value = UTFtoUnicode(valuename);
    QStringListIterator i(pagedata);
    QString line;
    while (i.hasNext()) {
        line = i.next();
        int position =  line.indexOf(value, 0);
        if (position != -1) {

            result = line.mid(position + value.length() + 1 , len).trimmed();

            return result;
        }
    }

    return result;
}

QMap<int, QString> ProcessorLST::GetTBNFIO(QStringList pagedata) {

    QMap<int, QString> result;
    const QString fio = UTFtoUnicode("Фамилия, Имя, Отчество");
    const QString tbn = UTFtoUnicode("ТБН");

    QStringListIterator i(pagedata);
    QString line;

    while (i.hasNext()) {
        line = i.next();

        int position =  line.indexOf(fio, 0, Qt::CaseInsensitive);
        if (position != -1) {

            line = i.next();

            result[1] = line.mid(1, 70);

            qDebug() << "fio " << result[1];
        }
    }

    i.toFront();
    while (i.hasNext()) {
        line = i.next();

        int position =  line.indexOf(tbn, 0, Qt::CaseInsensitive);
        if (position != -1) {

            line = i.next();

            result[2] = line.mid(position - 1, 4);

            qDebug() << "tbn " << result[2];
        }
    }

    return result;


}

QList<QStringList> ProcessorLST::GetTable(QStringList pagedata) {

    QList<QStringList> result;

    const QChar startsym(9484);
    const QChar endsym(0x2514);
    const QChar separator(0x2502);

    QString line;

    QStringListIterator i(pagedata);
    while (i.hasNext()) {

        line = i.next();

        if(line[0] == startsym) {

            // пропускаем заголовок
            i.next();
            i.next();
            i.next();

            line = i.next();

            while (line[0] != endsym) {

                result << line.split(separator);
                line = i.next();

            }
            break;
        }
    }

    return result;
}

QStringList ProcessorLST::GetPara4(QStringList pagedata) {

    QStringList result;
    QString para4_1 = UTFtoUnicode("Суммы предоставленных налогоплательщику налоговых вычетов");

    QStringListIterator i(pagedata);
    QString line;

    while (i.hasNext()) {
        line = i.next();

        int position =  line.indexOf(para4_1, 0, Qt::CaseInsensitive);
        if (position != -1) {

            i.next();
            line = i.next();

            QStringList list1 = line.split(" ");
            QMutableStringListIterator it(list1);

            while (it.hasNext()) {

                if (it.next().compare("") == 0)
                    it.remove();
            }

            result << list1;

            break;
        }
    }

    result.insert(0, "");
    while (result.count() < 9)
        result.append("");

    return result;

}

QList<QStringList> ProcessorLST::GetPara5(QStringList pagedata) {

    QList<QStringList> result;

    const QChar separator(0x2502);
    const QString para5 = UTFtoUnicode("суммы дохода и налога по итогам налогового периода");

    QString line;

    QStringListIterator i(pagedata);
    while (i.hasNext()) {

        line = i.next();

        if (line.contains(para5)) {
            i.next();
            line = i.next();

            while (!line.isEmpty()) {

                QStringList list1 = line.split(separator);
                result << list1;

                i.next();
                line = i.next();

            }
            break;

        }

    }

    return result;


}
