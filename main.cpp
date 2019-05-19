#include<QtCore/QCoreApplication>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QtDebug>
#include<QtSql/qtsqlglobal.h>
#include<QSqlTableModel>
#include<iostream>
#include<string>
#include<Windows.h>
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
		QSqlQuery query(db);
		query.exec("CREATE TABLE IF NOT EXISTS STUDENTS(name VARCHAR(50) NOT NULL,gender VARCHAR(50) NOT NULL,birthday DATE NOT NULL,phonenumber VARCHAR(50) NOT NULL,emailaddress VARCHAR(50) NOT NULL,school VARCHAR(50) NOT NULL) ENGINE =InnoDB DEFAULT CHARSET=utf-8");
		query.exec("CREATE TABLE IF NOT EXISTS COLLEAGUES(name VARCHAR(50) NOT NULL,gender VARCHAR(50) NOT NULL,birthday DATE NOT NULL,phonenumber VARCHAR(50) NOT NULL,emailaddress VARCHAR(50) NOT NULL,company VARCHAR(50) NOT NULL) ENGINE =InnoDB DEFAULT CHARSET=utf-8");
		query.exec("CREATE TABLE IF NOT EXISTS FRIENDS(name VARCHAR(50) NOT NULL,gender VARCHAR(50) NOT NULL,birthday DATE NOT NULL,phonenumber VARCHAR(50) NOT NULL,emailaddress VARCHAR(50) NOT NULL,place VARCHAR(50) NOT NULL) ENGINE =InnoDB DEFAULT CHARSET=utf-8");
		query.exec("CREATE TABLE IF NOT EXISTS RELATIVES(name VARCHAR(50) NOT NULL,gender VARCHAR(50) NOT NULL,birthday DATE NOT NULL,phonenumber VARCHAR(50) NOT NULL,emailaddress VARCHAR(50) NOT NULL,chenghu VARCHAR(50) NOT NULL) ENGINE =InnoDB DEFAULT CHARSET=utf-8");
	}
}
void close_mysql()	//关闭数据库
{
	db.close();
}
void mainmenu()		//主菜单界面
{
	system("cls");
	cout << "***************通讯录管理系统***************" << endl;
	cout << "1.新建联系人\t\t\t2.编辑联系人" << endl;
	cout << "3.删除联系人\t\t\t4.显示联系人" << endl;
	cout << "5.查找联系人\t\t\t6.其他操作" << endl;
	cout << "7.退出" << endl;
	cout << "********************************************" << endl;
	return;
}
void newcontacts()		//新建联系人菜单界面
{
	system("cls");
	cout << "***************新建联系人***************" << endl;
	cout << "1.新建同学联系人\t2.新建同事联系人" << endl;
	cout << "3.新建朋友联系人\t4.新建亲戚联系人" << endl;
	cout << "其他:返回上一级" << endl;
	cout << "****************************************" << endl;
	return;
}
void editcontacts()		//编辑联系人菜单界面
{
	system("cls");
	cout << "***************编辑联系人***************" << endl;
	cout << "1.编辑同学联系人\t2.编辑同事联系人" << endl;
	cout << "3.编辑朋友联系人\t4.编辑亲戚联系人" << endl;
	cout << "其他:返回上一级" << endl;
	cout << "****************************************" << endl;
	return;
}
void deletecontacts()		//删除联系人菜单界面
{
	system("cls");
	cout << "***************删除联系人***************" << endl;
	cout << "1.删除同学联系人\t2.删除同事联系人" << endl;
	cout << "3.删除朋友联系人\t4.删除亲戚联系人" << endl;
	cout << "其他:返回上一级" << endl;
	cout << "****************************************" << endl;
}
void findcontacts()		//显示联系人菜单界面
{
	system("cls");
	cout << "***************显示联系人***************" << endl;
	cout << "1.显示同学联系人\t2.显示同事联系人" << endl;
	cout << "3.显示朋友联系人\t4.显示亲戚联系人" << endl;
	cout << "5.显示全体联系人\t6.按生日顺序显示" << endl;
	cout << "7.按姓名顺序显示\t其他：返回上一级" << endl;
	cout << "****************************************" << endl;
}
void others()		//其他操作
{
	system("cls");
	cout << "*****************其他操作*****************" << endl;
	cout << "1.计算同月生日人数\t\t2其他：返回上一级" << endl;
	cout << "******************************************" << endl;
}
QString str2QStr(string str)	//将string转成QString并解决乱码问题
{
	return QString::fromLocal8Bit(str.data());
}
void BirthdayCard()
{
	Contacts obj;
	obj.BirthdayFind();
	obj.~Contacts();
}

int main(int argc, char* argv[])
{
	int n;
	QCoreApplication a(argc, argv);		//创建窗口实例
	connect_mysql();	//建立数据库连接并返回连接状态
jiemian:mainmenu();	//进入主界面
	BirthdayCard();
	while (cin >> n)
	{
		switch (n)		//判断主界面的操作选择
		{
			//添加联系人
		case 1: {
			char com;
			xinjian:newcontacts(); 
			cin >> com;
			switch (com)		//判断联系人菜单的操作选择
			{
			case '1': {
				string name, gender, birthday, phonenumber, email, school;
				cout << "请输入联系人信息:"<<endl;
				cin >> name >> gender >> birthday >> phonenumber >> email >> school;
				Students obj(name, gender, birthday, phonenumber, email, school);
				obj.Add();
				cout << "新建成功!" << endl;
			}; goto xinjian;
			case '2': {
				string name, gender, birthday, phonenumber, email, company;
				cout << "请输入联系人信息:";
				cin >> name >> gender >> birthday >> phonenumber >> email >>company;
				Colleagues obj(name, gender, birthday, phonenumber, email, company);
				obj.Add();
				cout << "新建成功!" << endl;
			}; goto xinjian;
			case '3': {
				string name, gender, birthday, phonenumber, email, place;
				cout << "请输入联系人信息:";
				cin >> name >> gender >> birthday >> phonenumber >> email >> place;
				Friends obj(name, gender, birthday, phonenumber, email, place);
				obj.Add();
				cout << "新建成功!" << endl;
			}; goto xinjian;
			case '4': {
				string name, gender, birthday, phonenumber, email,chenghu;
				cout << "请输入联系人信息:";
				cin >> name >> gender >> birthday >> phonenumber >> email >> chenghu;
				Relatives obj(name, gender, birthday, phonenumber, email, chenghu);
				obj.Add();
				cout << "新建成功!" << endl;
			}; goto xinjian;
			default: goto jiemian;
			}
		}break;
			//编辑联系人
		case 2: 
		{
			char com;
			bianji:editcontacts();
			cin >> com;
			switch (com)		//判断联系人菜单的操作选择
			{
			case '1': {
				Students obj;
				obj.Print();
				int x;
				string name, newinfo;
				cout << "1.编辑联系方式\t2.编辑邮件地址\t3.编辑学校" << endl;
				cin >> x;
				cout << "请输入姓名和更改信息:" << endl;
				cin >>name>> newinfo;
				QString qname=str2QStr(name),qnewinfo = str2QStr(newinfo);
				obj.Edit(x, qnewinfo,qname);
				cout << "修改成功!" << endl;
			}; goto bianji;
			case '2': {
				Colleagues obj;
				obj.Print();
				int x;
				string name, newinfo;
				cout << "1.编辑联系方式\t2.编辑邮件地址\t3.编辑单位" << endl;
				cin >> x;
				cout << "请输入姓名和更改信息:" << endl;
				cin >> name >> newinfo;
				QString qname = str2QStr(name), qnewinfo = str2QStr(newinfo);
				obj.Edit(x, qnewinfo, qname);
				cout << "修改成功!" << endl;
			}; goto bianji;
			case '3': {
				Friends obj;
				obj.Print();
				int x;
				string name, newinfo;
				cout << "1.编辑联系方式\t2.编辑邮件地址\t3.编辑认识地点" << endl;
				cin >> x;
				cout << "请输入姓名和更改信息:" << endl;
				cin >> name >> newinfo;
				QString qname = str2QStr(name), qnewinfo = str2QStr(newinfo);
				obj.Edit(x, qnewinfo, qname);
				cout << "修改成功!" << endl;
			}; goto bianji;
			case '4': {
				Relatives obj;
				obj.Print();
				int x;
				string name, newinfo;
				cout << "1.编辑联系方式\t2.编辑邮件地址\t3.编辑称呼" << endl;
				cin >> x;
				cout << "请输入姓名和更改信息:" << endl;
				cin >> name >> newinfo;
				QString qname = str2QStr(name), qnewinfo = str2QStr(newinfo);
				obj.Edit(x, qnewinfo, qname);
				cout << "修改成功!" << endl;
			}; goto bianji;
			default: goto jiemian; 
			}
		}break;
		//删除联系人
		case 3: 
		{char com;
			shanchu:deletecontacts();
			cin >> com;
			switch (com)		//判断联系人菜单的操作选择
			{
			case '1': {
				Students obj;
				obj.Print();
				cout << "请输入要删除的对象:" << endl;
				string name;
				cin >> name;
				QString qname = str2QStr(name);
				obj.DeleteContacts(qname);
				obj.Print();
				system("pause");
			};goto shanchu;
			case '2': {
				Colleagues obj;
				obj.Print();
				cout << "请输入要删除的对象:" << endl;
				string name;
				cin >> name;
				QString qname = str2QStr(name);
				obj.DeleteContacts(qname);
				obj.Print();
				system("pause");
			}; goto shanchu;
			case '3': {
				Friends obj;
				obj.Print();
				cout << "请输入要删除的对象:" << endl;
				string name;
				cin >> name;
				QString qname = str2QStr(name);
				obj.DeleteContacts(qname);
				obj.Print();
				system("pause");
			}; goto shanchu;
			case '4': {
				Relatives obj;
				obj.Print();
				cout << "请输入要删除的对象:" << endl;
				string name;
				cin >> name;
				QString qname = str2QStr(name);
				obj.DeleteContacts(qname);
				obj.Print();
				system("pause");
			}; goto shanchu;
			default: goto jiemian; 
			}
			}break;
		//显示联系人
		case 4: 
		{	char com;
			xianshi:findcontacts();
			cin >> com;
			switch (com)		//判断联系人菜单的操作选择
			{
			case '1': {
				Students obj;
				obj.Print();
				system("pause");
			}; goto xianshi;
			case '2': {
				Colleagues obj;
				obj.Print();
				system("pause");
			}; goto xianshi;
			case '3': {
				Friends obj;
				obj.Print();
				system("pause");
			}; goto xianshi;
			case '4': {
				Relatives obj;
				obj.Print();
				system("pause");
			}; goto xianshi;
			case '5': {
				Contacts obj;
				obj.Print();
				system("pause");
			}; goto xianshi;
			case '6': {
				Contacts obj;
				obj.Sortbybirthday();
				system("pause");
			}; goto xianshi;
			case '7': {
				Contacts obj;
				obj.Sortbyname();
				system("pause");
			}; goto xianshi;
			default: goto jiemian; 
			}
			}break;
		//查找联系人
		case 5: 
		{
			Contacts obj;
			string name,command;
			int x;
			shuru:cout << "请输入要查找的联系人:" << endl;
			cin >> name;
			QString qname = str2QStr(name);
			obj.ContactsFind(qname);	//查找联系人
			system("pause");
			cout << "请决定下一步操作：1.继续查找；2.返回" << endl;
			cin >> x;
			if (x == 1) goto shuru;
			else  goto jiemian; 
		}; break;
		case 6: 
		{
			char com;
			qita:others();
			cin >> com;
			switch (com)		//判断联系人菜单的操作选择
			{
			case '1': {
				Contacts obj;
				string m;
				cout << "请输入月份:" << endl;
				cin >> m;
				QString qm = str2QStr(m);
				obj.CountTheSameMonth(qm);
				system("pause");
			}; goto qita;
			default: goto jiemian;
			}
			}break;
		case 7:goto guanbi;
		default:cout << "error!" << endl; break; 
		}
	}
	guanbi:close_mysql();
	return 0;
}
