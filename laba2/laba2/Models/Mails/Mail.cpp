#include "Mail.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;

void Mail::get_mails() {
	string file = "Mail.txt";
	//string file;
	//cout << "Enter filename to get mail from: ";
	//getline(cin, file);
	ifstream filein(file);
	if (!filein.is_open()) {
		cout << "Failed to open the file." << endl;
		return;
	}
	getline(filein, Mail::sender);
	getline(filein, Mail::destination);
	getline(filein, Mail::body);
	getline(filein, Mail::date);

	filein.close();
}

void Mail::send_mail() {
	//string file;
	//cout << "Enter filename to get mail from: ";
	//getline(cin, file);
	string file = "Mail.txt";
	ofstream fileout(file);
	if (!fileout.is_open()) {
		cout << "Failed to open the file." << endl;
		return;
	}
	string tmp;
	cout << "Enter sender name: ";
	getline(cin, tmp);
	fileout << tmp << endl;

	cout << "Enter destination: ";
	getline(cin, tmp);
	fileout << tmp << endl;

	cout << "Write your mail: ";
	getline(cin, tmp);
	fileout << tmp << endl;

	auto now = chrono::system_clock::now();
	time_t t = chrono::system_clock::to_time_t(now);
	fileout << t << endl;
}

void Mail::PrintInfo() {
	cout << "From: " << sender << endl;
	cout << "To: " << destination << endl;
	cout << "Body: " << body << endl;
	cout << "Date: " << date << endl;
	cout << "----------------------" << endl;
}
