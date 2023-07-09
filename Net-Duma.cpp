#include <iostream>
#include "NameSpace.h"

std::shared_ptr<Person> readPerson(void)
{
    std::string firstName;
    std::string otherNames;
    std::string emailAddress;
    std::string phoneNumbers;
    std::string street;
    std::string town;
    std::string country;

    std::cout << "Insert first name" << std::endl;
    std::cin >> firstName;

    std::cout << "Insert other names" << std::endl;
    std::cin >> otherNames;

    std::cout << "Insert emailAddress" << std::endl;
    std::cin >> emailAddress;

    std::cout << "Insert phone number" << std::endl;
    std::cin >> phoneNumbers;
    for (const auto& c : phoneNumbers)
    {
        if (!isdigit(c))
        {
            std::cerr << "Incorrect format" << std::endl;
            return nullptr;
        }
    }

    std::cout << "Insert street" << std::endl;
    std::cin >> street;

    std::cout << "Insert town" << std::endl;
    std::cin >> town;

    std::cout << "Insert country" << std::endl;
    std::cin >> country;

    return std::make_shared<Person>(firstName, otherNames, emailAddress, phoneNumbers, street, town, country);
}

std::shared_ptr<Person> searchPerson(NameSpace& ns)
{
    std::string name;
    char option;

    std::cout << "Enter search by\n 1) First name \n 2) Other names \n 3) Email Address \n 4) Phone number \n 5) Town \n 6) Country" << std::endl;
    std::cin >> option;

    std::cout << "Enter name by search" << std::endl;
    std::cin >> name;

    NameSpace::SearchType searchType; 
    switch (option)
    {
    case '1': 
        searchType = NameSpace::SearchType::FIRST_NAME;
        break;
    case '2':
        searchType = NameSpace::SearchType::OTHER_NAMES;
        break;
    case '3':
        searchType = NameSpace::SearchType::EMAIL;
        break;
    case '4':
        searchType = NameSpace::SearchType::TELEPHONE;
        break;
    case '5':
        searchType = NameSpace::SearchType::TOWN;
        break;
    case '6':
        searchType = NameSpace::SearchType::COUNTRY;
        break;
    default:
        return nullptr;
    }

    std::vector<std::shared_ptr<Person>> vpPerson = ns.searchByName(name, searchType);
    for (const auto& p : vpPerson)
    {
        std::cout << *p << std::endl;
    }
    if (vpPerson.size() == 0)
    {
        return nullptr;
    }
    else
    {
        return vpPerson[0];
    }
}

int main()
{
    NameSpace ns;
    bool end = false;
    std::shared_ptr<Person> pPerson = nullptr;
    ns.readNameSpace();
    ns.printPersons();

    while (!end)
    {
        char option = 4;
        std::cout << "Enter option: \n 1) Add Person\n 2) Remove (searched) person\n 3) Search Person\n 4) Print all namespace\n 5) Stop program\n";
        std::cin >> option;
        
        switch (option) {
        case '1':
            pPerson = readPerson();
            ns.addPerson(pPerson);
            break;
        case '2':
            ns.removePerson(pPerson);
            break;
        case '3':
            pPerson = searchPerson(ns);
            break;
        case '4':
            ns.printPersons();
            break;
        case '5':
            end = true;
            break;
        default:
            break;
        }
    }
    ns.saveNameSpace();
}
