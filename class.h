#pragma once
#ifndef _CLASS_H_
#define _CLASS_H_

static QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");	//声明一个数据库实例，并规定连接方式

/*定义父类Contacts*/
class Contacts
{
public:
	Contacts(QString Name,QString Gender,QString Birthday,QString Emailaddress,QString Phonenumber)
	{
		this->Name = Name;
		this->Gender = Gender;
		this->Birthday = Birthday;
		this->Phonenumber = Phonenumber;
		this->Emailaddress = Emailaddress;
	}	//构造联系人
	~Contacts();	//析构联系人
	virtual void Add();		//新增联系人
	virtual void DeleteContacts(QString Name);	//删除联系人
	virtual void Print();	//打印全体人员的姓名、出生日期、电话和email地址
	virtual void Edit();	//编辑联系人（姓名和出生日期除外）
	/*void Sort();	//按照姓名或出生日期排序并打印
	void BirthdayFind();	//查找生日
	void ContactsFind();	//查找联系人
	void CountTheSameMonth();	//计算同一个月出生的人数*/
	friend void connect_mysql();
	friend void close_mysql();
protected:
	QString Name, Gender, Birthday, Phonenumber, Emailaddress;
};
/*父类的函数*/
Contacts::~Contacts() {}
void Contacts::Add()	//新增联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT CONTACTS (name,gender,birthday,email,phonenumber) VALUES ('%1','%2','%3','%4','%5')").arg(Name).arg(Gender).arg(Birthday).arg(Emailaddress).arg(Phonenumber);		//调用数据库语句实现插入操作
	query.exec(sql);	//执行此数据库语句
}
void Contacts::DeleteContacts(QString desName)		//删除联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("DELETE FROM STUDENTS WHERE name='%1'").arg(desName);
	query.exec(sql);
}
void Contacts::Edit()
{}
void Contacts::Print()
{
	QSqlQuery query(db);
	query.exec("select * from contacts");
	std::cout <<"姓名"<<" | " << "性别" << " | " << "出生日期" << " | " <<"邮箱地址"<< " | " << "联系方式"<<std::endl;
	while (query.next())
	{
		
		qDebug() << query.value(0).toString()<<"|"<< query.value(1).toString()<<"|"<<query.value(2).toString()<< "|" << query.value(3).toString()<< "|" << query.value(4).toString();
	}
}

/*定义子类Students*/
class Students:public Contacts
{
public:
	Students(QString Name, QString Gender, QString Birthday, QString Phonenumber, QString Emailaddress, QString school)
	:Contacts(Name, Gender, Birthday, Phonenumber, Emailaddress){
		this->school = school;
	}	//构造同学
	~Students() {}	//析构同学
	void Add();		//新增同学联系人
	//void Edit();	//编辑同学联系人（姓名和出生日期除外）
	void DeleteContacts(QString Name);	//删除同学联系人
	//void Print();	//打印全体同学的姓名、出生日期、电话和email地址*/
private:
	QString school;
};
/*定义子类Students的函数*/
void Students::Add()	//新增联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT STUDENTS (name,school) VALUES ('%1','%2')").arg(Name).arg(school);		//调用数据库语句实现插入操作
	query.exec(sql);	//执行此数据库语句
}
void Students::DeleteContacts(QString desName)		//删除联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("DELETE FROM STUDENTS WHERE name='%1'").arg(desName);
	query.exec(sql);
}

/*定义子类Colleagues*/
class Colleagues :public Contacts
{
public:
	Colleagues(QString Name, QString Gender, QString Birthday, QString Phonenumber, QString Emailaddress, QString company)
		:Contacts(Name, Gender, Birthday, Phonenumber, Emailaddress) {
		this->company = company;
	}//构造同学
	~Colleagues() {}	//析构同事
	void Add();		//新增同事联系人
	//void Edit();	//编辑同事联系人（姓名和出生日期除外）
	void DeleteContacts(QString desName);	//删除同事联系人
	//void Print();	//打印全体同事的姓名、出生日期、电话和email地址*/
private:
	QString company;
};
/*定义子类Colleagues的函数*/
void Colleagues::Add()	//新增联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT COLLEAGUES (name,company) VALUES ('%1','%2')").arg(Name).arg(company);		//调用数据库语句实现插入操作
	query.exec(sql);	//执行此数据库语句
}
void Colleagues::DeleteContacts(QString desName)		//删除联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("DELETE FROM COLLEAGUES WHERE name='%1'").arg(desName);
	query.exec(sql);
}

/*定义子类Friends*/
class Friends :public Contacts
{
public:
	Friends(QString Name, QString Gender, QString Birthday, QString Phonenumber, QString Emailaddress, QString place)
		:Contacts(Name, Gender, Birthday, Phonenumber, Emailaddress) {
		this->place = place;
	}	//构造同学
	~Friends() {};		//析构朋友
	void Add();	//新增朋友联系人
	//void Edit();	//编辑朋友联系人（姓名和出生日期除外）
	void DeleteContacts(QString desName);	//删除朋友联系人
	//void Print();	//打印全体朋友的姓名、出生日期、电话和email地址*/
private:
	QString place;
};
/*定义子类Friends的函数*/
void Friends::Add()	//新增联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT FRIENDS (name,place) VALUES ('%1','%2')").arg(Name).arg(place);		//调用数据库语句实现插入操作
	query.exec(sql);	//执行此数据库语句
}
void Friends::DeleteContacts(QString desName)		//删除联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("DELETE FROM FRIENDS WHERE name='%1'").arg(desName);
	query.exec(sql);
}

/*定义子类Relatives*/
class Relatives :public Contacts
{
public:
	Relatives(QString Name, QString Gender, QString Birthday, QString Phonenumber, QString Emailaddress, QString chenghu)
		:Contacts(Name, Gender, Birthday, Phonenumber, Emailaddress) {
		this->chenghu= chenghu;
	}	//构造亲戚
	~Relatives() {}	//析构亲戚
	void Add();		//新增亲戚联系人
	//void Edit();	//编辑亲戚联系人（姓名和出生日期除外）
	void DeleteContacts(QString desName);	//删除亲戚联系人
	//void Print();	//打印全体亲戚的姓名、出生日期、电话和email地址*/
private:
	QString chenghu;
};
/*定义Relatives的函数*/
void Relatives::Add()	//新增联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT RELATIVES (name,chenghu) VALUES ('%1','%2')").arg(Name).arg(chenghu);		//调用数据库语句实现插入操作
	query.exec(sql);	//执行此数据库语句
}
void Relatives::DeleteContacts(QString desName)		//删除联系人
{
	QSqlQuery query(db);
	QString sql = QObject::tr("DELETE FROM RELATIVES WHERE name='%1'").arg(desName);
	query.exec(sql);
}
#endif