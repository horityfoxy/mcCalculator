#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()), this, SLOT(buttons_pressed()));

    connect(ui->pushButton_clear,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_negative,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_percent,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_point,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_division,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_multiply,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_minus,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_plus,SIGNAL(released()), this, SLOT(buttons_pressed()));
    connect(ui->pushButton_equals,SIGNAL(released()), this, SLOT(buttons_pressed()));
}

MainWindow::~MainWindow(){
    delete ui;
}

double firstNum = 0;
double secondNum = 0;
bool isFirstNumTyped = false;
bool isUserTypeSecondNum = true;
std::string operation = "";
bool clearLabel = false;

void clearField(QLabel *labelText){
    labelText->setText("");
}

void labelUpdate(QLabel *labelText, QString symbol){
    if (clearLabel == true){
        clearField(labelText);
        clearLabel = false;
    }
    if(labelText->text()=="0" && symbol != "."){
        labelText->setText("");
    }
    labelText->setText(labelText->text() + symbol);
}

void clearAll(QLabel *labelText){
    labelText->setText("0");
    firstNum = 0;
    secondNum = 0;
    operation = "";
    isFirstNumTyped = false;
}

void setGlobalNumbers(QLabel *labelText){
    if (isFirstNumTyped == false){
        firstNum = labelText->text().toDouble();
        isFirstNumTyped = true;
    }else{
        secondNum = labelText->text().toDouble();
    }
}

void resCount(QLabel *labelText, std::string newOperation){

    if (newOperation == "⁺∕-"){
        double TEMP = labelText->text().toDouble() * -1;
        clearField(labelText);
        labelUpdate(labelText, QString::number(TEMP));
        clearLabel = true;
        return;
    }

    setGlobalNumbers(labelText);
    clearLabel = true;
    if (newOperation == "%"){
        if(operation == "+")
            firstNum = firstNum * (1 + secondNum/100);
        else if (operation == "-")
            firstNum = firstNum * (1 - secondNum/100);
        else if (operation == "×")
            firstNum = firstNum * secondNum/100;
        if (operation == "÷"){
            if (secondNum == 0){
                labelUpdate(labelText, "Undefined");
                return;
            }else{
                firstNum = firstNum / (secondNum/100);
            }
        }
        labelUpdate(labelText, QString::number(firstNum));
        operation = "";
        return;
    }

    if (operation == "×"){
        firstNum = firstNum * secondNum;
        labelUpdate(labelText, QString::number(firstNum));
    }else if (operation == "÷"){
        if (secondNum == 0){
            labelUpdate(labelText, "Undefined");
        }else{
            firstNum = firstNum / secondNum;
            labelUpdate(labelText, QString::number(firstNum));
        }
    }else if (operation == "+"){
        firstNum = firstNum + secondNum;
        labelUpdate(labelText, QString::number(firstNum));
    }else if (operation == "-"){
        firstNum = firstNum - secondNum;
        labelUpdate(labelText, QString::number(firstNum));
    }
    isUserTypeSecondNum = false;
    operation = newOperation;
    clearLabel = true;
}

void MainWindow::buttons_pressed(){
    QPushButton * buttonText = (QPushButton *)sender();
    if(buttonText->text() == "0" || buttonText->text() == "1" || buttonText->text() == "2" || buttonText->text() == "3" ||
        buttonText->text() == "4" ||buttonText->text() == "5" || buttonText->text() == "6" || buttonText->text() == "7" ||
        buttonText->text() == "8" || buttonText->text() == "9"){
        if (isFirstNumTyped == true){
            isUserTypeSecondNum = true;
        }
        labelUpdate(ui->label, buttonText->text());
    }else if(buttonText->text() == "="){
        resCount(ui->label, "");
        isFirstNumTyped = false;
        isUserTypeSecondNum = true;
        firstNum = 0;
        secondNum = 0;
        operation = "";
    }else if(buttonText->text() == "AC"){
        clearAll(ui->label);
    }else if(buttonText->text() == "."){
        if (!ui->label->text().contains('.')) {
            labelUpdate(ui->label, ".");
        }
    }else{
        if(isUserTypeSecondNum){
            resCount(ui->label, buttonText->text().toStdString());
        }else{
            operation = buttonText->text().toStdString();
        }
    }
}
