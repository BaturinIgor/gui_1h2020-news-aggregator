#include "information.h"

Information::Information()
{

}

Information::Information(QString title, QString date, QString site, QString info)
{
    this->title = title;
    this->date = date;
    this->site = site;
    this->info = info;
}

void Information::setTitle(QString title) {
    this->title = title;
}

void Information::setDate(QString date) {
    this->date = date;
}

void Information::setSite(QString site) {
    this->site = site;
}

void Information::setInfo(QString info) {
    this->info = info;
}

void Information::setDescription(QString description)
{
    this->description = description;
}

QString Information::getTitle() {
    return this->title;
}

QString Information::getDate() {
    return this->date;
}

QString Information::getSite() {
    return this->site;
}

QString Information::getInfo() {
    return this->info;
}

QString Information::getDescription() {
    return this->description;
}
