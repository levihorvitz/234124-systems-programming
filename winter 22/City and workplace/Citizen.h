#ifndef EX2_CITIZEN_H
#define EX2_CITIZEN_H

#include <iostream>

using std::string;
namespace mtm {
	enum CitizenType {
		EMPLOYEE, MANAGER
	};

	class Citizen {
	protected:
		int id;
		std::string first_name;
		std::string last_name;
		int birth_year;
	public:
		/**
	 * Citizen: Constructor of the Citizen class.
         * @param
         * id - id of the Citizen that is created.
         * first_name - First name of the Citizen that is created.
         * last_name - Last name of the Citizen that is created.
         * birth_year - Birth year of the Citizen that is created.
	 */
		Citizen(int id, std::string first_name, std::string last_name, int birth_year);

		/**
		* Citizen: Copy of the Citizen class.
		 * @param
		 * Citizen - A given Citizen that we will copy to a new created Citizen.
		*/
		Citizen(const Citizen&) = default;

		/**
		* ~Citizen: Destroy of the Citizen class.
		*/
		virtual ~Citizen() = default;

		/**
	    * operator= : Replace an existing Citizen with a given Citizen.
	    */
		Citizen& operator=(const Citizen&) = default;

		/**
		 * getId: Returns id of the citizen.
		 * @return
		 * id of the citizen.
		 */
		int getId() const;

		/**
		 * getFirstName: Returns the citizen's first name.
		 * @return
		 * first_name of the citizen.
		 */
		std::string getFirstName() const;

		/**
		 * getLastName: Returns the citizen's last name.
		 * @return
		 * last_name of the citizen.
		 */
		std::string getLastName() const;

		/**
		 * getBirthYear: Returns the year in which the citizen was born in.
		 * @return
		 * birth_year of the citizen.
		 */
		int getBirthYear() const;

		/**
		 * getSalary: Virtual function that returns the salary of the citizen.
		 */
		virtual int getSalary() const = 0;

		/**
         * getSalary: Virtual function that returns the type of the citizen.
         */
		virtual CitizenType getType() const = 0;

		/**
         * operator< :
         * @return
         * Returns true if citizen1 id is smaller than citizen2 id.
         * Otherwise returns false.
         */
		friend bool operator<(const Citizen& citizen1, const Citizen& citizen2);


		/**
         * printShort: Virtual function that prints short information of the citizen.
         */
		virtual std::ostream& printShort(std::ostream& os) = 0;

		/**
         * printShort: Virtual function that prints long information of the citizen.
         */
		virtual std::ostream& printLong(std::ostream& os) = 0;

		/**
         * printShort: Virtual function that returns a clone of the citizen.
         */
		virtual Citizen* clone() const = 0;

	};

	/**
	 * operator== :
	 * @return
	 * Returns true if citizen1 id is equal to citizen2 id.
	 * Otherwise returns false.
	 */
	bool operator==(const Citizen& citizen1, const Citizen& citizen2);

	/**
     * operator!= :
     * @return
     * Returns true if citizen1 id is not equal to citizen2 id.
     * Otherwise returns false.
     */
	bool operator!=(const Citizen& citizen1, const Citizen& citizen2);

	/**
     * operator> :
     * @return
     * Returns true if citizen1 id is bigger to citizen2 id.
     * Otherwise returns false.
     */
	bool operator>(const Citizen& citizen1, const Citizen& citizen2);

	/**
     * operator<= :
     * @return
     * Returns true if citizen1 id is smaller or equal to citizen2 id.
     * Otherwise returns false.
     */
	bool operator<=(const Citizen& citizen1, const Citizen& citizen2);

	/**
     * operator>= :
     * @return
     * Returns true if citizen1 id is bigger or equal to citizen2 id.
     * Otherwise returns false.
     */
	bool operator>=(const Citizen& citizen1, const Citizen& citizen2);
}

#endif //EX2_CITIZEN_H
