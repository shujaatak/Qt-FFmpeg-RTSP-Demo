#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <qstring.h>
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    QString getRtspURL();
private slots:
    void on_btn_play_clicked();

private:
    Ui::Login *ui;
    QString rtspURL;
};

#endif // LOGIN_H
