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
#include <QComboBox>

class BookManageWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit BookManageWindow(QWidget *parent = 0);
    ~BookManageWindow();

protected:
    bool isAddingBook;        //用于判断当前时添加还是删除图书

    //添加界面的元素
    QLineEdit* getTitile;     //用于获取标题
    QLineEdit* getAuthor;     //用于获取作者
    QLineEdit* getPress;      //用于获取出版社
    QComboBox* getCategory;    //用于获取图书类别
    QTextEdit* getDescription; //用于获取简介
    QSpinBox* getAmount;     //用于获取数量
    QPixmap cover;          //获取封面
    QString* defaultCoverPath;     //默认封面路径
    QPixmap* rightArrow;
    QPixmap* leftArrow;
    QPushButton* addBookBtn;  //添加图书按钮
    QPushButton* addCoverBtn; //添加封面按钮
    QToolButton* changePatternBtn; //改变模式的按钮，添加界面为左箭头，否则为右箭头
    Book* newBook;
    void paintEvent(QPaintEvent *paintEvent);

signals:

public slots:
    void changePattern();        //改变模式的函数
    void chooseCover();         //弹出选择图片界面的窗口
    void addNewBook();          //按下添加图书按钮后添加新书

};

#endif // BOOKMANAGEWINDOW_H
