#include <book_mgmt.h>
#include <vector>
#include <QString>
#include <QRegularExpression>
#include <algorithm>
#include <QTextCodec>
#include <QCryptographicHash>
#include <QByteArray>

QDomDocument doc;
std::vector<Book> booklist,*pbooklist;
QDomNode firstNode;
QDomNodeList list;
extern QDate systemDate;

//数据文件目录与路径,均在main.cpp中作为全局变量定义
extern QString dataDir;
extern QString bookInfoPath;
extern QString readerInfoPath;
extern QString coverDir;

Book::Book(){
    is_modf = false;
    is_delete = false;
}
Book & Book::operator= (const Book & dul){
    if (this == &dul) return *this;
    this->title = dul.title;
    this->author = dul.author;
    this->press = dul.press;
    this->desp = dul.desp;
    this->id = dul.id;
    this->amount = dul.amount;
    this->total = dul.total;
    this->category = dul.category;
    this->refer_count = dul.refer_count;
    this->bor_count = dul.bor_count;
    this->loc = dul.loc;
    this->is_resv = dul.is_resv;
    return *this;
}

Book::Book(const QDomNode a){
    QDomNodeList list=a.childNodes();
    this->title=list.at(0).toElement().text();
    this->author = list.at(1).toElement().text();
    this->press = list.at(2).toElement().text();
    this->desp = list.at(3).toElement().text();
    this->id = list.at(4).toElement().text();
    this->amount = list.at(5).toElement().text().toInt();
    this->total = list.at(6).toElement().text().toInt();
    this->category =list.at(7).toElement().text();
    this->refer_count = list.at(8).toElement().text().toInt();
    this->bor_count = list.at(9).toElement().text().toInt();
    QString tmp = list.at(10).toElement().text();
    if (tmp[0]==':') this->loc = tmp;
    else this->loc = coverDir + tmp;
    tmp = list.at(11).toElement().text();
    if (tmp=="0")
        this->is_resv = false;
    else
        this->is_resv = true;
    is_modf = false;
    is_delete = false;
}

Book::Book(QString &t, QString &a, QString &p, QString &d, QString &i, QString &c, int am, int to, int rc, int bc,QString &lc,int is_r){
    this->title = t;
    this->author = a;
    this->press = p;
    this->desp = d;
    this->id = i;
    this->amount = am;
    this->total = to;
    this->category = c;
    this->refer_count =rc;
    this->bor_count = bc;
    this->loc = lc;
    this->is_resv = is_r;
    is_modf = false;
    is_delete = false;
}

QDomElement Book::toDom(){

    QDomElement titleNode = doc.createElement(QString("title"));
    QDomText text = doc.createTextNode(title);
    titleNode.appendChild(text);
    QDomElement authorNode = doc.createElement(QString("author"));
    text = doc.createTextNode(author);
    authorNode.appendChild(text);
    QDomElement pressNode = doc.createElement(QString("press"));
    text = doc.createTextNode(press);
    pressNode.appendChild(text);
    QDomElement despNode = doc.createElement(QString("description"));
    text = doc.createTextNode(desp);
    despNode.appendChild(text);
    QDomElement idNode = doc.createElement(QString("id"));
    text = doc.createTextNode(id);
    idNode.appendChild(text);
    QDomElement amNode =doc.createElement(QString("amount"));
    text = doc.createTextNode(QString::number(amount));
    amNode.appendChild(text);
    //qDebug() << amNode.toElement().text();
    QDomElement toNode = doc.createElement(QString("total"));
    text = doc.createTextNode(QString::number(total));
    toNode.appendChild(text);
    QDomElement catNode = doc.createElement(QString("category"));
    text = doc.createTextNode(category);
    catNode.appendChild(text);
    QDomElement rcNode = doc.createElement(QString("refer_count"));
    text = doc.createTextNode(QString::number(refer_count));
    rcNode.appendChild(text);
    QDomElement bcNode = doc.createElement(QString("bor_count"));
    text = doc.createTextNode(QString::number(bor_count));
    bcNode.appendChild(text);
    QDomElement lcNode = doc.createElement(QString("loc"));
    if (loc[0]==':') text = doc.createTextNode(loc);
    else text = doc.createTextNode(loc.right(loc.length()-coverDir.length()));
    lcNode.appendChild(text);
    QDomElement rdNode = doc.createElement(QString("is_resv"));
    if (is_resv) text = doc.createTextNode(QString("1"));
        else text = doc.createTextNode(QString("0"));
    rdNode.appendChild(text);
    QDomElement new_book = doc.createElement(QString("book"));
    new_book.appendChild(titleNode);
    new_book.appendChild(authorNode);
    new_book.appendChild(pressNode);
    new_book.appendChild(despNode);
    new_book.appendChild(idNode);
    new_book.appendChild(amNode);
    new_book.appendChild(toNode);
    new_book.appendChild(catNode);
    new_book.appendChild(rcNode);
    new_book.appendChild(bcNode);
    new_book.appendChild(lcNode);
    new_book.appendChild(rdNode);
    return new_book;
}

QString Book::getStringByTag(QString tag){
    if (tag == "title") return title;
    if (tag == "author") return author;
    if (tag == "press") return press;
    if (tag == "description") return desp;
    if (tag == "id") return id;
    if (tag == "category") return category;
    if (tag == "loc") return loc;
    return QString("");
}

int Book::getIntByTag(QString tag){
    if (tag == "amount") return amount;
    if (tag == "total") return total;
    if (tag == "refer_count") return refer_count;
    if (tag == "bor_count") return bor_count;
}

void Book::setStringByTag(QString tag, QString text){
    is_modf = true;
    if (tag == "title") this->title = text;
    if (tag == "author") this->author = text;
    if (tag == "press") this->press = text;
    if (tag == "description") this->desp = text;
    if (tag == "id") this->id = text;
    if (tag == "category") this->category = text;
    if (tag == "loc") this->loc = text;
}

void Book::setIntByTag(QString tag, int num){
    is_modf = true;
    if (tag == "amount") this->amount = num;
    if (tag == "total") this->total = num;
    if (tag == "refer_count") this->refer_count = num;
    if (tag == "bor_count") this->bor_count = num;
}

void Book::DecIntByTag(QString tag){
    is_modf = true;
    if (tag == "amount") --this->amount;
    if (tag == "total") --this->total;
    if (tag == "refer_count") --this->refer_count;
    if (tag == "bor_count") --this->bor_count;
}

void Book::IncIntByTag(QString tag){
    is_modf = true;
    if (tag == "amount") ++this->amount;
    if (tag == "total") ++this->total;
    if (tag == "refer_count") ++this->refer_count;
    if (tag == "bor_count") ++this->bor_count;
}

std::vector<Book> * getXml(){
    QFile file(bookInfoPath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Open failed.";
        return NULL;
    }
    if (!doc.setContent(&file)){
        file.close();
        return NULL;
    }
    file.close();
    firstNode = doc.documentElement();
    list = firstNode.childNodes();
    for (int i=0;i<list.count();i++){
        booklist.push_back(Book(list.at(i)));
        booklist[i].order = i;
    }
    pbooklist = &booklist;
    return pbooklist;
}

void Book::display(){
        qDebug() << qPrintable(this->title) <<" " << qPrintable(this->author);
}

void add_newbook(Book & book){
    for (std::vector<Book>::iterator it=booklist.begin();it!=booklist.end();++it)
        if (it->getStringByTag(QString("id")) == book.getStringByTag(QString("id"))){
            it->setIntByTag(QString("id"),it->getIntByTag(QString("amount"))+book.getIntByTag(QString("amount")));
            return;
        }
     if (booklist.size())
        book.order=booklist.back().order + 1;
    else book.order=0;
    booklist.push_back(book);
}

void fileUpdate(){
    if (!booklist.empty()){
        while (booklist.back().is_delete == true) booklist.pop_back();
        for (std::vector<Book>::iterator it=booklist.begin();it!=booklist.end();++it)
            if (it->is_delete) {
                firstNode.removeChild(firstNode.childNodes().at(it->order));
                for (std::vector<Book>::iterator ir=it+1;ir!=booklist.end();ir++)
                    ir->order--;
                booklist.erase(it);
            }
            else if (it->is_modf && it->order < list.count()){
                QDomNode tmp = it->toDom();
                firstNode.replaceChild(tmp,firstNode.childNodes().at(it->order));
                list = firstNode.childNodes();
            }
            else if (it->order >= list.count())
                doc.documentElement().appendChild(it->toDom());
    }
}

void saveXml(){
    QFile file(bookInfoPath);
    fileUpdate();
    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate)) return;
    QTextStream out(&file);
    doc.save(out,2);
    file.close();
}

bool match(Book & b,QRegExp &rx,int mode){
    if (mode == 1) return rx.exactMatch(b.getStringByTag("title"));
    else if (mode == 2) return rx.exactMatch(b.getStringByTag("author"));
    else if (mode == 3) return rx.exactMatch(b.getStringByTag("press"));
    else if (mode == 4) return rx.exactMatch(b.getStringByTag("description"));
    else if (mode == 5) return rx.exactMatch(b.getStringByTag("id"));
    else if (mode == 6) return rx.exactMatch(b.getStringByTag("category"));
    else return ((rx.exactMatch(b.getStringByTag("title"))) || (rx.exactMatch(b.getStringByTag("author"))) || (rx.exactMatch(b.getStringByTag("press"))) || (rx.exactMatch(b.getStringByTag("description"))) || (rx.exactMatch(b.getStringByTag("id"))) || (rx.exactMatch(b.getStringByTag("category"))));
}

std::vector<Book *> search(QString kw,int mode){
    QString pattern("^.*");
    if (mode!=5)
    for (int i=0;i<kw.size();i++)
        pattern += "("+kw[i]+").*";
    else pattern += kw;
    pattern += "$";
    QRegExp rx(pattern);
    std::vector<Book *> res;
    for (int i=0;i<booklist.size();i++)
        if (match(booklist[i],rx,mode)) res.push_back(&booklist[i]);
    return res;
}

bool compareBor(Book &i,Book &j){
    return i.getIntByTag("bor_count") < j.getIntByTag("bor_count");
}

bool compareRef(Book &i,Book &j){
    return i.getIntByTag("refer_count")<j.getIntByTag("refer_count");
}

std::vector<Book *> topBor(){
    std::vector<Book> mylist = booklist;
    std::sort(mylist.begin(),mylist.end(),compareBor);
    std::vector<Book *> res;
    for (int i=0;i<10;i++){
        res.push_back(&mylist[i]);
    }
    return res;
}

std::vector<Book *> topRef(){
    std::vector<Book> mylist = booklist;
    std::sort(mylist.begin(),mylist.end(),compareRef);
    std::vector<Book *> res;
    for (int i=0;i<10;i++){
        res.push_back(&mylist[i]);
    }
    return res;
}

QString myHash(QString author,QString press, QString category,QString name){
    unsigned int a,p,n;
    a=p=n=0;
    QCryptographicHash sha(QCryptographicHash::Sha1);
    QByteArray tmp = sha.hash(author.toUtf8(),QCryptographicHash::Sha1);
    for (int i=0;i<tmp.size();i++)
        a = (a+(unsigned int)tmp[i]) %2053;
    a %= 1000;
    tmp = sha.hash(press.toUtf8(),QCryptographicHash::Sha1);
    for (int i=0;i<tmp.size();i++)
        p = (p+(unsigned int)tmp[i]) %2203;
    p %= 1000;
    tmp = sha.hash(name.toUtf8(),QCryptographicHash::Sha1);
    for (int i=0;i<tmp.size();i++)
        n = (n+(unsigned int)tmp[i]) % 2689;
    n %= 1000;
    QString res = categoryId(category)+QString(QString::number(a)+QString::number(p)+QString::number(n));
    int flag =1;
    while (flag){
        flag = 0;
        for (int i=0;i<booklist.size();i++)
            flag = flag || (booklist[i].getStringByTag("id") == res);
        if (flag==1) {
            n = (n+1)%1000;
            res.replace(8,3,QString::number(n));
        }
    }
    return res;
}

QString categoryString(QString s){
    if (s=="10") return "文学";
    if (s=="11") return "小说";
    if (s=="12") return "传记";
    if (s=="13") return "青春与动漫";
    if (s=="14") return "经济";
    if (s=="15") return "投资理财";
    if (s=="16") return "少儿";
    if (s=="17") return "历史";
    if (s=="18") return "哲学与宗教";
    if (s=="19") return "国学";
    if (s=="20") return "心理学";
    if (s=="21") return "政治与军事";
    if (s=="22") return "法律";
    if (s=="23") return "社会科学";
    if (s=="24") return "孕产育儿";
    if (s=="25") return "旅游与地图";
    if (s=="26") return "烹饪美食与酒";
    if (s=="27") return "健身与保健";
    if (s=="28") return "婚恋与两性";
    if (s=="29") return "娱乐";
    if (s=="30") return "时尚";
    if (s=="31") return "家居休闲";
    if (s=="32") return "教辅";
    if (s=="33") return "考试";
    if (s=="34") return "英语与其他外语";
    if (s=="35") return "词典与工具书";
    if (s=="36") return "励志与成功";
    if (s=="37") return "科技";
    if (s=="38") return "医学";
    if (s=="39") return "计算机与互联网";
    if (s=="40") return "科学与自然";
}

QString categoryId(QString s){
    if(s=="文学")
        return QString::number(10);
    if(s=="小说")
        return QString::number(11);
    if(s=="传记")
        return QString::number(12);
    if(s=="青春与动漫")
        return QString::number(13);
    if(s=="经济")
        return QString::number(14);
    if(s=="投资理财")
        return QString::number(15);
    if(s=="少儿")
        return QString::number(16);
    if(s=="历史")
        return QString::number(17);
    if(s=="哲学与宗教")
        return QString::number(18);
    if(s=="国学")
        return QString::number(19);
    if(s=="心理学")
        return QString::number(20);
    if(s=="政治与军事")
        return QString::number(21);
    if(s=="法律")
        return QString::number(22);
    if(s=="社会科学")
        return QString::number(23);
    if(s=="孕产育儿")
        return QString::number(24);
    if(s=="旅游与地图")
        return QString::number(25);
    if(s=="烹饪美食与酒")
        return QString::number(26);
    if(s=="健身与保健")
        return QString::number(27);
    if(s=="婚恋与两性")
        return QString::number(28);
    if(s=="娱乐")
        return QString::number(29);
    if(s=="时尚")
        return QString::number(30);
    if(s=="家居休闲")
        return QString::number(31);
    if(s=="教辅")
        return QString::number(32);
    if(s=="考试")
        return QString::number(33);
    if(s=="英语与其他外语")
        return QString::number(34);
    if(s=="词典与工具书")
        return QString::number(35);
    if(s=="励志与成功")
        return QString::number(36);
    if(s=="科技")
        return QString::number(37);
    if(s=="医学")
        return QString::number(38);
    if(s=="计算机与互联网")
        return QString::number(39);
    if(s=="科学与自然")
        return QString::number(40);
}

void log_print(QString format,QString a,QString b,QString c){
    QFile f(dataDir+ "/library.log");
    if (!f.open(QIODevice::Append|QIODevice::Text))
        if (!f.open(QIODevice::WriteOnly|QIODevice::Text)) return;
    QTextStream outlog(&f);
    //QTextCodec *codec=QTextCodec::codecForName("GBK");
    //outlog.setCodec(codec);
    if (format == "initial") outlog <<systemDate.toString("yyyy-MM-dd")<<QString(" 程序已启动")<<".\n";
    if (format == "borrow") outlog<<systemDate.toString("yyyy-MM-dd")<<QString(" 用户<")<<a<<QString(">已借阅图书<")<<b<<QString(">,预期归还时间为")<<c<<".\n";
    //  borrowform.cpp 107
    if (format == "reserve") outlog<<systemDate.toString("yyyy-MM-dd")<<QString(" 用户<")<<a <<QString(">已预订图书<")<<b<<">.\n";
    //  resvform.cpp 120
    if (format == "add") outlog<<systemDate.toString("yyyy-MM-dd") <<QString(" 管理员<")<<a<<QString(">已添加图书<")<<b<<">.\n";
    //  bookmamagewindow.cpp 460
    if (format == "delete") outlog<<systemDate.toString("yyyy-MM-dd") <<QString(" 管理员<")<<a<<QString(">已删除图书<")<<b<<QString(">,删除原因为")<<c<<".\n";
    //  bookmanagewindow.cpp 511
    if (format == "modify") outlog<<systemDate.toString("yyyy-MM-dd") <<QString(" 管理员<")<<a<<QString(">已修改图书<")<<b<<QString(">,修改原因为")<<c<<".\n";
    //  bookmanagewindow.cpp 533
    if (format == "report") outlog<<systemDate.toString("yyyy-MM-dd") <<QString(" 用户<")<<a<<QString(">已挂失图书<")<<b<<QString(">,挂失理由为")<<c<<".\n";
    //  reportreasonwindow.cpp
    if (format == "renew") outlog <<systemDate.toString("yyyy-MM-dd") <<QString(" 用户<")<<a<<QString(">已续借图书<")<<b<<QString(">,预期归还时间为")<<c<<".\n";
    //  reader_mgmt.cpp 309
    if (format == "recharge") outlog <<systemDate.toString("yyyy-MM-dd") <<QString(" 用户<")<<a<<QString(">已充值")<<b<<QString("元,余额为")<<c<<QString("元")<<".\n";
    //  personalinfowindow.cpp 294
    if (format == "return") outlog<<systemDate.toString("yyyy-MM-dd") <<QString(" 用户<")<<a<<QString(">已于")<<b<<QString(" 归还图书<")<<c<<">.\n";
    //  reader_mgmt.cpp 329
    if (format == "login") outlog<<systemDate.toString("yyyy-MM-dd") <<QString(" 用户<")<<a<<QString(">已登陆")<<".\n";
    //  loginwindow.cpp 109
    if (format == "signup") outlog<<systemDate.toString("yyyy-MM-dd") <<QString(" 新用户<")<<a<<QString(">已注册并登陆")<<".\n";
    // signupwindow.cpp 97
    if (format == "expire") outlog<<systemDate.toString("yyyy-MM-dd") <<QString(" 用户<")<<a<<QString(">借阅图书<")<<b<<QString(">已超期")<<c<<QString("天")<<".\n";
    //  widget.cpp 445 469 487
    if (format == "balance") outlog <<systemDate.toString("yyyy-MM-dd") <<QString(" 用户<")<<a<<QString(">账户余额扣除")<<b<<QString("元,余额为")<<c<<QString("元")<<".\n";
    //  widget.cpp 494 498 502
    if (format == "signout") outlog<<systemDate.toString("yyyy-MM-dd") <<QString(" 用户<")<<a<<QString(">已登出")<<".\n";
    //  widget.cpp 371 381
    if (format == "illegal"){
        if (c == "3") outlog <<systemDate.toString("yyyy-MM-dd") <<QString( " 用户<")<<a<<QString(">不良记录次数已累计")<<b<<QString("次,信用等级现为差")<<".\n";
        else if (c == "2") outlog<<systemDate.toString("yyyy-MM-dd") <<QString( " 用户<")<<a<<QString(">不良记录次数已累计")<<b<<QString("次,信用等级现为良好")<<".\n";
        else outlog<<systemDate.toString("yyyy-MM-dd") <<QString( " 用户<")<<a<<QString(">不良记录次数已累计")<<b<<QString("次,信用等级现为优秀")<<".\n";
    }
    //  widget.cpp 451
    if (format == "close") outlog<<systemDate.toString("yyyy-MM-dd")<<QString(" 程序已关闭.")<<"\n";
    f.close();
}

std::vector<QString> getTopCat(void){
    int cnt[31];
    int flag[31];
    for (int i=0;i<=30;i++) { cnt[i]=0; flag[i]=i;}
    for (int i=0;i<booklist.size();i++)
        cnt[categoryId(booklist[i].getStringByTag("category")).toInt()-10]++;
    for (int i=0;i<=30;i++)
        for (int j=i+1;j<=30;j++)
            if (cnt[i]<cnt[j]) {
                int tmp = cnt[i];
                cnt[i]=cnt[j];
                cnt[j]=tmp;
                tmp = flag[i];
                flag[i] = flag[j];
                flag[j]=tmp;
            }
    std::vector<QString> res;
    for (int i=0;i<8;i++)
        res.push_back(categoryString(QString::number(flag[i]+10)));
    return res;
}

std::vector<Book *> getCatTopBor(QString cat){
    std::vector<Book> mylist;
    for (int i=0;i<booklist.size();i++)
        if (booklist[i].getStringByTag("category")==cat)
            mylist.push_back(booklist[i]);
    std::sort(mylist.begin(),mylist.end(),compareBor);
    std::vector<Book *> res;
    for (int i=0;i<(mylist.size()<10?mylist.size():10);i++)
         res.push_back(&booklist[mylist[i].order]);
    return res;
}

std::vector<Book *> getCatTopRef(QString cat){
    std::vector<Book> mylist;
    for (int i=0;i<booklist.size();i++)
        if (booklist[i].getStringByTag("category")==cat)
            mylist.push_back(booklist[i]);
    std::sort(mylist.begin(),mylist.end(),compareRef);
    std::vector<Book *> res;
    for (int i=0;i<(mylist.size()<10?mylist.size():10);i++)
         res.push_back(&booklist[mylist[i].order]);
    return res;
}

QDate getDate(){
    QFile f(dataDir+"/system.cfg");
    if (!f.open(QIODevice::ReadOnly|QIODevice::Text))
        return QDate::currentDate();
    QTextStream in(&f);
    QString d;
    in >> d;
    QDate res;
    if (d.length()==10)
        res = QDate::fromString(d,"yyyy-MM-dd");
    else
        res = QDate::currentDate();
    f.close();
    return res;
}

void configureDate(){
    QFile f(dataDir+"/system.cfg");
    if (!f.open(QIODevice::WriteOnly|QIODevice::Text)) return;
    QTextStream out(&f);
    out << systemDate.toString("yyyy-MM-dd");
    f.close();
}
