#pragma once
#include "QMainWindow"
#include "Node.h"
#include "QMessageBox"
#include "QDebug"
#include "QDateTIme"
#include "QFile"
#include "sstream"
#include "set"
#include "QProcess"
#include "QPixmap"
#include "thread"
#include "chrono"
#include "time.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow (QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_pushButton_clicked();

        void on_pushButton_2_clicked();

        void on_pushButton_3_clicked();

        void on_pushButton_4_clicked();

        void on_pushButton_5_clicked();

        void on_pushButton_6_clicked();

    private:
        Ui::MainWindow *ui;
        vector<Service> services;
        int node_count = 0;
        int service_count = 0;
        void set_node_count ();
        void set_service_count();
        void set_table_3();
        vector<Node> nodes;
};
