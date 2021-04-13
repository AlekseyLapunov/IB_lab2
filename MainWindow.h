#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <RSA_Engine.h>
#include <BigInteger.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // Ограничитель, являющийся числом, которое не должно превышать никакое из секретных ключей (e),
    // оно создано в тех целях, чтобы избежать переполнения (string)
    int limiter = 1611;
    bool Alice_knows = false, Bob_knows = false;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendFromAlice();
    void sendFromBob();
    void sendCFromAlice();
    void sendCFromBob();
    void decodeAlice();
    void decodeBob();
    void generateKeys();
    void clearForms();
private:
    void copyBI();
    void setLabels();
    BI P_Al, Q_Al, N_Al, d_Al, s_Al, e_Al;
    BI P_Bob, Q_Bob, N_Bob, d_Bob, s_Bob, e_Bob;
    RSA_Engine RSA;
    void manageWidgets(bool);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
