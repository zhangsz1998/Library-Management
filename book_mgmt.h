#ifndef BOOK_MGMT_H
#define BOOK_MGMT_H
#include <QFile>
#include <QtXml>
#include <QCoreApplication>
#include <vector>

class Book;

class Book{
private:
    QDomElement self;
    QString title,author,press,desp,id,category;
    int amount,total,refer_count,bor_count;
public:
    int order;
    Book();
    bool is_modf;
    Book & operator=(const Book &);
    Book(const QDomNode a);
    QDomElement toDom();
    QString getStringByTag(QString tag);
    int getIntByTag(QString tag);
    void setStringByTag(QString tag,QString &text);
    void setIntByTag(QString tag,int num);
    void IncIntByTag(QString tag);
    void DecIntByTag(QString tag);
    void display();
    Book(QString &t,QString &a,QString &p,QString &d,QString &i,QString &c,int am,int to,int rc,int bc);
};

std::vector<Book> * getXml();//Get Xml from file to vector <Book>
void saveXml();//save Xml from file to vector <Book>
void update();
void add_newbook(Book &);
QString convert2id();



#endif // BOOK_MGMT_H
