#pragma once
#include "Person.h"
#include <memory>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <fstream>

class NameSpace
{
	std::unordered_set<std::shared_ptr<Person>> m_hsPtsPerson;
	std::unordered_multimap <std::string, std::shared_ptr<Person >> m_htFirstName;
	std::unordered_multimap <std::string, std::shared_ptr<Person >> m_htOtherNames;
	std::unordered_multimap <std::string, std::shared_ptr<Person >> m_htEmail;
	std::unordered_multimap <std::string, std::shared_ptr<Person >> m_htTelephone;
	std::unordered_multimap <std::string, std::shared_ptr<Person >> m_htTown;
	std::unordered_multimap <std::string, std::shared_ptr<Person >> m_htCountry;
	
	const std::string NS_NAME = "Namespace.csv";

	void insert(std::unordered_multimap <std::string, std::shared_ptr<Person >>& ht,
		const std::string& name,
		std::shared_ptr<Person> pPerson)
	{
		ht.insert(std::pair<std::string, std::shared_ptr<Person>>(name, pPerson));
	}

	void eraseIt(std::unordered_multimap <std::string, std::shared_ptr<Person >>& ht,
		const std::string& name,
		const std::shared_ptr<Person>& pPerson)
	{
		auto range = ht.equal_range(name);
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second == pPerson)
			{
				ht.erase(it);
				return;
			}
		}
	}

public:
	enum class SearchType
	{
		FIRST_NAME,
		OTHER_NAMES,
		EMAIL,
		TELEPHONE,
		TOWN,
		COUNTRY
	};
	NameSpace()
	{
	}


	void addPerson(const std::shared_ptr<Person>& pPerson)
	{
		if (pPerson == nullptr)
		{
			std::cerr << "Addition unsuccessful" << std::endl;
			return;
		}
		m_hsPtsPerson.insert(pPerson);
		insert(m_htFirstName, pPerson->m_firstName, pPerson);
		insert(m_htOtherNames, pPerson->m_otherNames, pPerson);
		insert(m_htEmail, pPerson->m_emailAddress, pPerson);
		insert(m_htTelephone, pPerson->m_phoneNumber, pPerson);
		insert(m_htTown, pPerson->m_address.m_town, pPerson);
		insert(m_htCountry, pPerson->m_address.m_country, pPerson);
	}

	/**
	* Removes person from the namespace including indices used for faster search. 
	*/
	void removePerson(const std::shared_ptr<Person>& pPerson)
	{
		if (pPerson == nullptr)
		{
			std::cerr << "Invalid person" << std::endl;
			return;
		}
		m_hsPtsPerson.erase(pPerson);

		std::pair<
			std::unordered_multimap <std::string, std::shared_ptr<Person >>::const_iterator,
			std::unordered_multimap <std::string, std::shared_ptr<Person >>::const_iterator> range;

		eraseIt(m_htFirstName, pPerson->m_firstName, pPerson);
		eraseIt(m_htOtherNames, pPerson->m_otherNames, pPerson);
		eraseIt(m_htEmail, pPerson->m_emailAddress, pPerson);
		eraseIt(m_htTelephone, pPerson->m_phoneNumber, pPerson);
		eraseIt(m_htTown, pPerson->m_address.m_town, pPerson);
		eraseIt(m_htCountry, pPerson->m_address.m_country, pPerson);
	}

	const std::vector<std::shared_ptr<Person>> 
	searchByName(const std::string& name, const SearchType& searchType) const
	{
		std::vector<std::shared_ptr<Person>> vOuts;
		std::pair<
			std::unordered_multimap <std::string, std::shared_ptr<Person >>::const_iterator, 
			std::unordered_multimap <std::string, std::shared_ptr<Person >>::const_iterator> range;

		switch (searchType) {
			case SearchType::FIRST_NAME:
				range = m_htFirstName.equal_range(name);
				break;
			case SearchType::OTHER_NAMES:
				range = m_htOtherNames.equal_range(name);
				break;
			case SearchType::EMAIL:
				range = m_htEmail.equal_range(name);
				break;
			case SearchType::TELEPHONE:
				range = m_htTelephone.equal_range(name);
				break;
			case SearchType::TOWN:
				range = m_htTown.equal_range(name);
				break;
			case SearchType::COUNTRY:
				range = m_htCountry.equal_range(name);
				break;
			default: 
				std::cerr << "Search incorrect" << std::endl; 
		}
		for (auto it = range.first; it != range.second; ++it) {
			vOuts.push_back(it->second);
		}
		return vOuts;
	}
	friend std::ostream& operator<<(std::ostream& out, const NameSpace& ns)
	{
		for (const auto& pPerson : ns.m_hsPtsPerson)
		{
			out << *pPerson << std::endl;
		}
		return out;
	}
	void printPersons()
	{
		std::cout << "Ouptputing all persons" << std::endl;
		std::cout << *this;
	}

	void saveNameSpace(void)
	{
		std::ofstream fOut(NS_NAME);
		fOut << *this;
	}

	void readNameSpace()
	{
		std::ifstream fIn(NS_NAME);
		std::shared_ptr<Person> pPerson = std::make_shared<Person>();
		while (fIn >> (*pPerson))
		{
			addPerson(pPerson);
			pPerson = std::make_shared<Person>();
		}
	}
};

