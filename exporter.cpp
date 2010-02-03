#include "exporter.h"
#include <QDir>
#include<QDebug>

Exporter::Exporter(Importer* instance)
{
    data = instance;

}

Exporter::~Exporter()
{
    delete mExcel;
    data = NULL;
}

QString Exporter::replaceExt(const QString name)
{
    QString filename = name;
    filename = filename.remove(filename.length() - 3, 3);
    return  filename + "xls";
}

QVariant Exporter::getSheetName(int docNum, QAxObject *sheets)
{
    if (docNum > 1)
    {
      QAxObject* sheet = sheets->querySubObject("Item(const QVariant&)", QVariant(docNum - 1));
      sheetsNames.append( sheet->property("Name").toString());
    }

    QString name = data->params[QString::number(docNum) + "_TBN"];
    QString newName = name;
    int i = 2;
    while (sheetsNames.contains(newName))
        newName = name + "(" + QString::number(i++) + ")";

    return newName;
}

void Exporter::exportToExcel()
{    
    QString filename = QDir::toNativeSeparators(replaceExt(data->inputFile));

    QFile::remove(filename);
    QFile::copy(QDir::toNativeSeparators(QDir::currentPath() + "\\tpl_2ndfl.xls"), filename);

    mExcel = new QAxObject( "Excel.Application", this ); //получаем указатьтель на excel      
    QAxObject *workbooks = mExcel->querySubObject( "Workbooks" );
    QAxObject *workbook = workbooks->querySubObject( "Open(const QString&)", filename);
    QAxObject *mSheets = workbook->querySubObject( "Sheets" );
    QAxObject *tplSheet = mSheets->querySubObject( "Item(const QVariant&)", QVariant("2ndfl") );
    mExcel->setProperty("DisplayAlerts", "0");

    for (int i = 1; i < data->numberDoc; i++)
    {        
        tplSheet->dynamicCall("Copy(IDispatch *)", tplSheet->asVariant());
        
        QAxObject *currentSheet = mSheets->querySubObject( "Item(const QVariant&)", QVariant(i) );
        currentSheet->setProperty("Name", getSheetName(i, mSheets));
        mExcel->dynamicCall( "SetVisible(bool)", TRUE ); //делаем его видимым

        // СПРАВКА О ДОХОДАХ ФИЗИЧЕСКОГО ЛИЦА за 2009 год № 1 от 17.12.2009 в ИФНС №7610
        QString text = "СПРАВКА О ДОХОДАХ ФИЗИЧЕСКОГО ЛИЦА за " + data->params[QString::number(i) + "_Year"] + " год № " + data->params[QString::number(i) + "_Number"] + " от " + data->params[QString::number(i) + "_Date"] + " в ИФНС №" + data->params[QString::number(i) + "_IFNS"];
        QAxObject *range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B5")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(Importer::WINtoUnicode(text)));


        // 1.1. ИНН/КПП для организации или ИНН для физического лица
        text = data->params[QString::number(i) + "_INN/CPP"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("Y8")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 1.2. Наименование организации / Фамилия, имя, отчество физического лица
        text = data->params[QString::number(i) + "_Orgname"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B10")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 1.3. Код ОКАТО
        text = data->params[QString::number(i) + "_OKATO"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("H11")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 1.4. Телефон
        text = data->params[QString::number(i) + "_Tel"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AG11")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2. Данные о физическом лице - получателе доходов
        // 2.1. ИНН
        text = data->params[QString::number(i) + "_INN"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("F14")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ТБН
        text = data->params[QString::number(i) + "_TBN"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AR13")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.2. Фамилия, имя, отчество
        text = data->params[QString::number(i) + "_FIO"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB14")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.3. Статус (1-резидент, 2-нерезидент)
        text = data->params[QString::number(i) + "_Status"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("Q15")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.4. Дата рождения
        text = data->params[QString::number(i) + "_Birthday"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB15")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.5. Гражданство (код страны)
        text = data->params[QString::number(i) + "_Grajdanstvo"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AR15")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.6. Код документа, удостоверяющего личность
        text = data->params[QString::number(i) + "_CodeDoc"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("T16")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.7. Серия, номер документа
        text = data->params[QString::number(i) + "_SeriesAndNumberDoc"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ16")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.8. Адрес места жительства в Российской Федерации:
        // почтовый индекс
        text = data->params[QString::number(i) + "_Index"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AF17")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // код региона
        text = data->params[QString::number(i) + "_RegCode"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AQ17")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // район
        text = data->params[QString::number(i) + "_Raion"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D18")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // город
//        text = data->WINtoUnicode("город");
//        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S18")));
//        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_City"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("V18")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        //   населенный пункт
//        text = data->WINtoUnicode("населенный пункт");
//        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S18")));
//        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_НасПункт"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("I19")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // улица
        text = data->params[QString::number(i) + "_Street"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D20")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // дом
        text = data->params[QString::number(i) + "_Дом"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB20")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // корпус
        text = data->params[QString::number(i) + "_Корпус"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AI20")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // квартира
        text = data->params[QString::number(i) + "_Квартира"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AR20")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 2.9. Адрес в стране проживания: Код страны:
        text = data->params[QString::number(i) + "_КодСтраныПроживания"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S21")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // Адрес
        text = data->params[QString::number(i) + "_АдресВСтранеПроживания"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B22")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 3. Доходы, облагаемые по ставке 13%
        text = data->params[QString::number(i) + "_СтавкаНалога"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("Q24")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        for (int j = 1; j < data->params[QString::number(i) + "_incomeTableRowsCount"].toInt(); j++)
        {
            text = data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_1"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_2"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("D" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_3"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("I" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_4"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("P" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_5"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("T" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));


            text = data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_6"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AB" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_7"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_8"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AH" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_9"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AM" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

            text = data->params[QString::number(i) + "_Строка_" + QString::number(j) + "_Столбец_10"];
            range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AQ" + QString::number(25 + j, 10))));
            range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        }

        // 4. Стандартные и имущественные налоговые вычеты
        // 4.1. Суммы налоговых вычетов, право на получение которых имеется у налогоплательщика
        text = data->params[QString::number(i) + "_Код4.1"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("B46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_СуммаВычета4.1"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("G46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_Код4.2"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("N46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_СуммаВычета4.2"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("S46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_Код4.3"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AA46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_СуммаВычета4.3"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AF46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_Код4.4"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AK46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        text = data->params[QString::number(i) + "_СуммаВычета4.4"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AP46")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 4.2. № Уведомления, подтверждающего право на имущественный налоговый вычет
        text = data->params[QString::number(i) + "_НомерУведомления"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AI48")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 4.3. Дата выдачи Уведомления
        text = data->params[QString::number(i) + "_ДатаВыдачиУведомления"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("N49")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 4.4.Код налогового органа, выдавшего Уведомление
        text = data->params[QString::number(i) + "_КодИФНСУведомления"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AP49")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));


        // 4.5. Общая сумма предоставленных стандартных налоговых вычетов
        text = data->params[QString::number(i) + "_СуммаНалВычетов"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD50")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 4.6. Общая сумма предоставленных имущественных налоговых вычетов
        text = data->params[QString::number(i) + "_СуммаИмущественныхНалВычетов "];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AD51")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5. Общая сумма дохода и налога на доходы по итогам налогового периода
        // 5.1. Общая сумма дохода
        text = data->params[QString::number(i) + "_СуммаДоходов"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ54")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.2. Облагаемая сумма дохода
        text = data->params[QString::number(i) + "_ОблагаемаяСуммаДоходов"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ55")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.3. Сумма налога исчисленная
        text = data->params[QString::number(i) + "_СуммаП5.3"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ56")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.4. Сумма налога удержанная
        text = data->params[QString::number(i) + "_СуммаП5.4"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ57")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.5. Сумма возврата налога по перерасчету с доходов прошлых лет
        text = data->params[QString::number(i) + "_СуммаП5.5"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ58")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.6. Сумма, зачтенная при уплате налога по перерасчету с доходов прошлых лет
        text = data->params[QString::number(i) + "_СуммаП5.6"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ59")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.7. Сумма, удержанная при уплате налога по перерасчету с доходов прошлых лет
        text = data->params[QString::number(i) + "_СуммаП5.7"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ60")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.8. Задолженность по налогу за налогоплательщиком
        text = data->params[QString::number(i) + "_СуммаП5.8"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ61")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.9. Сумма налога, излишне удержанная налоговым агентом
        text = data->params[QString::number(i) + "_СуммаП5.9"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ62")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // 5.10. Сумма налога, переданная на взыскание в налоговый орган
        text = data->params[QString::number(i) + "_СуммаП5.10"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AJ63")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // Налоговый агент
        text = data->params[QString::number(i) + "_Должность"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("J66")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        // ФИО
        text = data->params[QString::number(i) + "_ФИОАгента"];
        range = currentSheet->querySubObject( "Range(const QVariant&)", QVariant( QString("AK66")));
        range->dynamicCall( "SetValue(const QVariant&)", QVariant(text));

        workbook->dynamicCall("Save()");

    }

    tplSheet->dynamicCall("Delete()");
    workbook->dynamicCall("Save()");

}
