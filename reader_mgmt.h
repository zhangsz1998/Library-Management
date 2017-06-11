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

class Reader{
private :
    QDomElement self;
    QString name,id,password,agency,authority,credit;
    int illegal_count,bor_num,resv_num,msg_num;
public:
    int order;
    double balance;
    bor_item bor_list[20];
    QString resvs[20];
    QString msg[30];
    Reader();
    bool is_modf;
    Reader & operator=(const Reader &);
    Reader(const QDomNode a);
    QString getStringByTag(QString tag);
    QDomElement toDom();
    int getIntByTag(QString tag);
    void setStringByTag(QString tag,QString  text);
    void setIntByTag(QString tag,int num);
    void IncIntByTag(QString tag);
    void DecIntByTag(QString tag);
    void display();
    Reader(QString &n,QString &i,QString &p,QString &ag,QString &au,QString &cr,int il,int bn,int rn,int mn,double bal);
};

Reader* sign_in(QString &id,QString &pa, int &flag);
void borrow(Book * b,Reader * r,QDate & cur, QDate & exp);
std::vector<Reader> * getXml2();
int add_newreader(Reader & reader);
void update2();
void saveXml2();
void returning(int order, Reader * r, QDate &cur);
void reservation(Book * b, Reader * r);
int renew(int order, Reader * r, QDate &cur);
void daycheck();
Reader * getUser(QString id);
void report(int order,Reader *r,QString reason);

#endif // READER_MGMT_H

