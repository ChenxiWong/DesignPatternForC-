// Last Update:2017-05-23 17:06:34
/**
 * @file visitor_pattern.cpp
 * @brief
 * @author wangchenxi
 * @version 0.1.00
 * @date 2017-05-23
 */
#include <iostream>
#include <string>
#include <list>
using namespace std;

class Element;

class Visitor
{
    public:
        virtual void Visit( Element *element ){};
};

class Element  // "Element"
{
    public:
        virtual void Accept( Visitor *visitor ){}; // Methods
};


class Employee : public Element
{ // "ConcreteElement"
    public:
        string name;
        double income;
        int vacationDays;

    public :
        Employee( string name, double income,
                int vacationDays )
        {
            this->name = name;
            this->income = income;
            this->vacationDays = vacationDays;
        }

        void Accept( Visitor *visitor )
        {
            visitor->Visit( this ); // 访问者优势体现在这里，方法可以渗透到类对象内部，对对象内部数据进行更改。从某种角度上来说，这是一种对封装的破坏
        }
};

class IncomeVisitor : public Visitor
{
    public:
        void Visit( Element *element ) // 访问者模式将有关的行为集中到一个访问者对象中，而不是分散到一个个的节点类中。
        { // 积累状态。每一个单独的访问者对象都集中了相关的行为，从而也就可以在访问的过程中将执行操作的状态积累在自己内部，而不是分散到很多的节点对象中。这是有益于系统维护的优点。
            Employee *employee = ((Employee*)element);
            employee->income *= 1.10;
            cout<<employee->name<<" 's new income: " <<employee->income<<endl;

        }
};

class VacationVisitor : public Visitor
{
    public :
        void Visit( Element *element )
        { // Provide 3 extra vacation days
            Employee *employee = ((Employee*)element);
            employee->vacationDays += 3;
            cout<<employee->name<<" 's new vacation days: " <<employee->vacationDays<<endl;
        }
};

class Employees
{ // "ObjectStructure"
    private :
        list< Employee*> employees;

    public :

        void Attach( Employee *employee )
        {
            employees.push_back(employee);
        }

        void Detach( Employee *employee )
        {
            employees.remove(employee);
        }

        void Accept( Visitor *visitor )
        {
            for (std::list<Employee*>::iterator it=employees.begin(); it != employees.end(); ++it)
                (*it)->Accept(visitor);
        }
};

int main(int argc, char* argv[] )
{
    Employees *e = new Employees();  // 工会成立
    e->Attach( new Employee( "Tom", 25000.0, 14 ) );  // Tom加入了工会
    e->Attach( new Employee( "Thomas", 35000.0, 16 ) ); // Thomas加入了工会
    e->Attach( new Employee( "Roy", 45000.0, 21 ) );  // Roy加入了工会
    /* 缺点体现在这个地方，例如新需求要求添加工作时间管理，你就需要修改Employee的同时还要添加新的visitor */

    /* Create two visitors */
    IncomeVisitor *v1 = new IncomeVisitor();   // 薪资管理专员
    VacationVisitor *v2 = new VacationVisitor(); // 假期管理专员
    /*  优点体现在这个地方，可以根据实际情况添加“ 专员” */

    /* Employees are visited */
    e->Accept( v1 );   // 工会要求给员工涨工资
    e->Accept( v2 );   // 工会要求给员工多放几天假期
}

