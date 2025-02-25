#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QComboBox>
#include <QLabel>

static ControllerType ControllerTypeFromString(const QString& text) {
    if (text == "double")   return ControllerType::DOUBLE;
    if (text == "float")    return ControllerType::FLOAT;
    if (text == "uint8_t")  return ControllerType::UINT8_T;
    if (text == "int")      return ControllerType::INT;
    if (text == "int64_t")  return ControllerType::INT64_T;
    if (text == "size_t")   return ControllerType::SIZE_T;
    if (text == "Rational") return ControllerType::RATIONAL;
    return ControllerType::DOUBLE;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    InitConnections();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb) {
    digit_cb_ = std::move(cb);
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) {
    operation_cb_ = std::move(cb);
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) {
    control_cb_ = std::move(cb);
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb) {
    controller_cb_ = std::move(cb);
}

void MainWindow::SetInputText(const std::string &text) {
    ui_->l_result->setStyleSheet("");
    ui_->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string &text) {
    ui_->l_result->setStyleSheet("color: red;");
    ui_->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string &text) {
    ui_->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string &text) {
    ui_->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string> &key) {
    if (key.has_value()) {
        ui_->tb_extra->show();
        ui_->tb_extra->setText(QString::fromStdString(key.value()));
    } else {
        ui_->tb_extra->hide();
    }
}

void MainWindow::InitConnections()
{
    connect(ui_->cmb_controller,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::OnComboBoxIndexChanged);

    connect(ui_->btn_MC, &QPushButton::clicked, this, &MainWindow::OnControlButtonClicked);
    connect(ui_->btn_MR, &QPushButton::clicked, this, &MainWindow::OnControlButtonClicked);
    connect(ui_->btn_MS, &QPushButton::clicked, this, &MainWindow::OnControlButtonClicked);
    connect(ui_->btn_C, &QPushButton::clicked, this, &MainWindow::OnControlButtonClicked);
    connect(ui_->btn_revers, &QPushButton::clicked, this, &MainWindow::OnControlButtonClicked);
    connect(ui_->btn_0, &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->btn_1, &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->btn_2, &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->btn_3, &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->btn_4, &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->btn_5, &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->btn_6, &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->btn_7, &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->btn_8, &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->btn_9, &QPushButton::clicked, this, &MainWindow::OnDigitButtonClicked);
    connect(ui_->btn_chop, &QPushButton::clicked, this, &MainWindow::OnControlButtonClicked);
    connect(ui_->tb_extra, &QPushButton::clicked, this, &MainWindow::OnControlButtonClicked);
    connect(ui_->btn_pow, &QPushButton::clicked, this, &MainWindow::OnOperationButtonClicked);
    connect(ui_->btn_dev, &QPushButton::clicked, this, &MainWindow::OnOperationButtonClicked);
    connect(ui_->btn_mult, &QPushButton::clicked, this, &MainWindow::OnOperationButtonClicked);
    connect(ui_->btn_sub, &QPushButton::clicked, this, &MainWindow::OnOperationButtonClicked);
    connect(ui_->btn_add, &QPushButton::clicked, this, &MainWindow::OnOperationButtonClicked);
    connect(ui_->btn_result, &QPushButton::clicked, this, &MainWindow::OnControlButtonClicked);
}

void MainWindow::OnComboBoxIndexChanged(int)
{
    if (!controller_cb_) {
        return;
    }
    QString text = ui_->cmb_controller->currentText();
    ControllerType ct = ControllerTypeFromString(text);
    controller_cb_(ct);
}

void MainWindow::OnDigitButtonClicked()
{
    if (!digit_cb_) {
        return;
    }
    QObject* senderObj = sender();
    if (senderObj == ui_->btn_0) {
        digit_cb_(0);
    } else if (senderObj == ui_->btn_1) {
        digit_cb_(1);
    } else if (senderObj == ui_->btn_2) {
        digit_cb_(2);
    } else if (senderObj == ui_->btn_3) {
        digit_cb_(3);
    } else if (senderObj == ui_->btn_4) {
        digit_cb_(4);
    } else if (senderObj == ui_->btn_5) {
        digit_cb_(5);
    } else if (senderObj == ui_->btn_6) {
        digit_cb_(6);
    } else if (senderObj == ui_->btn_7) {
        digit_cb_(7);
    } else if (senderObj == ui_->btn_8) {
        digit_cb_(8);
    } else if (senderObj == ui_->btn_9) {
        digit_cb_(9);
    }
}

void MainWindow::OnOperationButtonClicked()
{
    if (!operation_cb_) {
        return;
    }
    QObject* senderObj = sender();
    if (senderObj == ui_->btn_add) {
        operation_cb_(Operation::ADDITION);
    } else if (senderObj == ui_->btn_sub) {
        operation_cb_(Operation::SUBTRACTION);
    } else if (senderObj == ui_->btn_mult) {
        operation_cb_(Operation::MULTIPLICATION);
    } else if (senderObj == ui_->btn_dev) {
        operation_cb_(Operation::DIVISION);
    } else if (senderObj == ui_->btn_pow) {
        operation_cb_(Operation::POWER);
    }
}

void MainWindow::OnControlButtonClicked()
{
    if (!control_cb_) {
        return;
    }
    QObject* senderObj = sender();
    if (senderObj == ui_->btn_result) {
        control_cb_(ControlKey::EQUALS);
    } else if (senderObj == ui_->btn_C) {
        control_cb_(ControlKey::CLEAR);
    } else if (senderObj == ui_->btn_MS) {
        control_cb_(ControlKey::MEM_SAVE);
    } else if (senderObj == ui_->btn_MR) {
        control_cb_(ControlKey::MEM_LOAD);
    } else if (senderObj == ui_->btn_MC) {
        control_cb_(ControlKey::MEM_CLEAR);
    } else if (senderObj == ui_->btn_revers) {
        control_cb_(ControlKey::PLUS_MINUS);
    } else if (senderObj == ui_->btn_chop) {
        control_cb_(ControlKey::BACKSPACE);
    } else if (senderObj == ui_->tb_extra) {
        control_cb_(ControlKey::EXTRA_KEY);
    }
}
