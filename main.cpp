#include<iostream>
#include<fstream>
#include<string>

class Adress
{
public:

	Adress(std::string adress, std::string street, std::string number_house, std::string number_apartment)
	{
		this->adress = adress;
		this->street = street;
		this->number_house = number_house;
		this->number_apartment = number_apartment;
	}

	std::string OutPutStr()
	{
		if (adress == "Не корректные данные в файле чтения.")
			return adress;
		return adress + ", " + street + ", " + number_house + ", " + number_apartment + ".";
	}

	std::string ReturnAdress()
	{
		return adress;
	}

	std::string ReturnStreet()
	{
		return street;
	}

	std::string ReturnNumberHouse()
	{
		return number_house;
	}

	std::string ReturnNumberApartment()
	{
		return number_apartment;
	}
	void Initalizator(std::string adress,std::string street,std::string number_house,std::string number_apartment)
	{
		this->adress = adress;
		this->street = street;
		this->number_house = number_house;
		this->number_apartment = number_apartment;
	}
	
private:
	std::string adress;
	std::string street;
	std::string number_house;
	std::string number_apartment;
};

void SortAdress(Adress* ptr, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			if (ptr[i].ReturnAdress() > ptr[j].ReturnAdress())
			{
				std::string adress = ptr[i].ReturnAdress();
				std::string street = ptr[i].ReturnStreet();
				std::string number_house = ptr[i].ReturnNumberHouse();
				std::string number_apartment = ptr[i].ReturnNumberApartment();
				ptr[i].Initalizator(ptr[j].ReturnAdress(), ptr[j].ReturnStreet(), ptr[j].ReturnNumberHouse(), ptr[j].ReturnNumberApartment());
				ptr[j].Initalizator(adress, street, number_house, number_apartment);
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	std::ifstream InFile("in.txt");
	if (!InFile.is_open())
	{
		return 0;
	}
	std::string str_size_struct;
	getline(InFile, str_size_struct);
	size_t size_struct = std::stoi(str_size_struct);

	//Adress* ptr_adress = new Adress[size_struct];

	Adress* ptr_adress = (Adress*)operator new(size_struct * sizeof(Adress));
	for (int i = 0; i < size_struct; ++i)
	{
		std::string adress;
		std::string street;
		std::string str_number_house;
		std::string str_number_apartment;

		getline(InFile, adress);
		getline(InFile, street);
		getline(InFile, str_number_house);
		getline(InFile, str_number_apartment);

		new (ptr_adress + i) Adress(adress, street, str_number_house, str_number_apartment);
		//ptr_adress[i].Initalizator(adress, street, str_number_house, str_number_apartment);
	}
	InFile.close();

	SortAdress(ptr_adress, size_struct);

	std::ofstream OutFile("out.txt");
	OutFile << str_size_struct << std::endl;
	for (int i = 0 ; i != size_struct; ++i)
	{
		OutFile << ptr_adress[i].OutPutStr() << std::endl;
	}
	OutFile.close();
	operator	delete(ptr_adress); 
}