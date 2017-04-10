#ifndef READER_MGMT_H
#define READER_MGMT_H
#include <QFile>
#include <QtXml>
#include <QCoreApplication>
#include <vector>

class Reader{
private :
    QDomElement self;
    QString name,id,password,agency,authority,credit;
    int illegal_count;
    QDomNodeList bor_list,resv,msg;
public:
    int order;
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
    Reader(QString &n,QString &i,QString &p,QString &ag,QString &au,QString &cr,int il);
};

#endif // READER_MGMT_H
