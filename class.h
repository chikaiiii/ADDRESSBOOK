#pragma once

using namespace std;
static QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");	//声明一个数据库实例，并规定连接方式

/*定义父类Contacts*/
class Contacts
{
public:
	Contacts() {}
	Contacts(string Name,string Gender,string Birthday,string Phonenumber,string Emailaddress)
	{
		qName = str2QStr(Name);
		qGender = str2QStr(Gender);
		qBirthday = str2QStr(Birthday);
		qPhonenumber = str2QStr(Phonenumber);
		qEmailaddress = str2QStr(Emailaddress);
	}	//构造联系人
	~Contacts();	//析构联系人
	virtual void Add();	//新增联系人
	virtual void DeleteContacts();	//删除联系人
	virtual void Print();	//打印全体人员的姓名、出生日期、电话和email地址
	virtual void Edit();	//编辑联系人（姓名和出生日期除外）
	void Sortbyname();	//按照姓名排序并打印
	void Sortbybirthday();	//按照出生日期排序并打印
	void BirthdayFind();	//查找生日
	void ContactsFind(QString desName);	//查找联系人
	void CountTheSameMonth(QString month);	//计算同一个月出生的人数
	friend void connect_mysql();
	friend void close_mysql();
	friend QString str2QStr(string str);
protected:
	QString qName, qGender, qBirthday, qPhonenumber, qEmailaddress;
};
/*父类的函数*/
Contacts::~Contacts() {}
void Contacts::Add() { return; }
void Contacts::DeleteContacts() { return; }
void Contacts::Edit() { return; }
void Contacts::Print()	//打印全体联系人
{
	QSqlQuery query(db);
	query.exec("SELECT name,gender,birthday,phonenumber,emailaddress,school as remarks FROM STUDENTS UNION SELECT name,gender,birthday,phonenumber,emailaddress,company as remarks FROM COLLEAGUES UNION SELECT name,gender,birthday,phonenumber,emailaddress,place as remarks FROM FRIENDS UNION SELECT name,gender,birthday,phonenumber,emailaddress,chenghu as remarks FROM RELATIVES");
	std::cout <<"姓名"<<" | " << "性别" << " | " << "出生日期" << " | " <<"邮箱地址"<< " | " << "联系方式"<<" | "<<"备注"<<std::endl;
	while (query.next())
	{
		qDebug()<<query.value("name").toString()<<"|"<<query.value("gender").toString()<<"|"<<query.value("birthday").toString()<<"|"<< query.value("phonenumber").toString()<<"|"<< query.value("emailaddress").toString()<<"|"<<query.value("remarks").toString();
	}
	return;
}
void Contacts::Sortbyname()	//根据名字排序
{
	QSqlQuery query(db);
	query.exec("SELECT * FROM (SELECT name,gender,birthday,phonenumber,emailaddress,school as remarks FROM STUDENTS UNION SELECT name,gender,birthday,phonenumber,emailaddress,company as remarks FROM COLLEAGUES UNION SELECT name,gender,birthday,phonenumber,emailaddress,place as remarks FROM FRIENDS UNION SELECT name,gender,birthday,phonenumber,emailaddress,chenghu as remarks FROM RELATIVES) as c ORDER BY convert(name using gbk) asc");
	std::cout << "姓名" << " | " << "性别" << " | " << "出生日期" << " | " << "邮箱地址" << " | " << "联系方式" << " | " << "备注" << std::endl;
	while (query.next())
	{
		qDebug() << query.value("name").toString() << "|" << query.value("gender").toString() <<"|" << query.value("birthday").toString() << "|" << query.value("phonenumber").toString() << "|" << query.value("emailaddress").toString() << "|" << query.value("remarks").toString();
	}

}
void Contacts::Sortbybirthday()		//根据出生日期排序
{
	QSqlQuery query(db);
	query.exec("SELECT * FROM (SELECT name,gender,birthday,phonenumber,emailaddress,school as remarks FROM STUDENTS UNION SELECT name,gender,birthday,phonenumber,emailaddress,company as remarks FROM COLLEAGUES UNION SELECT name,gender,birthday,phonenumber,emailaddress,place as remarks FROM FRIENDS UNION SELECT name,gender,birthday,phonenumber,emailaddress,chenghu as remarks FROM RELATIVES) as c ORDER BY birthday");
	std::cout << "姓名" << " | " << "性别" << " | " << "出生日期" << " | " << "邮箱地址" << " | " << "联系方式" << " | " << "备注" << std::endl;
	while (query.next())
	{
		qDebug() << query.value("name").toString() << "|" << query.value("gender").toString() << "|" << query.value("birthday").toString() << "|" << query.value("phonenumber").toString() << "|" << query.value("emailaddress").toString() << "|" << query.value("remarks").toString();
	}
}
void Contacts::ContactsFind(QString desName)
{
	bool key = false;
	QSqlQuery query(db);
	QString sql=QObject::tr("SELECT name,gender,birthday,phonenumber,emailaddress,school as remarks FROM STUDENTS WHERE name='%1' UNION SELECT name,gender,birthday,phonenumber,emailaddress,company as remarks FROM COLLEAGUES WHERE name='%1' UNION SELECT name,gender,birthday,phonenumber,emailaddress,place as remarks FROM FRIENDS WHERE name='%1' UNION SELECT name,gender,birthday,phonenumber,emailaddress,chenghu as remarks FROM RELATIVES WHERE name='%1'").arg(desName);
	query.exec(sql);
		while (query.next())
	{
		qDebug() << query.value("name").toString() << "|" << query.value("gender").toString() << "|" << query.value("birthday").toString() << "|" << query.value("phonenumber").toString() << "|" << query.value("emailaddress").toString() << "|" << query.value("remarks").toString();
		key = true;
	}
		if (!key) cout << "NO RESULT!" << endl;
}
void Contacts::BirthdayFind()	//查找生日并发送贺卡
{
	bool isbirthday = false;
	QSqlQuery query(db);
	query.exec("SELECT name FROM STUDENTS WHERE DATE_FORMAT(birthday,'%m%d') BETWEEN DATE_FORMAT(CURDATE(),'%m%d') AND DATE_FORMAT(CURDATE()+INTERVAL 5 DAY,'%m%d') UNION SELECT name FROM COLLEAGUES WHERE DATE_FORMAT(birthday,'%m%d') BETWEEN DATE_FORMAT(CURDATE(),'%m%d') AND DATE_FORMAT(CURDATE()+INTERVAL 5 DAY,'%m%d') UNION SELECT name FROM FRIENDS WHERE DATE_FORMAT(birthday,'%m%d') BETWEEN DATE_FORMAT(CURDATE(),'%m%d') AND DATE_FORMAT(CURDATE()+INTERVAL 5 DAY,'%m%d') UNION SELECT name FROM RELATIVES WHERE DATE_FORMAT(birthday,'%m%d') BETWEEN DATE_FORMAT(CURDATE(),'%m%d') AND DATE_FORMAT(CURDATE()+INTERVAL 5 DAY,'%m%d')");
	while (query.next())
	{
		cout << "消息提示:" << endl;
		qDebug() << query.value("name").toString()<<":"; 
		cout << "祝生日快乐，健康幸福。\n祝贺人姓名" << endl;
		isbirthday = true;
	}
	if (!isbirthday) cout << "消息提示：近期无人生日" << endl;
}
void Contacts::CountTheSameMonth(QString month)
{
	int count = 0;
	QSqlQuery query(db);
	QString sql=QObject::tr("SELECT name,birthday FROM STUDENTS WHERE MONTH(birthday)='%1' UNION SELECT name,birthday FROM COLLEAGUES WHERE MONTH(birthday)='%1' UNION SELECT name,birthday FROM FRIENDS WHERE MONTH(birthday)='%1' UNION SELECT name,birthday FROM RELATIVES WHERE MONTH(birthday)='%1' ").arg(month);
	query.exec(sql);
	while (query.next())
	{
		count++;
	}
	std::cout << "同一个月出生人数为："<<count << std::endl;
}
/*定义子类Students*/
class Students:public Contacts
{
public:
	Students() {}
	Students(string Name, string Gender, string Birthday, string Phonenumber, string Emailaddress, string school):Contacts(Name,Gender,Birthday,Phonenumber,Emailaddress)
	{
		qschool = str2QStr(school);
	}
	~Students() {}	//析构同学
	void Add();		//新增同学联系人
	void Edit(int x,QString newinfo,QString name);	//编辑同学联系人（姓名和出生日期除外）
	void DeleteContacts(QString Name);	//删除同学联系人
	void Print();	//打印全体同学的姓名、出生日期、电话和email地址*/
private:
	QString qschool;
};
/*定义子类Students的函数*/
void Students::Add()	//新增联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT STUDENTS (name,gender,birthday,phonenumber,emailaddress,school) VALUES ('%1','%2','%3','%4','%5','%6')").arg(qName).arg(qGender).arg(qBirthday).arg(qPhonenumber).arg(qEmailaddress).arg(qschool);		//调用数据库语句实现插入操作
	query.exec(sql);	//执行此数据库语句
}
void Students::DeleteContacts(QString desName)		//删除联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("DELETE FROM STUDENTS WHERE name='%1'").arg(desName);
	query.exec(sql);
}
void Students::Print()
{
	QSqlQuery query(db);
	query.exec("SELECT * FROM STUDENTS ");
	std::cout << "姓名" << " | " << "性别" << " | " << "出生日期" << " | " << "联系方式" << " | " << "邮箱地址" <<" | "<<"学校"<< std::endl;
	while (query.next())
	{
		qDebug() << query.value("name").toString() << "|" << query.value("gender").toString() << "|" << query.value("birthday").toString() << "|" << query.value("phonenumber").toString() << "|" << query.value("emailaddress").toString() << "|" << query.value("school").toString();
	}
	return;
}
void Students::Edit(int x,QString newinfo,QString name)
{
	switch (x)
	{
	case 1: {
		QSqlQuery query(db);
		QString sql = QObject::tr("UPDATE STUDENTS SET PHONENUMBER='%1' WHERE name='%2'").arg(newinfo).arg(name);
		query.exec(sql);
	}break;
	case 2: {
		QSqlQuery query(db);
		QString sql = QObject::tr("UPDATE STUDENTS SET EMAILADDRESS='%1' WHERE name='%2'").arg(newinfo).arg(name);
		query.exec(sql);
	}break;
	case 3: {
		QSqlQuery query(db);
		QString sql = QObject::tr("UPDATE STUDENTS SET SCHOOL='%1' WHERE name='%2'").arg(newinfo).arg(name);
		query.exec(sql);
	}break;
	default:break;
	}
	return;
}
/*定义子类Colleagues*/
class Colleagues :public Contacts
{
public:
	Colleagues() {}
	Colleagues(string Name, string Gender, string Birthday, string Phonenumber, string Emailaddress, string company) :Contacts(Name, Gender, Birthday, Phonenumber, Emailaddress)
	{
		qcompany = str2QStr(company);
	} //构造同学
	~Colleagues() {}	//析构同事
	void Add();		//新增同事联系人
	void Edit(int x,QString newinfo,QString name);	//编辑同事联系人（姓名和出生日期除外）
	void DeleteContacts(QString desName);	//删除同事联系人
	void Print();	//打印全体同事的姓名、出生日期、电话和email地址*/
private:
	QString qcompany;
};
/*定义子类Colleagues的函数*/
void Colleagues::Add()	//新增联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT COLLEAGUES (name,gender,birthday,phonenumber,emailaddress,company) VALUES ('%1','%2','%3','%4','%5','%6')").arg(qName).arg(qGender).arg(qBirthday).arg(qPhonenumber).arg(qEmailaddress).arg(qcompany);		//调用数据库语句实现插入操作
	query.exec(sql);	//执行此数据库语句
}
void Colleagues::DeleteContacts(QString desName)		//删除联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("DELETE FROM COLLEAGUES WHERE name='%1'").arg(desName);
	query.exec(sql);
}
void Colleagues::Print()
{
	QSqlQuery query(db);
	query.exec("SELECT * FROM COLLEAGUES");
	std::cout << "姓名" << " | " << "性别" << " | " << "出生日期" << " | " << "联系方式" << " | " << "邮箱地址" << " | " << "单位" << std::endl;
	while (query.next())
	{
		qDebug() << query.value("name").toString() << "|" << query.value("gender").toString() << "|" << query.value("birthday").toString() << "|" << query.value("phonenumber").toString() << "|" << query.value("emailaddress").toString() << "|" << query.value("company").toString();
	}
	return;
}
void Colleagues::Edit(int x, QString newinfo, QString name)
{
	switch (x)
	{
	case 1: {
		QSqlQuery query(db);
		QString sql = QObject::tr("UPDATE STUDENTS SET PHONENUMBER='%1' WHERE name='%2'").arg(newinfo).arg(name);
		query.exec(sql);
	}break;
	case 2: {
		QSqlQuery query(db);
		QString sql = QObject::tr("UPDATE STUDENTS SET EMAILADDRESS='%1' WHERE name='%2'").arg(newinfo).arg(name);
		query.exec(sql);
	}break;
	case 3: {
		QSqlQuery query(db);
		QString sql = QObject::tr("UPDATE STUDENTS SET COMPANY='%1' WHERE name='%2'").arg(newinfo).arg(name);
		query.exec(sql);
	}break;
	default:break;
	}
}
/*定义子类Friends*/
class Friends :public Contacts
{
public:
	Friends() {}
	Friends(string Name, string Gender, string Birthday, string Phonenumber, string Emailaddress, string place) :Contacts(Name, Gender, Birthday, Phonenumber, Emailaddress)
	{
		qplace = str2QStr(place);
	}	//构造同学
	~Friends() {};		//析构朋友
	void Add();	//新增朋友联系人
	void Edit(int x,QString newinfo,QString name);	//编辑朋友联系人（姓名和出生日期除外）
	void DeleteContacts(QString desName);	//删除朋友联系人
	void Print();	//打印全体朋友的姓名、出生日期、电话和email地址*/
private:
	QString qplace;
};
/*定义子类Friends的函数*/
void Friends::Add()	//新增联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT FRIENDS (name,gender,birthday,phonenumber,emailaddress,place) VALUES ('%1','%2','%3','%4','%5','%6')").arg(qName).arg(qGender).arg(qBirthday).arg(qPhonenumber).arg(qEmailaddress).arg(qplace);		//调用数据库语句实现插入操作
	query.exec(sql);	//执行此数据库语句
}
void Friends::DeleteContacts(QString desName)		//删除联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("DELETE FROM FRIENDS WHERE name='%1'").arg(desName);
	query.exec(sql);
}
void Friends::Print()
{
	QSqlQuery query(db);
	query.exec("SELECT * FROM FRIENDS");
	std::cout << "姓名" << " | " << "性别" << " | " << "出生日期" << " | " << "联系方式" << " | " << "邮箱地址" << " | " << "认识地点" << std::endl;
	while (query.next())
	{
		qDebug() << query.value("name").toString() << "|" << query.value("gender").toString() << "|" << query.value("birthday").toString() << "|" << query.value("phonenumber").toString() << "|" << query.value("emailaddress").toString() << "|" << query.value("place").toString();
	}
	return;
}
void Friends::Edit(int x, QString newinfo, QString name)
{
	switch (x)
	{
	case 1: {
		QSqlQuery query(db);
		QString sql = QObject::tr("UPDATE STUDENTS SET PHONENUMBER='%1' WHERE name='%2'").arg(newinfo).arg(name);
		query.exec(sql);
	}break;
	case 2: {
		QSqlQuery query(db);
		QString sql = QObject::tr("UPDATE STUDENTS SET EMAILADDRESS='%1' WHERE name='%2'").arg(newinfo).arg(name);
		query.exec(sql);
	}break;
	case 3: {
		QSqlQuery query(db);
		QString sql = QObject::tr("UPDATE STUDENTS SET PLACE='%1' WHERE name='%2'").arg(newinfo).arg(name);
		query.exec(sql);
	}break;
	default:break;
	}
}
/*定义子类Relatives*/
class Relatives :public Contacts
{
public:
	Relatives() {}
	Relatives(string Name, string Gender, string Birthday, string Phonenumber, string Emailaddress, string chenghu) :Contacts(Name, Gender, Birthday, Phonenumber, Emailaddress)
	{
		qchenghu = str2QStr(chenghu);
	}	//构造亲戚
	~Relatives() {}	//析构亲戚
	void Add();		//新增亲戚联系人
	void Edit(int x,QString newinfo,QString name);	//编辑亲戚联系人（姓名和出生日期除外）
	void DeleteContacts(QString desName);	//删除亲戚联系人
	void Print();	//打印全体亲戚的姓名、出生日期、电话和email地址*/
private:
	QString qchenghu;
};
/*定义Relatives的函数*/
void Relatives::Add()	//新增联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT RELATIVES (name,gender,birthday,phonenumber,emailaddress,chenghu) VALUES ('%1','%2','%3','%4','%5','%6')").arg(qName).arg(qGender).arg(qBirthday).arg(qPhonenumber).arg(qEmailaddress).arg(qchenghu);		//调用数据库语句实现插入操作
	query.exec(sql);	//执行此数据库语句
}
void Relatives::DeleteContacts(QString desName)		//删除联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("DELETE FROM RELATIVES WHERE name='%1'").arg(desName);
	query.exec(sql);
}
void Relatives::Print()
{
	QSqlQuery query(db);
	query.exec("SELECT * FROM RELATIVES");
	std::cout << "姓名" << " | " << "性别" << " | " << "出生日期" << " | " << "联系方式" << " | " << "邮箱地址" << " | " << "称呼" << std::endl;
	while (query.next())
	{
		qDebug() << query.value("name").toString() << "|" << query.value("gender").toString() << "|" << query.value("birthday").toString() << "|" << query.value("phonenumber").toString() << "|" << query.value("emailaddress").toString() << "|" << query.value("chenghu").toString();
	}
	return;
}
void Relatives::Edit(int x, QString newinfo, QString name)
{
	switch (x)
	{
	case 1: {
		QSqlQuery query(db);
		QString sql = QObject::tr("UPDATE STUDENTS SET PHONENUMBER='%1' WHERE name='%2'").arg(newinfo).arg(name);
		query.exec(sql);
	}break;
	case 2: {
		QSqlQuery query(db);
		QString sql = QObject::tr("UPDATE STUDENTS SET EMAILADDRESS='%1' WHERE name='%2'").arg(newinfo).arg(name);
		query.exec(sql);
	}break;
	case 3: {
		QSqlQuery query(db);
		QString sql = QObject::tr("UPDATE STUDENTS SET CHENGHU='%1' WHERE name='%2'").arg(newinfo).arg(name);
		query.exec(sql);
	}break;
	default:break;
	}
}
