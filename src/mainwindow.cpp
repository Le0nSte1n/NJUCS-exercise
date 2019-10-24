#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new Database("test",QString("/home/jackey/GitHub/Warehouse/data/warehouse.db"));

    maxId = db->getMaxId("data");
    ui->lineId->setText(QString::number(maxId));

    displayDetailById(maxId);
}

MainWindow::~MainWindow()
{
    delete db;
    delete ui;
}

bool MainWindow::displayDetailById(int id)
{
    if(id<0) return false;
    if(id>maxId) return false;

    //先进行关键词过滤
    QString filter = ui->PTEFilter->toPlainText();
    QString keywords;
    if(!filter.isEmpty()){
        sql = QString("select keywords from property where id = %1").arg(currentId);
        db->query->prepare(sql);
        if(db->query->exec()){
            while(db->query->next()){
                keywords = db->query->value(0).toString();
            }
        }
    }

    QStringList filterList = filter.split(" ");
    QStringList keywordsList = keywords.split(" ");
    for(QString filterWord : filterList){
        for(QString keyword : keywordsList){
            if(keyword == filterWord) return displayDetailById(id+1);
        }
    }
    //过滤结束

    sql = QString("select id,title,question from data where id= %1").arg(currentId);
    db->query->prepare(sql);
    if(db->query->exec()){
        while(db->query->next()){
            ui->textBrowser->setText(db->query->value("question").toString());
            ui->lineId->setText(db->query->value("id").toString());
            ui->lineTitle->setText(db->query->value("title").toString());
        }
    }
    else {
        qDebug()<<"Cannot query detail from data table :"<<db->query->lastError();
    }
    return true;
}

void MainWindow::on_actionNew_triggered()
{
    bool status = db->createTables();
    if(status){
        QMessageBox::information(this,tr("New"),tr("Create new database successfully"),QMessageBox::Ok);
    }
    else {
        QMessageBox::information(this,tr("New"),tr("Create new database successfully"),QMessageBox::Ok);
    }
}

void MainWindow::on_actionImport_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,tr("Open"));

    if(filePath.isEmpty()){
        QMessageBox::information(this,tr("Tips"),tr("Selected nothing"),QMessageBox::Ok);
        return;
    }
}

void MainWindow::on_actionExport_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this,tr("Export"));

    if(filePath.isEmpty()){
        QMessageBox::information(this,tr("Tips"),tr("Selected nothing"),QMessageBox::Ok);
        return;
    }
}

void MainWindow::on_actionExit_triggered()
{
    qApp->exit(0);
}

void MainWindow::on_actionQt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionIndex_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/JackeyLea/Warehouse"));
}

void MainWindow::on_buttonPrevious_clicked()
{
    if(currentId<0){
        currentId = maxId;
    }
    else {
        currentId--;
    }

    displayDetailById(currentId);
}

void MainWindow::on_buttonNext_clicked()
{
    if(currentId>=maxId){
        currentId = 0;
    }
    else {
        currentId++;
    }

    displayDetailById(currentId);
}

void MainWindow::on_buttonTips_clicked()
{
    QString msg = QString("No tip");
    sql = QString("select tips from data where id = %1").arg(currentId);
    db->query->prepare(sql);
    if(db->query->exec()){
        while(db->query->next()){
            msg = db->query->value(0).toString();
        }
    }

    QMessageBox::information(this,tr("Tips"),msg,QMessageBox::Ok);
}

void MainWindow::on_buttonAnswer_clicked()
{
    QString msg = QString("No answer");
    sql = QString("select answer from answer where id = %1").arg(currentId);
    db->query->prepare(sql);
    if(db->query->exec()){
        while(db->query->next()){
            msg = db->query->value(0).toString();
        }
    }

    QMessageBox::information(this,tr("Answer"),msg,QMessageBox::Ok);
}

void MainWindow::on_buttonAdd_clicked()
{
    sql.clear();
    sql = QString("insert into data values(:");
}

void MainWindow::on_buttonUpdate_clicked()
{
}

void MainWindow::on_buttonDelete_clicked()
{
    sql = QString("delete from question where id = %1").arg(currentId);

    db->query->prepare(sql);
    if(db->query->exec()){
        QMessageBox::information(this,tr("Tip"),tr("Deletion is done"),QMessageBox::Ok);
    }
    else {
        qDebug()<<"Cannot delete from question where id = "<<currentId;
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QString msg;

    QMessageBox::information(this,tr("About"),msg,QMessageBox::Ok);
}
