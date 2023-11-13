#include "Employee.h"
#include "exceptions.h"


using std::string;
using namespace mtm;

bool fnCompareId(const Skill& first_skill, const Skill& second_skill)
{
	return first_skill.getId() < second_skill.getId();
}


Employee::Employee(int id, string first_name, string last_name, int birth_year) :
		Citizen(id, std::move(first_name), std::move(last_name), birth_year)
{
	salary = 0;
	score = 0;
	skills = set<Skill, bool (*)(const Skill&, const Skill&)>(fnCompareId);
}


Employee::Employee(const Employee& employee) : Citizen(employee)
{
	salary = employee.salary;
	score = employee.score;
	skills = employee.skills;
}


int Employee::getSalary() const
{
	return this->salary;
}

int Employee::getScore() const
{
	return this->score;
}

void Employee::setSalary(int salary_of_employee)
{
	if (this->salary + salary_of_employee < 0) {
		this->salary = 0;
		return;
	}
	this->salary += salary_of_employee;
}

void Employee::setScore(int score_of_employee)
{
	if (this->score + score_of_employee < 0) {
		this->score = 0;
		return;
	}
	this->score += score_of_employee;
}

CitizenType Employee::getType() const
{
	return EMPLOYEE;
}


void Employee::learnSkill( Skill& skill)
{
	if (hasSkill(skill.getId())) {
		throw mtm::SkillAlreadyLearned();
	}
	if (score < skill.getRequiredPoints()) {
		throw mtm::CanNotLearnSkill();
	}
	skills.insert(skill);
}

Skill Employee::getSkillById(int id) const
{
	set<Skill>::iterator it;
	for (it = skills.begin(); it != skills.end(); it++) {
		if (it->getId() == id) {
			return *it;
		}
	}
	return Skill(0,"",0);
}

void Employee::forgetSkill(int id)
{

	if (!hasSkill(id)) {
		throw mtm::DidNotLearnSkill();
	}
	Skill skill = getSkillById(id);
	skills.erase(skill);
}

bool Employee::hasSkill(int id)
{
	set<Skill>::iterator it;
	for (it = skills.begin(); it != skills.end(); it++) {
		if (it->getId() == id) {
			return true;
		}
	}
	return false;
}

Employee* Employee::clone() const
{
	return new Employee(*this);
}

ostream& Employee::printShort(ostream& os)
{
	return os << this->getFirstName() << " " << this->getLastName() << endl << "Salary: " << this->salary << " Score: "
			  << this->score << endl;
}

ostream& Employee::printLong(ostream& os)
{
	os << this->getFirstName() << " " << this->getLastName() << endl << "id - " << this->id << " birth_year - "
	   << this->birth_year << endl << "Salary: " << this->salary << " Score: "
	   << this->score;
	if (skills.begin() != skills.end()) {
		os << " Skills: ";
	}
	os << endl;
	set<Skill>::iterator it;
	for (it = skills.begin(); it != skills.end(); it++) {
			os << it->getName() << endl;
	}
	return os;
}


