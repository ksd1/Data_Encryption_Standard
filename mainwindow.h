#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <QTime>
#include "des_c_dll.h"

#define ENCRYPTION_MODE 1
#define DECRYPTION_MODE 2
#define FILE_KEY 1
#define MANUAL_INPUT_KEY 2

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

    void on_decryptionRadioButton_clicked();

    void on_encryptionRadioButton_clicked();

    void on_browseOutputFileButton_clicked();

    void on_manualKeyRadioButton_clicked();

    void on_keyFromFileRadioButton_clicked();

    void on_autoGenerateKeyCheckBox_stateChanged(int arg1);

signals:
    void inputFileName_ChangedSignal(QString);
    void outputFileName_ChangedSignal(QString);
    void keyFileName_ChangedSignal(QString);
    void nextDataPartEnded_Signal(int);



protected:
    void setKeyFileName(QString fileName);
private:
    Ui::MainWindow *ui;

    int mode;
    int keyMode;
    bool autoGenerateKey;

    QString inputFileName;
    QString outputFileName;
    QString keyFileName;
    QTimer *timer;
    int progressBarCounter;
    QFile inputFile;
    QFile outputFile;
    QFile keyFile;

    long long int dataSize;
    long long int key;

    int progressBarMin;
    int progressBarMax;


    void parseKey();
};

#endif // MAINWINDOW_H
