#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QTimer>

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


private slots:
    void on_browseInputFileButton_clicked();
    void progressBar_ChangeValue();
    void on_executeButton_clicked();

signals:
    void inputFileName_ChangedSignal(QString);



private:
    Ui::MainWindow *ui;
    QString inputFileName;
    QTimer *timer;
    int progressBarCounter;
    QFile inputFile;
    QFile outputFile;
    QFile keyFile;

};

#endif // MAINWINDOW_H
