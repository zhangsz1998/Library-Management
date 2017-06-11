#include "reader_mgmt.h"
#include <QString>

QDomDocument doc2;
std::vector<Reader> readerlist,*preaderlist;
QDomNodeList list2;
QDomNode firstNode2;
extern QString readerInfoPath;
extern QDate systemDate;
extern std::vector<Book> booklist;
extern bool userMessageChanged;
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
        this->bor_list[i].st=QDate::fromString(tmp.at(i).childNodes().at(1).toElement().text(),"yyyy-MM-dd");
        this->bor_list[i].exp=QDate::fromString(tmp.at(i).childNodes().at(2).toElement().text(),"yyyy-MM-dd");
    }
    tmp=list.at(8).childNodes();
    this->resv_num=tmp.size();
    for(int i=0;i<resv_num;i++){
        this->resvs[i] = tmp.at(i).childNodes().at(0).toElement().text();
    }
    tmp=list.at(9).childNodes();
    this->msg_num=tmp.size();
    for (int i=0;i<msg_num;i++)
        this->msg[i]=tmp.at(i).toElement().text();
    this->balance = list.at(10).toElement().text().toDouble();
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
    this->balance = dul.balance;
    return *this;
}

Reader::Reader(QString &n, QString &i, QString &p, QString &ag, QString &au, QString &cr, int il,int bn,int rn, int mn, double bal){
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
    this->balance = bal;
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
    QDomElement borId,borSt,borExp;
    QDomText idText,stText,expText;
    for (int i=0;i<bor_num;i++){
        QDomElement borItem = doc2.createElement(QString("book"));
        idText = doc2.createTextNode(bor_list[i].id);
        stText = doc2.createTextNode(bor_list[i].st.toString("yyyy-MM-dd"));
        expText = doc2.createTextNode(bor_list[i].exp.toString("yyyy-MM-dd"));
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
    QDomElement resvId,resvExp;
    for (int i=0;i<resv_num;i++){
        QDomElement resvItem = doc2.createElement(QString("book"));
        idText = doc2.createTextNode(resvs[i]);
        resvId = doc2.createElement(QString("id"));
        resvId.appendChild(idText);
        resvItem.appendChild(resvId);
        resvNode.appendChild(resvItem);
    }
    QDomElement msgNode = doc2.createElement(QString("messages"));
    for (int i=0;i<msg_num;i++){
        QDomElement msgItem = doc2.createElement(QString("message"));
        text = doc2.createTextNode(msg[i]);
        msgItem.appendChild(text);
        msgNode.appendChild(msgItem);
    }
    QDomElement balNode = doc2.createElement(QString("balance"));
    text = doc2.createTextNode(QString::number(balance,'f',2));
    balNode.appendChild(text);
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
    new_reader.appendChild(balNode);
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
    if (tag == "resv_num") return resv_num;
    if (tag == "msg_num") return msg_num;
    return 0;
}

void Reader::setIntByTag(QString tag, int num){
    is_modf = true;
    if (tag == "illegal_count") this->illegal_count = num;
    if (tag == "bor_num") this->bor_num = num;
    if (tag == "resv_num") this->resv_num = num;
    if (tag == "msg_num") this->msg_num = num;
}

void Reader::setStringByTag(QString tag, QString text){
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
    if (tag == "resv_num") ++this->resv_num;
    if (tag == "msg_num") ++this->msg_num;
}

void Reader::DecIntByTag(QString tag){
    is_modf = true;
    if (tag == "illegal_count") --this->illegal_count;
    if (tag == "bor_num") --this->bor_num;
    if (tag == "resv_num") --this->resv_num;
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
    if (!readerlist.empty()){
        for (std::vector<Reader>::iterator it=readerlist.begin();it!=readerlist.end();it++)
            if (it->is_modf && it->order <list2.count()){
                QDomNode tmp = it->toDom();
                firstNode2.replaceChild(tmp,firstNode2.childNodes().at(it->order));
                list2 = firstNode2.childNodes();
            }
            else if (it->order >= list2.count())
                doc2.documentElement().appendChild(it->toDom());
    }
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
    int num = r->getIntByTag("bor_num");
    r->bor_list[num].id = b->getStringByTag("id");
    r->bor_list[num].st = cur;
    r->bor_list[num].exp = exp;
    r->IncIntByTag("bor_num");
}


void reservation(Book * b,Reader *r){
    b->is_resv = true;
    int num = r->getIntByTag("resv_num");
    r->resvs[num] = b->getStringByTag("id");
    r->IncIntByTag("resv_num");
}

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

int renew(int order,Reader *r, QDate &cur){
    QDate due = r->bor_list[order].exp;
    QString id = r->bor_list[order].id;
    Book *b;
    for (int i=0;i<booklist.size();i++)
        if (booklist[i].getStringByTag("id") == id) {
            b = &booklist[i];
            break;
        }
    if (b->is_resv) return 2; //yi bei yu ding
    if (cur > due) {
        r->IncIntByTag("illegal_count");
        return 1; //bu neng xu jie
    }
    if (due < cur.addDays(15)) {
        r->bor_list[order].exp = cur.addDays(15);
        log_print("renew",r->getStringByTag("id"),b->getStringByTag("id"),"");
        return 0; //xujiechenggong
    }
    return 3; // riqi mei bian
}

void returning(int order,Reader *r, QDate &cur){
    QDate due = r->bor_list[order].exp;
    QString id = r->bor_list[order].id;
    Book * b;
    for (int i=0;i<booklist.size();i++)
        if (booklist[i].getStringByTag("id") == id) {
            b = &booklist[i];
            break;
        }
    b->IncIntByTag("amount");
    int num = r->getIntByTag("bor_num");
    for (int j=order+1;j<num;j++)
        r->bor_list[j-1] = r->bor_list[j];
    r->DecIntByTag("bor_num");
    log_print("return",r->getStringByTag("id"),cur.toString("yyyy-MM-dd"),b->getStringByTag("id"));
    if (b->is_resv && b->getIntByTag("amount") == 1)
        for (int i=0;i<readerlist.size();i++){
            int rnum = readerlist[i].getIntByTag("resv_num");
            for (int j=0;j<rnum;j++)
                if (readerlist[i].resvs[j] == b->getStringByTag("id")) {
                    for (int k=j+1;k<rnum;k++)
                        readerlist[i].bor_list[k-1] = readerlist[i].bor_list[k];
                    rnum--;
                    if (readerlist[i].getIntByTag("msg_num")!=30)
                        readerlist[i].msg[readerlist[i].getIntByTag("msg_num")] = systemDate.toString("yyyy-MM-dd")+" 您预约的图书"+b->getStringByTag("id")+"已有库存，请尽快前往借阅！";
                    else {
                       for (int k=0;k<29;k++)
                           readerlist[i].msg[k]=readerlist[i].msg[k+1];
                       readerlist[i].msg[29] = systemDate.toString("yyyy-MM-dd")+" 您预约的图书"+b->getStringByTag("id")+"已有库存，请尽快前往借阅！";
                    }
                    if (readerlist[i].getIntByTag("msg_num") != 30) readerlist[i].IncIntByTag("msg_num");
                    else readerlist[i].is_modf = true;
                    userMessageChanged=true;
                }
            readerlist[i].setIntByTag("resv_num",rnum);
        }
}

void report(int order,Reader *r,QString reason){
    QDate due = r->bor_list[order].exp;
    QString id = r->bor_list[order].id;
    Book * b;
    for (int i=0;i<booklist.size();i++)
        if (booklist[i].getStringByTag("id") == id) {
            b = &booklist[i];
            break;
        }
    b->DecIntByTag("total");
    int num = r->getIntByTag("bor_num");
    for (int j=order+1;j<num;j++)
        r->bor_list[j-1] = r->bor_list[j];
    r->DecIntByTag("bor_num");

    if (r->getIntByTag("msg_num")!=30)
        r->msg[r->getIntByTag("msg_num")] = systemDate.toString("yyyy-MM-dd")+" 您借阅的图书"+b->getStringByTag("id")+"已挂失成功,从您的账户中扣除10元!";
    else {
       for (int k=0;k<29;k++)
           r->msg[k]=r->msg[k+1];
       r->msg[29] = systemDate.toString("yyyy-MM-dd")+" 您借阅的图书"+b->getStringByTag("id")+"已挂失成功,从您的账户中扣除10元!";
    }
    if (r->getIntByTag("msg_num") != 30) r->IncIntByTag("msg_num");
    else r->is_modf = true;
    log_print("report",r->getStringByTag("id"),b->getStringByTag("id"),reason);

    r->IncIntByTag("illegal_count");
    int cnt = r->getIntByTag("illegal_count");
    if (cnt>5) r->setStringByTag("credit",QString("3"));
    else if (cnt > 3) r->setStringByTag("credit",QString("2"));
    else r->setStringByTag("credit",QString("1"));
    log_print("illegal",r->getStringByTag("id"),QString::number(cnt),r->getStringByTag("credit"));

    r->balance -= 10;
    r->is_modf = true;
    log_print("balance",r->getStringByTag("id"),"10.00",QString::number(r->balance,'f',2));
}

Reader * getUser(QString id){
    for (int i=0;i<readerlist.size();i++)
        if (readerlist[i].getStringByTag("id") == id) return &readerlist[i];
    return Q_NULLPTR;
}
