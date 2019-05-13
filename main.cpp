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
	db.setHostName("127.0.0.1");      //连接数据库主机名(可填"127.0.0.1"或"localhost"）
	db.setPort(3306);                 //连接数据库端口号
	db.setDatabaseName("ADDRESSBOOK");      //连接数据库名
	db.setUserName("admin");          //数据库用户名
	db.setPassword("123456");    //数据库密码
	db.open();
	if (!db.open())	//检测连接状态
	{
		qDebug() << "Connect Failed!" << db.lastError().text();
		return;
	}
	else
	{
		qDebug() << "Connect Success!";
	}
}
void close_mysql()	//关闭数据库
{
	db.close();
}
int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);		//创建窗口实例
	connect_mysql();
	Contacts ex("gg", "male", "2019-05-12", "example@outlook.com", "324545345");
	ex.Print();
	close_mysql();
	return 0;
}
