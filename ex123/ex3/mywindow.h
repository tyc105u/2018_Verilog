#include <QtGui/QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QImage>

bool accuracy();

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent*);

private slots:
    void NextButton_clicked();

private:
    /*Button*/
    QPushButton *next_btn;
};
