#include "loginwindow.h"

extern Reader* activereader;
LoginWindow::LoginWindow(QWidget *parent) : QDialog(parent)
{
    this->setGeometry(300*dpi,180*dpi,450*dpi,350*dpi);
    setWindowFlags(Qt::FramelessWindowHint);      //设置无边

    closeBtn= new ToolButton(this,QColor(0,0,0,0),QColor(0,153,255,255));
    closeBtn->setEnterColor("#ff6666");
    closeBtn->setGeometry(this->width()-29*dpi,1*dpi,29*dpi,29*dpi);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeBtn->setIcon(closePix);
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    loginBtn=new ToolButton(this);
    loginBtn->setPlainColor("#09a3dc");
    loginBtn->setEnterColor("#3cc3f5");
    QPalette textPalette(Qt::white);
    loginBtn->setPalette(textPalette);
    loginBtn->setGeometry(50*dpi,290*dpi,150*dpi,35*dpi);
    loginBtn->setText("登录");
    connect(loginBtn,SIGNAL(clicked()),this,SLOT(checkPassWord()));

    signUpBtn=new ToolButton(this);
    signUpBtn->setPlainColor("#09a3dc");
    signUpBtn->setEnterColor("#3cc3f5");
    signUpBtn->setPalette(textPalette);
    signUpBtn->setGeometry(250*dpi,290*dpi,150*dpi,35*dpi);
    signUpBtn->setText("注册");
    connect(signUpBtn,SIGNAL(clicked()),this,SLOT(showSignUpWindow()));

    getUserName=new QLineEdit(this);
    getUserName->setGeometry(100*dpi,200*dpi,250*dpi,40*dpi);
    getUserName->setStyleSheet("background-color:transparent;border:1px;border-color:#c0c0c0;border-style:solid;border-top-left-radius:4px;border-top-right-radius: 4px;");
    getUserName->setFont(QFont("微软雅黑",15));
    getUserName->setPlaceholderText("Id");

    getPassWord=new QLineEdit(this);
    getPassWord->setGeometry(100*dpi,240*dpi,250*dpi,40*dpi);
    getPassWord->setStyleSheet("background-color:transparent;border: 1px;border-top:0px;border-color:#c0c0c0;border-style:solid;border-bottom-left-radius:4px;border-bottom-right-radius: 4px;");
    getPassWord->setFont(QFont("微软雅黑",15));
    getPassWord->setEchoMode(QLineEdit::Password);
    getPassWord->setPlaceholderText("密码");
    connect(getPassWord,SIGNAL(returnPressed()),this,SLOT(checkPassWord()));

    popUp=new MessageBox(this);
    popUp->move(QPoint(100*dpi,100*dpi));
    popUp->setStyleSheet("background-color:white");
    popUp->setText("用户名或密码错误");
    popUp->setVisible(false);
    connect(popUp->confirmBtn,SIGNAL(clicked()),this,SLOT(tryToClose()));

    signUpWindow=new SignUpWindow(this);
    signUpWindow->setVisible(false);
    connect(signUpWindow,SIGNAL(signedUp()),this,SLOT(userSignedUp()));
    connect(signUpWindow,SIGNAL(loggedIn()),this,SLOT(close()));

}

LoginWindow::~LoginWindow()
{
    delete getUserName;
    delete getPassWord;
    delete loginBtn;
    delete signUpBtn;
    delete closeBtn;
    delete signUpWindow;
    delete popUp;
}

void LoginWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap background(":/Images/Icons/Login.png");
    painter.drawPixmap(1,1,background.scaled(448*dpi,173*dpi,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void LoginWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        //改变并存储鼠标形状
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);

        //计算鼠标位置与界面位置的差值
        offset=event->globalPos()-this->pos();
    }
}

void LoginWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QApplication::restoreOverrideCursor();
}

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        //计算需要移动到的新位置
        QPoint temp;
        temp=event->globalPos()-offset;

        //移动界面
        move(temp);
    }
}

void LoginWindow::checkPassWord()
{
    QString id=getUserName->text();
    QString passWord=getPassWord->text();
    //match?
    int loginPattern;
    activereader = sign_in(id, passWord, loginPattern);
    if(loginPattern==1)
    {
        popUp->setText("登录成功");
        log_print("login",activereader->getStringByTag("id"),"","");
        this->getUserName->clear();
        this->getPassWord->clear();
        emit logedIn();
    }
    else if(loginPattern==2)
    {
        popUp->setText("密码错误");
        this->getPassWord->clear();
    }
    else
        popUp->setText("用户不存在");
    popUp->setVisible(true);
}

void LoginWindow::showSignUpWindow()
{
    signUpWindow->setVisible(true);
}

void LoginWindow::tryToClose()
{
    if(popUp->getText()=="登录成功")
    {
        this->close();
    }
}

void LoginWindow::userSignedUp()
{
    emit logedIn();
}


