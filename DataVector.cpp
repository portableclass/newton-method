#include "DataVector.h"

#include <iomanip>
#include <fstream>

// 1. Constructiors:
DataVector::DataVector() : name("defult data") {}

DataVector::DataVector(const std::vector <double>& data) : DataVector() // ����� ������������ �� ���������
{
	this->data = data; // ������������� ������ ������������
}
DataVector::DataVector(const std::string& name) : name(name) {}
DataVector::DataVector(const char* name) : name(name) {}

DataVector::DataVector(const std::vector <double>& data, const std::string& name) : data(data), name(name) {} //��������� ����������� � ������ ���� vector � string
DataVector::DataVector(const std::vector <double>& data, const char* name) : data(data), name(name) {} //��������� ����������� � ������ ���� vector � char ������

DataVector::DataVector(const std::string& name, const std::vector <double>& data) : DataVector(data, name){} // ������������� ������������ ������������� (�������������)
DataVector::DataVector(const char* name, const std::vector <double>& data) : DataVector(data, name) {}

// 2. Destructor:
DataVector::~DataVector()
{
	data.clear();
	data.shrink_to_fit();
	name.clear();
	name.shrink_to_fit();
}

// 3. Geters and seters:
const std::string& DataVector::getName()
{
	return name;
};
const std::vector <double>& DataVector::getData()
{
	return data;
};
void  DataVector::setName(const std::string& name)
{
	this->name = name;
};
void  DataVector::setData(const std::vector <double>& data)
{
	this->data = data;
};
void DataVector::setEmpty()
{
	data = std::vector <double>();
};

// 4. Other methods:
void DataVector::Save(const std::string& way, const int FractionalPart)
{
	// The type conversion is there: 
	const char* way_c = way.c_str();

	// The object adds:
	std::ofstream outf;

	// The file opens:
	outf.open(way_c, std::ios::app);

	if (outf.is_open())
	{
		// The name output is there:
		outf << name << std::endl;

		// The values output is there:
		for (double i : data)
		{
			outf << std::setprecision(FractionalPart - 1) << std::scientific << i << std::endl; // std::scientific sets format an output as X.XXX...XeSXX; std::setprecision() sets the length of the mantissa
		}
	}
};
const double& DataVector::at(const unsigned int& iter)
{
	return data.at(iter);
};
void DataVector::push_back(const double& value)
{
	data.push_back(value);
};
const unsigned int& DataVector::size() 
{
	return data.size();
}