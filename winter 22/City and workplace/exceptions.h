#ifndef EX2_EXCEPTIONS_H
#define EX2_EXCEPTIONS_H

#include <exception>

namespace mtm {
	class exceptions : public std::exception {
	};

	class NegativePoints : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class SkillAlreadyLearned : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class CanNotLearnSkill : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class DidNotLearnSkill : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class EmployeeAlreadyHired : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class EmployeeNotHired : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class EmployeeNotSelected : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class ManagerIsNotHired : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class ManagerAlreadyHired : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class CanNotHireManager : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class EmployeeIsNotHired : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class EmployeeNotAccepted : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class EmployeeAlreadyExists : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class ManagerAlreadyExists : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class FacultyAlreadyExists : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class WorkplaceAlreadyExists : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class EmployeeDoesNotExist : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class FacultyDoesNotExist : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class ManagerDoesNotExist : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class WorkplaceDoesNotExist : public exceptions {
	public:
		const char* what() const noexcept override;
	};

	class CitizenAlreadyExists : public exceptions {
	public:
		const char* what() const noexcept override;
	};

}

#endif //EX2_EXCEPTIONS_H
