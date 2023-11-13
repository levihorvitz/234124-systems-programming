#include "City.h"
#include <algorithm>

using namespace std;
using namespace mtm;

bool compereCitizen(Citizen* first_citizen, Citizen* second_citizens)
{
	return first_citizen->getId() < second_citizens->getId();
}

City::City(std::string name)
{
	name = std::move(name);
	citizens = set<Citizen*, bool (*)(Citizen*, Citizen*)>(compereCitizen);
	work_places = set<Workplace*>();
	faculties = set<Faculty<Condition>*>();

}

City::City(const City& other)
{
	name = other.name;
	bool (* fn_pt)(Citizen*, Citizen*) = compereCitizen;
	citizens = set<Citizen*, bool (*)(Citizen*, Citizen*)>(fn_pt);
	work_places = set<Workplace*>();
	faculties = set<Faculty<Condition>*>();

	set<Citizen*>::iterator citizen;
	for (citizen = other.citizens.begin(); citizen != other.citizens.end(); citizen++) {
		citizens.insert((*citizen)->clone());
	}

	set<Faculty<Condition>*>::iterator faculty;
	for (faculty = other.faculties.begin(); faculty != other.faculties.end(); faculty++) {
		faculties.insert((*faculty)->clone());
	}
	set<Workplace*>::iterator work_place;
	for (work_place = other.work_places.begin(); work_place != other.work_places.end(); work_place++) {
		work_places.insert((*work_place)->clone());
	}
}

City::~City()
{
	auto citizen = citizens.begin();
	while (citizen != citizens.end()) {
		delete *citizen;
		citizens.erase(citizen);
		citizen = citizens.begin();
	}

	set<Faculty<Condition>*>::iterator faculty;
	for (faculty = faculties.begin(); faculty != faculties.end(); faculty++) {
		delete *faculty;
	}
	set<Workplace*>::iterator work_place;
	for (work_place = work_places.begin(); work_place != work_places.end(); work_place++) {
		delete *work_place;
	}
	citizens.clear();
	faculties.clear();
	work_places.clear();
}


City& City::operator=(const City& other)
{
	if (this == &other) {
		return *this;
	}
	name = other.name;
	set<Citizen*>::iterator citizen;
	for (citizen = other.citizens.begin(); citizen != other.citizens.end(); citizen++) {
		citizens.insert((*citizen)->clone());
	}

	set<Faculty<Condition>*>::iterator faculty;
	for (faculty = other.faculties.begin(); faculty != other.faculties.end(); faculty++) {
		faculties.insert((*faculty)->clone());
	}
	set<Workplace*>::iterator work_place;
	for (work_place = other.work_places.begin(); work_place != other.work_places.end(); work_place++) {
		work_places.insert((*work_place)->clone());
	}
	return *this;
}


bool City::hasCitizen(int id)
{
	set<Citizen*>::iterator it;
	for (it = citizens.begin(); it != citizens.end(); it++) {
		if ((*it)->getId() == id) {
			return true;
		}
	}
	return false;
}

bool City::hasFaculty(int id)
{
	set<Faculty<Condition>*>::iterator it;
	for (it = faculties.begin(); it != faculties.end(); it++) {
		if ((*it)->getId() == id) {
			return true;
		}
	}
	return false;
}

bool City::hasWorkPlace(int id)
{
	set<Workplace*>::iterator it;
	for (it = work_places.begin(); it != work_places.end(); it++) {
		if ((*it)->getId() == id) {
			return true;
		}
	}
	return false;
}

void City::addEmployee(int id, std::string first_name, std::string last_name, int birth_year)
{
	if (hasCitizen(id)) {
		throw mtm::CitizenAlreadyExists();
	}
	auto* employee = new Employee(id, std::move(first_name), std::move(last_name), birth_year);
	this->citizens.insert(employee);
}

void City::addManager(int id, std::string first_name, std::string last_name, int birth_year)
{
	if (hasCitizen(id)) {
		throw mtm::CitizenAlreadyExists();
	}
	auto* manager = new Manager(id, std::move(first_name), std::move(last_name), birth_year);
	this->citizens.insert(manager);
}

void City::addFaculty(int id, const Skill& skill, int added_points, Condition* condition)
{
	if (hasFaculty(id)) {
		throw mtm::FacultyAlreadyExists();
	}
	Faculty<Condition>* faculty= new Faculty<Condition>(id, skill, added_points, condition);
	faculties.insert(faculty);
}

void City::createWorkplace(int id, std::string work_place_name, int worker_salary, int managers_salary)
{
	if (hasWorkPlace(id)) {
		throw mtm::WorkplaceAlreadyExists();
	}
	auto* workplace = new Workplace(id, std::move(work_place_name), worker_salary, managers_salary);
	work_places.insert(workplace);
}

Citizen* City::getCitizenById(int id)
{
	set<Citizen*>::iterator it;
	for (it = citizens.begin(); it != citizens.end(); it++) {
		if ((*it)->getId() == id) {
			return *it;
		}
	}
	return nullptr;
}

Faculty<Condition>* City::getFacultyById(int id)
{
	set<Faculty<Condition>*>::iterator it;
	for (it = faculties.begin(); it != faculties.end(); it++) {
		if ((*it)->getId() == id) {
			return *it;
		}
	}
	return nullptr;
}

Workplace* City::getWorkplaceById(int id)
{
	set<Workplace*>::iterator it;
	for (it = work_places.begin(); it != work_places.end(); it++) {
		if ((*it)->getId() == id) {
			return *it;
		}
	}
	return nullptr;
}

void City::teachAtFaculty(int id_employee, int id_faculty)
{
	Citizen* citizen = getCitizenById(id_employee);
	Faculty<Condition>* faculty = getFacultyById(id_faculty);

	if (citizen == nullptr || citizen->getType() == MANAGER) {
		throw mtm::EmployeeDoesNotExist();
	}
	if (faculty == nullptr) {
		throw mtm::FacultyDoesNotExist();
	}

	auto* employee = dynamic_cast<Employee*>(citizen);
	faculty->teach(employee);
}

void City::hireManagerAtWorkplace(int id_manager, int id_work_place)
{
	Citizen* citizen = getCitizenById(id_manager);
	Workplace* workplace = getWorkplaceById(id_work_place);

	if (citizen == nullptr || citizen->getType() == EMPLOYEE) {
		throw mtm::ManagerDoesNotExist();
	}
	if (workplace == nullptr) {
		throw mtm::WorkplaceDoesNotExist();
	}

	auto* manager = dynamic_cast<Manager*>(citizen);
	workplace->hireManager(manager);
}

void City::fireEmployeeAtWorkplace(int id_employee, int id_manager, int id_work_place)
{
	Workplace* workplace = getWorkplaceById(id_work_place);
	if (!hasCitizen(id_employee)) {
		throw mtm::EmployeeDoesNotExist();
	}
	if (!hasCitizen(id_manager)) {
		throw mtm::ManagerDoesNotExist();
	}
	if (workplace == nullptr) {
		throw mtm::WorkplaceDoesNotExist();
	}
	workplace->fireEmployee(id_manager, id_employee);
}

void City::fireManagerAtWorkplace(int id_manager, int id_work_place)
{
	Workplace* workplace = getWorkplaceById(id_work_place);
	Citizen* citizen = getCitizenById(id_manager);
	if (citizen == nullptr) {
		throw mtm::ManagerDoesNotExist();
	}
	if (workplace == nullptr) {
		throw mtm::WorkplaceDoesNotExist();
	}

	auto* manager = dynamic_cast<Manager*>(citizen);
	set<Employee*, bool (*)(Employee*, Employee*)> employees = manager->getEmployees();
	auto employee = employees.begin();
	while (employee != employees.end()) {
		workplace->fireEmployee(id_manager, (*employee)->getId());
		employees = manager->getEmployees();
		employee = employees.begin();
	}
	workplace->fireManager(id_manager);
}

int City::getAllAboveSalary(std::ostream& os, int salary)
{
	int sum = 0;
	set<Citizen*, bool (*)(Citizen*, Citizen*)>::iterator citizen;
	for (citizen = citizens.begin(); citizen != citizens.end(); citizen++) {
		if ((*citizen)->getSalary() >= salary) {
			(*citizen)->printShort(os);
			sum++;
		}
	}
	return sum;
}

static bool isInWorkPlace(const set<Manager*, bool (*)(Manager*, Manager*)>& managers, int id_employee)
{
	set<Manager*>::iterator manager;
	for (manager = managers.begin(); manager != managers.end(); manager++) {
		set<Employee*, bool (*)(Employee*, Employee*)> employees = (*manager)->getEmployees();
		set<Employee*, bool (*)(Employee*, Employee*)>::iterator employee;
		for (employee = employees.begin(); employee != employees.end(); employee++)
			if ((*employee)->getId() == id_employee) {
				return true;
			}
	}
	return false;
}

bool City::isWorkingInTheSameWorkplace(int first_id_employee, int second_id_employee)
{
	if (!(hasCitizen(first_id_employee) && hasCitizen(second_id_employee))) {
		throw mtm::EmployeeDoesNotExist();
	}
	set<Workplace*>::iterator work_place;
	for (work_place = work_places.begin(); work_place != work_places.end(); work_place++) {
		if (isInWorkPlace((*work_place)->getManagers(), first_id_employee) &&
			isInWorkPlace((*work_place)->getManagers(), second_id_employee)) {
			return true;
		}
	}
	return false;
}

void City::printAllEmployeesWithSkill(std::ostream& os, int id_skill)
{
	set<Citizen*, bool (*)(Citizen*, Citizen*)>::iterator citizen;
	for (citizen = citizens.begin(); citizen != citizens.end(); citizen++) {
		if ((*citizen)->getType() == EMPLOYEE) {
			auto* employee = dynamic_cast<Employee*>(*citizen);
			if (employee->hasSkill(id_skill)) {
				employee->printShort(os);
			}

		}
	}
}

