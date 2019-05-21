#include "mywindow.h"

int count=0;//第幾張圖片
MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Example 3");
    resize(380, 480);
	setStyleSheet("background-color:#BDC3C7;");
    
    /* 下一張按鈕 */
    next_btn = new QPushButton(">>",this);
	next_btn->setStyleSheet("QPushButton{border: 2px solid #95A5A6;border-radius:10px;color:rgb(22,160,133);background-color:rgb(149,165,166);}");
    next_btn->setFont(QFont("Courier", 25, QFont::Bold));
    next_btn->setGeometry(122, 370, 135, 80);
    connect(next_btn, SIGNAL(clicked()), this, SLOT(NextButton_clicked()));
}

void MyWindow::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	char img_str[15];
	
	if(count>9)
		count=0;
	/*顯示第幾張圖片*/
	snprintf(img_str,sizeof(img_str),"fruit/f%02d.jpg",count);
	/*座標(49,49)大小280×280圖片*/
	painter.drawImage(49,49,QImage(img_str).scaled(280, 280, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MyWindow::NextButton_clicked()
{
	count++;//下一張圖片
    update();
}