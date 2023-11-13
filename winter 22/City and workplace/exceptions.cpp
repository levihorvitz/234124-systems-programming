#include "exceptions.h"

const char* mtm::NegativePoints::what() const noexcept
{
	return "A city related error has occurred: NegativePoints";
}

const char* mtm::SkillAlreadyLearned::what() const noexcept
{
	return "A city related error has occurred: SkillAlreadyLearned";
}

const char* mtm::CanNotLearnSkill::what() const noexcept
{
	return "A city related error has occurred: CanNotLearnSkill";
}

const char* mtm::DidNotLearnSkill::what() const noexcept
{
	return "A city related error has occurred: CanNotLearnSkill";
}

const char* mtm::EmployeeAlreadyHired::what() const noexcept
{
	return "A city related error has occurred: EmployeeAlreadyHired";
}

const char* mtm::EmployeeNotHired::what() const noexcept
{
	return "A city related error has occurred: EmployeeNotHired";
}

const char* mtm::EmployeeNotSelected::what() const noexcept
{
	return "A city related error has occurred: EmployeeNotHired";
}

const char* mtm::ManagerIsNotHired::what() const noexcept
{
	return "A city related error has occurred: ManagerIsNotHired";
}

const char* mtm::ManagerAlreadyHired::what() const noexcept
{
	return "A city related error has occurred: ManagerIsNotHired";
}

const char* mtm::CanNotHireManager::what() const noexcept
{
	return "A city related error has occurred: CanNotHireManager";
}

const char* mtm::EmployeeIsNotHired::what() const noexcept
{
	return "A city related error has occurred: CanNotHireManager";
}

const char* mtm::EmployeeNotAccepted::what() const noexcept
{
	return "A city related error has occurred: EmployeeNotAccepted";
}

const char* mtm::EmployeeAlreadyExists::what() const noexcept
{
	return "A city related error has occurred: EmployeeAlreadyExists";
}

const char* mtm::ManagerAlreadyExists::what() const noexcept
{
	return "A city related error has occurred: ManagerAlreadyExists";
}

const char* mtm::FacultyAlreadyExists::what() const noexcept
{
	return "A city related error has occurred: FacultyAlreadyExists";
}

const char* mtm::WorkplaceAlreadyExists::what() const noexcept
{
	return "A city related error has occurred: WorkplaceAlreadyExists";
}

const char* mtm::EmployeeDoesNotExist::what() const noexcept
{
	return "A city related error has occurred: EmployeeDoesNotExist";
}

const char* mtm::FacultyDoesNotExist::what() const noexcept
{
	return "A city related error has occurred: FacultyDoesNotExist";
}

const char* mtm::ManagerDoesNotExist::what() const noexcept
{
	return "A city related error has occurred: ManagerDoesNotExist";
}

const char* mtm::WorkplaceDoesNotExist::what() const noexcept
{
	return "A city related error has occurred: WorkplaceDoesNotExist";
}


const char* mtm::CitizenAlreadyExists::what() const noexcept
{
	return "A city related error has occurred: CitizenAlreadyExists";
}
