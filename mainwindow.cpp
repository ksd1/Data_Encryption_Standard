#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);

    timer = new QTimer(this);

    connect(this,SIGNAL(inputFileName_ChangedSignal(QString)),ui->inputFileNameTextBox,SLOT(setText(QString)));
    connect(timer, SIGNAL(timeout()), this, SLOT(progressBar_ChangeValue()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setInputFileName(QString fileName)
{
    if(inputFileName == fileName)
        return;

    inputFileName = fileName;
    emit inputFileName_ChangedSignal(inputFileName);
}

void MainWindow::on_browseInputFileButton_clicked()
{
    setInputFileName(QFileDialog::getOpenFileName(this,tr("Otwórz"),QDir::homePath(),tr("*")));
    inputFile.setFileName(inputFileName);
}

void MainWindow::progressBar_ChangeValue()
{
    int val = ui->progressBar->value() + 1;
    ui->progressBar->setValue(val);
}

void MainWindow::on_executeButton_clicked()
{

    timer->start(100);
}
