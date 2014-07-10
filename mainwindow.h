#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QTimer>
#include "des_c_dll.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void setInputFileName(QString fileName);
    void setOutputFileName(QString fileName);
    int encryptFile();
    int decryptFile();
    void toCharArray(long long int value, char* buffer);
    void setProgressBarMax(int);


private slots:
    void on_browseInputFileButton_clicked();
    void progressBar_ChangeValue(int);
    void on_executeButton_clicked();

    void on_browseKeyFileButton_clicked();

signals:
    void inputFileName_ChangedSignal(QString);
    void outputFileName_ChangedSignal(QString);
    void nextDataPartEnded_Signal(int);



private:
    Ui::MainWindow *ui;
    QString inputFileName;
    QString outputFileName;
    QTimer *timer;
    int progressBarCounter;
    QFile inputFile;
    QFile outputFile;
    QFile keyFile;

    long long int dataSize;
    long long int key;

    int progressBarMin;
    int progressBarMax;


};

#endif // MAINWINDOW_H
