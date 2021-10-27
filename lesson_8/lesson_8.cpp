#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <gtest/gtest.h>



struct Person
{
private:
    std::string m_Fistname;
    std::string m_Name;
    std::string m_Patronymic;
public:
    Person(std::string Firstname, std::string Name, std::string Patronymic) : m_Fistname(Firstname), m_Name(Name), m_Patronymic(Patronymic)
    {

    }

    Person(std::string Firstname, std::string Name) : m_Fistname(Firstname), m_Name(Name), m_Patronymic("")
    {

    }

    void print_person() const
    {
        std::cout << m_Fistname << '\t' << m_Name << '\t' << m_Patronymic << '\t';
    }

    std::string GetFirstName() const
    {
        return m_Fistname;
    }

    std::string GetName() const
    {
        return m_Name;
    }

    std::string GetPatronimic() const
    {
        return m_Patronymic;
    }



    ~Person()
    {

    }

};



struct PhoneNumber
{
private:
    size_t m_country_code;
    size_t m_city_code;
    size_t m_phone_number;
    size_t m_adition_number;

public:
    PhoneNumber(size_t con_code, size_t city_code, size_t p_num, size_t add_num) :
        m_country_code(con_code), m_city_code(city_code), m_phone_number(p_num), m_adition_number(add_num)
    {

    }

    PhoneNumber(size_t con_code, size_t city_code, size_t p_num) :
        m_country_code(con_code), m_city_code(city_code), m_phone_number(p_num), m_adition_number(0)
    {

    }

    void print_number() const
    {
        if (m_adition_number)
        {
            std::cout << "\t+" << m_country_code << " (" << m_city_code << ") " << m_phone_number << " " << m_adition_number << "\n";
        }
        else
        {
            std::cout << "\t+" << m_country_code << " (" << m_city_code << ") " << m_phone_number << "\n";
        }
    }

    void ChangeNumber(size_t con_code, size_t city_code, size_t p_num, size_t add_num = 0)
    {
        m_country_code = con_code;
        m_city_code = city_code;
        m_phone_number = p_num;
        m_adition_number = add_num;

    }

    ~PhoneNumber()
    {

    }
};

class PhoneBook
{
private:

    std::vector<std::pair<Person, PhoneNumber>> PBook;

public:
    PhoneBook(std::string path)
    {
        std::ifstream phone_book(path);

        if (!phone_book.is_open())
        {
            std::cout << "ERROR: File isn't found!" << std::endl;
        }

        std::string first_name;
        std::string name;
        std::string patronymic;
        std::string country_code;
        std::string city_code;
        std::string number;
        std::string add_number;

        while (phone_book.good())
        {
            std::getline(phone_book, first_name, ',');
            std::getline(phone_book, name, ',');
            std::getline(phone_book, patronymic, ',');
            std::getline(phone_book, country_code, ',');
            std::getline(phone_book, city_code, ',');
            std::getline(phone_book, number, ',');
            std::getline(phone_book, add_number, '\n');

           
            Person person(first_name, name, patronymic);

            int co_code = std::stoi(country_code);
            int ci_code = std::stoi(city_code);
            int num = std::stoi(number);
            int add_num = 0;
            if (add_number != "")
            {
                add_num = std::stoi(add_number);
            }


            PhoneNumber p_number(co_code, ci_code, num, add_num);


            

            std::pair<Person, PhoneNumber> pair1(person, p_number);

          

            PBook.push_back(pair1);

        }
        phone_book.close();
    }

    void printPhonebook()const
    {
        for (auto i : PBook)
        {
            i.first.print_person();
            i.second.print_number();
        }
    }

    void SortByName()
    {
        std::sort(PBook.begin(), PBook.end(), [](std::pair<Person, PhoneNumber> pair1, std::pair<Person, PhoneNumber> pair2)
            {return pair1.first.GetFirstName() < pair2.first.GetFirstName(); });



    }

    void GetPhoneNumber(std::string Firstname) const
    {
        int one_person = 0;
        for (auto i : PBook)
        {
            if (Firstname == i.first.GetFirstName())
            {
                i.first.print_person();
                i.second.print_number();
                one_person++;
            }
        }
        if (one_person == 0)
        {
            std::cout << "Not found!" << std::endl;
        }
        else if (one_person > 1)
        {
            std::cout << "Found more than 1 person";
        }

    }

    std::string get_name(std::string Firstname) const
    {
        for (auto i : PBook)
        {
            if (Firstname == i.first.GetFirstName())
            {
              //  i.first.print_person();
                return i.first.GetFirstName();
                
            }
        }
    }



    void ChangePhoneNumber(size_t country_code, size_t city_code, size_t number, size_t add_number, std::string FirstName, std::string Name, std::string Patronimic = "")
    {
        for (auto i : PBook)
        {
            if ((i.first.GetFirstName() == FirstName) && (i.first.GetName() == Name) && (i.first.GetPatronimic() == Patronimic))
            {
                std::cout << "Previous number: ";
                i.second.print_number();
                std::cout << "Changes number: ";
                i.second.ChangeNumber(country_code, city_code, number, add_number);
                i.second.print_number();
            }
        }
    }

    ~PhoneBook()
    {

    }
};

TEST(coincidence, first_mane)
{
    std::string f_m = "sidorov";
    PhoneBook pb("phones.csv"); 
    //pb.GetPhoneNumber(f_m);
    ASSERT_EQ(f_m , pb.get_name("Solovev"));
}

int main(int argc, char* argv[])
{

    PhoneBook pb("phones.csv");

    pb.printPhonebook();

    std::cout << std::endl;

    pb.SortByName();

    pb.printPhonebook();

    std::cout << std::endl;

    pb.GetPhoneNumber("Solovev");

    std::cout << std::endl;

    pb.ChangePhoneNumber(453, 332, 6788983, 0, "Makeev", "Marat");

    std::cout << std::endl;
    std::cout << std::endl;

    //std::cout << pb.get_name("Solovev") << std::endl;

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}