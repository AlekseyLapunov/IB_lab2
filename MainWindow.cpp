#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manageWidgets(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendFromAlice()
{
    if(!ui->Alice_TE->toPlainText().isEmpty())
    {
        ui->Bob_TE->setPlainText(ui->Alice_TE->toPlainText());
        ui->Alice_TE->clear();
        ui->statusbar->showMessage("Alice: Bob received my \"N\" and public key.", 2000);
    } else ui->statusbar->showMessage("Alice: Nothing to send", 2000);
}

void MainWindow::sendFromBob()
{
    if(!ui->Bob_TE->toPlainText().isEmpty())
    {
        ui->Alice_TE->setPlainText(ui->Bob_TE->toPlainText());
        ui->Bob_TE->clear();
        ui->statusbar->showMessage("Bob: Alice received my \"N\" and public key.", 2000);
    } else ui->statusbar->showMessage("Bob: Nothing to send", 2000);
}

void MainWindow::sendCFromAlice()
{
    ui->Alice_TE->setDisabled(true);

    ui->Alice_TE->setPlainText(
                QString::fromStdString(RSA.encode(ui->Alice_TE->toPlainText().toStdString(), RSA_Engine::Alice))
                );

    this->sendFromAlice();
    ui->Alice_TE->setDisabled(false);
}

void MainWindow::sendCFromBob()
{
    ui->Bob_TE->setDisabled(true);

    ui->Bob_TE->setPlainText
                (
                    QString::fromStdString(RSA.encode(ui->Bob_TE->toPlainText().toStdString(), RSA_Engine::Bob))
                );

    this->sendFromBob();
    ui->Bob_TE->setDisabled(false);
}

void MainWindow::decodeAlice()
{
    ui->Alice_TE->setDisabled(true);

    ui->Alice_TE->setPlainText
                (
                    QString::fromStdString(RSA.decode(ui->Alice_TE->toPlainText().toStdString(), RSA_Engine::Alice))
                );

    ui->Alice_TE->setDisabled(false);
}

void MainWindow::decodeBob()
{
    ui->Bob_TE->setDisabled(true);

    ui->Bob_TE->setPlainText
                (
                    QString::fromStdString(RSA.decode(ui->Bob_TE->toPlainText().toStdString(), RSA_Engine::Bob))
                );

    ui->Bob_TE->setDisabled(false);
}

void MainWindow::generateKeys()
{
    do
    {
        RSA.generateBI();
        this->copyBI();
        setLabels();
    } while(e_Al > this->limiter || e_Bob > this->limiter);
    manageWidgets(true);
}

void MainWindow::clearForms()
{
    manageWidgets(false);
}

void MainWindow::copyBI()
{
    for(int i = 0; i < 12; i++)
    {
        switch (i)
        {
        case 0:
            P_Al = RSA.getBI(i);
            break;
        case 1:
            Q_Al = RSA.getBI(i);
            break;
        case 2:
            N_Al = RSA.getBI(i);
            break;
        case 3:
            d_Al = RSA.getBI(i);
            break;
        case 4:
            s_Al = RSA.getBI(i);
            break;
        case 5:
            e_Al = RSA.getBI(i);
            break;
        case 6:
            P_Bob = RSA.getBI(i);
            break;
        case 7:
            Q_Bob = RSA.getBI(i);
            break;
        case 8:
            N_Bob = RSA.getBI(i);
            break;
        case 9:
            d_Bob = RSA.getBI(i);
            break;
        case 10:
            s_Bob = RSA.getBI(i);
            break;
        case 11:
            e_Bob = RSA.getBI(i);
            break;
        default:
            break;
        }
    }
}

void MainWindow::setLabels()
{
    ui->P_Al_label->setText("P: " + QString::fromStdString(P_Al.getNumber()));
    ui->Q_Al_label->setText("Q: " + QString::fromStdString(Q_Al.getNumber()));
    ui->N_Al_label->setText("N: " + QString::fromStdString(N_Al.getNumber()));
    ui->Public_Al_label->setText("Public key (s): " + QString::fromStdString(s_Al.getNumber()));
    ui->Private_Al_label->setText("Private key (e): " + QString::fromStdString(e_Al.getNumber()));

    ui->P_Bob_label->setText("P: " + QString::fromStdString(P_Bob.getNumber()));
    ui->Q_Bob_label->setText("Q: " + QString::fromStdString(Q_Bob.getNumber()));
    ui->N_Bob_label->setText("N: " + QString::fromStdString(N_Bob.getNumber()));
    ui->Public_Bob_label->setText("Public key (s): " + QString::fromStdString(s_Bob.getNumber()));
    ui->Private_Bob_label->setText("Private key (e): " + QString::fromStdString(e_Bob.getNumber()));
}

void MainWindow::manageWidgets(bool flag)
{
    // Set Disabled
    ui->Alice_label->setDisabled(!flag);
    ui->Bob_label->setDisabled(!flag);
    ui->Alice_TE->setDisabled(!flag);
    ui->Bob_TE->setDisabled(!flag);
    ui->Alice_TE->clear();
    ui->Bob_TE->clear();
    ui->Send_Al_button->setDisabled(!flag);
    ui->Send_Bob_button->setDisabled(!flag);
    ui->Send_C_Al_button->setDisabled(!flag);
    ui->Send_C_Bob_button->setDisabled(!flag);
    ui->Decode_Al_button->setDisabled(!flag);
    ui->Decode_Bob_button->setDisabled(!flag);
    ui->Clear_button->setDisabled(!flag);
    ui->Generate_keys_button->setDisabled(flag);
    // Set Visible
    ui->P_Al_label->setVisible(flag);
    ui->P_Bob_label->setVisible(flag);
    ui->Q_Al_label->setVisible(flag);
    ui->Q_Bob_label->setVisible(flag);
    ui->N_Al_label->setVisible(flag);
    ui->N_Bob_label->setVisible(flag);
    ui->Public_Al_label->setVisible(flag);
    ui->Public_Bob_label->setVisible(flag);
    ui->Private_Al_label->setVisible(flag);
    ui->Private_Bob_label->setVisible(flag);
}




















