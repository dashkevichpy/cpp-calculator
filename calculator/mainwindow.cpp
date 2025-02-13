#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow){

    ui_->setupUi(this);
    ui_->l_result->setText("0");
    ui_->l_memory->clear();
    ui_->l_formula->clear();
}

MainWindow::~MainWindow(){

    delete ui_;
}

// ==================== Работа с памятью ====================

void MainWindow::on_btn_MC_clicked(){

    memory_cell_ = 0;
    memory_saved_ = false;
    ui_->l_memory->clear();
}

void MainWindow::on_btn_MR_clicked(){

    if (memory_saved_) {
        active_number_ = memory_cell_;
        input_number_ = QString::number(active_number_);
        ui_->l_result->setText(input_number_);
    }
}

void MainWindow::on_btn_MS_clicked(){

    if (!input_number_.isEmpty()) {
        active_number_ = input_number_.toDouble();
    }
    memory_cell_ = active_number_;
    memory_saved_ = true;
    ui_->l_memory->setText("M");
}

// =============== Очистка и изменение знака ===============

void MainWindow::on_btn_C_clicked(){

    input_number_.clear();
    active_number_ = 0;
    current_operation_ = Operation::NO_OPERATION;
    ui_->l_formula->clear();
    ui_->l_result->setText(QString::number(active_number_));
}

void MainWindow::on_btn_revers_clicked(){

    if (input_number_.isEmpty()) {
        active_number_ = -active_number_;
        ui_->l_result->setText(QString::number(active_number_));
    } else {
        if (input_number_.startsWith('-')) {
            input_number_.remove(0, 1);
        } else {
            input_number_.prepend("-");
        }
        ui_->l_result->setText(input_number_);
    }
}

// ==================== Ввод чисел ====================

void MainWindow::on_btn_0_clicked(){
    if(input_number_ == "0")
        return;
    updateActiveNumber("0");

}

void MainWindow::on_btn_1_clicked(){

    updateActiveNumber("1");

}

void MainWindow::on_btn_2_clicked(){

    updateActiveNumber("2");

}

void MainWindow::on_btn_3_clicked(){

    updateActiveNumber("3");

}

void MainWindow::on_btn_4_clicked(){

    updateActiveNumber("4");

}

void MainWindow::on_btn_5_clicked(){

    updateActiveNumber("5");

}

void MainWindow::on_btn_6_clicked(){

    updateActiveNumber("6");

}

void MainWindow::on_btn_7_clicked(){

    updateActiveNumber("7");

}

void MainWindow::on_btn_8_clicked(){

    updateActiveNumber("8");

}

void MainWindow::on_btn_9_clicked(){

    updateActiveNumber("9");

}

void MainWindow::on_btn_dot_clicked(){

    if (!input_number_.contains('.')) {
        input_number_ += ".";
    }
}

void MainWindow::on_btn_chop_clicked(){

    input_number_.chop(1);
}

// ============== Арифметические операции ==============

void MainWindow::on_btn_add_clicked(){

    updateOperation(Operation::ADDITION, "+");
}

void MainWindow::on_btn_sub_clicked(){

    updateOperation(Operation::SUBTRACTION, "−");
}

void MainWindow::on_btn_mult_clicked(){

    updateOperation(Operation::MULTIPLICATION, "×");
}

void MainWindow::on_btn_dev_clicked(){

    updateOperation(Operation::DIVISION, "÷");
}

void MainWindow::on_btn_pow_clicked(){

    updateOperation(Operation::POWER, "^");
}

void MainWindow::on_btn_result_clicked(){

    if (current_operation_ == Operation::NO_OPERATION)
        return;

    double secondOperand = (!input_number_.isEmpty()) ? input_number_.toDouble() : active_number_;

    ui_->l_formula->setText(QString("%1 %2 %3 =")
                                .arg(calculator_.GetNumber())
                                .arg(operation_symbol_)
                                .arg(secondOperand));

    switch (current_operation_) {
    case Operation::ADDITION:
        calculator_.Add(secondOperand);
        break;
    case Operation::SUBTRACTION:
        calculator_.Sub(secondOperand);
        break;
    case Operation::MULTIPLICATION:
        calculator_.Mul(secondOperand);
        break;
    case Operation::DIVISION:
        calculator_.Div(secondOperand);
        break;
    case Operation::POWER:
        calculator_.Pow(secondOperand);
        break;
    default:
        break;
    }

    active_number_ = calculator_.GetNumber();
    ui_->l_result->setText(QString::number(active_number_));

    input_number_.clear();
    current_operation_ = Operation::NO_OPERATION;
}

// ================ Вспомогательные методы ================

void MainWindow::updateOperation(Operation op, const QString &symbol){

    if (!input_number_.isEmpty()) {
        active_number_ = input_number_.toDouble();
    }
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }
    current_operation_ = op;
    operation_symbol_ = symbol;
    input_number_.clear();
    ui_->l_formula->setText(QString("%1 %2")
                                .arg(active_number_)
                                .arg(operation_symbol_));
}

void MainWindow::updateActiveNumber(QString n){
    input_number_ += n;
    ui_->l_result->setText(input_number_);
}
