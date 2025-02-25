#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <functional>
#include <optional>
#include <string>

#include "enums.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetDigitKeyCallback(std::function<void(int key)> cb);
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);
    void SetControllerCallback(std::function<void(ControllerType controller)> cb);


    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);

private:
    Ui::MainWindow *ui_;


    std::function<void(Operation key)> operation_cb_;
    std::function<void(int key)> digit_cb_;
    std::function<void(ControlKey key)> control_cb_;
    std::function<void(ControllerType controller)> controller_cb_;


    void InitConnections();

private slots:
    void OnDigitButtonClicked();
    void OnOperationButtonClicked();
    void OnControlButtonClicked();
    void OnComboBoxIndexChanged(int index);
};

#endif // MAINWINDOW_H
