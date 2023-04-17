#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <qcustomplot.h>
#include "receiverHWImpl.h"
#include "Complex.h"


class Window:public QWidget, public QThread
{
    Q_OBJECT
    protected:
    QFrame *frame; // рамка
    QLabel *centFreqLabel;
    QLineEdit *centFreqEdit;
    QLabel *sampleFreqLabel;
    QLineEdit *sampleFreqEdit;
    QLabel *bytes_to_readLabel;
    QLineEdit *bytes_to_readEdit;
    QLabel  *sampleCountLabel;
    QLineEdit *sampleCountEdit;
    QPushButton *set;
    QPushButton *start; // кнопка старт
    QPushButton *stop; // кнопка стоп
    QCustomPlot *real;
    QCustomPlot *imag;
    QCustomPlot *spectr;
    public:
        Window(QWidget *parent=0);
        virtual ~Window(){};
//        ReceiverHWImpl rcv;
    public slots:
        void begin();
        void calc();
        void setReceiverParameters();
        void startReceiver(QVector<double> &x,QVector<double> &y);
        void stopReceiver();

};



class StrValidator:public QValidator // класс компонента проверки ввода
{
    public:
    StrValidator(QObject *parent):QValidator(parent){}
    virtual State validate(QString &str,int &pos)const
    {
        return Acceptable; // метод всегда принимает вводимую строку
    }
};

QVector<double> soz(QVector<Complex<double>> &vec);

void grapInit(QCustomPlot *graph,QVector<double> &x,QVector<double> &y);



#endif // WINDOW_H
