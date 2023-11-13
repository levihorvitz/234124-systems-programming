#ifndef EX2_SKILL_H
#define EX2_SKILL_H

#include <iostream>
#include <string>


class Skill {
private:
	int ID;
	std::string name;
	int points;

public:

	/**
	 * Skill: Constructor of the Skill class.
		 * @param
		 * ID - id of the Skill that is created.
		 * name - Name of the Skill that is created.
		 * points - Amount of the points that Skill is worth.
	 */
	Skill(int ID, std::string name, int points);

	/**
	   * ~Skill: Destroy of the Skill class.
	   */
	~Skill() = default;

	/**
 * Skill: Creates new skill and copies recieved Skill to skill.
 * @param Skills& - A skill that we copy information from to another skill.
 * @return
 *
 */
	Skill(const Skill& skill) = default;

/**
 * operator=: Copies recieved Skill to an already existing skill.
 * @param Skills& - A skill that we copy information from to another skill.
 * @return
 *
 */
	Skill& operator=(const Skill&) = default;

	/**
		 * getRequiredPoints: Returns the required amount of points to learn the skill.
		 * @return
		 * points.
		 */
	int getRequiredPoints() const;

	/**
		 * getName: Returns the name of the skill.
		 * @return
		 * name of the skill.
		 */
	std::string getName() const;

	/**
		 * getName: Returns the id of the skill.
		 * @return
		 * id of the skill.
		 */
	int getId() const;

	/**
		 * operator<< : Prints info of skill.
		 */
	friend std::ostream& operator<<(std::ostream& os, const Skill& skill);

	/**
		 * operator< :
		 * @return
		 * Returns true if skill1 id is smaller than skill2 id.
		 * Otherwise returns false.
		 */
	friend bool operator<(const Skill& skill1, const Skill& skill2);

	/**
		 * operator== :
		 * @return
		 * Returns true if skill1 id is equal to skill2 id.
		 * Otherwise returns false.
		 */
	friend bool operator==(const Skill& skill1, const Skill& skill2);

	/**
		 * operator++ :
		 * Add the points of the skill by 1.
		 */
	Skill operator++(int);

	/**
		 * operator+= :
		 * Add the points of the skill by a specific number.
		 */
	Skill& operator+=(int point);


};

/**
         * operator+ :
         * Add the points of the skill by a specific number.
         */
Skill operator+(const Skill& skill, int point);

/**
         * operator+ :
         * Add the points of the skill by a specific number.
         */
Skill operator+(int point, const Skill& skill);

/**
         * operator> :
         * @return
         * Returns true if skill1 id is bigger than skill2 id.
         * Otherwise returns false.
         */
bool operator>(const Skill& skill1, const Skill& skill2);

/**
         * operator<= :
         * @return
         * Returns true if skill1 id is smaller or equal to skill2 id.
         * Otherwise returns false.
         */
bool operator<=(const Skill& skill1, const Skill& skill2);

/**
         * operator>= :
         * @return
         * Returns true if skill1 id is bigger or equal to skill2 id.
         * Otherwise returns false.
         */
bool operator>=(const Skill& skill1, const Skill& skill2);

/**
         * operator!= :
         * @return
         * Returns true if skill1 id is not equal to skill2 id.
         * Otherwise returns false.
         */
bool operator!=(const Skill& skill1, const Skill& skill2);


#endif //EX2_SKILL_H
