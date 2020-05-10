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
    void setDescription(QString description);
    QString getTitle();
    QString getDate();
    QString getSite();
    QString getInfo();
    QString getDescription();

private:
    QString title,
            date,
            site,
            info,
            description;
};

#endif // INFORMATION_H
