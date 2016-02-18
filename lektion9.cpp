/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lektion9.cpp
 * Author: bps
 *
 * Created on den 16 februari 2016, 13:21
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include<typeinfo>

using namespace std;

/*
 * 
 */

//Person.h basklass
class Person
{
private:
	string name;
	string email;
public:
	string getName() const
	{
		return this->name;
	}
	string getemail() const
	{
		return this->email;
	}
	void setName(string name)
	{
		this->name=name;
	}
	void setEmail(string email)
	{
		this->email=email;
	}
	Person(string name, string email)
	{
		this->name=name;
		this->email=email;
	}
	virtual string toStringSpecific() const=0;
	string toString()
	{
		cout << " " << this->name << " " << this->email << " ";
		return toStringSpecific();
	}
	virtual ~Person(){}
	Person(const Person &obj)
	{
		this->name=obj.name;
		this->email=obj.email;
	}
	//Assigment op
	Person& operator=(const Person &orig)//or instead of void person&(reference to object)). reference to object need when a=b=c become a=c; worst case void = c that's bad
	{                                    //a.operator=(b.operator=(c))
		//make sure P1=P1 do not happen
		if(this != &orig)
		{
			this->name = orig.email;
			this->email = orig.email;
		}
		return *this;
	}
	//set and get functions
	virtual Person* clone() const=0;
};

//Student.h
//#include "Person.h"
class Student: public Person
{
private:
	int regNr;
public:
	
	Student(string name, string email, int regNr):Person(name, email)
	{
		this->regNr=regNr;
	}
	~Student(){} //virtual optional
	string toStringSpecific()const
	{
		stringstream ss;
		ss << " " << this->regNr;
		return ss.str();
	}
	//copy constructor wher obj also get sent to Person copyconstructor becuse of name and email.
	Student(const Student &orig):Person(orig)
	{
		this->regNr=orig.regNr;
	}
	//Assigment op
	Student& operator=(const Student &orig)//or instead of void person&(reference to object)). reference to object need when a=b=c become a=c; worst case void = c that's bad
	{
		//make sure P1=P1 do not happen
		if(this != &orig)
		{
			//we manage the person class variables with the person assigment operator.
			Person::operator =(orig);
			this->regNr= orig.regNr;
			
		}
		return *this;
	}
	int getRegNr()const
	{
		return this->regNr;
	}
	//caller or colen get sent into Student construktor and dynamically created into obj of class. Then adress to obj gets returned.
	virtual Student* clone() const
	{
		return new Student(*this);
	}
};
//Employee.h
class Employee : public Person
{
private:
	string department;
	int salery;
public:
	Employee(string name, string email, string department, int salary): Person(name, email)
	{
		this->department=department;
		this->salery=salary;
	}
	string toStringSpecific() const
	{
		stringstream ss;
		ss <<  " " << this->department << " " << this->salery << " ";
		return ss.str();
	}
	~Employee(){}//virtual optional here
	//copy construct and send name email with Person copy constructor.
	Employee(const Employee &orig):Person(orig)
	{
		this->department=orig.department;
		this->salery=orig.salery;
	}
	//Assigment operator
	Employee& operator=(const Employee &orig)//or instead of void person&(reference to object)). reference to object need when a=b=c become a=c; worst case void = c that's bad
	{
		//make sure P1=P1 do not happen
		if(this != &orig)
		{
			Person::operator =(orig);
			this->department= orig.department;
			this->salery=orig.salery;
			
		}
		return *this;
	}
	//void setName(string name)
	//{}
	virtual Employee* clone()const
	{
		return new Employee(*this);
	}
};

//UniversityReg.h
//used like container class
//#include"student.h" "Employee.h"
class UniversityReg
{
private:
	int nrofPersons, capacity;
	Person **persons;
public:
	bool addPerson(string name, string email, int regNr);
	
	bool addPerson(string name, string email, string department, int salary);
	bool removePerson(string name, string email, int regNr);
	void removePerson(string name, string email, int salary, string department);
	UniversityReg(int capacity);
	UniversityReg();
	~UniversityReg();
	int getNrOfEmployees()const;
	int getnrOfPerson()const;
	int getnrOfStudent()const;
	void printAllPersons()const;
	UniversityReg(const UniversityReg &orig);
	UniversityReg& operator=(const UniversityReg &orig);
	
};
//UniversityReg.cpp
/**#include "Uni...Reg.h"
 */
UniversityReg::UniversityReg(int capacity)
{
	this->nrofPersons=0;
	this->capacity=capacity;
	this->persons= new Person*[this->capacity];
}
UniversityReg::UniversityReg()
{
	this->nrofPersons=0;
	this->capacity=3;
	this->persons= new Person*[this->capacity];
}

bool UniversityReg::addPerson(string name, string email, int regNr)
{
	bool flag = false;
	if(this->nrofPersons < this->capacity)
	{
		this->persons[this->nrofPersons++]= new Student(name, email, regNr);
		flag = true;
	}
	return flag;
}
bool UniversityReg::addPerson(string name,string email, string department, int salary)
{
	bool flag = false;
	if(this->nrofPersons < this->capacity)
	{
		this->persons[this->nrofPersons++]= new Employee(name, email, department, salary);
		flag = true;
	}
	return flag;
}

UniversityReg::~UniversityReg()
{
	for(int i=0; i< this->nrofPersons; i++)
	{
		delete this->persons[i];
	}
	delete [] this->persons;
}

bool UniversityReg::removePerson(string name, string email, int regNr)  //(string department, int salary))
{
	bool flag = false;
	Student * studentPtr=NULL; // Employee *employeeptr=NULL;
	for(int i=0; i < this->nrofPersons; i++)
	{
		studentPtr = dynamic_cast<Student*>(persons[i]); // employeeptr = dynamic_cast<Employee*>(persons[i]);
		
		
		if(studentPtr != NULL && this->persons[i]->getName()==name && this->persons[i]->getemail()==email && studentPtr->getRegNr()==regNr) //check department and salary
		{
			delete persons[i];
			persons[i]= persons[nrofPersons-1];
			nrofPersons--;
			flag=true;
			
		}
	}
}
int UniversityReg::getnrOfStudent() const
{
	int nrofStudents=0;
	Student* studentptr = NULL;
	for(int i=0; i < this->nrofPersons; i++)
	{
		studentptr = dynamic_cast<Student*>(this->persons[i]);//if not student still null
		if(studentptr != NULL)
		{
			nrofStudents++;
		}
	}
	return nrofStudents;
}
int UniversityReg::getNrOfEmployees() const
{
	int nrofEmployees=0;
	for(int i=0; i < this->nrofPersons; i++)
	{
		if(typeid(*this->persons[i])==typeid(Employee))
		{
			nrofEmployees++;
		}
	}
	return nrofEmployees;
}
//getnrofperson som de andra
void UniversityReg::printAllPersons() const
{
	for(int i=0; i < this->nrofPersons; i++)
	{
		cout << this->persons[i]->toString();
	}
}
UniversityReg::UniversityReg(const UniversityReg &orig)
{
	this->nrofPersons = orig.nrofPersons;
	this->capacity=orig.capacity;
	this->persons= new Person *[this->capacity];
	for(int i=0; i < this->nrofPersons; i++)
	{
		if(typeid(*orig.persons[i])==typeid(Student))
		{
			this->persons[i]= new Student(*((Student*)orig.persons[i])); //*orig.persons[i]]
		}
		else
		{
			this->persons[i]= new Employee(*((Employee*)orig.persons[i])); 
		}
	}
}
UniversityReg& UniversityReg::operator =(const UniversityReg& orig)
{
	if(this != &orig)
	{
		for(int i=0; i < this->nrofPersons; i++)
		{
			delete this->persons[i];
		}
		delete [] this->persons;
		
		this->nrofPersons=orig.nrofPersons;
		this->capacity=orig.capacity;
		this->persons= new Person*[this->capacity];
		for(int i=0; i < this->nrofPersons; i++)
		{
			//part a
			if(typeid(*orig.persons[i])==typeid(Student))
			{
				this->persons[i]=new Student(*((Student*)orig.persons[i]));
			}
			else
			{
				this->persons[i]=new Employee(*((Employee*)orig.persons[i]));
			}
			//part a end
			//could use part a with
			this->persons[i]=orig.persons[i]->clone(); //create obj 
		}
	}
	return *this;
}
int main(int argc, char** argv)
{
	/*Employee *aa= new Employee("Rocket", "rocket@dflund.se","IT", 23 );
	Person *P1= new Employee("Rock", "rock@dflund.se","Science", 333 );
	//Student *bb= new Student("Rocket", "rocket@dflund.se",34 );
	//aa->setEmail("rocket@dflund.se");
	//aa->setName("Rocket");
	aa->toString();
	//aa.toStringSpecific();
	//bb.toString();
	//bb->toStringSpecific();
	//Inlämning B göra test i main()
	
	//test copy construct
	Person* P2 = P1;
	cout << P1->toString();
	cout <<P2->toString();
	
	//Test deep copying
	P1->setName("name2");
	cout << P1->toString();// output: name2, email1, 123
	cout << P2->toString();//output: name1, email1, 123
	//Relations
	//Inheritence "is-a" student is a Person 
	//composition "has-a" car-engine arrow go to car
	//Aggregation "has-a" university has a student
	//  Person----<>university
	delete P1;
	delete P2;
	delete aa;*/
	
	UniversityReg bth;
	bth.addPerson("name1", "name1@bth.se", 123);
	bth.addPerson("name2", "name2@bth.se", "IT", 20000);
	bth.printAllPersons();
	UniversityReg kth=bth;
	kth.printAllPersons();
	UniversityReg kth2;
	cout << "\nNow kth2 gets bth data." << endl;
	kth2.addPerson("name3", "name3@kth.se", 456);
	kth2=bth;
	kth2.printAllPersons();
		
	return 0;
}

// Person.h
