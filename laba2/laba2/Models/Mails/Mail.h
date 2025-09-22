#pragma once
#include <string>


class Mail {
public:
	std::string sender;
	std::string destination;
	std::string body;
	std::string date;

	void get_mails();
	void send_mail();
	void PrintInfo();
};
