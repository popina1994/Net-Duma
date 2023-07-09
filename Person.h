#pragma once
#include <string>
#include <vector>
#include "Address.h"
#include <iostream>
#include <sstream>

struct Person
{
	std::string m_firstName;
	std::string m_otherNames;
	std::string m_emailAddress;
	std::string m_phoneNumber;
	Address m_address;

	std::string m_street;
	std::string m_town;
	std::string m_country;
	Person()
	{

	}

	Person(const std::string& firstName, const std::string& otherNames,
		const std::string& emailAddress, const std::string& phoneNumber,
		const std::string& street, const std::string& town, const std::string& country):
		m_firstName(firstName), m_otherNames(otherNames), m_emailAddress(emailAddress),
		m_phoneNumber(phoneNumber), m_address(street, town, country)
	{
	}

	friend std::ostream& operator<<(std::ostream& out, const Person& p)
	{
		out << p.m_firstName << " " << p.m_otherNames << " " << p.m_emailAddress << " " << p.m_phoneNumber << " " << p.m_address;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Person& p)
	{
		in >> p.m_firstName >> p.m_otherNames >> p.m_emailAddress >> p.m_phoneNumber >> p.m_address;
		return in;
	}


};

