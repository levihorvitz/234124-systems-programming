#ifndef EX2_WORKPLACE_H
#define EX2_WORKPLACE_H

#include <string>
#include <set>

#include "Manager.h"
#include "exceptions.h"

using namespace mtm;

class Workplace {
private:
	int id;
	std::string name;
	int worker_salary;
	int managers_salary;
	set<Manager*, bool (*)(Manager*, Manager*)> managers;

public:

	/**
	 * Workplace: Constructor of the Workplace class.
         * @param
         * id - id of the workplace the we want to construct.
         * name - name of the workplace the we want to construct.
         * worker_salary - Salary of the employees that will work in the workplace that is constructed.
         * managers_salary - Salary of the managers that will work in the workplace that is constructed.
	 */
	Workplace(int id,
			  std::string name,
			  int worker_salary,
			  int managers_salary);

	/**
	 * Workplace: Copy Constructor of the Workplace class.
	  * @param
	  * workplace - A given workplace that we will copy to a new constructed workplace.
	 */
	Workplace(const Workplace& workplace) = default;

	/**
	 * operator= : Replace an existing workplace with a given workplace.
	 */
	Workplace& operator=(const Workplace& other) = default;

	/**
         * getManagersSalary: Returns salary of managers in a workplace.
         * @return
         * managers_salary - Salary of the managers.
         */
	int getManagersSalary() const;

	/**
         * getWorkersSalary: Returns salary of employees in a workplace.
         * @return
         * worker_salary - Salary of the employees.
         */
	int getWorkersSalary() const;

	/**
         * getName: Returns the name of a workplace .
         * @return
         * name - the name of the workplace.
         */
	std::string getName() const;

	/**
         * getId: Returns the id of a workplace .
         * @return
         * id - the id of the workplace.
         */
	int getId() const;

	/**
         * hireEmployee: Hires an employee under a manager at a workplace.
         * @param
         * condition - object function that checks the conditions of the hiring.
         * id_employee - id of a employee that will be hired.
         * id_manager - id of a manager that an employee will be hired under.
         * id_work_place - id of a workplace that an employee will be hired at.
         */
	template<class Condition>
	void hireEmployee(Condition condition, Employee* employee, int id_manager)
	{
		Manager* manager = getManagerById(id_manager);
		if (manager == nullptr) {
			throw mtm::ManagerIsNotHired();
		}
		if (!condition(employee)) {
			throw mtm::EmployeeNotSelected();
		}
		if (manager->hasEmployee(employee->getId())) {
			throw mtm::EmployeeAlreadyHired();
		}
		employee->setSalary(worker_salary);
		manager->addEmployee(employee);
	}


	/**
         * hireManager: Hires a manager to a workplace.
         * @param manager - A manager that we want to hire.
         */
	void hireManager(Manager* manager);

	/**
         * fireEmployee: Fires an employee that works under a certain manager in the workplace.
         * @param id_manager - id of a manager that an employee works under.
         *        id_employee - id of the employee that we want to fire.
         */
	void fireEmployee(int id_manager, int id_employee);

	/**
         * fireManager: Fires an employee from a workplace.
         * @param id_manager - id of a manager in the workplace.
         */
	void fireManager(int id_manager);

	/**
         * getManagerById: Return a manager that fits the id.
         * @param id_manager - id of a manager in the workplace.
         * @return
         * manager - pointer to a manager that we want to get.
         */
	Manager* getManagerById(int id_manager);

	/**
         * operator<< : Prints info of workplace.
         */
	friend std::ostream& operator<<(ostream& os, const Workplace& workplace);

	/**
         * clone: Returns a copy of a workplace.
         * @return
         * Returns a pointer to a copy of a workplace.
         */
	Workplace* clone() const;

	/**
         * getManagers: Prints the managers that work at workplace.
         */
	set<Manager*, bool (*)(Manager*, Manager*)> getManagers() const;

};


#endif //EX2_WORKPLACE_H
