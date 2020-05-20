#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDomDocument>
#include <QListView>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    amountOfNews = 0;
    headingInit();

    ui->treeWidget->setColumnCount(5);

    columnNames << "Заголовок" << "Дата" << "Время" << "Категория" << "Сайт";
    ui->treeWidget->setColumnWidth(0, 450);
    ui->treeWidget->setColumnWidth(1, 80);
    ui->treeWidget->setColumnWidth(2, 60);
    ui->treeWidget->setColumnWidth(3, 120);
    ui->treeWidget->setColumnWidth(4, 150);
    ui->treeWidget->setHeaderLabels(columnNames);

    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(on_treeWidget_itemClicked(QTreeWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addElem(Information info) {
    QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->treeWidget, ui->treeWidget->currentItem());

    newItem->setText(0, info.getTitle());
    newItem->setText(1, info.getDate());
    newItem->setText(2, info.getTime());
    newItem->setText(3, info.getInfo());
    newItem->setText(4, info.getSite());

    newItem->setExpanded(true);
}


void MainWindow::replyFinished(QNetworkReply* reply) {
    QString data = QString::fromUtf8(reply->readAll());

    QFile file("test.xml");

    if (file.open(QIODevice::WriteOnly))
    {
        file.write(data.toLocal8Bit().data());
        file.close();
    }

    QDomDocument domDoc;

    if(file.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&file)) {
            QDomElement domElement= domDoc.documentElement();
            traverseNode(domElement);
            newsSorting(ui->comboBox_2->currentIndex());
        }
        file.close();
    }
}

void MainWindow::traverseNode(const QDomNode& node)
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull() && index < amountOfNews) {
        if(domNode.isElement()) {
           QDomElement domElement = domNode.toElement();
           if(!domElement.isNull()) {
               if(domElement.tagName() == "contact") {
                   qDebug() << "Attr: "
                            << domElement.attribute("number", "");
               }
               else {
                   if (domElement.tagName() == "title")
                       info[index].setTitle(domElement.text());
                   else if(domElement.tagName() == "link")
                       info[index].setLink(domElement.text());
                   else if (domElement.tagName() == "pubDate") {
                       info[index].setDate(domElement.text().mid(5, 11));
                       info[index].setTime(domElement.text().mid(17, 8));
                   }
                   else if (domElement.tagName() == "category")
                       info[index].setInfo(domElement.text());
                   else if (domElement.tagName() == "dc:creator")
                       info[index].setSite(domElement.text());
                   else if (domElement.tagName() == "description") {
                       info[index].setDescription(domElement.text());
                       index++;
                   }
              }
           }
        }
        traverseNode(domNode);
        domNode = domNode.nextSibling();
     }
}

void MainWindow::headingInit() {
    headings = {
        {"Автомобили и мото транспорт", "http://www.autotoday.ru/feed/"},
        {"Бизнес и финансы", "http://www.commercetoday.ru/feed/"},
        {"Промышленность", "http://www.industrytoday.ru/feed/"},
        {"Дом и семья", "http://www.hometoday.ru/feed/"},
        {"Досуг и развлечения", "http://www.dosugtoday.ru/feed/"},
        {"Интернет и технологии", "http://www.internettoday.ru/feed/"},
        {"Красота и мода", "http://www.beautytoday.ru/feed/"},
        {"Культура и искусство", "http://www.culturetoday.ru/feed/"},
        {"Медицина и здоровье", "http://www.healthtoday.ru/feed/"},
        {"Наука и образование", "http://www.learntoday.ru/feed/"},
        {"Общество", "http://www.worldtoday.ru/feed/"},
        {"Туризм, путешествия и отды", "http://www.turizmtoday.ru/feed/"},
        {"СМИ и периодика", "http://www.smitoday.ru/feed/"},
        {"Спорт", "http://www.sporttoday.ru/feed/"},
        {"Строительство и недвижимость", "http://www.realtytoday.ru/feed/"},
        {"Товары и услуги", "http://www.markettoday.ru/feed/"}
    };
    for (int j = 0; j < headings.size(); j++) {
        ui->comboBox->addItem(headings[j].first);
    }
}

void MainWindow::newsSorting(int criterion)
{       
    switch (criterion) {
    case 0:
        for(int j = index-1; j >= 1; j-- ) {
            if (info[j].getTitle().contains(ui->lineEdit->text(), Qt::CaseInsensitive) ||
                info[j].getDate().contains(ui->lineEdit->text(), Qt::CaseInsensitive) ||
                info[j].getInfo().contains(ui->lineEdit->text(), Qt::CaseInsensitive) ||
                info[j].getSite().contains(ui->lineEdit->text(), Qt::CaseInsensitive) ||
                info[j].getDescription().contains(ui->lineEdit->text(), Qt::CaseInsensitive) ||
                info[j].getTime().contains(ui->lineEdit->text(), Qt::CaseInsensitive))
                addElem(info[j]);
        }
        break;
    case 1:
        for(int j = 1; j <= index-1; j++ ) {
            if (info[j].getTitle().contains(ui->lineEdit->text(), Qt::CaseInsensitive) ||
                info[j].getDate().contains(ui->lineEdit->text(), Qt::CaseInsensitive) ||
                info[j].getInfo().contains(ui->lineEdit->text(), Qt::CaseInsensitive) ||
                info[j].getSite().contains(ui->lineEdit->text(), Qt::CaseInsensitive) ||
                info[j].getDescription().contains(ui->lineEdit->text(), Qt::CaseInsensitive) ||
                info[j].getTime().contains(ui->lineEdit->text(), Qt::CaseInsensitive))
                addElem(info[j]);
        }
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->treeWidget->clear();
    index = 0;
    amountOfNews = ui->comboBox_3->currentText().toInt() + 1;
    info = new Information[amountOfNews];
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    for (int j = 0; j < headings.size(); j++) {
        if (headings[j].first == ui->comboBox->currentText()) {
            manager->get(QNetworkRequest(QUrl(headings[j].second)));
            break;
        }
        else continue;
    }
    currentItem = NULL;
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item)
{
    for(int j = 1; j <= index-1; j++ ) {
        if (info[j].getTitle() == item->text(0)) {
            ui->plainTextEdit->setReadOnly(1);
            ui->plainTextEdit->setFont(QFont( "Helvetica", 11 ));
            ui->plainTextEdit->document()->setPlainText("Заголовок:\t\t\t" + info[j].getTitle() + "\n" +
                                                        "Дата и время публикации:\t" + info[j].getDate() + " " + info[j].getTime() + "\n" +
                                                        "Категория:\t\t\t" + info[j].getInfo() + "\n" +
                                                        "Сайт:\t\t\t" + info[j].getSite() + "\n" +
                                                        "   " + info[j].getDescription() + "\n" +
                                                        "Продолждение: " + info[j].getLink() + "\n" +
                                                        "Все новости \"" + info[0].getTitle() + "\": " + info[j].getSite());

            break;
        }
        else continue;
    }
}
