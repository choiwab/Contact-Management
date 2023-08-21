#include<sstream>
//=================================================================================
#include<cstdlib>
#include<iostream>
#include<string>
#include<fstream>
#include<exception>
#include<iomanip>
#include<cctype>
#include <regex>
#include "myvector.h"
#include "contact.h"
#include "contactbst.h"

//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"update <key>       :Update a contact's details"<<endl
		<<"remove <key>       :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markFav <key>      :Mark as favourite"<<endl
		<<"unmarkFav <key>    :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printFav           :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================

// to be completed with ALL the necessary method definitions

//==========================================================
int main(void)
{
	ContactBST bst;

	listCommands();
	string user_input;
	string command;
	string parameter;

	do{
		cout<<">";
		getline(cin,user_input);

		stringstream sstr(user_input);
		getline(sstr,command,' '); 
		getline(sstr,parameter);										//call valid method for input

		if(command =="import") 		
			{
				cout << bst.importCSV(parameter) << " records have been imported" << endl;				
			}
		else if(command == "export")    
		{
			ofstream fout;
			fout.open(parameter, ios::out);
			cout << bst.exportCSV(bst.getRoot(), fout) << " records have been exported" << endl;
		}
		else if(command == "add")		
			{
				char favchoice;
				bool isfav;
				string fname, lname, email, phone, city, country, key;
				cout << "Please enter the details of the contact : "<< endl;

				regex name_regex("^[a-zA-Z]+$");									//check if input is valid
				do{
					cout << "First name : ";
					cin >> fname;
					if (!regex_match(fname, name_regex)) 
					{
			       		cout << "invalid input" << endl;
			  		}

				}while(!regex_match(fname, name_regex));

				do{
					cout << "Last name : ";
					cin >> lname;
					if (!regex_match(lname, name_regex)) 
					{
			       		cout << "invalid input" << endl;
			  		}

				}while(!regex_match(lname, name_regex));
				
				regex email_regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
				do{
					cout << "Email : ";
					cin >> email;

					if (!regex_match(email, email_regex))
					{
			       		cout << "invalid input" << endl;
			  		}

				}while(!regex_match(email, email_regex));


				regex phone_regex("^(\\+)?[0-9]+$");

					do{
						cout << "Phone : ";
						cin >> phone;

					if (!regex_match(phone, phone_regex))
					{
			       		cout << "invalid input" << endl;
			  		}

				}while(!regex_match(phone, phone_regex));

				regex c_regex("^[a-zA-Z- ]+$");

				do{
						cout << "City : ";
						cin >> city;

					if (!regex_match(city, c_regex))
					{
			       		cout << "invalid input" << endl;
			  		}

				}while(!regex_match(city, c_regex));

				do{
						cout << "Country : ";
						cin >> country;

					if (!regex_match(country, c_regex))
					{
			       		cout << "invalid input" << endl;
			  		}

				}while(!regex_match(country, c_regex));


				cout << "Do you want to add the contact in your favorites (y/n) : ";
				while(true)
				{
					cin >> favchoice;
					if (favchoice=='Y'||favchoice == 'y') 
						{
							isfav = true;
							break;
						}	
					else if(favchoice =='N'|| favchoice =='n') 
						{
							isfav = false;
							break;
						}	
					else
					{
						cout << endl << "enter valid command"<<endl;
						continue;
					}
				}

				cin.clear();
				cin.ignore();

				key = fname + lname;

				Contact* data = new Contact(fname, lname, email, phone, city, country, isfav);					//add new node with given data
				bst.add(bst.getRoot(),key, data);
			}
		else if(command == "update")		bst.update(parameter);
		else if(command == "remove")		
		{
			bst.remove(bst.getRoot(), parameter);
		}
		else if(command =="searchFor")		bst.searchFor(bst.getRoot(),parameter);
		else if(command == "markFav")		bst.markFav(parameter);
		else if(command == "unmarkFav")		bst.unmarkFav(parameter);
		else if(command == "printASC")		bst.printASC(bst.getRoot());
		else if(command == "printDES")		bst.printDES(bst.getRoot());
		else if(command == "printFav")		bst.printFav(bst.getRoot());
		else if(command == "help")			listCommands();
		else if(command == "exit" or command=="quit")			break;
		else cout<<"Invalid Command!!"<<endl;

	}while(true);

	return 0;
}