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
    QString title,author,press,desp,id,category,loc;
    int amount,total,refer_count,bor_count;
public:
    int is_delete;
    int is_resv;
    int order;
    Book();
    bool is_modf;
    Book & operator=(const Book &);
    Book(const QDomNode a);
    QDomElement toDom();
    QString getStringByTag(QString tag);
    int getIntByTag(QString tag);
    void setStringByTag(QString tag,QString text);
    void setIntByTag(QString tag,int num);
    void IncIntByTag(QString tag);
    void DecIntByTag(QString tag);
    void display();
    Book(QString &t,QString &a,QString &p,QString &d,QString &i,QString &c,int am,int to,int rc,int bc,QString & lc,int is_r);
};

std::vector<Book> * getXml();//Get Xml from file to vector <Book>
void saveXml();//save Xml from file to vector <Book>
void fileUpdate();
void add_newbook(Book &);
QString convert2id();
bool match(Book & b,QRegExp & rx,int mode);
std::vector<Book *> search(QString kw,int mode);
void log_print(QString format,QString a,QString b,QString c);
QString myHash(QString author,QString press, QString category,QString name);
QString categoryId(QString s);
QString categortString(QString s);
std::vector<QString> getTopCat();
std::vector<Book *> getCatTopBor(QString cat);
std::vector<Book *> getCatTopRef(QString cat);
QDate getDate();
void configureDate();

#endif // BOOK_MGMT_H
