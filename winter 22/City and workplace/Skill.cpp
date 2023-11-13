#include "Skill.h"
#include "exceptions.h"

using namespace mtm;

Skill::Skill(int ID, std::string name, int points) :
		ID(ID), name(std::move(name)), points(points)
{}


int Skill::getRequiredPoints() const
{
	return points;
}

std::string Skill::getName() const
{
	return name;
}

int Skill::getId() const
{
	return ID;
}

bool operator<(const Skill& skill1, const Skill& skill2)
{
	return skill1.getId() < skill2.getId();
}

bool operator==(const Skill& skill1, const Skill& skill2)
{
	return skill1.getId() == skill2.getId();
}

Skill Skill::operator++(int)
{
	Skill skill = *this;
	points++;
	return skill;
}

Skill& Skill::operator+=(int point)
{
	if (point < 0) {
		throw mtm::NegativePoints();
	}
	this->points += point;
	return *this;
}

Skill operator+(const Skill& skill, int point)
{
	if (point < 0) {
		throw mtm::NegativePoints();
	}
	Skill dest_skill = skill;
	dest_skill += point;
	return dest_skill;
}

Skill operator+(int point, const Skill& skill)
{
	if (point < 0) {
		throw mtm::NegativePoints();
	}
	Skill dest_skill = skill;
	dest_skill += point;
	return dest_skill;
}

bool operator>(const Skill& skill1, const Skill& skill2)
{
	return skill1.getId() > skill2.getId();
}

bool operator<=(const Skill& skill1, const Skill& skill2)
{
	return skill1.getId() <= skill2.getId();
}

bool operator>=(const Skill& skill1, const Skill& skill2)
{
	return skill1.getId() >= skill2.getId();
}

bool operator!=(const Skill& skill1, const Skill& skill2)
{
	return skill1.getId() != skill2.getId();
}

std::ostream& operator<<(std::ostream& os, const Skill& skill)
{
	return os << skill.getName() << std::endl;
}


