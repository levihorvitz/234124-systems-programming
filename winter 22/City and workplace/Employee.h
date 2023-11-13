#ifndef EX2_EMPLOYEE_H
#define EX2_EMPLOYEE_H

#include "Skill.h"
#include "Citizen.h"
#include <set>

using namespace std;
namespace mtm {
	class Employee : public Citizen {
	private:
		int salary;
		int score;
		set<Skill, bool (*)(const Skill&, const Skill&)> skills;
	public:

		/**
	 * Employee: Constructor of the Employee class.
         * @param
         * id - id of the Employee that is created.
         * first_name - First name of the Employee that is created.
         * last_name - Last name of the employee that is created.
         * birth_year - Birth year of the employee that is created.
	 */
		Employee(int id, std::string first_name, std::string last_name, int birth_year);

		/**
		* Employee: Copy of the Employee class.
		 * @param
		 * Employee - A given Employee that we will copy to a new created Employee.
		*/
		Employee(const Employee& employee);

		/**
		* ~Employee: Destroy of the Employee class.
		*/
		~Employee() override = default;

		/**
			 * operator= : Replace an existing Employee with a given Employee.
			 */
		Employee& operator=(const Employee& employee) = default;

		///ask if need copy

		/**
		 * getSalary: Returns the salary of the employee.
		 * @return
		 * salary of the employee.
		 */
		int getSalary() const override;

		/**
		 * getType: Returns the Citizen Type of the employee.
		 * @return
		 * CitizenType of the employee.
		 */
		CitizenType getType() const override;

		/**
		 * getType: Returns the score of the employee.
		 * @return
		 * score of the employee.
		 */
		int getScore() const;

		/**
         * getSkillById: Finds a Skill according to the given id.
         * @param id - The id of the skill we need to find.
         * @return
         * *it - A pointer to the skill that match the id.
         */
		Skill getSkillById(int id) const;

		/**
         * learnSkill: Checks if employee has enough points to learn a skill and adds it to his skill set if yes.
         * @param skill - A skill that we want the employee to learn.
         */

		void learnSkill( Skill& skill);

		/**
         * forgetSkill: Checks if employee has a skill according to its id deletes it from his skill set if yes.
         * @param id - An id of a skill that we want the employee to forget.
         */
		void forgetSkill(int id);

		/**
         * hasSkill: Checks if employee has a certain skill.
         * @param id - The id of the skill we need to check if employee has in his skill set.
         * @return
         * true - if employee has the skill in his skill set.
         * false - if employee doesn't have the skill in his skill set.
         */
		bool hasSkill(int id);

		/**
         * setSalary: Sets the salary of an employee
         * @param salary - The salary that we want an employee to have.
         */
		void setSalary(int salary);

		/**
         * setSalary: Sets the score of an employee
         * @param score - The score that we want an employee to have.
         */
		void setScore(int score);

		/**
         * printShort: Prints short info of employee.
         */
		std::ostream& printShort(ostream& os) override;

		/**
         * printLong: Prints detailed info of employee.
         */
		std::ostream& printLong(ostream& os) override;

		/**
         * clone: Returns a copy of an employee.
         * @return
         * Returns a pointer to a copy of an employee.
         */
		Employee* clone() const override;

	};

}
#endif //EX2_EMPLOYEE_H
