// GetCommandOut.cpp : This file contains the 'main' function. Program execution begins and ends there.
// not bidirectional, only executes command and returns input.

#include "pch.h"
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
using namespace std;

std::string exec(const char* cmd) {
	char buffer[128];
	std::string result = "";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe) throw std::runtime_error("popen() failed!");
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	}
	catch (...) {
		_pclose(pipe);
		throw;
	}
	_pclose(pipe);
	return result;
}

int main()
{
	char command[1024] = { 0 };
	while (1) {
		cin >> command;
		if (strcmp(command, "quit") == 0)
			break;
		std::string out = exec(command);
		std::cout << out << endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
