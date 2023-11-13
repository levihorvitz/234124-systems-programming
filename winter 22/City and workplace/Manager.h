#ifndef EX2_MANAGER_H
#define EX2_MANAGER_H

#include <string>
#include "Citizen.h"
#include "Skill.h"
#include "Employee.h"
#include <set>

namespace mtm {
	enum ManagerStatus {
		HIRED, NOT_HIRED
	};

	class Manager : public Citizen {
	protected:
		int salary;
		set<Employee*, bool (*)(Employee*, Employee*)> employees;
		ManagerStatus managerStatus;
	public:

		/**
	 * Manager: Constructor of the Manager class.
         * @param
         * id - id of the Manager that is created.
         * first_name - First name of the Manager that is created.
         * last_name - Last name of the Manager that is created.
         * birth_year - Birth year of the Manager that is created
	 */
		Manager(int id, std::string first_name, std::string last_name, int birth_year);

		/**
	     * ~Manager: Destroy of the Manager class.
	     */
		~Manager() override = default;

		/**
	     * Manager: Copy Constructor of the Manager class.
	     * @param
	     * Manager - A given Manager that we will copy to a new constructed Manager.
	     */
		Manager(const Manager& manager)=default;

		/**
	     * operator= : Replace an existing Manager with a given Manager.
	     */
		Manager& operator=(const Manager& manager) = default;

		/**
         * getSalary: Returns salary of a manager.
         * @return
         * Salary of the manager.
         */
		int getSalary() const override;

		/**
		 * getType: Returns the Citizen Type of a manager.
		 * @return
		 * CitizenType of the manager.
		 */
		CitizenType getType() const override;

		/**
         * getSkillById: Finds an employee under a manager according to the given id.
         * @param id - The id of an employee we need to find.
         * @return
         * employee - A pointer to the employee that matches the id.
         */
		Employee* getEmployeeById(int id);

		/**
         * addEmployee: Adds an employee under a manager.
         * @param employee - An employee that we want to add.
         */
		void addEmployee(Employee* employee);

		/**
         * removeEmployee: Removes an employee under a manager.
         * @param id - id of an employee that we want to remove.
         */
		void removeEmployee(int id);

		/**
         * hasEmployee: Checks if employee belongs to a manager.
         * @param id - The id of an employee that we want to check if belongs to manager.
         * @return
         * true - if employee belongs to manager.
         * false - if employee doesn't belong to manager.
         */
		bool hasEmployee(int id);

		/**
         * setSalary: Sets the salary of a manager
         * @param salary_manager - The salary that we want a manager to have.
         */
		void setSalary(int salary_manager);

		/**
         * printShort: Prints short info of Manager.
         */
		std::ostream& printShort(std::ostream& os) override;

		/**
         * printLong: Prints detailed info of Manager.
         */
		std::ostream& printLong(std::ostream& os) override;

		/**
         * clone: Returns a copy of a manager.
         * @return
         * Returns a pointer to a copy of a manager.
         */
		Manager* clone() const override;

		/**
         * getManagerEmploymentStatus: Returns the status of manager.
         * @return
         * managerStatus - returns if manager is hired or NOT hired.
         */
		ManagerStatus getManagerEmploymentStatus();

		/**
         * setManagerEmploymentStatus: Upgrades the status of manager.
         * @param
         * managerStatus - the new status of manager that we want upgraded.
         */
		void setManagerEmploymentStatus(ManagerStatus managerStatus);

		/**
         * getEmployees: Prints the employees that work under manager.
         */
		set<Employee*, bool (*)(Employee*, Employee*)> getEmployees();
	};
}

#endif //EX2_MANAGER_H
