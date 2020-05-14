#include "information.h"

Information::Information()
{

}

void Information::setTitle(QString title) {
    this->title = title;
}

void Information::setDate(QString date) {
    this->date = date;
}

void Information::setTime(QString time)
{
    this->time = time;
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

void Information::setLink(QString link)
{
    this->link = link;
}

QString Information::getTitle() {
    return this->title;
}

QString Information::getDate() {
    return this->date;
}

QString Information::getTime()
{
    return this->time;
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

QString Information::getLink()
{
    return this->link;
}
