#include "ExamDetails.h"

#include <iostream>
#include <string>
#include <cmath>

using std::endl;
using std::string;

/
bool mtm::ExamDetails::isTimeValid(double time)
{
	double hours;
	double minutes = modf(time, &hours);
	return (fabs(minutes - HALF_HOUR) < EPSILON || fabs(minutes) < EPSILON) && 0 <= hours && hours < HOURS_IN_DAY;
}


std::string mtm::ExamDetails::timeToText(double time)
{
	string text;
	double hours;
	double minutes = modf(time, &hours) * 60;
	text += std::to_string(static_cast<int>(hours)) + ":";
	if (minutes < 10) {
		text += "0";
	}
	text += std::to_string(static_cast<int>(minutes));
	return text;
}


mtm::ExamDetails::ExamDetails(int num_course, int month, int day, double time, double exam_length, const string& link)
		: num_course(num_course), month(month), day(day), time(time), exam_length(exam_length), link(link)
{
	if (month < 1 || MONTHS_IN_YEAR < month || day < 1 || DAYS_IN_MONTH < day) {
		throw ExamDetails::InvalidDateException();
	}
	if (!isTimeValid(time)) {
		throw ExamDetails::InvalidTimeException();
	}
	if (num_course < 0 || exam_length < 0) {
		throw ExamDetails::InvalidArgsException();
	}
}


std::string mtm::ExamDetails::getLink() const
{
	return link;
}


void mtm::ExamDetails::setLink(const string& new_link)
{
	link = new_link;
}


int mtm::ExamDetails::operator-(const mtm::ExamDetails& exam) const
{
	return (month - exam.month) * DAYS_IN_MONTH + (day - exam.day);
}


bool mtm::ExamDetails::operator<(const mtm::ExamDetails& exam) const
{
	int days = *this - exam;
	return days < 0;
}


std::ostream& mtm::operator<<(std::ostream& os, const mtm::ExamDetails& exam)
{
	os << "Course Number: " << exam.num_course << endl;
	os << "Time: " << exam.day << "." << exam.month << " at " << exam.timeToText(exam.time) << endl;
	os << "Duration: " << exam.timeToText(exam.exam_length) << endl;
	os << "Zoom Link: " << exam.link << endl;
	return os;
}


mtm::ExamDetails mtm::ExamDetails::makeMatamExam()
{
	return mtm::ExamDetails(MTM_COURSE_NUMBER,
							MTM_COURSE_MONTH,
							MTM_COURSE_DAY,
							MTM_COURSE_TIME,
							MTM_EXAM_LENGTH,
							std::string(MTM_COURSE_LINK));
}
*/

bool mtm::ExamDetails::isTimeValid(double time){
	double hours;
	double minutes = modf(time, &hours);
	return (fabs(minutes - HALF_HOUR) < EPSILON || fabs(minutes) < EPSILON) && 0 <= hours && hours < HOURS_IN_DAY;
}
std::string mtm::ExamDetails::timeToText(double time){
	string text;
	double hours;
	double minutes = modf(time, &hours) * 60;
	text += std::to_string(static_cast<int>(hours)) + ":";
	if (minutes < 10) {
		text += "0";
	}
	text += std::to_string(static_cast<int>(minutes));
	return text;
}
mtm::ExamDetails::ExamDetails(int num_course, int day, int month, double time, double exam_length,
							  const std::string& link_to_exam):num_course(num_course), day(day),month(month),time(time),exam_length(exam_length),link_to_exam(link_to_exam)
{
	if (month < 1 || MONTHS_IN_YEAR < month || day < 1 || DAYS_IN_MONTH < day)
		throw ExamDetails::InvalidTimeException();
	if (!isTimeValid(time))
		throw ExamDetails::InvalidDateException();
	if (num_course<0 || exam_length<0)
		throw ExamDetails::InvalidArgsException();
}


std::string mtm::ExamDetails::getLink()
{
	return link_to_exam;
}

void mtm::ExamDetails::setLink(string new_link)
{
	link_to_exam = new_link;
}

int mtm::ExamDetails::operator-(const ExamDetails& exam) const
{
	return (month - exam.month) * DAYS_IN_MONTH + (day - exam.day);
}

bool mtm::ExamDetails::operator<(const ExamDetails& exam) const
{
	int days = *this - exam;
	return days > 0;
}

std::ostream& mtm::operator<<(std::ostream& os, const ExamDetails& exam)
{
	os<< "Course Number: " << exam.num_course<<endl;
	os<< "Time: " << exam.time<<endl;
	os<< "Duration: " << exam.timeToText(exam.exam_length)<<endl;
	os<< "Zoom Link: " << exam.link_to_exam<<endl;


}

mtm::ExamDetails mtm::ExamDetails::makeMatamExam()
{
	return mtm::ExamDetails(MTM_NUMBER_COURSE, MTM_EXAM_DAY, MTM_EXAM_MONTH, MTM_COURSE_TIME, MTM_EXAM_LENGTH,
							MTM_COURSE_LINK);
}