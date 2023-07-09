#pragma once
#include <string>
#include <iostream>
class Address
{
public:
	std::string m_street;
	std::string m_town;
	std::string m_country;

	Address()
	{

	}
	Address(const std::string& street, const std::string& town, const std::string& country)
	: m_street(street), m_town(town), m_country(country) {

	}

	friend std::ostream& operator<<(std::ostream& out, const Address& a)
	{
		out << a.m_street << " " << a.m_town<< " " << a.m_country;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Address& a)
	{
		in >> a.m_street >> a.m_town >> a.m_country;
		return in;
	}

};

