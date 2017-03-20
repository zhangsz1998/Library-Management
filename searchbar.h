#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QLabel>

class SearchBar : public QWidget
{
    Q_OBJECT
public:
    SearchBar(QWidget* parent);
    QLabel* label;
    QLineEdit* lineEdit;
    //QToolButton* searchButton;
public:
    QString text()
    {
        return lineEdit->text();
    }
};

#endif // SEARCHBAR_H
