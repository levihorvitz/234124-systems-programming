#include "Manager.h"
#include "exceptions.h"

using namespace mtm;

bool fnCompareId(Employee* first_citizen, Employee* second_citizens)
{
	return (*first_citizen).getId() < (*second_citizens).getId();
}

Manager::Manager(int id, string first_name, string last_name, int birth_year) :
		Citizen(id, std::move(first_name), std::move(last_name), birth_year)
{
	salary = 0;
	employees = set<Employee*, bool (*)(Employee*, Employee*)>(fnCompareId);
	managerStatus = NOT_HIRED;
}

int Manager::getSalary() const
{
	return this->salary;
}

ManagerStatus Manager::getManagerEmploymentStatus()
{
	return managerStatus;
}

Employee* Manager::getEmployeeById(int id_employee)
{
	for (auto employee : employees) {
		if (employee->getId() == id_employee) {
			return employee;
		}
	}
	return nullptr;
}

set<Employee*, bool (*)(Employee*, Employee*)> Manager::getEmployees()
{
	return employees;
}

CitizenType Manager::getType() const
{
	return MANAGER;
}

void Manager::setSalary(int salary_manager)
{
	if (this->salary + salary_manager < 0) {
		this->salary = 0;
		return;
	}
	this->salary += salary_manager;
}

void Manager::setManagerEmploymentStatus(ManagerStatus status)
{
	managerStatus = status;
}

bool Manager::hasEmployee(int id)
{
	for (auto employee : employees) {
		if ((*employee).getId() == id) {
			return true;
		}
	}
	return false;
}

void Manager::addEmployee(Employee* employee)
{
	if (hasEmployee(employee->getId())) {
		throw mtm::EmployeeAlreadyHired();
	}
	employees.insert(employee);
}

void Manager::removeEmployee(int id)
{
	Employee* employee = getEmployeeById(id);
	if (employee == nullptr) {
		throw mtm::EmployeeIsNotHired();
	}
	this->employees.erase(employee);
}

Manager* Manager::clone() const
{
	return new Manager(*this);
}

std::ostream& Manager::printShort(std::ostream& os)
{
	return os << this->getFirstName() << " " << this->getLastName() << endl
			  << "Salary: " << this->salary << endl;
}

std::ostream& Manager::printLong(std::ostream& os)
{
	os << this->getFirstName() << " " << this->getLastName() << endl << "id - " << this->id << " birth_year - "
	   << this->birth_year << endl << "Salary: " << this->salary << endl;
	if (employees.begin() != employees.end()) {
		os << "Employees: " << endl;
	}
	for (auto employee : this->employees) {
		employee->printShort(os);
	}
	return os;
}


