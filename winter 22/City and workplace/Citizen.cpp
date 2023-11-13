#include "Citizen.h"

using namespace mtm;

Citizen::Citizen(int id, std::string first_name, std::string last_name, int birth_year) :
		id(id), first_name(std::move(first_name)), last_name(std::move(last_name)), birth_year(birth_year)
{

}

int Citizen::getId() const
{
	return this->id;
}

std::string Citizen::getFirstName() const
{
	return this->first_name;
}

std::string Citizen::getLastName() const
{
	return this->last_name;
}

int Citizen::getBirthYear() const
{
	return this->birth_year;
}

bool operator<(const Citizen& citizen1, const Citizen& citizen2)
{
	return citizen1.getId() < citizen2.getId();
}

bool operator==(const Citizen& citizen1, const Citizen& citizen2)
{
	return citizen1.getId() == citizen2.getId();
}

bool operator>(const Citizen& citizen1, const Citizen& citizen2)
{
	return citizen1.getId() > citizen2.getId();
}

bool operator<=(const Citizen& citizen1, const Citizen& citizen2)
{
	return citizen1.getId() <= citizen2.getId();
}

bool operator>=(const Citizen& citizen1, const Citizen& citizen2)
{
	return citizen1.getId() >= citizen2.getId();
}

bool operator!=(const Citizen& citizen1, const Citizen& citizen2)
{
	return citizen1.getId() != citizen2.getId();
}
