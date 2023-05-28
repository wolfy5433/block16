#include "chat.h"

using namespace std;

Chat::Chat()
{

}

Chat::~Chat()
{
	users.clear();
	users.shrink_to_fit();
}

bool Chat::isEqualName(const User& currentUser, string& userName)
{
	if (currentUser.GetUserNameW().compare(userName) == 0)
	{
		return true;
	}
	return false;
}
bool Chat::isEqualPass(const User& currentUser, uint*& sha1_password)
{
	if (*currentUser.GetSha1Pass() == *sha1_password)
	{
		return true;
	}
	return false;
}
bool Chat::isEqualLogin(const User& currentUser, string& login)
{
	if (currentUser.GetLogin().compare(login) == 0) //  возвращает 0, если они равны!
	{
		return true;
	}
	return false;
}

void Chat::addUser(const User& newUser)
{
	users.push_back(newUser);
}

void Chat::addMessage(User& currentUser, string& message)
{
	currentUser._messages.push_back(message);
}

void Chat::SetNewPass(User& currentUser, uint*& newPassword)
{
	currentUser._authData.second = newPassword;
}

void Chat::printAllMessages(const User& currentUser)
{
	for (string msg : currentUser._messages)
	{
		cout << msg << endl;
	}
	cout << endl;
}

void Chat::registration(string userName, string login, string password)
{
	User newUser;
	newUser._userName = userName;
	uint* sha1_password = sha1(const_cast<char*>(password.c_str()), password.length());
	newUser._authData = make_pair(login, sha1_password);
	addUser(newUser);
}

void Chat::sendMessage(string login, string message)
{
	for (vector<User>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (isEqualLogin(*it, login) == true)
		{
			addMessage(*it, message);
			break;
		}
	}
}

bool Chat::checkUser(string login, string password)
{
	uint* sha1_password = sha1(const_cast<char*>(password.c_str()), password.length());
	for (vector<User>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (isEqualLogin(*it, login) == true && isEqualPass(*it, sha1_password) == true)
		{
			return true;
		}
	}
	return false;
}

bool Chat::checkUserByName(string& userName)
{
	for (vector<User>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (isEqualName(*it, userName) == true)
		{
			return true;
		}
	}
	return false;
}

bool Chat::checkPassByName(string& userName, string& password)
{
	uint* sha1_password = sha1(const_cast<char*>(password.c_str()), password.length());
	for (vector<User>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (isEqualPass(*it, sha1_password) == true)
		{
			return true;
		}
	}
	return false;
}

bool Chat::checkLoginExist(string& login)
{
	for (vector<User>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (isEqualLogin(*it, login))
		{
			return true;
		}
	}
	return false;
}

string Chat::GetLoginByUserName(string userName)
{
	User currentUser;
	for (vector<User>::iterator it = users.begin(); it != users.end(); ++it)
	{
		currentUser = *it;
		if ((currentUser.GetUserNameW().compare(userName) == 0))
		{
			return currentUser.GetLogin();
		}
	}
}

string Chat::GetNameByLogin(string login)
{
	User currentUser;
	for (vector<User>::iterator it = users.begin(); it != users.end(); ++it)
	{
		currentUser = *it;
		if (currentUser.GetLogin().compare(login) == 0)
		{
			return currentUser.GetUserNameW();
		}
	}
}

void Chat::SetNewPassByName(string& userName, string& newPassword)
{
	uint* sha1_newPassword = sha1(const_cast<char*>(newPassword.c_str()), newPassword.length());
	for (vector<User>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (isEqualName(*it, userName) == true)
		{
			SetNewPass(*it, sha1_newPassword);
		}
	}
}

void Chat::sendMessageToAllUsersExceptCurrent(string login, string& message)
{
	User currentUser;
	for (vector<User>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (isEqualLogin(*it, login) == true)
		{
			continue;
		}
		else
		{
			currentUser = *it;
			sendMessage(currentUser.GetLogin(), message);
		}
	}
}

void Chat::printAllUsersExceptCurrent(string login)
{
	User currentUser;
	for (vector<User>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (isEqualLogin(*it, login) == true)
		{
			continue;
		}
		else
		{
			currentUser = *it;
			cout << "Логин: " << currentUser.GetLogin() << " (Имя пользователя: " << currentUser.GetUserNameW() << ")" << endl;
		}
	}
}

void Chat::showAllUsers()
{
	if (!users.empty())
	{
		User currentUser;
		for (vector<User>::iterator it = users.begin(); it != users.end(); ++it)
		{
			currentUser = *it;
			cout << "-------" << endl;
			cout << "Имя: " << currentUser.GetUserNameW() << "\nЛогин: " << currentUser.GetLogin() << endl;
		}
		cout << "-------" << endl;
	}
	else
	{
		cout << "Не создано ещё ниодного аккаунта" << endl;
	}
}


void Chat::print(string login)
{
	for (vector<User>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (isEqualLogin(*it, login) == true)
		{
			printAllMessages(*it);
			break;
		}
	}
}

void clearCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
}