#pragma once

#include <vector>
#include <string>

class DataVector
{
private:
	// 0. Values:
	std::vector <double> data;
	std::string name;

public:
	// 1. Constructors:
	DataVector();
	DataVector(const std::vector <double>&);
	DataVector(const std::string&);
	DataVector(const char*);
	DataVector(const std::vector <double>&, const std::string&);
	DataVector(const std::vector <double>&, const char*);
	DataVector(const std::string&, const std::vector <double>&);
	DataVector(const char*, const std::vector <double>&);

	// 2. Destructor:
	~DataVector();

	// 3. Getters and setters:
	const std::string& getName();
	const std::vector <double>& getData();
	void setName(const std::string&);
	void setData(const std::vector <double>&);
	void setEmpty();

	// 4. Other methods:
	void Save(const std::string&, int = 6);
	const double& at(const unsigned int&);
	void push_back(const double&);
	const unsigned int& size();
};

