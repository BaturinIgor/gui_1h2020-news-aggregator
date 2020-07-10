#ifndef INFORMATION_H
#define INFORMATION_H

#include <QString>

class Information
{
public:
    Information();
    void setTitle(QString title);
    void setDate(QString date);
    void setTime(QString time);
    void setSite(QString site);
    void setInfo(QString info);
    void setDescription(QString description);
    void setLink(QString link);
    QString getTitle();
    QString getDate();
    QString getTime();
    QString getSite();
    QString getInfo();
    QString getDescription();
    QString getLink();

private:
    QString title,
            date,
            time,
            site,
            info,
            description,
            link;
};

#endif // INFORMATION_H
