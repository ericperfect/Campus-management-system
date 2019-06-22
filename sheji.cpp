#include<iostream.h>//程序要用友元函数.h头文件才能用
#include<string.h>//C语言字符数组文件
#include<fstream.h>//文件输入输出用
#include<stdlib.h>//exit函数等需要
const int Size=80;
fstream iofile;//定义一个文件输入输出对象实现对文件的操作
//日期类的声明
class Date{
public:
	int year;
	int month;
	int day;
};
//声明一个Attr类用来存放人员的各个属性,声明两个重载友元函数用于向文件读写
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
	friend int operator-(Date& d1,Date& d2);//计算年龄
	
	
};
//声明人员类
class People{
protected:
    static int lengthT;
	static int lengthS;
	
	Date date;
public:
	People();
	Attr array[Size];
	virtual void Add_all()=0;//增加人员信息
	virtual void Add_file()=0;//从文件增加信息
	virtual void Add()=0;//增加信息
	virtual void display()=0;//虚函数display用于输出数组内容
	virtual int Aveage()=0;//虚函数用于求出平均年龄
	virtual void FindName(const char a_name[])=0;//虚函数用于按姓名查找
	virtual void FindAge(const int a_age)=0;//虚函数用于按年龄查找
	virtual void Delete_Name(char name[])=0;
	virtual void Delete(int i);
	virtual void modAge( int age)=0;
	virtual void modName(char a_name[])=0;
	
};
//声明教师类
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
//学生类的声明
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
		cout<<"不存在第"<<i<<"个元素!"<<endl;
	for(int j=i;j<lengthT;j++)
		array[j-1]=array[j];
	lengthT--;
	cout<<"删除成功!"<<endl;
}
void Teacher::modAge(int age){
	int j,newage;
	cout<<"修改年龄请按1    不修改按2"<<endl;
	cin>>j;
	if(j==1){
		for(int i=0;i<lengthT;i++)
			if(array[i].age==age)
			{	cout<<"请输入新年龄"<<endl;
			cin>>newage;
			array[i].age=newage;
			cout<<"修改成功"<<endl;
			}
			else if(j==2){
				break;
			}
			else
				cout<<"操作不正确!"<<endl;
	}
	
}
void Teacher::modName(char name[]){
	int j; char newname[20];
	cout<<"修改姓名请按1    不修改按2"<<endl;
	cin>>j;
				if(j==1){
					
					for(int i=0;i<lengthT;i++)
						if(strcmp(array[i].name,name)==0)
						{		
							cout<<"请输入新姓名"<<endl;
							cin.getline(newname,20,'#');
							strcpy(array[i].name,newname);
							
								cout<<"修改成功"<<endl;
						}
						
						
						else if(j==2){
							break;
						}
						else
							cout<<"操作不正确!"<<endl;
				}
				
}

void Teacher::Add_all(){
	char ch;
	iofile.open("Teacher_info.txt",ios::in|ios::binary|ios::out);
	do{
		cin>>array[lengthT];
		array[lengthT].age=date-array[lengthT].birth;
		iofile.write((char*)&array[lengthT],sizeof(array[lengthT]));
		cout<<"添加增加人员信息成功!"<<endl;
		lengthT++;
		if(lengthT==Size){
			cout<<"存储空间已满!"<<endl;
			break;
		}
		cout<<"继续添加吗?";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	iofile.close();
}
void Teacher::Add_file(){//理解起来稍有困难
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
		cout<<"存储空间已满!"<<endl;
		People::Delete(lengthT);
	}
	cout<<"增加人员信息成功!"<<endl;
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
		cout<<"信息存储空间已满!"<<endl;
	}
	cin>>array[lengthT];
	array[lengthT].age=date-array[lengthT].birth;
	iofile.write((char*)&array[lengthT],sizeof(array[lengthT]));
	cout<<"增加人员信息成功!"<<endl;
	lengthT++;
	iofile.close();
}
void Teacher::display(){
	cout<<"************输出教师信息************"<<endl;
	if(lengthT==0)
		cout<<"暂无信息!"<<endl;
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
			cout<<"不存在姓名为"<<name<<"的人员信息!"<<endl;
		for(int j=k;j<lengthT;j++)
			array[j-1]=array[i];
		lengthT--;
		cout<<"删除成功!"<<endl;
}
void Teacher::Delete(int i){
	if(i<1||i>lengthT)
		cout<<"不存在第"<<i<<"个元素!"<<endl;
	for(int j=i;j<lengthT;j++)
		array[j-1]=array[j];
	lengthT--;
	cout<<"删除成功!"<<endl;
}
void Student::modName(char name[]){
	int j; char newname[20];
	cout<<"修改姓名请按1    不修改按2"<<endl;
	cin>>j;
				if(j==1){
					
					for(int i=0;i<lengthT;i++)
					
						if(strcmp(array[i].name,name)==0)
					{		cout<<"请输入新姓名"<<endl;
					cin.getline(newname,20,'#');
					strcpy(array[i].name,newname);
					cout<<"修改成功"<<endl;
					}
					
				
					
					else if(j==2)
						break;
					
					else
						cout<<"操作不正确!"<<endl;
				}
				
}
void Student::modAge(int age){
	int j,newage;
	cout<<"修改年龄请按1    不修改按2"<<endl;
	cin>>j;
	if(j==1){
		
		for(int i=0;i<lengthT+lengthS;i++)
			if(array[i].age==age)
			{	cout<<"请输入新年龄"<<endl;
			cin>>newage;
			array[i].age=newage;
			cout<<"修改成功"<<endl;
			}
			else if(j==2){
				break;
			}
			else
				cout<<"操作不正确!"<<endl;
	}
	
}
void Student::Add_all(){
	char ch;
	iofile.open("Student_info.txt",ios::out|ios::binary);
	do{
		cin>>array[lengthS];
		array[lengthS].age=date-array[lengthS].birth;
		iofile.write((char*)&array[lengthS],sizeof(array[lengthS]));
		cout<<"增加人员信息成功!"<<endl;
		lengthS++;
		if(lengthS==Size){
			cout<<"存储空间已满!"<<endl;
			break;
		}
		cout<<"继续添加吗?";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	iofile.close();
}
void Student::Add_file(){//不同解决方案
	//lengthS=lengthS-1;
	iofile.open("Student_info.txt",ios::in|ios::binary);
	while(iofile.seekg(sizeof(array[lengthS]),ios::beg))
	{
		if(iofile.seekg(lengthS*sizeof(array[lengthS]),ios::beg))
			iofile.read((char*)&array[lengthS],sizeof(array[lengthS])); // 读取数据信息
		else
			break;
		// 信息长度增加
		lengthS++;
	}
	lengthS=lengthS-1;
	if(lengthS==Size){
		cout<<"存储空间已满!"<<endl;
		People::Delete(lengthS);
	}
	cout<<"增加人员信息成功!"<<endl;
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
		cout<<"信息存储空间已满!"<<endl;
	}
	cin>>array[lengthS];
	array[lengthS].age=date-array[lengthS].birth;
	iofile.write((char*)&array[lengthS],sizeof(array[lengthS]));
	cout<<"增加人员信息成功!"<<endl;
	lengthS++;
	iofile.close();
}
void Student::display(){
	//cout<<lengthS<<endl;
	cout<<"************输出学生信息************"<<endl;
	if(lengthS==0)
		cout<<"暂无信息!"<<endl;
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
			cout<<"不存在姓名为"<<name<<"的人员信息!"<<endl;
		for(int j=k;j<lengthS;j++)
			array[j-1]=array[j];
		lengthS--;
		cout<<"删除成功!"<<endl;
}
void Student::Delete(int i){
	if(i<1||i>lengthS)
		cout<<"不存在第"<<i<<"个信息!"<<endl;
	for(int j=i;j<lengthS;j++)
		array[j-1]=array[j];
	lengthS--;
	cout<<"删除成功!"<<endl;
}
int operator-(Date& d1,Date& d2){
	return d1.year-d2.year;
}
istream& operator>>(istream& in,Attr& A){	
	int y,m,d;
	cout<<"请输入编号并以#结束:"<<endl;
	in.getline(A.num,20,'#');
	cout<<"请输入姓名并以#结束:"<<endl;
	in.getline(A.name,20,'#');
	cout<<"请输入性别并以#结束:"<<endl;
	in.getline(A.sex,6,'#');
	cout<<"请输入工作部门并以#结束:"<<endl;
	in.getline(A.department,20,'#');
	cout<<"请输入出生日期:";//超出范围情况考虑设置默认值
	in>>y>>m>>d;
	A.birth.year=(y>=1960&&y<=2017)?y:1960;
	A.birth.month=(m>=1&&m<=12)?m:1;
	A.birth.day=(d>=1&&d<=31)?d:1;
	cout<<"请输入工作时间:";
	in>>y>>m>>d;
	A.worktime.year=(y>=1960&&y<=2017)?y:1960;
	A.worktime.month=(m>=1&&m<=12)?m:1;
	A.worktime.day=(d>=1&&d<=31)?d:1;
	return in;
	
	
}
ostream& operator<<(ostream& out,Attr& A){
	cout<<"编号:";
	out<<A.num<<endl;
	cout<<"姓名:";
	out<<A.name<<endl;
	cout<<"性别:";
	out<<A.sex<<endl;
	cout<<"部门:";
	out<<A.department<<endl;
	cout<<"出生日期:";
	out<<A.birth.year<<" "<<A.birth.month<<" "<<A.birth.day<<" "<<endl;
	cout<<"参加工作时间:";
	out<<A.worktime.year<<" "<<A.worktime.month<<" "<<A.worktime.day<<endl;
	cout<<"年龄:";
	out<<A.age<<endl;
	return out;
}
void fun(){
	cout<<"************人员信息管理系统************"<<endl;
	cout<<"0-从文件获取人员信息"<<endl;
	cout<<"1-重新录入"<<endl;
	cout<<"2-增加一位人员信息"<<endl;
	cout<<"3-显示全部人员信息"<<endl;
	cout<<"4-计算人员平均年龄"<<endl;
	cout<<"5-删除一个人员信息"<<endl;
	cout<<"6-按选项查找"<<endl;
	cout<<"7-按选项查找并修改"<<endl;
	cout<<"8-显示菜单"<<endl;
	cout<<"9-结束程序"<<endl;
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
		cout<<"请根据菜单选择操作:";
		cin>>c;
		switch(c){
		case 0:{
			cout<<"从文件获取人员信息"<<endl;
			cout<<"学生信息"<<endl;
			ptr_s->Add_file();
			cout<<"教师信息"<<endl;
			ptr_t->Add_file();
			break;
			   }
		case 1:{
			cout<<"重新录入"<<endl;
			cout<<"输入教师信息"<<endl;
			ptr_t->Add_all();
			cout<<"输入学生信息"<<endl;
			ptr_s->Add_all();
			break;
			   }
		case 2:{
			cout<<"增加一位人员信息"<<endl;
			cout<<"教师操作请按1  学生操作请按2"<<endl;
			cin>>i;
			if(i==1)
				ptr_t->Add();
			else if(i==2)
				ptr_s->Add();
			else
				cout<<"操作不正确!"<<endl;
			break;
			   }
		case 3:{
			cout<<"显示全部人员信息"<<endl;
			ptr_t->display();
			ptr_s->display();
			break;
			   }
		case 4:{
			cout<<"计算平均年龄"<<endl;
			cout<<"教师操作请按1  学生操作请按2"<<endl;
			cin>>i;
			if(i==1)
				cout<<"教师平均年龄"<<ptr_t->Aveage()<<endl;
			else if(i==2)
				cout<<"学生平均年龄"<<ptr_s->Aveage()<<endl;
			else
				cout<<"操作不正确!"<<endl;
			break;
			   }
		case 5:{
			cout<<"删除一个人员信息"<<endl;
			cout<<"教师操作请按1  学生操作请按2"<<endl;
			cin>>i;
			if(i==1){
				cout<<"按姓名删除请按1 按位置删除请按2"<<endl;
				cin>>j;
				if(j==1){
					cout<<"请输入人员的姓名并以#结束"<<endl;
					cin.getline(name,20,'#');
					ptr_t->Delete_Name(name);
				}
				else if(j==2){
					cout<<"请输入要删除人员的位置"<<endl;
					cin>>k;
					ptr_t->Delete(k);
				}
				else
					cout<<"操作不正确!"<<endl;
			}
			else if(i==2){
				cout<<"按姓名操作请按1  按位置操作请按2"<<endl;
				cin>>j;
				if(j==1){
					cout<<"请输入要删除人员的姓名并以#结束"<<endl;
					cin.getline(name,20,'#');
					ptr_s->Delete_Name(name);
				}
				else if(j==2){
					cout<<"请输入要删除人员的位置"<<endl;
					cin>>k;
					ptr_s->Delete(k);
				}
				else
					cout<<"操作不正确!"<<endl;
			}
			else
				cout<<"操作不正确!"<<endl;
			break;
			   }
		case 6:{
			cout<<"按类别查找一个人员信息"<<endl;
			cout<<"教师操作请按1  学生操作请按2"<<endl;
			cin>>i;
			if(i==1){
				cout<<"按年龄查找请按1 按姓名查找请按2"<<endl;
				cin>>j;
				if(j==1){
					cout<<"请输入要查找的人员的年龄"<<endl;
					cin>>k;
					ptr_t->FindAge(k);
				}
				else if(j==2){
					cout<<"请输入要查找的年龄的姓名并以#结束"<<endl;
					cin.getline(name,20,'#');
					ptr_t->FindName(name);
				}
				else
					cout<<"操作不正确!"<<endl;
			}
			else if(i==2){
				cout<<"按年龄查找请按1  按性别查找请按2"<<endl;
				cin>>j;
				if(j==1){
					cout<<"请输入要查找的人员的年龄"<<endl;
					cin>>k;
					ptr_t->FindAge(k);
				}
				else if(j==2){
					cout<<"请输入要查找的年龄的姓名并以#结束"<<endl;
					cin.getline(name,20,'#');
					ptr_t->FindName(name);
				}
				else
					cout<<"操作不正确!"<<endl;
			}
			else
				cout<<"操作不正确!"<<endl;
			break;
			   }
		case 7:{
			cout<<"按属性搜索并修改一个人员信息"<<endl;
			cout<<"教师操作请按1  学生操作请按2"<<endl;
			cin>>i;
			if(i==1){
				cout<<"按年龄修改请按1 按姓名修改请按2"<<endl;
				cin>>j;
				if(j==1){
					cout<<"请输入要查找的人员的年龄"<<endl;
					cin>>k;
					ptr_t->FindAge(k);
					ptr_t->modAge(k);
				}
				else if(j==2)
				{
					cout<<"请输入要查找的人员的姓名"<<endl;
					cin.getline(name,20,'#');
					ptr_t->FindName(name);
					ptr_t->modName(name);
					
				}
				else
					cout<<"操作不正确!"<<endl;
				break;
			}
			else if(i==2)
			{
				cout<<"按年龄修改请按1 按姓名修改请按2"<<endl;
				cin>>j;
				if(j==1){
					cout<<"请输入要查找的人员的年龄"<<endl;
					cin>>k;
					ptr_s->FindAge(k);
					ptr_s->modAge(k);
				}
				else if(j==2)
				{
					cout<<"请输入要查找的人员的姓名"<<endl;
					cin.getline(name,20,'#');
					ptr_s->FindName(name);
					ptr_s->modName(name);
					
				}
				else
					cout<<"操作不正确!"<<endl;
				break;
			}
			
			
		case 8:{
			cout<<"显示菜单目录"<<endl;
			fun();
			break;
			   }
		case 9:{
			cout<<"结束程序运行"<<endl;
			exit(0);
			   }
		default:
			cout<<"操作不正确!"<<endl;
			   }
	}
}
}