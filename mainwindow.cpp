#include "stdafx.h"
#include "mainwindow.h"

mainwindow::mainwindow(QWidget* parent) : QMainWindow(parent), status_(new QLabel("", this))
{
    ui.setupUi(this);
    create_tool_buttons();
    ui.statusBar->addPermanentWidget(status_);
}

mainwindow::~mainwindow() = default;

void mainwindow::on_action_quit_triggered()
{
    close();
}

void mainwindow::on_plainTextEdit_textChanged()
{
    if (is_saved_)
    {
        is_saved_ = false;
        status_->setText(file_path_ + tr(" (unsaved)"));
    }
}

void mainwindow::on_action_new_triggered()
{
    ui.action_save->setEnabled(true);
    ui.action_save_as->setEnabled(true);
    ui.action_close->setEnabled(true);
    ui.plainTextEdit->setEnabled(true);
    ui.menu_edit->setEnabled(true);
    file_path_ = "";
    is_saved_ = true;
    ui.plainTextEdit->clear();
    qDebug() << "Successfully create an empty file.";
}

void mainwindow::on_action_open_triggered()
{
    const auto path_bk = file_path_;
    file_path_ = QFileDialog::getOpenFileName(this, tr("Choose file to open"), ".",
        tr("All Files (*.*)"));
    if (file_path_.isEmpty())
    {
        qDebug() << "Nothing chosen.";
        file_path_ = path_bk;
        return;
    }
    QFile file(file_path_);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    ui.action_save->setEnabled(true);
    ui.action_save_as->setEnabled(true);
    ui.action_close->setEnabled(true);
    ui.plainTextEdit->setEnabled(true);
    ui.menu_edit->setEnabled(true);
    ui.plainTextEdit->setPlainText(file.readAll());
    is_saved_ = true;
    status_->setText(file_path_);
    file.close();
    qDebug() << "File is successfully opened.";
}

bool mainwindow::on_action_save_triggered()
{
    if (is_saved_) return false;
    if (file_path_.isEmpty())
        file_path_ = QFileDialog::getSaveFileName(this, tr("Choose file to save"), ".",
            tr("All Files (*.*)"));
    if (file_path_.isEmpty())
    {
        qDebug() << "Nothing chosen.";
        return false;
    }
    QFile file(file_path_);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(ui.plainTextEdit->toPlainText().toStdString().c_str());
    is_saved_ = true;
    status_->setText(file_path_);
    file.close();
    qDebug() << "File is successfully saved.";
    return true;
}

void mainwindow::on_action_save_as_triggered()
{
    const auto path_bk = file_path_;
    const auto saved_bk = is_saved_;
    file_path_ = "";
    is_saved_ = false;
    if (const auto res = on_action_save_triggered(); !res)
    {
        file_path_ = path_bk;
        is_saved_ = saved_bk;
    }
    qDebug() << "File is successfully saved as " << file_path_;
}

void mainwindow::on_action_close_triggered()
{
    ui.action_save->setEnabled(false);
    ui.action_save_as->setEnabled(false);
    ui.action_close->setEnabled(false);
    ui.plainTextEdit->setEnabled(false);
    ui.menu_edit->setEnabled(false);
    file_path_ = "";
    ui.plainTextEdit->clear();
    is_saved_ = true;
    status_->setText("");
    qDebug() << "File is successfully closed.";
}

void mainwindow::on_action_del_triggered()
{
    if (auto cursor = ui.plainTextEdit->textCursor(); cursor.selectedText().isEmpty()) cursor.deleteChar();
    else cursor.removeSelectedText();
}

void mainwindow::create_tool_buttons()
{
    QList tool_actions{
        ui.action_new,
        ui.action_open,
        ui.action_save,
        ui.action_save_as,
        ui.action_close,
        ui.action_quit,
    };
    for (const auto& tool_action : tool_actions)
    {
        const auto button = new QToolButton(this);
        button->setDefaultAction(tool_action);
        ui.mainToolBar->addWidget(button);
    }
}