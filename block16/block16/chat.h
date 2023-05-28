#pragma once
#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include "Sha1.h" 

using namespace std;

class Chat
{
private:
	struct User
	{
		string _userName;
		pair<string, uint*> _authData;
		list<string> _messages;

		User() : _userName("")
		{

		}
		~User()
		{

		}
		string GetLogin() const
		{
			return _authData.first;
		}
		string GetUserName() const
		{
			return _userName;
		}
		uint* GetSha1Pass() const
		{
			return _authData.second;
		}
	};
	vector<User> users;
	bool isEqualName(const User& currentUser, string& userName);
	bool isEqualLogin(const User& currentUser, string& login);
	bool isEqualPass(const User& currentUser, uint*& sha1_password);
	void addUser(const User& newUser);
	void addMessage(User& currentUser, string& message);
	void SetNewPass(User& currentUser, uint*& newPassword);
	void printAllMessages(const User& currentUser);

public:
	Chat();
	~Chat();
	void registration(string userName, string login, string password);
	void sendMessage(string login, string message);
	bool checkUser(string login, string password);
	bool checkUserByName(string& userName);
	bool checkPassByName(string& userName, string& password);
	bool checkLoginExist(string& login);
	string GetLoginByUserName(string userName);
	string GetNameByLogin(string login);
	void SetNewPassByName(string& userName, string& newPassword);
	void sendMessageToAllUsersExceptCurrent(string login, string& message);
	void printAllUsersExceptCurrent(string login);
	void showAllUsers();
	void print(string login);
};
void clearCin();