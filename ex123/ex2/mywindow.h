#include <QtGui/QWidget>
#include <QPushButton>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPixmap>
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
    void ClearButton_clicked();
    void ConfirmButton_clicked();   

private:
    //HandWriting
    QVector<QPoint> stroke;
    QVector<QVector<QPoint> >lines;
    bool painting;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    //Button
    QPushButton *clr_btn;
    QPushButton *conf_btn;
};

