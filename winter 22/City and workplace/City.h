#ifndef EX2_CITY_H
#define EX2_CITY_H

#include "Workplace.h"
#include "Faculty.h"
#include "Manager.h"
#include "exceptions.h"
#include "Employee.h"
#include "Citizen.h"
#include "Skill.h"

namespace mtm {
	class City {
	private:
		std::string name;
		set<Faculty<Condition>*> faculties;
		set<Citizen*, bool (*)(Citizen*, Citizen*)> citizens;
		set<Workplace*> work_places;
	public:

		/**
		* City: Constructor of the City class.
			* @param
			* name - A name of a city that is constructed.
		*/
		explicit City(std::string name);

		/**
		* ~City: Destroy of the City class.
		*/
		~City();

		/**
		* City: Copy Constructor of the City class.
		 * @param
		 * City - A given City that we will copy to a new constructed City.
		*/
		City(const City& other);

		/**
			 * operator= : Replace an existing City with a given City.
			 */
		City& operator=(const City& other);

		/**
			 * addEmployee: Adds an employee to a city.
			 * @param
			 * id - id of an employee that we want to add to a city.
			 * first_name - first name of an employee that we want to add to a city.
			 * last_name - last name of an employee that we want to add to a city.
			 * birth_year - birth year of an employee that we want to add to a city.
			 */
		void addEmployee(int id, std::string first_name, std::string last_name, int birth_year);

		/**
		 * addEmployee: Adds a manager to a city.
		 * @param
		 * id - id of an manager that we want to add to a city.
		 * first_name - first name of an manager that we want to add to a city.
		 * last_name - last name of an manager that we want to add to a city.
		 * birth_year - birth year of an manager that we want to add to a city.
		 */
		void addManager(int id,
						std::string first_name,
						std::string last_name,
						int birth_year);

		/**
		 * addFaculty: Adds a faculty to a city.
		 * @param
		 * id - id of a faculty that we want to add to a city.
		 * skill - Skill of a faculty that we want to add to a city.
		 * added_points - Added points of a faculty that we want to add to a city.
		 * condition - Condition to be accepted to a faculty that we want to add to a city.
		 */
		void addFaculty(int id, const Skill& skill, int added_points, Condition* condition);

		/**
		 * createWorkplace: Creates a workplace in a city.
		 * @param
		 * id - id of an workplace that we want to add to a city.
		 * work_place_name - A name of an workplace that we want to add to a city.
		 * worker_salary - A salary of a worker in a workplace that we want to add to a city.
		 * managers_salary - A salary of a manager in a workplace that we want to add to a city.
	 */
		void createWorkplace(int id, std::string work_place_name, int worker_salary, int managers_salary);

		/**
			 * teachAtFaculty: Teaches an employee in a faculty in a city a skill.
			 * @param
			 * id_employee - id of an employee in a city.
			 * id_faculty - id of a faculty in a city.
			 */
		void teachAtFaculty(int id_employee, int id_faculty);

		/**
			 * hireEmployeeAtWorkplace: Hires an employee under a manager at a workplace in a city.
			 * @param
			 * condition - object function that checks the conditions of the hiring.
			 * id_employee - id of a employee that will be hired.
			 * id_manager - id of a manager that an employee will be hired under.
			 * id_work_place - id of a workplace that an employee will be hired at.
			 */
		template<class Condition>
		void hireEmployeeAtWorkplace(Condition condition, int id_employee, int id_manager, int id_work_place)
		{
			auto* employee = dynamic_cast<Employee*>(getCitizenById(id_employee));
			auto* manager = dynamic_cast<Manager*>(getCitizenById(id_manager));
			Workplace* workplace = getWorkplaceById(id_work_place);

			if (employee == nullptr) {
				throw mtm::EmployeeDoesNotExist();
			}

			if (manager == nullptr) {
				throw mtm::ManagerDoesNotExist();
			}
			if (workplace == nullptr) {
				throw mtm::WorkplaceDoesNotExist();
			}
			workplace->hireEmployee(condition, employee, id_manager);
		}

		/**
			 * hireManagerAtWorkplace: Hires a manager at a workplace in a city.
			 * @param
			 * id_manager - id of a manager that will be hired.
			 * id_work_place - id of a workplace that a manager will be hired at.
			 */
		void hireManagerAtWorkplace(int id_manager, int id_work_place);

		/**
		 * fireEmployeeAtWorkplace: Fires an employee under a manager from a workplace in a city.
		 * @param
		 * id_employee - id of a employee a city that will be fired.
		 * id_manager - id of a manager a city that an employee who works under him will be fired.
		 * id_work_place - id of a workplace a city that an employee will be fired from.
		 */
		void fireEmployeeAtWorkplace(int id_employee, int id_manager, int id_work_place);

		/**
			 * fireManagerAtWorkplace: Fires a manager from a workplace in a city.
			 * @param
			 * id_manager - id of a manager a city that will be fired.
			 * id_work_place - id of a workplace in a city that a manager will be fired from.
			 */
		void fireManagerAtWorkplace(int id_manager, int id_work_place);

		/**
			 * getAllAboveSalary: Prints all the citizens that earn above salary and returns their collective salary.
			 * @param
			 * os -
			 * salary - A min salary that we want citizens who earn it or higher.
			 */
		int getAllAboveSalary(std::ostream& os, int salary);

		/**
		 * isWorkingInTheSameWorkplace: Checks if two employees work in the same workplace.
		 * @param
		 * first_id_employee - if of one employee.
		 * second_id_employee - if of a second employee.
		 * @return
		 * true - if the two employees work at the same workplace.
		 * false - if the two employees do Not work at the same workplace.
		 */
		bool isWorkingInTheSameWorkplace(int first_id_employee, int second_id_employee);

		/**
		 * printAllEmployeesWithSkill: Prints all the city employees that has a certain skill.
		 * @param
		 * os -
		 * id_skill - A skill that we want to check if a city employees has.
		 */
		void printAllEmployeesWithSkill(std::ostream& os, int id_skill);

		/**
		 * hasCitizen: Checks if a citizen belongs to a city.
		 * @param
		 * id - id of a citizen that we want to check.
		 * @return
		 * true - if the citizen belongs to city.
		 * false - if the citizen does NOT belongs to a city.
		 */
		bool hasCitizen(int id);

		/**
		 * hasFaculty: Checks if a faculty exists in a city.
		 * @param
		 * id - id of a faculty that we want to check.
		 * @return
		 * true - if the faculty exists in a city.
		 * false - if the faculty does NOT exists in a city.
	 */
		bool hasFaculty(int id);

		/**
		 * hasWorkPlace: Checks if a workplace exists in a city.
		 * @param
		 * id - id of a workplace that we want to check.
		 * @return
		 * true - if the workplace exists in a city.
		 * false - if the workplace does NOT exists in a city.
	*/
		bool hasWorkPlace(int id);

		/**
		 * getCitizenById: Returns citizen from city that matches the id.
		 * @param
		 * id - id of a citizen that we want to get.
		 * @return
		 * *it - A pointer to the citizen that matches the id.
		 * nullptr - If the citizen does NOT exist.
		 *
	*/
		Citizen* getCitizenById(int id);

		/**
		 * getFacultyById: Returns a faculty from city that matches the id.
		 * @param
		 * id - id of a faculty that we want to get.
		 * @return
		 * *it - A pointer to the faculty that matches the id.
		 * nullptr - If the faculty does NOT exist.
		 */
		Faculty<Condition>* getFacultyById(int id);

		/**
		 * getWorkplaceById: Returns a workplace from city that matches the id.
		 * @param
		 * id - id of a workplace that we want to get.
		 * @return
		 * *it - A pointer to the workplace that matches the id.
		 * nullptr - If the workplace does NOT exist.
		 */
		Workplace* getWorkplaceById(int id);
	};
}

#endif //EX2_CITY_H
