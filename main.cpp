#include <QtCore/QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include<QSql.h>
#include <QSqlTableModel>
#include<iostream>
#include"class.h"

using namespace std;

void connect_mysql()
{
	db.setHostName("127.0.0.1");      //�������ݿ�������(����"127.0.0.1"��"localhost"��
	db.setPort(3306);                 //�������ݿ�˿ں�
	db.setDatabaseName("ADDRESSBOOK");      //�������ݿ���
	db.setUserName("admin");          //���ݿ��û���
	db.setPassword("123456");    //���ݿ�����
	db.open();
	if (!db.open())	//�������״̬
	{
		qDebug() << "Connect Failed!" << db.lastError().text();
		return;
	}
	else
	{
		qDebug() << "Connect Success!";
	}
}
void close_mysql()	//�ر����ݿ�
{
	db.close();
}
int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);		//��������ʵ��
	connect_mysql();
	Contacts ex("gg", "male", "2019-05-12", "example@outlook.com", "324545345");
	ex.Print();
	close_mysql();
	return 0;
}
