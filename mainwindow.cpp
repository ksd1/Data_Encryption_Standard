#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);

    ui->encryptionRadioButton->setChecked(true);
    ui->desAlgorithmRadioButton->setChecked(true);

    timer = new QTimer(this);

    connect(this,SIGNAL(inputFileName_ChangedSignal(QString)),ui->inputFileNameTextBox,SLOT(setText(QString)));
    connect(this,SIGNAL(outputFileName_ChangedSignal(QString)),ui->outputFileNameTextBox,SLOT(setText(QString)));
    connect(this,SIGNAL(keyFileName_ChangedSignal(QString)),ui->keyFileNameTextBox,SLOT(setText(QString)));
    connect(this, SIGNAL(nextDataPartEnded_Signal(int)), this, SLOT(progressBar_ChangeValue(int)));

    //First gui initialization

    ui->encryptionRadioButton->setChecked(true);
    mode = ENCRYPTION_MODE;

    ui->manualKeyRadioButton->setChecked(true);
    keyMode = MANUAL_INPUT_KEY;
    autoGenerateKey = false;

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
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

void MainWindow::setOutputFileName(QString fileName)
{
    if(outputFileName == fileName)
        return;

    outputFileName = fileName;
    emit outputFileName_ChangedSignal(outputFileName);
}

void MainWindow::setKeyFileName(QString fileName)
{
    if(keyFileName == fileName)
        return;

    keyFileName = fileName;
    emit keyFileName_ChangedSignal(keyFileName);
}

void MainWindow::on_browseInputFileButton_clicked()
{
    setInputFileName(QFileDialog::getOpenFileName(this,tr("Otwórz"),QDir::homePath(),tr("*")));
    inputFile.setFileName(inputFileName);
}

void MainWindow::progressBar_ChangeValue(int nextPart)
{
    int val = ui->progressBar->value() + nextPart;
    ui->progressBar->setValue(val);
}

void MainWindow::on_executeButton_clicked()
{
     parseKey();

    if(ui->encryptionRadioButton->isChecked())
        encryptFile();
    else if(ui->decryptionRadioButton->isChecked())
        decryptFile();

    //timer->start(100);
}

void MainWindow::on_browseKeyFileButton_clicked()
{

    setKeyFileName(QFileDialog::getSaveFileName(this,tr("Otwórz"),QDir::homePath(),tr("*")));
    keyFile.setFileName(keyFileName);

}

void MainWindow::toCharArray(long long int value, char* buffer)
{
    for(int i=7; i>=0; i--)
    {
        buffer[i] = value&0xFF;
        value = value >> 8;
    }
}

void MainWindow::setProgressBarMax(int max)
{
    ui->progressBar->setMaximum(max);
}

void MainWindow::on_decryptionRadioButton_clicked()
{
    ui->autoGenerateKeyCheckBox->setEnabled(false);
    mode = DECRYPTION_MODE;
}

void MainWindow::on_encryptionRadioButton_clicked()
{
    if(keyMode == FILE_KEY)
        ui->autoGenerateKeyCheckBox->setEnabled(true);
    mode = ENCRYPTION_MODE;
}

int MainWindow::encryptFile()
{
    long long int tempdata = 0x0123456789ABCDEF;
    long long int tempkey = 0x133457799BBCDFF1;
    int loops, rest;
    char outData[8];

    //inputFile.open(QFile::ReadOnly);
    inputFile.open(QIODevice::ReadOnly);
    outputFile.open(QIODevice::ReadWrite);

    dataSize = inputFile.size();
    loops = dataSize/8;
    rest = dataSize%8;

    //setProgressBarMax(dataSize);
    ui->progressBar->reset();
    ui->progressBar->setRange(0,dataSize);
    ui->progressBar->setValue(0);

    char tab[8];
    long long int data = 0, temp = 0;
    int i = 0;

    for(int j=0; j<loops; j++)
    {
        inputFile.read(tab,8);

        for(i=0; i<8; i++)
        {
            data <<= 8;
            temp = (long long int)tab[i];
            data |= temp&0xFF;
        }
        long long int result = encrypt_message(data,key);
        //result = decrypt_message(result,tempkey);
        toCharArray(result, outData);
        outputFile.write(outData, 8);
        emit nextDataPartEnded_Signal(8);
    }

    inputFile.read(tab,rest);

    for(i=0; i<8; i++)
    {
        data <<= 8;
        if(i<rest)
        {
            temp = (long long int)tab[i];
            data |= temp&0xFF;
        }
    }
    emit nextDataPartEnded_Signal(rest);
    long long int result = encrypt_message(data,key);
    toCharArray(result, outData);
    outputFile.write(outData, 8);

    outputFile.close();
    inputFile.close();
    return 2;
}

int MainWindow::decryptFile()
{
    long long int tempdata = 0x0123456789ABCDEF;
    long long int tempkey = 0x133457799BBCDFF1;
    int loops, rest;
    char outData[8];


    inputFile.open(QIODevice::ReadOnly);
    outputFile.open(QIODevice::ReadWrite);

    dataSize = inputFile.size();
    loops = dataSize/8;

    ui->progressBar->reset();
    ui->progressBar->setRange(0,dataSize);
    ui->progressBar->setValue(0);

    char tab[8];
    long long int data = 0, temp = 0;
    int i = 0;

    for(int j=0; j<loops; j++)
    {
        inputFile.read(tab,8);

        for(i=0; i<8; i++)
        {
            data <<= 8;
            temp = (long long int)tab[i];
            data |= temp&0xFF;
        }
        long long int result = decrypt_message(data,key);
        toCharArray(result, outData);
        outputFile.write(outData, 8);
        emit nextDataPartEnded_Signal(8);
    }


    outputFile.close();
    inputFile.close();
    return 2;
}

long long int generateRandomKey()
{
    long long int key=0, temp=0;

    for(int i=0; i<8; i++)
    {
        key <<= 8;
        temp = qrand() % ((255 + 1) - 1) + 1;
        key |= temp;
    }

    return key;

    //return 0x133457799BBCDFF1;
}

void MainWindow::on_browseOutputFileButton_clicked()
{
    setOutputFileName(QFileDialog::getSaveFileName(this,tr("Otwórz"),QDir::homePath(),tr("*")));
    outputFile.setFileName(outputFileName);
}

void MainWindow::on_manualKeyRadioButton_clicked()
{
    keyMode = MANUAL_INPUT_KEY;
    ui->keyTextBox->setEnabled(true);

    ui->keyFileNameTextBox->setEnabled(false);

    ui->autoGenerateKeyCheckBox->setEnabled(false);
}

void MainWindow::on_keyFromFileRadioButton_clicked()
{
    keyMode = FILE_KEY;
    ui->keyFileNameTextBox->setEnabled(true);
    if(mode != DECRYPTION_MODE)
        ui->autoGenerateKeyCheckBox->setEnabled(true);

    ui->keyTextBox->setEnabled(false);
}

void MainWindow::parseKey()
{
    char *keyTab = new char[8];
    long long int parsedKey = 0, temp = 0;
    QByteArray array;

    if(autoGenerateKey == true)
    {
        key = generateRandomKey();
        toCharArray(key,keyTab);
        keyFile.open(QIODevice::ReadWrite);
        keyFile.write(keyTab,8);
        keyFile.close();
    }
    else
    {
        if(keyMode == MANUAL_INPUT_KEY)
        {
            QString keyString = ui->keyTextBox->text();
            array = keyString.toLocal8Bit();
            keyTab = array.data();
        }
        else if(keyMode == FILE_KEY)
        {
            keyFile.open(QIODevice::ReadOnly);
            keyFile.read(keyTab,8);
        }

        for(int i=0; i<8; i++)
        {
            parsedKey <<= 8;
            temp = (long long int)keyTab[i];
            parsedKey |= temp&0xFF;
        }

        key = parsedKey;
    }

}

void MainWindow::on_autoGenerateKeyCheckBox_stateChanged(int arg1)
{
    autoGenerateKey = arg1;

    if(autoGenerateKey == true)
    {
        QMessageBox::warning(this,tr("Ostrzeżenie"),tr("To ustawienie spowoduje nadpisanie pliku klucza!"),QMessageBox::Ok);
    }
}
