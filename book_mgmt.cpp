#include <book_mgmt.h>
#include <vector>

QDomDocument doc;
std::vector<Book> booklist,*pbooklist;
QDomNodeList list;

Book::Book(){
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
}

Book::Book(QString &t, QString &a, QString &p, QString &d, QString &i, QString &c, int am, int to, int rc, int bc){
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
    text = doc.createTextNode(QString(amount));
    amNode.appendChild(text);
    QDomElement toNode = doc.createElement(QString("total"));
    text = doc.createTextNode(QString(total));
    toNode.appendChild(text);
    QDomElement catNode = doc.createElement(QString("category"));
    text = doc.createTextNode(category);
    catNode.appendChild(text);
    QDomElement rcNode = doc.createElement(QString("refer_count"));
    text = doc.createTextNode(QString(refer_count));
    rcNode.appendChild(text);
    QDomElement bcNode = doc.createElement(QString("bor_count"));
    text = doc.createTextNode(QString(bor_count));
    bcNode.appendChild(text);
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
    return new_book;
}

QString Book::getStringByTag(QString tag){
    if (tag == "title") return title;
    if (tag == "author") return author;
    if (tag == "press") return press;
    if (tag == "description") return desp;
    if (tag == "id") return id;
    if (tag == "category") return category;
    return QString("");
}

int Book::getIntByTag(QString tag){
    if (tag == "amount") return amount;
    if (tag == "total") return total;
    if (tag == "refer_count") return refer_count;
    if (tag == "bor_count") return bor_count;
}

void Book::setStringByTag(QString tag, QString &text){
    is_modf = true;
    if (tag == "title") this->title = text;
    if (tag == "author") this->author = text;
    if (tag == "press") this->press = text;
    if (tag == "description") this->desp = text;
    if (tag == "id") this->id = text;
    if (tag == "category") this->category = text;
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
    QFile file("C:/Users/hank/Documents/qt/xml/my.xml");
    if (!file.open(QIODevice::ReadOnly)) return NULL;
    if (!doc.setContent(&file)){
        file.close();
        return NULL;
    }
    file.close();
    QDomNode firstNode = doc.documentElement();
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
    booklist.push_back(book);
}

void update(){
    for (std::vector<Book>::iterator it=booklist.begin();it!=booklist.end();++it)
        if (it->is_modf)
            list.at(it->order) = it->toDom();
}

void saveXml(){
    QFile file("C:/Users/hank/Documents/qt/xml/my.xml");
    update();
    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate)) return;
    QTextStream out(&file);
    doc.save(out,2);
    file.close();
}
