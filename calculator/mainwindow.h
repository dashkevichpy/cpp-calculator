#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Перечисление операций калькулятора
enum class Operation
{
    NO_OPERATION,
    MULTIPLICATION,
    DIVISION,
    SUBTRACTION,
    ADDITION,
    POWER
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Работа с памятью
    void on_btn_MC_clicked();
    void on_btn_MR_clicked();
    void on_btn_MS_clicked();

    // Очистка и изменение знака
    void on_btn_C_clicked();
    void on_btn_revers_clicked();

    // Ввод чисел
    void on_btn_0_clicked();
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_btn_dot_clicked();
    void on_btn_chop_clicked();

    // Арифметические операции
    void on_btn_add_clicked();
    void on_btn_sub_clicked();
    void on_btn_mult_clicked();
    void on_btn_dev_clicked();
    void on_btn_pow_clicked();
    void on_btn_result_clicked();

private:
    Ui::MainWindow *ui_;

    // Калькулятор для выполнения операций
    Calculator calculator_;

    // Текущая операция
    Operation current_operation_ = Operation::NO_OPERATION;

    // Введённое число в виде строки
    QString input_number_;

    // Отображаемое число (результат или текущий ввод)
    Number active_number_ = 0;

    // Значения памяти калькулятора
    Number memory_cell_ = 0;
    bool memory_saved_ = false;

    // Символ текущей операции
    QString operation_symbol_;

    // Обновляет выбранную операцию и формирует строку формулы
    void updateOperation(Operation operation, const QString &symbol);

    void updateActiveNumber(QString n);

};

#endif // MAINWINDOW_H
