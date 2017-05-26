#ifndef READER_MGMT_H
#define READER_MGMT_H
#include "book_mgmt.h"
#include <QFile>
#include <QtXml>
#include <QCoreApplication>
#include <vector>
#include <QDate>


struct bor_item{
    QString id;
    QDate st,exp;
};

struct resv{
    QString id;
    QDate d;
};

class Reader{
private :
    QDomElement self;
    QString name,id,password,agency,authority,credit;
    int illegal_count,bor_num,resv_num,msg_num;
public:
    int order;
    bor_item bor_list[20];
    resv resvs[20];
    QString msg[20];
    Reader();
    bool is_modf;
    Reader & operator=(const Reader &);
    Reader(const QDomNode a);
    QString getStringByTag(QString tag);
    QDomElement toDom();
    int getIntByTag(QString tag);
    void setStringByTag(QString tag,QString & text);
    void setIntByTag(QString tag,int num);
    void IncIntByTag(QString tag);
    void DecIntByTag(QString tag);
    void display();
    Reader(QString &n,QString &i,QString &p,QString &ag,QString &au,QString &cr,int il,int bn,int rn,int mn);
};

Reader* sign_in(QString &id,QString &pa, int &flag);
void borrow(Book & b,Reader & r,QDate & cur, QDate & exp);
std::vector<Reader> * getXml2();
int add_newreader(Reader & reader);
void update2();
void saveXml2();

#endif // READER_MGMT_H
