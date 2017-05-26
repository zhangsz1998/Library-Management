#ifndef BOOKMANAGEWINDOW_H
#define BOOKMANAGEWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QToolButton>
#include <QPainter>
#include <QSpinBox>
#include <QTextEdit>
#include <QFileDialog>
#include <QUrl>
#include "book_mgmt.h"
#include "toolbutton.h"
#include <QComboBox>
#include <QCheckBox>
#include "messagebox.h"
#include "authoritycheckwindow.h"
#include "getreasonwindow.h"
#include <QStringList>

enum Pattern
{
    adding,
    searching,
    editing
};

enum ChangeInfoPattern
{
    Modify,
    Delete
};

class BookManageWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit BookManageWindow(QWidget *parent = 0);
    int getCategoryIndex(QString s);
    ~BookManageWindow();

protected:
    Pattern pattern;        //用于判断当前时添加还是删除图书

    //添加/修改界面的元素
    QLineEdit* getTitile;     //用于获取标题
    QLineEdit* getAuthor;     //用于获取作者
    QLineEdit* getPress;      //用于获取出版社
    QComboBox* getCategory;    //用于获取图书类别
    QTextEdit* getDescription; //用于获取简介
    QSpinBox* getAmount;     //用于获取数量
    QPixmap cover;          //获取封面
    QString* defaultCoverPath;     //默认封面路径
    QString newCoverPath;
    QPixmap* rightArrow;
    QPixmap* leftArrow;
    QPushButton* addBookBtn;  //添加图书按钮
    QPushButton* addCoverBtn; //添加封面按钮

    //搜索界面
    ToolButton* searchBtn;    //搜索id
    QLineEdit* getId;     //用于获取图书编号

    //修改界面
    ToolButton* modifyConfirmBtn;   //确认修改；
    ToolButton* deleteBtn;    //删除图书按钮
    AuthorityCheckWindow* checkWindow;    //检查管理员身份
    GetReasonWindow* getReasonWindow;
    ChangeInfoPattern changeInfoPattern;  //判断当前修改模式是删除还是修改

    QToolButton* changePatternBtn; //改变模式的按钮，添加界面为左箭头，否则为右箭头
    Book* newBook;
    Book* bookEditing;
    MessageBox* popUp;  //添加成功弹窗
    void paintEvent(QPaintEvent *paintEvent);

    QStringList modifyReasons;
signals:

public slots:
    void changePattern();        //改变模式的函数:添加或删减图书
    void chooseCover();         //弹出选择图片界面的窗口
    void addNewBook();          //按下添加图书按钮后添加新书
    void searchToEdit();      //搜索修改的图书
    void changeBookInfo();      //修改图书信息
    void checkAuthority();      //弹出身份验证界面
    void notAuthorized();      //管理员身份验证失败
    void isAuthorized();        //验证成功
    void nowEditing();    //修改模式为修改
    void nowDeleting();       //修改模式为删除
};

#endif // BOOKMANAGEWINDOW_H
