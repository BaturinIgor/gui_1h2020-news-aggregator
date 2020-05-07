#ifndef INFORMATION_H
#define INFORMATION_H

#include <QString>

class Information
{
public:
    Information();
    Information(QString title, QString date, QString site, QString info);
    void setTitle(QString title);
    void setDate(QString date);
    void setSite(QString site);
    void setInfo(QString info);
    QString getTitle();
    QString getDate();
    QString getSite();
    QString getInfo();

private:
    QString title, date, site, info;
};

#endif // INFORMATION_H
