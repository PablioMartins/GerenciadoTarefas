#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tempo = new QTimer(this);

    connect(tempo, SIGNAL(timeout()), this, SLOT(geraTabela()));

    tempo->start(1000);
}

void MainWindow::geraTabela()
{
    ui->list_process->clear();

    std::vector<std::vector<std::string>> proc;

    proc = process.get_processors();

    int linhas = int(proc.size());
    int colunas = int(proc.at(0).size());

    ui->list_process->setColumnCount(colunas);
    ui->list_process->setRowCount(linhas);
    ui->list_process->verticalHeader()->setVisible(false);

    QStringList titulos;
    for(int i = 0; i < colunas; i++){
        titulos.append(QString::fromStdString(proc.at(0).at(i)));
    }
    ui->list_process->setHorizontalHeaderLabels(titulos);


    QTableWidgetItem *itens;
    for(int i = 1; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            itens = new QTableWidgetItem();
            itens->setText(QString::fromStdString(proc.at(i).at(j)));
            ui->list_process->setItem(i-1, j, itens);
        }
    }

    ui->list_process->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow()
{

    delete ui;
}



void MainWindow::on_b_filter_clicked()
{
    QString text = ui->filter_text->text();
    if(text != ""){
        process.setProcess_nome(text.toStdString());
    }
    else{
        process.setProcess_nome("null");
    }

}


void MainWindow::on_b_kill_clicked()
{
    QString text = ui->pid_text_all->text();
    process.kill_process(text.toInt());
    ui->pid_text_all->clear();
}


void MainWindow::on_b_stop_clicked()
{
    QString text = ui->pid_text_all->text();
    process.stop_process(text.toInt());
}

void MainWindow::on_b_cont_clicked()
{
    QString text = ui->pid_text_all->text();
    process.cont_process(text.toInt());
}

void MainWindow::on_b_priority_clicked()
{
    QString pid = ui->pid_text_priority->text();
    QString prio = ui->priority_text->text();
    process.set_prio(pid.toInt(), prio.toInt());
}


void MainWindow::on_b_cpuset_clicked()
{
    QString pid = ui->pid_text_cpu->text();
    QString cpu = ui->cpu_text->text();
    process.set_CPU(pid.toStdString(),cpu.toStdString());
}

