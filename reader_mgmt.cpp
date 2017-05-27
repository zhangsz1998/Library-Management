#include "reader_mgmt.h"
#include <QString>

QDomDocument doc2;
std::vector<Reader> readerlist,*preaderlist;
QDomNodeList list2;
QDomNode firstNode2;
extern QString readerInfoPath;
extern QDate systemDate;

Reader::Reader(){
}

Reader::Reader(const QDomNode a){
    QDomNodeList list=a.childNodes();
    this->name=list.at(0).toElement().text();
    this->id=list.at(1).toElement().text();
    this->password=list.at(2).toElement().text();
    this->agency=list.at(3).toElement().text();
    this->authority=list.at(4).toElement().text();
    this->illegal_count=list.at(6).toElement().text().toInt();
    this->credit=list.at(7).toElement().text();
    QDomNodeList tmp;
    tmp=list.at(5).childNodes();
    this->bor_num = tmp.size();
    for (int i=0;i<bor_num;i++){
        this->bor_list[i].id=tmp.at(i).childNodes().at(0).toElement().text();
        this->bor_list[i].st=QDate::fromString(tmp.at(i).childNodes().at(1).toElement().text(),"yyyyMMDD");
        this->bor_list[i].exp=QDate::fromString(tmp.at(i).childNodes().at(2).toElement().text(),"yyyyMMDD");
    }
    tmp=list.at(8).childNodes();
    this->resv_num=tmp.size();
    for(int i=0;i<resv_num;i++){
        this->resvs[i].id = tmp.at(i).childNodes().at(0).toElement().text();
        this->resvs[i].d = QDate::fromString(tmp.at(i).childNodes().at(1).toElement().text(),"yyyyMMDD");
    }
    tmp=list.at(9).childNodes();
    this->msg_num=tmp.size();
    for (int i=0;i<msg_num;i++)
        this->msg[i]=tmp.at(i).toElement().text();
}

Reader & Reader::operator =(const Reader & dul){
    if (this==&dul) return *this;
    this->name = dul.name;
    this->authority=dul.authority;
    this->id=dul.id;
    this->password = dul.password;
    this->agency = dul.agency;
    this->bor_num = dul.bor_num;
    for (int i=0;i<this->bor_num;i++)
        this->bor_list[i]=dul.bor_list[i];
    this->illegal_count = dul.illegal_count;
    this->credit = dul.credit;
    this->resv_num = dul.resv_num;
    for (int i=0;i<this->resv_num;i++)
        this->resvs[i] = dul.resvs[i];
    this->msg_num = dul.msg_num;
    for (int i=0;i<this->msg_num;i++)
        this->msg[i] = dul.msg[i];
    return *this;
}

Reader::Reader(QString &n, QString &i, QString &p, QString &ag, QString &au, QString &cr, int il,int bn,int rn, int mn){
    this->name = n;
    this->id = i;
    this->password = p;
    this->agency = ag;
    this->authority = au;
    this->credit = cr;
    this->illegal_count = il;
    this->bor_num = bn;
    this->msg_num = mn;
    this->resv_num = rn;
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
    QDomElement borItem = doc2.createElement(QString("book"));
    QDomElement borId,borSt,borExp;
    QDomText idText,stText,expText;
    for (int i=0;i<bor_num;i++){
        idText = doc2.createTextNode(bor_list[i].id);
        stText = doc2.createTextNode(bor_list[i].st.toString("yyyyMMdd"));
        expText = doc2.createTextNode(bor_list[i].exp.toString("yyyyMMdd"));
        borId = doc2.createElement(QString("id"));
        borId.appendChild(idText);
        borSt = doc2.createElement(QString("bor_time"));
        borSt.appendChild(stText);
        borExp = doc2.createElement(QString("due_time"));
        borExp.appendChild(expText);
        borItem.appendChild(borId);
        borItem.appendChild(borSt);
        borItem.appendChild(borExp);
        borNode.appendChild(borItem);
    }
    QDomElement resvNode = doc2.createElement(QString("reservations"));
    QDomElement resvItem = doc2.createElement(QString("book"));
    QDomElement resvId,resvExp;
    for (int i=0;i<resv_num;i++){
        idText = doc2.createTextNode(resvs[i].id);
        expText = doc2.createTextNode(resvs[i].d.toString("yyyyMMdd"));
        resvId = doc2.createElement(QString("id"));
        resvId.appendChild(idText);
        resvExp = doc2.createElement(QString("resv_time"));
        resvExp.appendChild(expText);
        resvItem.appendChild(resvId);
        resvItem.appendChild(resvExp);
        resvNode.appendChild(resvItem);
    }
    QDomElement msgNode = doc2.createElement(QString("messages"));
    QDomElement msgItem = doc2.createElement(QString("message"));
    for (int i=0;i<msg_num;i++){
        text = doc2.createTextNode(msg[i]);
        msgItem.appendChild(text);
        msgNode.appendChild(msgItem);
    }
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
    if (tag == "illegal_count") return illegal_count;
    if (tag == "bor_num") return bor_num;
    if (tag == "revs_num") return resv_num;
    if (tag == "msg_num") return msg_num;
    return 0;
}

void Reader::setIntByTag(QString tag, int num){
    is_modf = true;
    if (tag == "illegal_count") this->illegal_count = num;
    if (tag == "bor_num") this->bor_num = num;
    if (tag == "revs_num") this->resv_num = num;
    if (tag == "msg_num") this->msg_num = num;
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
    if (tag == "bor_num") ++this->bor_num;
    if (tag == "revs_num") ++this->resv_num;
    if (tag == "msg_num") ++this->msg_num;
}

void Reader::DecIntByTag(QString tag){
    is_modf = true;
    if (tag == "illegal_count") --this->illegal_count;
    if (tag == "bor_num") --this->bor_num;
    if (tag == "revs_num") --this->resv_num;
    if (tag == "msg_num") --this->msg_num;
}

std::vector<Reader> * getXml2(){
    QFile file(readerInfoPath);
    if (!file.open(QIODevice::ReadOnly)) return NULL;
    if (!doc2.setContent(&file)){
        file.close();
        return NULL;
    }
    file.close();
    firstNode2 = doc2.documentElement();
    list2 = firstNode2.childNodes();
    for (int i=0;i<list2.count();i++){
        readerlist.push_back(Reader(list2.at(i)));
        readerlist[i].order = i;
    }
    preaderlist = &readerlist;
    return preaderlist;
}

void update2(){
    for (std::vector<Reader>::iterator it=readerlist.begin();it!=readerlist.end();it++)
        if (it->is_modf && it->order <list2.count()){
            QDomNode tmp = it->toDom();
            firstNode2.replaceChild(tmp,firstNode2.childNodes().at(it->order));
            list2 = firstNode2.childNodes();
        }
        else doc2.documentElement().appendChild(it->toDom());
}


int add_newreader(Reader & reader){     //返回1表示添加成功，返回2表示注册用户以存在
    for (std::vector<Reader>::iterator it=readerlist.begin();it!=readerlist.end();it++)
        if (it->getStringByTag(QString("id")) == reader.getStringByTag(QString("id")))
            return 2;
    if (readerlist.size())
        reader.order = readerlist.back().order + 1;
    else reader.order = 0;
    readerlist.push_back(reader);
    return 1;
}

void saveXml2(){
    QFile file(readerInfoPath);
    update2();
    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate)) return;
    QTextStream out(&file);
    doc2.save(out,2);
    file.close();
}

void borrow(Book *b, Reader *r, QDate &cur, QDate &exp){
    b->DecIntByTag("amount");
    b->IncIntByTag("bor_count");
    r->IncIntByTag("bor_num");
    int num = r->getIntByTag("bor_num");
    r->bor_list[num-1].id = b->getStringByTag("id");
    r->bor_list[num-1].st = cur;
    r->bor_list[num-1].exp = exp;
}


void resvation(Book * b,Reader *r,QDate &cur);

Reader* sign_in(QString &id,QString &pa, int &flag){
    for (int i=0;i<readerlist.size();i++)
        if (readerlist[i].getStringByTag("id") == id){
            if (readerlist[i].getStringByTag("password") == pa){
                flag = 1;   //登陆成功
                return &readerlist[i];
            }
            else {
                flag = 2;   //密码错误
                return Q_NULLPTR;
            }
        }
    flag = 3;   //找不到用户
    return Q_NULLPTR;
}

void returning(Book &b, Reader &r, QDate &cur){
    b.IncIntByTag("amount");
    QDate due;
    int num = r.getIntByTag("bor_num");
    for (int i=0;i<num;i++)
        if (r.bor_list[i].id == b.getStringByTag("id")){
            due = r.bor_list[i].exp;
            for (int j=i+1;j<num;j++)
                r.bor_list[j-1] = r.bor_list[j];
            r.DecIntByTag("bor_num");
            break;
        }
    if (cur > due) r.IncIntByTag("illegal_count");
}

void daycheck(){
    for (int i=0;i<readerlist.size();i++){
        int num = readerlist[i].getIntByTag("bor_num");
        for (int j=0;j<num;j++)
            if (readerlist[i].bor_list[j].exp > systemDate){
                readerlist[i].IncIntByTag("msg_num");
                readerlist[i].msg[readerlist[i].getIntByTag("msg_num")] = QString("Book overdue"); //待替换，瞎写的。
            }
    }
}

