#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
double memoryVal = 0.0;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton* numButtons[10];
    for(int i = 0; i != 10 ; ++i) // iterating over num buttons and connecting their released signals
                                  // to slot NumPressed of calculator class.
    {
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i],SIGNAL(released()),this,SLOT(NumPressed()));
    }

    // setting up connection of signals to Math buttons
    connect(ui->ButtonPlus,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->ButtonMunis,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->ButtonDivide,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->ButtonMultiply,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    // settin up connection of signals to slot equal buttons
    connect(ui->ButtonEqual,SIGNAL(released()),this,SLOT(EqualButtonPressed()));
    // setting up connection of signals to number sign change of signal of button relased to the slot part of the claculator.
    connect(ui->ButtonSign,SIGNAL(released()),this,SLOT(ChangeNumberSign()));
    //setting up connection between signals and slots for memory
    connect(ui->ButtonM,SIGNAL(released()),this,SLOT(RetrieveMemory()));
    connect(ui->ButtonMPlus,SIGNAL(released()),this,SLOT(StoreMemory()));
    connect(ui->ButtonMMunis,SIGNAL(released()),this,SLOT(ClearMemory()));
    // setting up connection of signal to slot for clear display
    connect(ui->ButtonClear,SIGNAL(released()),this,SLOT(ClearDisplay()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton* button = (QPushButton*) sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if(displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0)
    {
        ui->Display->setText(butVal);
    }
    else
    {
        QString newdispVal = displayVal + butVal;
        double dblVal = newdispVal.toDouble();

        ui->Display->setText(QString::number(dblVal,'g',16));
    }
}

void Calculator::ChangeNumberSign()
{
    double currentval = ui->Display->text().toDouble();
    currentval = - currentval;
    ui->Display->setText(QString::number(currentval,'g',16));


}

void Calculator::EqualButtonPressed()
{
    double currentVal = ui->Display->text().toDouble();
    double result = 0.0;
    if(multTrigger)
    {
        result = calcVal * currentVal;

    }
    else if (divTrigger)
    {
        result = calcVal / currentVal;
    }
    else if (addTrigger)
    {
        result = calcVal + currentVal;
    }
    else if (subTrigger)
    {
        result = calcVal - currentVal;
    }
    else
    {
        return;
    }

    ui->Display->setText(QString::number(result,'g',16));
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

}
void Calculator::MathButtonPressed()
{
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString dispVal = ui->Display->text();
    calcVal = dispVal.toDouble();
    QPushButton* button = (QPushButton*)sender();

    if(button->text() == "+")
    {
        addTrigger = true;
        ui->Display->setText("+");
    }
    else if(button->text() == "-")
    {
        subTrigger = true;
        ui->Display->setText("-");

    }
    else if(button->text() == "/")
    {
        divTrigger = true;
        ui->Display->setText("/");

    }
    else if(button->text() == "*")
    {
        multTrigger = true;
        ui->Display->setText("*");

    }


}

void Calculator::StoreMemory()
{
    memoryVal = ui->Display->text().toDouble();

}
void Calculator::ClearMemory()
{
    memoryVal = 0.0;

}
void Calculator::RetrieveMemory()
{
    ui->Display->setText(QString::number(memoryVal,'g',16));
}

void Calculator::ClearDisplay()
{
    ui->Display->setText("0");

}
