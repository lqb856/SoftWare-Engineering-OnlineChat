#ifndef CHAT_H
#define CHAT_H

#include <QMainWindow>
#include <QMessageBox>
namespace Ui {
class Chat;
}

class Chat : public QMainWindow
{
    Q_OBJECT

public:
    Ui::Chat *ui;
    void closeEvent (QCloseEvent * e);

    explicit Chat(QWidget *parent = 0);
    ~Chat();

private:

signals:
    void ChatClose();

};

#endif // CHAT_H
