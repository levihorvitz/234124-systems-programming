#include "Workplace.h"

static bool compareManager(Manager* first_manager, Manager* second_manager)
{
	return first_manager->getId() < second_manager->getId();
}

Workplace::Workplace(int id, std::string name, int worker_salary, int managers_salary) :
		id(id), name(std::move(name)), worker_salary(worker_salary), managers_salary(managers_salary)
{
	managers = set<Manager*, bool (*)(Manager*, Manager*)>(compareManager);
}


int Workplace::getManagersSalary() const
{
	return this->managers_salary;
}

int Workplace::getWorkersSalary() const
{
	return this->worker_salary;
}

std::string Workplace::getName() const
{
	return this->name;
}

int Workplace::getId() const
{
	return this->id;
}

void Workplace::hireManager(Manager* manager)
{
	if (managers.find(manager) != managers.end()) {
		throw mtm::ManagerAlreadyHired();
	}
	if (manager->getManagerEmploymentStatus() == HIRED || manager->getSalary() > 0) {
		throw mtm::CanNotHireManager();
	}
	manager->setSalary(managers_salary);
	manager->setManagerEmploymentStatus(HIRED);
	managers.insert(manager);
}

void Workplace::fireEmployee(int id_manager, int id_employee)
{
	Manager* manager = getManagerById(id_manager);
	if (manager == nullptr) {
		throw mtm::ManagerIsNotHired();
	}
	Employee* employee = manager->getEmployeeById(id_employee);
	if (employee == nullptr) {
		throw mtm::EmployeeIsNotHired();
	}
	employee->setSalary(-worker_salary);
	manager->removeEmployee(id_employee);
}

void Workplace::fireManager(int id_manager)
{
	Manager* manager = getManagerById(id_manager);
	if (manager == nullptr) {
		throw mtm::ManagerIsNotHired();
	}

	manager->setSalary(-managers_salary);
	manager->setManagerEmploymentStatus(NOT_HIRED);
	managers.erase(manager);
}

Manager* Workplace::getManagerById(int id_manager)
{
	for (auto manager : managers) {
		if (manager->getId() == id_manager) {
			return manager;
		}
	}
	return nullptr;
}

Workplace* Workplace::clone() const
{
	return new Workplace(*this);
}

set<Manager*, bool (*)(Manager*, Manager*)> Workplace::getManagers() const
{
	return managers;
}

std::ostream& operator<<(ostream& os, const Workplace& workplace)
{
	os << "Workplace name - " << workplace.getName();
	if (workplace.managers.begin() != workplace.managers.end()) {
		os << " Groups:" << endl;
	} else {
		os << endl;
	}
	for (auto manager : workplace.managers) {
		os << "Manager ";
		manager->printLong(os);
	}
	return os;
}

