#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "medecin.h"
#include "statistiques.h"
#include<QIntValidator>
#include<QSqlQuery>
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_cin->setValidator(new QIntValidator(0, 9999999, this));
    ui->lineEdit_num->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_salaire->setValidator(new QIntValidator(0, 9999999, this));
    ui->tableView->setModel(M.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Ajouter_clicked()
{
    int id=ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString role=ui->lineEdit_role_2->text();
    int salaire=ui->lineEdit_salaire->text().toInt();
    QString email=ui->lineEdit_email->text();
    int num=ui->lineEdit_num->text().toInt();
    medecin M(id,nom,prenom,role,salaire,email,num);
    bool test = M.ajouter();
    if(test)
        ui->tableView->setModel(M.afficher());
    {
        QMessageBox::information(nullptr, QObject::tr("Ajout"),
                    QObject::tr("Enseignant Ajouter.\n"), QMessageBox::Ok);


}
}

void MainWindow::on_pushButton_Annuler_clicked()
{
    close();
}

void MainWindow::on_pushButton_annulersup_clicked()
{
    close();
}

void MainWindow::on_pushButton_supprimer_clicked()
{
 medecin M1 ;
 M1.setid(ui->lineEdit_supp->text().toInt());
 bool test = M1.supprimer(M1.getid());
 if(test)
      ui->tableView->setModel(M.afficher());
 {
     QMessageBox::information(nullptr, QObject::tr("Supprimer"),
                 QObject::tr("Suppression Terminer.\n"), QMessageBox::Ok);

}
}


void MainWindow::on_pushButton_Ajouter_edit_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
        QString nom=ui->lineEdit_nom_edit->text();
        QString prenom=ui->lineEdit_prenom_edit->text();
        QString role=ui->lineEdit_role_edit->text();
        int salaire=ui->lineEdit_salaire_edit->text().toInt();
        QString email=ui->lineEdit_email_edit->text();
        int num=ui->lineEdit_num_edit->text().toInt();



                    medecin M;
                    bool test=M.modifier(id,nom,prenom,role,salaire,email,num);

                    if(test)
                    ui->tableView->setModel(M.afficher());
                    {

                        QMessageBox::information(nullptr, QObject::tr("modifie une depot"),
                                          QObject::tr("depot modifiée.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
                        ui->tableView->setModel(M.afficher());

                        QMessageBox::critical(nullptr, QObject::tr("non modifie"),
                                    QObject::tr("Erreur !.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
                        ui->tableView->setModel(M.afficher());

}
}
void MainWindow::on_rech_clicked()
{
    QString val=ui->le_rech->text();
    QString option=ui->cb_rech_emp->currentText();
    if((val!="")&&(option=="id"))
{        ui->tableView->setModel(M.afficher_id(val));}
    else if((val!="")&&(option=="nom"))
    {
             ui->tableView->setModel(M.afficher_nom(val));
    }
    else if((val!="")&&(option=="salaire"))
    {
               ui->tableView->setModel(M.afficher_salaire(val));
    }else if(option=="choisir")
    {
       ui->tableView->setModel(M.afficher());
    }
}
void MainWindow::on_pdf_push_clicked()
{
    QString id_cb=ui->pdf_c->text();
    medecin * Me ;
    Me=M.readmedecin(id_cb);
    QString id_string=QString::number(Me->getid());
    QString nom_string = Me->getnom();
    QString prenom_string = Me->getprenom();
    QString role_string= Me->getrole();
    QString salaire_string=QString::number(Me->getsalaire());
    QString num_string=QString::number(Me->getnum());

     QPrinter printer;
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName("C:/Users/Admin/Desktop/pdf_projet/"+id_string+".pdf");
                           QPainter painter;
                           if(! painter.begin(&printer))
                           { qWarning("failed to open file");  }
                            painter.setFont(QFont("Sitka Heading", 25));
                            painter.setPen(Qt::blue);
                            painter.drawText(340,100," ADPH ");
                            painter.setPen(Qt::black);
                            painter.drawText(175,50,"Information relative à l'enseignant");
                            painter.setPen(Qt::black);
                            painter.drawText(250,300,"Identifiant : " + id_string);
                            painter.drawText(250,400,"Nom : "+nom_string);
                            painter.drawText(250,500,"Prenom : "+prenom_string);
                            painter.drawText(250,600,"Role : " +role_string);
                            painter.drawText(250,700,"Salaire : "+salaire_string);
                            painter.drawText(250,800,"Num : "+num_string);
                            painter.end();
}

void MainWindow::on_cb_tri_activated(const QString &arg1)
{
    QString choix=ui->cb_tri->currentText();
    ui->tableView->setModel(M.afficher_choix(choix));
}

void MainWindow::on_pb_stat_clicked()
{
    statistiques S;
     S.setModal(true);
     S.exec();
}





