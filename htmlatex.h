#ifndef HTMLATEX_H
#define HTMLATEX_H

#include <QMainWindow>

namespace Ui {
    class htmlatex;
}

class htmlatex : public QMainWindow {
    Q_OBJECT
private:
    Ui::htmlatex *ui;
protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *e);
public:
    htmlatex(QWidget *parent = 0);
    ~htmlatex();
};

#endif // HTMLATEX_H
