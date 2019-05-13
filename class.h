#pragma once
#ifndef _CLASS_H_
#define _CLASS_H_

static QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");	//����һ�����ݿ�ʵ�������涨���ӷ�ʽ

/*���常��Contacts*/
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
	}	//������ϵ��
	~Contacts();	//������ϵ��
	virtual void Add();		//������ϵ��
	virtual void DeleteContacts(QString Name);	//ɾ����ϵ��
	virtual void Print();	//��ӡȫ����Ա���������������ڡ��绰��email��ַ
	virtual void Edit();	//�༭��ϵ�ˣ������ͳ������ڳ��⣩
	/*void Sort();	//��������������������򲢴�ӡ
	void BirthdayFind();	//��������
	void ContactsFind();	//������ϵ��
	void CountTheSameMonth();	//����ͬһ���³���������*/
	friend void connect_mysql();
	friend void close_mysql();
protected:
	QString Name, Gender, Birthday, Phonenumber, Emailaddress;
};
/*����ĺ���*/
Contacts::~Contacts() {}
void Contacts::Add()	//������ϵ��
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT CONTACTS (name,gender,birthday,email,phonenumber) VALUES ('%1','%2','%3','%4','%5')").arg(Name).arg(Gender).arg(Birthday).arg(Emailaddress).arg(Phonenumber);		//�������ݿ����ʵ�ֲ������
	query.exec(sql);	//ִ�д����ݿ����
}
void Contacts::DeleteContacts(QString desName)		//ɾ����ϵ��
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
	std::cout <<"����"<<" | " << "�Ա�" << " | " << "��������" << " | " <<"�����ַ"<< " | " << "��ϵ��ʽ"<<std::endl;
	while (query.next())
	{
		
		qDebug() << query.value(0).toString()<<"|"<< query.value(1).toString()<<"|"<<query.value(2).toString()<< "|" << query.value(3).toString()<< "|" << query.value(4).toString();
	}
}

/*��������Students*/
class Students:public Contacts
{
public:
	Students(QString Name, QString Gender, QString Birthday, QString Phonenumber, QString Emailaddress, QString school)
	:Contacts(Name, Gender, Birthday, Phonenumber, Emailaddress){
		this->school = school;
	}	//����ͬѧ
	~Students() {}	//����ͬѧ
	void Add();		//����ͬѧ��ϵ��
	//void Edit();	//�༭ͬѧ��ϵ�ˣ������ͳ������ڳ��⣩
	void DeleteContacts(QString Name);	//ɾ��ͬѧ��ϵ��
	//void Print();	//��ӡȫ��ͬѧ���������������ڡ��绰��email��ַ*/
private:
	QString school;
};
/*��������Students�ĺ���*/
void Students::Add()	//������ϵ��
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT STUDENTS (name,school) VALUES ('%1','%2')").arg(Name).arg(school);		//�������ݿ����ʵ�ֲ������
	query.exec(sql);	//ִ�д����ݿ����
}
void Students::DeleteContacts(QString desName)		//ɾ����ϵ��
{
	QSqlQuery query(db);
	QString sql = QObject::tr("DELETE FROM STUDENTS WHERE name='%1'").arg(desName);
	query.exec(sql);
}

/*��������Colleagues*/
class Colleagues :public Contacts
{
public:
	Colleagues(QString Name, QString Gender, QString Birthday, QString Phonenumber, QString Emailaddress, QString company)
		:Contacts(Name, Gender, Birthday, Phonenumber, Emailaddress) {
		this->company = company;
	}//����ͬѧ
	~Colleagues() {}	//����ͬ��
	void Add();		//����ͬ����ϵ��
	//void Edit();	//�༭ͬ����ϵ�ˣ������ͳ������ڳ��⣩
	void DeleteContacts(QString desName);	//ɾ��ͬ����ϵ��
	//void Print();	//��ӡȫ��ͬ�µ��������������ڡ��绰��email��ַ*/
private:
	QString company;
};
/*��������Colleagues�ĺ���*/
void Colleagues::Add()	//������ϵ��
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT COLLEAGUES (name,company) VALUES ('%1','%2')").arg(Name).arg(company);		//�������ݿ����ʵ�ֲ������
	query.exec(sql);	//ִ�д����ݿ����
}
void Colleagues::DeleteContacts(QString desName)		//ɾ����ϵ��
{
	QSqlQuery query(db);
	QString sql = QObject::tr("DELETE FROM COLLEAGUES WHERE name='%1'").arg(desName);
	query.exec(sql);
}

/*��������Friends*/
class Friends :public Contacts
{
public:
	Friends(QString Name, QString Gender, QString Birthday, QString Phonenumber, QString Emailaddress, QString place)
		:Contacts(Name, Gender, Birthday, Phonenumber, Emailaddress) {
		this->place = place;
	}	//����ͬѧ
	~Friends() {};		//��������
	void Add();	//����������ϵ��
	//void Edit();	//�༭������ϵ�ˣ������ͳ������ڳ��⣩
	void DeleteContacts(QString desName);	//ɾ��������ϵ��
	//void Print();	//��ӡȫ�����ѵ��������������ڡ��绰��email��ַ*/
private:
	QString place;
};
/*��������Friends�ĺ���*/
void Friends::Add()	//������ϵ��
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT FRIENDS (name,place) VALUES ('%1','%2')").arg(Name).arg(place);		//�������ݿ����ʵ�ֲ������
	query.exec(sql);	//ִ�д����ݿ����
}
void Friends::DeleteContacts(QString desName)		//ɾ����ϵ��
{
	QSqlQuery query(db);
	QString sql = QObject::tr("DELETE FROM FRIENDS WHERE name='%1'").arg(desName);
	query.exec(sql);
}

/*��������Relatives*/
class Relatives :public Contacts
{
public:
	Relatives(QString Name, QString Gender, QString Birthday, QString Phonenumber, QString Emailaddress, QString chenghu)
		:Contacts(Name, Gender, Birthday, Phonenumber, Emailaddress) {
		this->chenghu= chenghu;
	}	//��������
	~Relatives() {}	//��������
	void Add();		//����������ϵ��
	//void Edit();	//�༭������ϵ�ˣ������ͳ������ڳ��⣩
	void DeleteContacts(QString desName);	//ɾ��������ϵ��
	//void Print();	//��ӡȫ�����ݵ��������������ڡ��绰��email��ַ*/
private:
	QString chenghu;
};
/*����Relatives�ĺ���*/
void Relatives::Add()	//������ϵ��
{
	QSqlQuery query(db);
	QString sql = QObject::tr("INSERT RELATIVES (name,chenghu) VALUES ('%1','%2')").arg(Name).arg(chenghu);		//�������ݿ����ʵ�ֲ������
	query.exec(sql);	//ִ�д����ݿ����
}
void Relatives::DeleteContacts(QString desName)		//ɾ����ϵ��
{
	QSqlQuery query(db);
	QString sql = QObject::tr("DELETE FROM RELATIVES WHERE name='%1'").arg(desName);
	query.exec(sql);
}
#endif