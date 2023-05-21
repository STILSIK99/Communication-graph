#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent)
    , ui (new Ui::MainWindow)
{
    ui->setupUi (this);
    ui->label->setAlignment (Qt::AlignCenter);
    ui->tabWidget->setCurrentIndex (0);
    ui->tabWidget->setTabVisible (1, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ++node_count;
    set_node_count();
}

void MainWindow::on_pushButton_2_clicked()
{
    if (!node_count) return;
    --node_count;
    set_node_count();
}

void MainWindow::set_node_count ()
{
    QStringList headers;
    for (int i = 0; i < node_count; ++i) {
        headers << "Узел № " + QString::number (i + 1);
    }
    ui->tableWidget->setColumnCount (node_count);
    ui->tableWidget->setHorizontalHeaderLabels (headers);
    ui->tableWidget_5->setColumnCount (node_count);
    ui->tableWidget_5->setHorizontalHeaderLabels (headers);
    set_table_3();
}

void MainWindow::set_service_count ()
{
    QStringList rows;
    ui->tableWidget_2->setRowCount (service_count);
    for (int i = 0; i < service_count; ++i) {
        rows << "Услуга № " + QString::number (i + 1);
        ui->tableWidget_2->setItem (i, 1, new QTableWidgetItem ("Услуга № " + QString::number (i + 1)));
    }
    ui->tableWidget_2->setVerticalHeaderLabels (rows);
    set_table_3();
}

void MainWindow::on_pushButton_3_clicked()
{
    ++service_count;
    set_service_count();
}


void MainWindow::on_pushButton_4_clicked()
{
    if (!service_count) return;
    --service_count;
    set_service_count();
}

void MainWindow::set_table_3()
{
    ui->tableWidget_3->setColumnCount (0);
    ui->tableWidget_3->setRowCount (0);
    ui->tableWidget_3->clear();
    if (! (service_count && node_count)) return;
    int rows = service_count * 3 + 3;
    ui->tableWidget_3->setColumnCount (node_count);
    ui->tableWidget_3->setRowCount (rows);
    QStringList vertical, horizontal;
    for (int i = 0; i < rows; ++i) {
        if (i % (service_count + 1)) {
            vertical << "Услуга № " + QString::number ((i % (service_count + 1)));
        } else {
            vertical << "";
        }
    }
    for (int i = 0; i < node_count; ++i) {
        horizontal << "Узел № " + QString::number (i + 1);
    }
    ui->tableWidget_3->setHorizontalHeaderLabels (horizontal);
    ui->tableWidget_3->setVerticalHeaderLabels (vertical);
    if (node_count < 1) return;
    for (int i = 0; i < rows; i += (service_count + 1)) {
        auto item = new QTableWidgetItem (
            "Предоставляемые услуги связи абоненту " +
            QString::number (i / service_count + 1) +
            " категории важности");
        item->setTextAlignment (Qt::AlignCenter);
        item->setFlags (item->flags() & (~Qt::ItemIsEditable));
        ui->tableWidget_3->setItem (i, 0, item);
        if (node_count <= 1) continue;
        ui->tableWidget_3->setSpan (i, 0, 1, node_count);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->tabWidget->setCurrentIndex (1);
    ui->tabWidget->setTabVisible (1, 1);
    ui->tabWidget->setTabVisible (0, 0);
    try {
        services.clear();
        services.reserve (service_count);
        for (int i = 0; i < service_count; ++i) {
            try {
                services.emplace_back (
                    Service (
                        ui->tableWidget_2->item (i, 1)->text(),
                        ui->tableWidget_2->item (i, 0)->text().toInt()
                    )
                );
            } catch (...) {}
        }
        nodes.clear();
        nodes.reserve (node_count);
        int rows = ui->tableWidget_3->rowCount();
        for (int i = 0; i < node_count; ++i) {
            Node node;
            for (int cat = 0 ; cat < 3; ++cat) {
                if (ui->tableWidget->item (cat, i) == nullptr) continue;
                if (ui->tableWidget->item (cat, i)->text() == "" ||
                    ui->tableWidget->item (cat, i)->text() == "0")
                    continue;
                node.abonents[cat] = ui->tableWidget->item (cat, i)->text().toInt();
            }
            for (int j = 0; j < rows; ++j) {
                static int cat, service;
                cat = j / (service_count + 1);
                service = j % (service_count + 1) - 1;
                qDebug() << j << " " << i;
                if (j % (service_count + 1)) {
                    if (ui->tableWidget_3->item (j, i) == nullptr) continue;
                    if (ui->tableWidget_3->item (j, i)->text() == "" ||
                        ui->tableWidget_3->item (j, i)->text() == "0")
                        continue;
                    node.count_by_cat_service[cat][services[service]] =
                        ui->tableWidget_3->item (j, i)->text().toInt();
                }
            }
            if (ui->tableWidget_5->item (0, i) == nullptr) node.thread = 0;
            else node.thread = ui->tableWidget_5->item (0, i)->text().toInt();
            if (ui->tableWidget_5->item (1, i) == nullptr) node.cons = 0;
            else node.cons = ui->tableWidget_5->item (1, i)->text().toInt();
            nodes.emplace_back (node);
        }
        vector<vector<int>> block_2 (node_count, vector<int> (5, 0));
        for (int node = 0; node < node_count; ++node) {
            for (int j = 0; j < 3; ++j) {
                block_2[node][0] += nodes[node].abonents[j];
            }
            block_2[node][1] = nodes[node].getServices (services);
            block_2[node][2] = nodes[node].getSpeed (services);
            block_2[node][3] = nodes[node].thread;
            block_2[node][4] = nodes[node].cons;
        }
        vector<vector<double>> block_3 (node_count, vector<double> (5, 0));
        vector<double> sums_2 (5, 0);
        for (int k = 0; k < 5; ++k) {
            for (int node = 0; node < node_count; ++node) {
                sums_2[k] += block_2[node][k];
            }
            for (int node = 0; node < node_count; ++node) {
                block_3[node][k] = block_2[node][k] / sums_2[k];
            }
        }

        vector<double> block_4 (node_count, 0);
        QStringList header_4;
        for (int node = 0; node < node_count; ++node) {
            double multiply = 1;
            for (int k = 0; k < 5; ++k) {
                multiply *= (1 - block_3[node][k]);
            }
            block_4[node] = 1 - multiply;
            ui->tableWidget_4->setColumnCount (node_count);
            header_4 << "Узел " + QString::number (node + 1);
            ui->tableWidget_4->setItem (0, node,
                                        new QTableWidgetItem (
                                            QString::number (block_4[node], ' ', 3))
                                       );
        }
        ui->tableWidget_4->setHorizontalHeaderLabels (header_4);
        stringstream graph;
        set<pair<int, int>> full;
        for (int node = 0; node < node_count; ++node) {
            full.insert ({nodes[node].cons, node});
        }
        set<pair<int, int>> dots;
        for (auto x : full) {
            int pos = x.second;
            for (char i = 1; i <= x.first; ++i) {
                int second;
                if (pos + i < node_count) {
                    second = x.second + i;
                } else {
                    second = (pos + i) % node_count;
                }
                dots.insert ({
                    min (x.second, second),
                    max (x.second, second)
                });
            }
        }
        for (auto dot : dots) {
            graph << char (dot.first + 'A') << " -- " << char (dot.second + 'A') << "; ";
        }

        QString name = QDateTime::currentDateTime().toString ("HH.mm.ss") + ".graph";
        QFile file (name);
        file.open (QIODevice::WriteOnly);
        file.write ("graph {");
        file.write (graph.str().c_str());
        file.write ("}");
        file.close();
        QProcess process;
        process.start ("\"graphviz/dot.exe\" -Tpng " +  name);
        process.waitForFinished();
        qDebug() << process.readAllStandardError();

        QFile out (name + ".png");
        if (out.open (QIODevice::WriteOnly))
            out.write (process.readAllStandardOutput());
        out.close();
        ui->label->clear();
        auto x = QPixmap (name + ".png");
        x.scaled (200, 200);
        ui->label->setPixmap (x);

    } catch (...) {
        QMessageBox::about (this, "Неверные данные", "Ошибка считывания исходных параметров.");
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->tabWidget->setCurrentIndex (0);
    ui->tabWidget->setTabVisible (0, 1);
    ui->tabWidget->setTabVisible (1, 0);
}
