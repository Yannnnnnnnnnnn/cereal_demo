#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//cereal
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>

class USER_ACCOUNT
{
public:
	string name_;
	int year_;
	int ID_;

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(	cereal::make_nvp("name", name_),
			cereal::make_nvp("year", year_),
			cereal::make_nvp("ID", ID_) );
	}
};

class SYSTEM
{
private:
	bool system_status_;

private:
	std::string user_data_file_;
	std::vector<USER_ACCOUNT> user_data_;

public:
	SYSTEM();
	~SYSTEM();
	void initSystem();
	void chooseOperations();
	bool systemStatus();
	
private:
	bool loadData();
	bool saveData();
	void showData();
	void addData();
	void exitSystem();

};

SYSTEM::SYSTEM()
{
	system_status_ = true;
	user_data_file_ = "data.json";
	user_data_.clear();

	initSystem();
}

SYSTEM::~SYSTEM()
{
	user_data_file_ = "data.json";
	user_data_.clear();
}

void SYSTEM::initSystem()
{
	cout << "Init System..." << endl;

	//check "data.json" exist or not
	std::fstream data_test;
	data_test.open(user_data_file_);
	if (!data_test)
	{
		cout << "**********************************************************************" << endl;
		cout << "There is no data in the system." << endl;
		cout << "The system will build an empty database." << endl;
		saveData();
	}
	else
	{
		cout << "**********************************************************************" << endl;
		cout << "Loading data into the system..." << endl;
		loadData();
	}
}

void SYSTEM::chooseOperations()
{
	cout << "**********************************************************************" << endl;
	cout << "choose an operation..." << endl;
	cout << "0:show data\t1:add data\t2:leave" << endl;
	int index;
	cin >> index;
	switch (index)
	{
	case 0:
		showData();
		break;
	case 1:
		addData();
		break;
	case 2:
		exitSystem();
		break;
	default:
		cout << "Unknown instructions" << endl;
		break;
	}
}

bool SYSTEM::systemStatus()
{
	return system_status_;
}

bool SYSTEM::loadData()
{
	std::ifstream os(user_data_file_);
	cereal::JSONInputArchive archive(os);
	archive(cereal::make_nvp("user", user_data_));

	return true;
}

bool SYSTEM::saveData()
{
	std::ofstream os(user_data_file_);
	cereal::JSONOutputArchive archive(os);
	archive(cereal::make_nvp("user", user_data_));
	
	return true;
}

void SYSTEM::showData()
{
	system_status_ = true;
	cout << "**********************************************************************" << endl;
	cout << "There are " << user_data_.size() << " in the system." << endl;

	for (size_t i = 0; i < user_data_.size(); i++)
	{
		cout << (i + 1) << "\t name:" << user_data_[i].name_ << "\t year:" << user_data_[i].year_ << "\t ID:" << user_data_[i].ID_ << endl;
	}


}

void SYSTEM::addData()
{
	system_status_ = true;

	cout << "**********************************************************************" << endl;

	USER_ACCOUNT user_data_temp;
	cout << "Please input the user name(must be string):";
	cin >> user_data_temp.name_;

	cout << "Please input the user year(must be int):";
	cin >> user_data_temp.year_;

	cout << "Please input the user ID(must be int):";
	cin >> user_data_temp.ID_;

	user_data_.push_back(user_data_temp);
}

void SYSTEM::exitSystem()
{
	system_status_ = false;
	cout << "**********************************************************************" << endl;
	cout << "Closing System..." << endl;
	cout << "Saving data into System." << endl;
	saveData();
	cout << "Finishing saving data." << endl;
}

int main()
{
	SYSTEM system;
	while (system.systemStatus())
	{
		system.chooseOperations();
	}

	return 0;
}