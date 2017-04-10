#include "reader_mgmt.h"
#include <QString>

QDomDocument doc2;
std::vector<Reader> readerlist,*preaderlist;
QDomNodeList list2;
extern QString readerInfoPath;

Reader::Reader(){
}

Reader::Reader(const QDomNode a){
    QDomNodeList list=a.childNodes();
    this->name=list.at(0).toElement().text();
    this->id=list.at(1).toElement().text();
    this->password=list.at(2).toElement().text();
    this->agency=list.at(3).toElement().text();
    this->authority=list.at(4).toElement().text();
    this->bor_list=list.at(5).childNodes();
    this->illegal_count=list.at(6).toElement().text().toInt();
    this->credit=list.at(7).toElement().text();
    this->resv=list.at(8).childNodes();
    this->msg=list.at(9).childNodes();
}

Reader & Reader::operator =(const Reader & dul){
    if (this==&dul) return *this;
    this->name = dul.name;
    this->authority=dul.authority;
    this->id=dul.id;
    this->password = dul.password;
    this->agency = dul.agency;
    this->bor_list = dul.bor_list;
    this->illegal_count = dul.illegal_count;
    this->credit = dul.credit;
    this->resv = dul.resv;
    this->msg = dul.msg;
    return *this;
}

Reader::Reader(QString &n, QString &i, QString &p, QString &ag, QString &au, QString &cr, int il){
    this->name = n;
    this->id = i;
    this->password = p;
    this->agency = ag;
    this->authority = au;
    this->credit = cr;
    this->illegal_count = il;
}

QDomElement Reader::toDom(){

    QDomElement nameNode = doc2.createElement(QString("name"));
    QDomText text = doc2.createTextNode(name);
    nameNode.appendChild(text);
    QDomElement idNode = doc2.createElement(QString("id"));
    text = doc2.createTextNode(id);
    idNode.appendChild(text);
    QDomElement passwordNode = doc2.createElement(QString("password"));
    text = doc2.createTextNode(password);
    passwordNode.appendChild(text);
    QDomElement agencyNode = doc2.createElement(QString("agency"));
    text = doc2.createTextNode(agency);
    agencyNode.appendChild(text);
    QDomElement authorityNode = doc2.createElement(QString("authority"));
    text = doc2.createTextNode(authority);
    authorityNode.appendChild(text);
    QDomElement creditNode = doc2.createElement(QString("credit"));
    text = doc2.createTextNode(credit);
    creditNode.appendChild(text);
    QDomElement illegalNode = doc2.createElement(QString("illegal_count"));
    text = doc2.createTextNode(QString::number(illegal_count));
    illegalNode.appendChild(text);
    QDomElement borNode = doc2.createElement(QString("booklist"));
    for (int i=0;i<bor_list.count();i++)
        borNode.appendChild(bor_list.at(i));
    QDomElement resvNode = doc2.createElement(QString("reservations"));
    for (int i=0;i<resv.count();i++)
        resvNode.appendChild(resv.at(i));
    QDomElement msgNode = doc2.createElement(QString("message"));
    for (int i=0;i<msg.count();i++)
        msgNode.appendChild(msg.at(i));
    QDomElement new_reader = doc2.createElement(QString("reader"));
    new_reader.appendChild(nameNode);
    new_reader.appendChild(idNode);
    new_reader.appendChild(passwordNode);
    new_reader.appendChild(agencyNode);
    new_reader.appendChild(authorityNode);
    new_reader.appendChild(borNode);
    new_reader.appendChild(illegalNode);
    new_reader.appendChild(creditNode);
    new_reader.appendChild(resvNode);
    new_reader.appendChild(msgNode);
    return new_reader;
}

QString Reader::getStringByTag(QString tag){
    if (tag == "name") return name;
    if (tag == "id") return id;
    if (tag == "password") return password;
    if (tag == "agency") return agency;
    if (tag == "authority") return authority;
    if (tag == "credit") return credit;
    return QString("");
}

int Reader::getIntByTag(QString tag){
    if (tag == "illegal_count");
    return illegal_count;
}

void Reader::setIntByTag(QString tag, int num){
    is_modf = true;
    if (tag == "illegal_count") this->illegal_count = num;
}

void Reader::setStringByTag(QString tag, QString &text){
    is_modf = true;
    if (tag == "name") this->name = text;
    if (tag == "id") this->id = text;
    if (tag == "password") this->password = text;
    if (tag == "agency") this->agency = text;
    if (tag == "authority") this->authority = text;
    if (tag == "credit") this->credit = text;
}

void Reader::IncIntByTag(QString tag){
    is_modf = true;
    if (tag == "illegal_count") ++this->illegal_count;
}

void Reader::DecIntByTag(QString tag){
    is_modf = true;
    if (tag == "illegal_count") --this->illegal_count;
}

std::vector<Reader> * getXml2(){
    QFile file(readerInfoPath);
    if (!file.open(QIODevice::ReadOnly)) return NULL;
    if (!doc2.setContent(&file)){
        file.close();
        return NULL;
    }
    file.close();
    QDomNode firstNode = doc2.documentElement();
    list2 = firstNode.childNodes();
    for (int i=0;i<list2.count();i++){
        readerlist.push_back(Reader(list2.at(i)));
        readerlist[i].order = i;
    }
    preaderlist = &readerlist;
    return preaderlist;
}

void update2(){
    for (std::vector<Reader>::iterator it=readerlist.begin();it!=readerlist.end();it++)
        if (it->is_modf && it->order <list2.count())
            list2.at(it->order) = it->toDom();
        else doc2.documentElement().appendChild(it->toDom());
}

void saveXml2(){
    QFile file(readerInfoPath);
    update2();
    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate)) return;
    QTextStream out(&file);
    doc2.save(out,2);
    file.close();
}

