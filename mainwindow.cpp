#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "configeditordialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Scoreboard");

    connect(ui->actionConfiguration, &QAction::triggered, this, &MainWindow::EditConfiguration);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::EditConfiguration()
{
    ConfigEditorDialog d;
    if (d.exec() == QDialog::Accepted)
    {
        d.SaveConfigValues();
        ui->centralwidget->RefreshAllSettings();
    }
}

