#pragma once

#include <QLabel>
#include <QString>
#include "ui_mainwindow.h"

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    mainwindow(QWidget* parent = nullptr);
    ~mainwindow();

private slots:
    void on_action_quit_triggered();
    void on_plainTextEdit_textChanged();
    void on_action_new_triggered();
    void on_action_open_triggered();
    bool on_action_save_triggered();
    void on_action_save_as_triggered();
    void on_action_close_triggered();
    void on_action_del_triggered();

private:
    Ui::mainwindow ui;
    QLabel* status_;
    QString file_path_;
    bool is_saved_ = true;
    void create_tool_buttons();
};
