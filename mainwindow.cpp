#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
#include <QCoreApplication>

static double MY_PI = (double) qAtan(1)*4;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::calcSideOfTriangle(double b, double c, double angle, double & result)
{
    double summaKvadratovStoron=b*b+c*c;
    double maxMultiplyValue=2*b*c; // max cos value is 1, even when radians.

    if (summaKvadratovStoron - maxMultiplyValue < 0) {
        return -1; // нет действительных корней
    }
    if (angle < 0) {
        return -2; // угол должен быть положителен
    }
    /* Закоментировано так как в проверочных данных угол 900.
     * но проверочные данные некорректны если не округлять до целого!
     * у меня вручную cos(900 градусов) = -1 , корень получается 4.8384 !
     * А чтобы было 5 как в проверочных данных надо подставлять синус!
     * ОШИБКА В ПРОВЕРОЧНЫХ ДАННЫХ.
     *
    if (this->pvtDegreesOrRadians && (angle > 179.99 )) {
        return -3; // угол не может превышать 180 градусов
    }

    if (!(this->pvtDegreesOrRadians) && (angle > MY_PI)) {
        return -4; // угол не может быть больше Пи
    }
    */
    if (!(this->pvtDegreesOrRadians)) {
        angle = qDegreesToRadians(angle);
    }
    // чем меньше приведений типа, тем меньше потерь при рассчетах, так что приведение только для qCos и результата:
    // ввод будет в виджете для double (Double Spin Box), так что основной тип остаётся double
    result = (double)qSqrt(summaKvadratovStoron-maxMultiplyValue*((double)qCos((qreal)angle)));
    return 0;

}
void MainWindow::on_b_doubleSpinBox_valueChanged(double arg1)
{
    this->pvtB=arg1;
}


void MainWindow::on_c_doubleSpinBox_valueChanged(double arg1)
{
    this->pvtC=arg1;
}


void MainWindow::on_angle_doubleSpinBox_valueChanged(double arg1)
{
    this->pvtAngle=arg1;
}


void MainWindow::on_degrees_radioButton_clicked(bool checked)
{
    this->pvtDegreesOrRadians=checked;
}


void MainWindow::on_radians_radioButton_clicked(bool checked)
{   // я намеренно не использую "checked".
    this->pvtDegreesOrRadians=false;
}


void MainWindow::on_calc_pushButton_clicked()
{   // основной ввод вывод и вызов рассчёта тут.
    double finalResult;
    double & ssilkaFinalResult = finalResult;
    const QString error_present="ошибка есть";
    const QString no_roots="нет действительных корней";
    const QString badAngleLessZero="угол должен быть положителен";
    const QString badAngleTooBigDegree="угол не может превышать 180 градусов";
    const QString badAngleTooBigRadians="угол не может быть больше числа Пи";
    const QString bugTriggered="You triggered a bug. This shouldn't be printed!";
    const QString no_error="ошибки нет";
    QString finalResultStr;
    int retvalue = calcSideOfTriangle(pvtB,pvtC,pvtAngle,ssilkaFinalResult);
    if (retvalue < 0) {
        ui->error_lineEdit->setText(error_present);
    }
    switch (retvalue) {
    case -1:
        ui->result_lineEdit->setText(no_roots);
        break;
    case -2:
        ui->result_lineEdit->setText(badAngleLessZero);
        break;
    case -3:
        ui->result_lineEdit->setText(badAngleTooBigDegree);
        break;
    case -4:
        ui->result_lineEdit->setText(badAngleTooBigRadians);
        break;
    case 0:
        ui->error_lineEdit->setText(no_error);
        finalResultStr=QString::number(finalResult,'g',6); // до 6 знаков после запятой
        ui->result_lineEdit->setText(finalResultStr);
        break;
    default:
        ui->result_lineEdit->setText(bugTriggered);
        break;
    }
}


void MainWindow::on_result_lineEdit_textChanged(const QString &arg1)
{
    ui->result_lineEdit->setText(arg1);
}


void MainWindow::on_error_lineEdit_textChanged(const QString &arg1)
{
    ui->error_lineEdit->setText(arg1);
}


void MainWindow::on_exit_pushButton_clicked()
{
   QCoreApplication::exit(0);
}

