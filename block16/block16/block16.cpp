#include "chat.h"

using namespace std;

int main()
{
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251);

	Chat chat;
	string userName, login, password, message;

	cout << "Добро пожаловать в чат.\nВыберите,что вы хотите сделать:" << endl;
	cout << "1.[Создать аккаунт] 2.[Войти в аккаунт] 3.[Отобразить всех пользователей] 4.[Выйти из чата]" << endl;

	char open;
	cin >> open;
	clearCin();

	cout << endl;

	while (open != '4')
	{
		switch (open)
		{
		case '1':
		{
			cout << "Введите имя: ";
			getline(cin, userName);
			while ((userName.empty()) || (userName[0] == ' ') || (userName[userName.size() - 1] == ' '))
			{
				cout << "Строка с именем не должна быть пустой и имя не должно начинатся или заканчиваться пробелом.\nПожалуйста, введите имя еще раз: ";
				getline(cin, userName);
			}

			cout << "Введите логин: ";
			getline(cin, login);
			while ((login.empty()) || (login[0] == ' ') || (login[login.size() - 1] == ' '))
			{
				cout << "Строка с логином не должна быть пустой и логин не должен начинатся или заканчиваться пробелом.\nПожалуйста, введите логин еще раз: ";
				getline(cin, login);
			}
			while (chat.checkLoginExist(login) == true)
			{
				cout << "Такой логин уже существует. Пожалуйста, придумайте другой логин: ";
				getline(cin, login);
				while (login.empty() || (login[0] == ' ') || (login[login.size() - 1] == ' '))
				{
					cout << "Строка с логином не должна быть пустой, начинаться и заканчиваться пробелом.\nПожалуйста, введите логин: ";
					getline(cin, login);
				}
			}
			cout << "Введите пароль: ";
			getline(cin, password);
			while (password.empty() || (password[0] == ' ') || (password[password.size() - 1] == ' '))
			{
				cout << "Строка с паролем не должна быть пустой, начинаться и заканчиваться пробелом.\nПожалуйста, введите пароль: ";
				getline(cin, password);
			}
			cout << endl;

			chat.registration(userName, login, password);

			cout << "Аккаунт успешно создан\n" << endl;

			break;
		}
		case '2':
		{
			cout << "Введите логин: ";
			getline(cin, login);
			cout << "Введите пароль: ";
			getline(cin, password);
			cout << endl;
			if (chat.checkUser(login, password) == true)
			{
				string nameOfCurrentUser = chat.GetNameByLogin(login);

				char choiceInsideCase2;
				cout << "Выберите действие:" << endl << "1.[Написать сообщение] 2.[Показать сообщение] 3.[Сменить пароль] 4.[Выйти из аккаунта]" << endl;
				cin >> choiceInsideCase2;
				clearCin();
				cout << endl;

				while (choiceInsideCase2 != '4')
				{
					switch (choiceInsideCase2)
					{
					case '1':
					{
						cout << "Кому вы хотите написать сообщение:\n1.[Определенному пользователю] 2.[Групповое сообщение] 3.[Вернутся назад]" << endl;
						char choiceInsideCase2InsideCase1;
						cin >> choiceInsideCase2InsideCase1;
						cout << endl;
						clearCin();

						while (choiceInsideCase2InsideCase1 != '3')
						{
							switch (choiceInsideCase2InsideCase1)
							{
							case '1': // сообщение пользователю
							{
								cout << "Пользователи:" << endl;
								chat.printAllUsersExceptCurrent(chat.GetLoginByUserName(nameOfCurrentUser));

								cout << endl;

								cout << "Введите логин пользователя кому хотите написать сообщение: ";
								getline(cin, login);
								if (chat.checkLoginExist(login) == true)
								{
									cout << "Введите сообщение: ";
									getline(cin, message);
									while (message.empty())
									{
										cout << "Сообщение не отправлено(отсутсвует текст). Введите сообщение: ";
										getline(cin, message);
									}
									message = "У вас сообщение от пользователя " + nameOfCurrentUser + " " + "(" + login + ")" + ": " + '\"' + message + '\"';
									chat.sendMessage(login, message);
									cout << "Сообщение успешно отправлено!" << endl;
								}

								break;
							}
							case '2': // групповое сообщение
							{
								cout << "Введите сообщение: ";
								getline(cin, message);
								while (message.empty())
								{
									cout << "Сообщение не отправлено(отсутсвует текст). Введите сообщение: ";
									getline(cin, message);
								}
								message = "У вас групповое сообщение от пользователя " + nameOfCurrentUser + " " + "(" + chat.GetLoginByUserName(nameOfCurrentUser) + ")" + ": " + '\"' + message + '\"';
								chat.sendMessageToAllUsersExceptCurrent(chat.GetLoginByUserName(nameOfCurrentUser), message);
								cout << "Сообщение успешно отправлено!" << endl;

								break;
							}
							default:
							{
								cout << "Неверное значение\n" << endl;

								break;
							}
							}
							cout << endl;
							cout << "Кому вы хотите написать сообщение:\n1.[Определенному пользователю] 2.[Групповое сообщение] 3.[Вернутся назад]" << endl;
							cin >> choiceInsideCase2InsideCase1;
							cout << endl;
							clearCin();
						};

						break;
					}
					case '2':
					{
						chat.print(login);
						system("pause>0"); // Ставит программу на паузу, чтобы пользователь прочитал сообщение

						break;
					}
					case '3': //Смена пароля на новый
					{
						string newpassword;
						cout << "Введите старый пароль: ";
						getline(cin, password);
						while (chat.checkPassByName(nameOfCurrentUser, password) == false)
						{
							cout << "Пароль неверный\nВведите старый пароль: ";
							getline(cin, password);
						}
						cout << "Введите новый пароль: ";
						getline(cin, newpassword);
						while (newpassword.empty() || (newpassword[0] == ' ') || (newpassword[newpassword.size() - 1] == ' '))
						{
							cout << "Строка с паролем не должна быть пустой, начинаться и заканчиваться пробелом.\nПожалуйста, введите пароль: ";
							getline(cin, newpassword);
						}
						while (newpassword == password)
						{
							cout << "Это ваш старый пароль! Придумайте другой пароль: ";
							getline(cin, newpassword);
							while (newpassword.empty() || (newpassword[0] == ' ') || (newpassword[newpassword.size() - 1] == ' '))
							{
								cout << "Строка с паролем не должна быть пустой, начинаться и заканчиваться пробелом.\nПожалуйста, введите пароль: ";
								getline(cin, newpassword);
							}
						}
						chat.SetNewPassByName(nameOfCurrentUser, newpassword);
						cout << "Пароль успешно изменен!\n" << endl;

						break;
					}
					default:
					{
						cout << "Неверное значение\n" << endl;

						break;
					}
					}

					cout << "Выберите действие:\n1.[Написать сообщение] 2.[Показать сообщение] 3.[Сменить пароль] 4.[Выйти из аккаунта]" << endl;
					cin >> choiceInsideCase2;
					clearCin();

					cout << endl;
				};

				cout << endl;

				break;
			}
			else
			{
				cout << "Неверный логин или пароль\n" << endl;
				break;
			}
			break;
		}
		case '3':
		{
			chat.showAllUsers();
			cout << endl;

			break;
		}
		default:
		{
			cout << "Неверное значение\n" << endl;

			break;
		};
		}
		cout << "1.[Создать аккаунт] 2.[Войти в аккаунт] 3.[Отобразить всех пользователей] 4.[Выйти из чата]" << endl;

		cin >> open;
		clearCin();
		cout << endl;
	}

	return 0;
}