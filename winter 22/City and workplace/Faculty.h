#ifndef EX2_FACULTY_H
#define EX2_FACULTY_H

#include "Employee.h"
#include "exceptions.h"

using namespace mtm;
namespace mtm {
	class Condition {
	public:
		virtual bool operator()(Employee* employee) = 0;
	};

	template<class T>
	class Faculty {
	protected:
		int id;
		Skill skill;
		int added_points;
		T* condition;

	public:

		/**
	* Faculty: Constructor of the Faculty class.
		* @param
		* id - id of the Faculty the we want to construct.
		* skill - A skill that is needed to study in the faculty.
		* added_points - points that will be acquired if accepted to the faculty.
		* condition - object function that checks the conditions of the acceptance to the faculty.
	*/
		Faculty(int id, const Skill& skill, int added_points, T* condition):
				id(id), skill(skill), added_points(added_points), condition(condition){};

		/**
	* Faculty: Copy Constructor of the Faculty class.
	 * @param
	 * faculty -A given Faculty that we will copy to a new constructed Faculty.
	*/
		Faculty(const Faculty& faculty)=default;

		/**
	     * ~Faculty: Destroy of the Faculty class.
	     */
		~Faculty() = default;

		/**
	     * operator= : Replace an existing Faculty with a given Faculty.
	     */
		Faculty& operator=(const Faculty& faculty)=default;

        /**
         * getAddedPoints: Returns the added points if accepted to the faculty.
         * @return
         * added_points -
         */
		int getAddedPoints() const;

		/**
         * getId: Returns id of a faculty.
         * @return
         * id - id of a faculty.
         */
		int getId() const;

		/**
         * getSkill: Gets a skill from a faculty.
         * @return
         * skill - a skill from a faculty.
         */
		Skill getSkill() const;

		/**
         * teach: Teaches an employee in a faculty a skill.
         * @param employee - An employee in a faculty.
         */
		void teach(Employee* employee);

		/**
         * clone: Returns a copy of a faculty.
         * @return
         * Faculty - A copy of a faculty.
         */
		Faculty* clone() const;

	};

	template<class Condition>
	int Faculty<Condition>::getAddedPoints() const
	{
		return added_points;
	}

	template<class Condition>
	int Faculty<Condition>::getId() const
	{
		return id;
	}

	template<class Condition>
	Skill Faculty<Condition>::getSkill() const
	{
		return skill;
	}

	template<class Condition>
	void Faculty<Condition>::teach(Employee* employee)
	{
		if (!(*condition)(employee)) {
			throw mtm::EmployeeNotAccepted();
		}
		employee->setScore(added_points);
		try {
			employee->learnSkill(skill);
		}
		catch (CanNotLearnSkill&) {
			employee->setScore(-added_points);
		}
		catch (SkillAlreadyLearned&) {
			employee->setScore(-added_points);
		}

	}

	template<class Condition>
	Faculty<Condition>* Faculty<Condition>::clone() const
	{
		return new Faculty<Condition>(id, skill, added_points, condition);
	}
}

#endif //EX2_FACULTY_H
