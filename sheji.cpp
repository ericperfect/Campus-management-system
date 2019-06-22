#include<iostream.h>//����Ҫ����Ԫ����.hͷ�ļ�������
#include<string.h>//C�����ַ������ļ�
#include<fstream.h>//�ļ����������
#include<stdlib.h>//exit��������Ҫ
const int Size=80;
fstream iofile;//����һ���ļ������������ʵ�ֶ��ļ��Ĳ���
//�����������
class Date{
public:
	int year;
	int month;
	int day;
};
//����һ��Attr�����������Ա�ĸ�������,��������������Ԫ�����������ļ���д
class Attr{
public:
	char num[20];
	char name[20];
	char sex[6];
	Date birth;
	char department[20];
	Date worktime;
	int age;
	friend istream& operator>>(istream& in,Attr& A);
	friend ostream& operator<<(ostream& out,Attr& A);
	friend int operator-(Date& d1,Date& d2);//��������
	
	
};
//������Ա��
class People{
protected:
    static int lengthT;
	static int lengthS;
	
	Date date;
public:
	People();
	Attr array[Size];
	virtual void Add_all()=0;//������Ա��Ϣ
	virtual void Add_file()=0;//���ļ�������Ϣ
	virtual void Add()=0;//������Ϣ
	virtual void display()=0;//�麯��display���������������
	virtual int Aveage()=0;//�麯���������ƽ������
	virtual void FindName(const char a_name[])=0;//�麯�����ڰ���������
	virtual void FindAge(const int a_age)=0;//�麯�����ڰ��������
	virtual void Delete_Name(char name[])=0;
	virtual void Delete(int i);
	virtual void modAge( int age)=0;
	virtual void modName(char a_name[])=0;
	
};
//������ʦ��
class Teacher:virtual public People{
public:
	virtual void FindName(const char a_name[]);
    virtual void FindAge(const int a_age);
	virtual void Add_all();
	virtual void Add_file();
	virtual void Add();
	virtual void display();
	virtual int Aveage();
	virtual void Delete_Name(char name[]);
	virtual void Delete(int i);
	virtual void modAge( int age);
    virtual void modName(char a_name[]);
	
};
//ѧ���������
class Student:virtual public People{
public:
	virtual void FindName(const char a_name[]);
    virtual void FindAge(const int a_age);
	virtual void Add_all();
	virtual void Add_file();
	virtual void Add();
	virtual void display();
	virtual int Aveage();
	virtual void Delete_Name(char name[]);
	virtual void Delete(int i);
	virtual void modAge( int age);
	virtual void modName(char a_name[]);
	
};
int People::lengthT=0;
int People::lengthS=0;


People::People(){
	//int length=0;
	date.year=2017;
	date.month=2;
	date.day=24;
	
	
}

/*void People::display(){
for(int i=0;i<length;i++)
cout<<array[i];
}*/
/*int People::Aveage(){
int sum=0;
for(int i=0;i<lengthT+lengthS;i++)
sum+=array[i].age;
return sum/lengthT+lengthS;
}*/
/*void People::FindName(const char a_name[]){
for(int i=0;i<lengthT+lengthS;i++)
if(strcmp(array[i].name,a_name)==0)
cout<<array[i];
}
void People::FindAge(const int a_age){
for(int i=0;i<lengthT+lengthS;i++)
if(array[i].age==a_age)
cout<<array[i];
}*/

void People::Delete(int i){
	if(i<1||i>lengthT)
		cout<<"�����ڵ�"<<i<<"��Ԫ��!"<<endl;
	for(int j=i;j<lengthT;j++)
		array[j-1]=array[j];
	lengthT--;
	cout<<"ɾ���ɹ�!"<<endl;
}
void Teacher::modAge(int age){
	int j,newage;
	cout<<"�޸������밴1    ���޸İ�2"<<endl;
	cin>>j;
	if(j==1){
		for(int i=0;i<lengthT;i++)
			if(array[i].age==age)
			{	cout<<"������������"<<endl;
			cin>>newage;
			array[i].age=newage;
			cout<<"�޸ĳɹ�"<<endl;
			}
			else if(j==2){
				break;
			}
			else
				cout<<"��������ȷ!"<<endl;
	}
	
}
void Teacher::modName(char name[]){
	int j; char newname[20];
	cout<<"�޸������밴1    ���޸İ�2"<<endl;
	cin>>j;
				if(j==1){
					
					for(int i=0;i<lengthT;i++)
						if(strcmp(array[i].name,name)==0)
						{		
							cout<<"������������"<<endl;
							cin.getline(newname,20,'#');
							strcpy(array[i].name,newname);
							
								cout<<"�޸ĳɹ�"<<endl;
						}
						
						
						else if(j==2){
							break;
						}
						else
							cout<<"��������ȷ!"<<endl;
				}
				
}

void Teacher::Add_all(){
	char ch;
	iofile.open("Teacher_info.txt",ios::in|ios::binary|ios::out);
	do{
		cin>>array[lengthT];
		array[lengthT].age=date-array[lengthT].birth;
		iofile.write((char*)&array[lengthT],sizeof(array[lengthT]));
		cout<<"���������Ա��Ϣ�ɹ�!"<<endl;
		lengthT++;
		if(lengthT==Size){
			cout<<"�洢�ռ�����!"<<endl;
			break;
		}
		cout<<"���������?";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	iofile.close();
}
void Teacher::Add_file(){//���������������
	//lengthT=lengthT-1;
	iofile.open("Teacher_info.txt",ios::in);
	while(iofile.seekg(sizeof(array[lengthT]),ios::beg)){
		if(iofile.seekg(lengthT*sizeof(array[lengthT]),ios::beg))
			iofile.read((char*)&array[lengthT],sizeof(array[lengthT]));
		else
			break;
		lengthT++;
	}
	lengthT=lengthT-1;
	if(lengthT==Size){
		cout<<"�洢�ռ�����!"<<endl;
		People::Delete(lengthT);
	}
	cout<<"������Ա��Ϣ�ɹ�!"<<endl;
	iofile.close();
}
void Teacher::FindName(const char a_name[]){
	for(int i=0;i<lengthT+lengthS;i++)
		if(strcmp(array[i].name,a_name)==0)
			cout<<array[i];
}
void Teacher::FindAge(const int a_age){
	for(int i=0;i<lengthT+lengthS;i++)
		if(array[i].age==a_age)
			cout<<array[i];
}

void Teacher::Add(){
	
	iofile.open("Teacher_info.txt",ios::app|ios::out|ios::binary);
	if(lengthT==Size){
		cout<<"��Ϣ�洢�ռ�����!"<<endl;
	}
	cin>>array[lengthT];
	array[lengthT].age=date-array[lengthT].birth;
	iofile.write((char*)&array[lengthT],sizeof(array[lengthT]));
	cout<<"������Ա��Ϣ�ɹ�!"<<endl;
	lengthT++;
	iofile.close();
}
void Teacher::display(){
	cout<<"************�����ʦ��Ϣ************"<<endl;
	if(lengthT==0)
		cout<<"������Ϣ!"<<endl;
	for(int i=0;i<lengthT;i++)
		cout<<array[i]<<"========================================================================="<<'\n';
}
int Teacher::Aveage(){
	int sum=0;
	for(int i=0;i<lengthT;i++)
		sum+=array[i].age;
	return sum/lengthT;
}
void Teacher::Delete_Name(char name[]){
	int k=0;
	for(int i=0;i<lengthT;i++)
		if(strcmp(array[i].name,name)==0){
			k=i+1;
			break;
		}
		if(k<1)
			cout<<"����������Ϊ"<<name<<"����Ա��Ϣ!"<<endl;
		for(int j=k;j<lengthT;j++)
			array[j-1]=array[i];
		lengthT--;
		cout<<"ɾ���ɹ�!"<<endl;
}
void Teacher::Delete(int i){
	if(i<1||i>lengthT)
		cout<<"�����ڵ�"<<i<<"��Ԫ��!"<<endl;
	for(int j=i;j<lengthT;j++)
		array[j-1]=array[j];
	lengthT--;
	cout<<"ɾ���ɹ�!"<<endl;
}
void Student::modName(char name[]){
	int j; char newname[20];
	cout<<"�޸������밴1    ���޸İ�2"<<endl;
	cin>>j;
				if(j==1){
					
					for(int i=0;i<lengthT;i++)
					
						if(strcmp(array[i].name,name)==0)
					{		cout<<"������������"<<endl;
					cin.getline(newname,20,'#');
					strcpy(array[i].name,newname);
					cout<<"�޸ĳɹ�"<<endl;
					}
					
				
					
					else if(j==2)
						break;
					
					else
						cout<<"��������ȷ!"<<endl;
				}
				
}
void Student::modAge(int age){
	int j,newage;
	cout<<"�޸������밴1    ���޸İ�2"<<endl;
	cin>>j;
	if(j==1){
		
		for(int i=0;i<lengthT+lengthS;i++)
			if(array[i].age==age)
			{	cout<<"������������"<<endl;
			cin>>newage;
			array[i].age=newage;
			cout<<"�޸ĳɹ�"<<endl;
			}
			else if(j==2){
				break;
			}
			else
				cout<<"��������ȷ!"<<endl;
	}
	
}
void Student::Add_all(){
	char ch;
	iofile.open("Student_info.txt",ios::out|ios::binary);
	do{
		cin>>array[lengthS];
		array[lengthS].age=date-array[lengthS].birth;
		iofile.write((char*)&array[lengthS],sizeof(array[lengthS]));
		cout<<"������Ա��Ϣ�ɹ�!"<<endl;
		lengthS++;
		if(lengthS==Size){
			cout<<"�洢�ռ�����!"<<endl;
			break;
		}
		cout<<"���������?";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	iofile.close();
}
void Student::Add_file(){//��ͬ�������
	//lengthS=lengthS-1;
	iofile.open("Student_info.txt",ios::in|ios::binary);
	while(iofile.seekg(sizeof(array[lengthS]),ios::beg))
	{
		if(iofile.seekg(lengthS*sizeof(array[lengthS]),ios::beg))
			iofile.read((char*)&array[lengthS],sizeof(array[lengthS])); // ��ȡ������Ϣ
		else
			break;
		// ��Ϣ��������
		lengthS++;
	}
	lengthS=lengthS-1;
	if(lengthS==Size){
		cout<<"�洢�ռ�����!"<<endl;
		People::Delete(lengthS);
	}
	cout<<"������Ա��Ϣ�ɹ�!"<<endl;
	iofile.close();
}
void Student::FindName(const char name[]){
	for(int i=0;i<lengthT+lengthS;i++)
		if(strcmp(array[i].name,name)==0)
			cout<<array[i];
}
void Student::FindAge(const int age){
	for(int i=0;i<lengthT+lengthS;i++)
		if(array[i].age==age)
			cout<<array[i];
}


void Student::Add(){
	iofile.open("Student_info.txt",ios::app|ios::out|ios::binary);
	if(lengthS==Size){
		cout<<"��Ϣ�洢�ռ�����!"<<endl;
	}
	cin>>array[lengthS];
	array[lengthS].age=date-array[lengthS].birth;
	iofile.write((char*)&array[lengthS],sizeof(array[lengthS]));
	cout<<"������Ա��Ϣ�ɹ�!"<<endl;
	lengthS++;
	iofile.close();
}
void Student::display(){
	//cout<<lengthS<<endl;
	cout<<"************���ѧ����Ϣ************"<<endl;
	if(lengthS==0)
		cout<<"������Ϣ!"<<endl;
	for(int i=0;i<lengthS;i++)
		cout<<array[i]<<"========================================================================="<<'\n';
}
int Student::Aveage(){
	int sum=0;
	for(int i=0;i<lengthS;i++)
		sum+=array[i].age;
	return sum/lengthS;
}
void Student::Delete_Name(char name[]){
	int k=0;
	for(int i=0;i<lengthS;i++)
		if(strcmp(array[i].name,name)==0){
			k=i+1;
			break;
		}
		if(k<1)
			cout<<"����������Ϊ"<<name<<"����Ա��Ϣ!"<<endl;
		for(int j=k;j<lengthS;j++)
			array[j-1]=array[j];
		lengthS--;
		cout<<"ɾ���ɹ�!"<<endl;
}
void Student::Delete(int i){
	if(i<1||i>lengthS)
		cout<<"�����ڵ�"<<i<<"����Ϣ!"<<endl;
	for(int j=i;j<lengthS;j++)
		array[j-1]=array[j];
	lengthS--;
	cout<<"ɾ���ɹ�!"<<endl;
}
int operator-(Date& d1,Date& d2){
	return d1.year-d2.year;
}
istream& operator>>(istream& in,Attr& A){	
	int y,m,d;
	cout<<"�������Ų���#����:"<<endl;
	in.getline(A.num,20,'#');
	cout<<"��������������#����:"<<endl;
	in.getline(A.name,20,'#');
	cout<<"�������Ա���#����:"<<endl;
	in.getline(A.sex,6,'#');
	cout<<"�����빤�����Ų���#����:"<<endl;
	in.getline(A.department,20,'#');
	cout<<"�������������:";//������Χ�����������Ĭ��ֵ
	in>>y>>m>>d;
	A.birth.year=(y>=1960&&y<=2017)?y:1960;
	A.birth.month=(m>=1&&m<=12)?m:1;
	A.birth.day=(d>=1&&d<=31)?d:1;
	cout<<"�����빤��ʱ��:";
	in>>y>>m>>d;
	A.worktime.year=(y>=1960&&y<=2017)?y:1960;
	A.worktime.month=(m>=1&&m<=12)?m:1;
	A.worktime.day=(d>=1&&d<=31)?d:1;
	return in;
	
	
}
ostream& operator<<(ostream& out,Attr& A){
	cout<<"���:";
	out<<A.num<<endl;
	cout<<"����:";
	out<<A.name<<endl;
	cout<<"�Ա�:";
	out<<A.sex<<endl;
	cout<<"����:";
	out<<A.department<<endl;
	cout<<"��������:";
	out<<A.birth.year<<" "<<A.birth.month<<" "<<A.birth.day<<" "<<endl;
	cout<<"�μӹ���ʱ��:";
	out<<A.worktime.year<<" "<<A.worktime.month<<" "<<A.worktime.day<<endl;
	cout<<"����:";
	out<<A.age<<endl;
	return out;
}
void fun(){
	cout<<"************��Ա��Ϣ����ϵͳ************"<<endl;
	cout<<"0-���ļ���ȡ��Ա��Ϣ"<<endl;
	cout<<"1-����¼��"<<endl;
	cout<<"2-����һλ��Ա��Ϣ"<<endl;
	cout<<"3-��ʾȫ����Ա��Ϣ"<<endl;
	cout<<"4-������Աƽ������"<<endl;
	cout<<"5-ɾ��һ����Ա��Ϣ"<<endl;
	cout<<"6-��ѡ�����"<<endl;
	cout<<"7-��ѡ����Ҳ��޸�"<<endl;
	cout<<"8-��ʾ�˵�"<<endl;
	cout<<"9-��������"<<endl;
	cout<<"****************************************"<<endl;
}

void main(){
	
	Teacher tea;
	Student stu;
    memset(tea.array, 0, sizeof(int)*1000);  
    memset(stu.array, 0, sizeof(int)*1000);  
	People *ptr_t=&tea;
	People *ptr_s=&stu;
	int c,i,j,k;
	char name[20];
	fun();
	while(1){
		cout<<"����ݲ˵�ѡ�����:";
		cin>>c;
		switch(c){
		case 0:{
			cout<<"���ļ���ȡ��Ա��Ϣ"<<endl;
			cout<<"ѧ����Ϣ"<<endl;
			ptr_s->Add_file();
			cout<<"��ʦ��Ϣ"<<endl;
			ptr_t->Add_file();
			break;
			   }
		case 1:{
			cout<<"����¼��"<<endl;
			cout<<"�����ʦ��Ϣ"<<endl;
			ptr_t->Add_all();
			cout<<"����ѧ����Ϣ"<<endl;
			ptr_s->Add_all();
			break;
			   }
		case 2:{
			cout<<"����һλ��Ա��Ϣ"<<endl;
			cout<<"��ʦ�����밴1  ѧ�������밴2"<<endl;
			cin>>i;
			if(i==1)
				ptr_t->Add();
			else if(i==2)
				ptr_s->Add();
			else
				cout<<"��������ȷ!"<<endl;
			break;
			   }
		case 3:{
			cout<<"��ʾȫ����Ա��Ϣ"<<endl;
			ptr_t->display();
			ptr_s->display();
			break;
			   }
		case 4:{
			cout<<"����ƽ������"<<endl;
			cout<<"��ʦ�����밴1  ѧ�������밴2"<<endl;
			cin>>i;
			if(i==1)
				cout<<"��ʦƽ������"<<ptr_t->Aveage()<<endl;
			else if(i==2)
				cout<<"ѧ��ƽ������"<<ptr_s->Aveage()<<endl;
			else
				cout<<"��������ȷ!"<<endl;
			break;
			   }
		case 5:{
			cout<<"ɾ��һ����Ա��Ϣ"<<endl;
			cout<<"��ʦ�����밴1  ѧ�������밴2"<<endl;
			cin>>i;
			if(i==1){
				cout<<"������ɾ���밴1 ��λ��ɾ���밴2"<<endl;
				cin>>j;
				if(j==1){
					cout<<"��������Ա����������#����"<<endl;
					cin.getline(name,20,'#');
					ptr_t->Delete_Name(name);
				}
				else if(j==2){
					cout<<"������Ҫɾ����Ա��λ��"<<endl;
					cin>>k;
					ptr_t->Delete(k);
				}
				else
					cout<<"��������ȷ!"<<endl;
			}
			else if(i==2){
				cout<<"�����������밴1  ��λ�ò����밴2"<<endl;
				cin>>j;
				if(j==1){
					cout<<"������Ҫɾ����Ա����������#����"<<endl;
					cin.getline(name,20,'#');
					ptr_s->Delete_Name(name);
				}
				else if(j==2){
					cout<<"������Ҫɾ����Ա��λ��"<<endl;
					cin>>k;
					ptr_s->Delete(k);
				}
				else
					cout<<"��������ȷ!"<<endl;
			}
			else
				cout<<"��������ȷ!"<<endl;
			break;
			   }
		case 6:{
			cout<<"��������һ����Ա��Ϣ"<<endl;
			cout<<"��ʦ�����밴1  ѧ�������밴2"<<endl;
			cin>>i;
			if(i==1){
				cout<<"����������밴1 �����������밴2"<<endl;
				cin>>j;
				if(j==1){
					cout<<"������Ҫ���ҵ���Ա������"<<endl;
					cin>>k;
					ptr_t->FindAge(k);
				}
				else if(j==2){
					cout<<"������Ҫ���ҵ��������������#����"<<endl;
					cin.getline(name,20,'#');
					ptr_t->FindName(name);
				}
				else
					cout<<"��������ȷ!"<<endl;
			}
			else if(i==2){
				cout<<"����������밴1  ���Ա�����밴2"<<endl;
				cin>>j;
				if(j==1){
					cout<<"������Ҫ���ҵ���Ա������"<<endl;
					cin>>k;
					ptr_t->FindAge(k);
				}
				else if(j==2){
					cout<<"������Ҫ���ҵ��������������#����"<<endl;
					cin.getline(name,20,'#');
					ptr_t->FindName(name);
				}
				else
					cout<<"��������ȷ!"<<endl;
			}
			else
				cout<<"��������ȷ!"<<endl;
			break;
			   }
		case 7:{
			cout<<"�������������޸�һ����Ա��Ϣ"<<endl;
			cout<<"��ʦ�����밴1  ѧ�������밴2"<<endl;
			cin>>i;
			if(i==1){
				cout<<"�������޸��밴1 �������޸��밴2"<<endl;
				cin>>j;
				if(j==1){
					cout<<"������Ҫ���ҵ���Ա������"<<endl;
					cin>>k;
					ptr_t->FindAge(k);
					ptr_t->modAge(k);
				}
				else if(j==2)
				{
					cout<<"������Ҫ���ҵ���Ա������"<<endl;
					cin.getline(name,20,'#');
					ptr_t->FindName(name);
					ptr_t->modName(name);
					
				}
				else
					cout<<"��������ȷ!"<<endl;
				break;
			}
			else if(i==2)
			{
				cout<<"�������޸��밴1 �������޸��밴2"<<endl;
				cin>>j;
				if(j==1){
					cout<<"������Ҫ���ҵ���Ա������"<<endl;
					cin>>k;
					ptr_s->FindAge(k);
					ptr_s->modAge(k);
				}
				else if(j==2)
				{
					cout<<"������Ҫ���ҵ���Ա������"<<endl;
					cin.getline(name,20,'#');
					ptr_s->FindName(name);
					ptr_s->modName(name);
					
				}
				else
					cout<<"��������ȷ!"<<endl;
				break;
			}
			
			
		case 8:{
			cout<<"��ʾ�˵�Ŀ¼"<<endl;
			fun();
			break;
			   }
		case 9:{
			cout<<"������������"<<endl;
			exit(0);
			   }
		default:
			cout<<"��������ȷ!"<<endl;
			   }
	}
}
}