#include "medecin.h"
#include<QSqlQuery>
#include<QDebug>
#include<QObject>

medecin::medecin()
{
id=0, nom=" ",prenom=" ",role=" ",salaire=0,email=" ",num=0;
}

medecin::medecin(int id,QString nom,QString prenom,QString role,int salaire,QString email,int num)
{this->id=id;this->nom=nom;this->prenom=prenom;this->role=role;this->salaire=salaire;this->email=email;this->num=num;}

                    /* ##########     GET     ########## */

int medecin::getid(){return id;}
QString medecin::getnom(){return nom;}
QString medecin::getprenom(){return prenom;}
QString medecin::getrole(){return role;}
int medecin::getsalaire(){return salaire;}
QString medecin::getemail(){return email;}
int medecin::getnum(){return num;}

                    /* ##########     SET     ########## */

void medecin::setid(int id){this->id=id;}
void medecin::setnom(QString nom){this->nom=nom;}
void medecin::setprenom(QString prenom){this->prenom=prenom;}
void medecin::setrole(QString role){this->role=role;}
void medecin::setsalaire(int salaire){this->salaire=salaire;}
void medecin::setemail(QString email){this->email=email;}
void medecin::setnum(int num){this->num=num;}

bool medecin::ajouter(){
    QSqlQuery query;
    QString id_string= QString::number(id);
          query.prepare("INSERT INTO MEDECIN (id, nom, prenom, role, salaire, email, num) "
                        "VALUES (:id, :forename, :surname, :role, :salaire, :email, :num)");
          query.bindValue(":id", id_string);
          query.bindValue(":forename", nom);
          query.bindValue(":surname", prenom);
          query.bindValue(":role", role);
          query.bindValue(":salaire", salaire);
          query.bindValue(":email", email);
          query.bindValue(":num", num);
    return query.exec();
}

bool medecin::supprimer(int id)
{
    QSqlQuery query;
          query.prepare("Delete from MEDECIN where id = :id");
          query.bindValue(0, id);
    return query.exec();


}

QSqlQueryModel* medecin::afficher(){

              QSqlQueryModel* model=new QSqlQueryModel();
                   model->setQuery("SELECT * FROM MEDECIN");
                   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
                   model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
                   model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
                   model->setHeaderData(3, Qt::Horizontal, QObject::tr("ROLE"));
                   model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
                   model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
                   model->setHeaderData(6, Qt::Horizontal, QObject::tr("NUM"));

              return model;
}

bool medecin::modifier(int id ,QString nom,QString prenom,QString role,int salaire,QString email,int num)
          {
              QSqlQuery query;
              query.prepare("UPDATE MEDECIN SET id= :id,nom= :nom,prenom = :prenom,role=:role,salaire=:salaire,email=:email,num=:num  WHERE id= :id ");
              query.bindValue(":id",id);
              query.bindValue(":nom",nom);
              query.bindValue(":prenom",prenom);
             query.bindValue(":role",role);
             query.bindValue(":salaire",salaire);
             query.bindValue(":email",email);
             query.bindValue(":num",num);

              return    query.exec();
          }
