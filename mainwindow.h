#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_b_doubleSpinBox_valueChanged(double arg1);

    void on_c_doubleSpinBox_valueChanged(double arg1);

    void on_angle_doubleSpinBox_valueChanged(double arg1);

    void on_degrees_radioButton_clicked(bool checked);

    void on_radians_radioButton_clicked(bool checked);

    void on_calc_pushButton_clicked();

    void on_result_lineEdit_textChanged(const QString &arg1);

    void on_error_lineEdit_textChanged(const QString &arg1);

    void on_exit_pushButton_clicked();

private:
    int calcSideOfTriangle(double b, double c, double angle, double & result);
    Ui::MainWindow *ui;
    qreal pvtAngle;
    double pvtB;
    double pvtC;
    bool pvtDegreesOrRadians = true; // true - degrees, false - radians
};
#endif // MAINWINDOW_H
