#include "contactbst.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

bool updateflag = true;


ContactBST::ContactBST()									//constructor
{
	root = NULL;
}
ContactBST::~ContactBST()									//destructor
{
	delete root;
}
Node* ContactBST::getRoot()						//returns the root of the Tree
{
	return root;
}
void ContactBST::add(Node* ptr,string key, Contact *data)		//add key into tree/subtree with root ptr
{
if(ptr ==NULL)
{
	root = new Node(key, data);
	return;
}

if(key < ptr -> getKey()) 			//when key is smaller than the root
{
	if(ptr-> left ==NULL)			//if the left of the root is empty, insert node
	{
		ptr -> left = new Node(key, data);
		ptr -> left -> parent = ptr;
	}
	else							//if the left is not empty, recursively call function again, traverse
	{
		add(ptr-> left, key, data);
	}
}
else if(key > ptr -> getKey())    	//when the key is larger than the root
{
	if(ptr->right == NULL)			//if the right of the root is empty, insert node
	{
		ptr->right = new Node(key, data);
		ptr->right -> parent = ptr;
	}
	else							//if the right is not empty, recursively call function again, traverse
	{
		add(ptr->right, key, data);
	}
}
else
{
	ptr-> contactVector.push_back(data);	//if the key is identical, add the new key to the vector
}
} 

void ContactBST::update(string key) 	//Edit the node with key
{
	int which_value, which_person = 1;
	string first_name, last_name, new_value, removeKey;
	char choice;

	Node* node = searchFor(root, key);		//search for the key

	if(node == NULL)
	{
		cout << "contact not found" << endl;  
		return;  
	}

	while(true)
	{
		cout << "Please select the person you want to update: ";					//let user select person to update even if there is vector size is 1
		cin >> which_person;
		if(which_person < 1 || which_person > node->contactVector.size())
			{cout << "pleae enter a valid number" << endl;
			continue;
		}
		break;
	}

	Contact* contact = node->contactVector.at(which_person-1);						//access the contact vector of the person

	removeKey = contact->fname + contact->lname;        //storing key to delete after adding new updated node (if in case name is updated)

	while(true)								//update data
	{

	cout << "Which field would you want to edit?"<<endl;
	cout << "1) First Name, 2) Last Name, 3) Email, 4) Phone#, 5) City, 6) Country : ";
	cin >> which_value;

	switch(which_value){
	case 1:{
	regex name_regex("^[a-zA-Z]+$");							//receive updated input
		do{
			cout << "First name : ";
			cin >> first_name;
			if (!regex_match(first_name, name_regex)) 
			{
	       		cout << "invalid input" << endl;
	  		}

		}while(!regex_match(first_name, name_regex));
		contact->fname = first_name;
		break;
	}
	case 2:{
		regex name_regex("^[a-zA-Z]+$");
		do{
			cout << "Last name : ";
			cin >> last_name;
			if (!regex_match(last_name, name_regex)) 
			{
	       		cout << "invalid input" << endl;
	  		}

		}while(!regex_match(last_name, name_regex));
		contact->lname = last_name;
		break;
	}
	case 3:{
	regex email_regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
		do{
			cout << "Email : ";
			cin >> new_value;

			if (!regex_match(new_value, email_regex))
			{
	       		cout << "invalid input" << endl;
	  		}

		}while(!regex_match(new_value, email_regex));
		contact->email = new_value;
		break;}
	case 4:{
		regex phone_regex("^(\\+)?[0-9]+$");

		do{
			cout << "Phone : ";
			cin >> new_value;

		if (!regex_match(new_value, phone_regex))
		{
       		cout << "invalid input" << endl;
  		}

		}while(!regex_match(new_value, phone_regex));
		contact->phone = new_value;
		break;
	}
	case 5:{
		regex c_regex("^[a-zA-Z- ]+$");
		do{
			cout << "City : ";
			cin >> new_value;

		if (!regex_match(new_value, c_regex))
		{
       		cout << "invalid input" << endl;
  		}
		}while(!regex_match(new_value, c_regex));
		contact->city = new_value;
		break;
		}
	case 6:{
		regex c_regex("^[a-zA-Z- ]+$");
		do{
			cout << "Country : ";
			cin >> new_value;

		if (!regex_match(new_value, c_regex))
		{
       		cout << "invalid input" << endl;
  		}

		}while(!regex_match(new_value, c_regex));
		contact->country = new_value;
		break;
		}
	default:{
		cout << "Invalid selection, try again"<< endl;
		continue;
	}
	}


	if(which_value ==1 || which_value==2)									//in case the name is changed add new node with modified name and delete the original node/erase vector in case of John Smith
	{			
		if(which_value ==1) add(root, first_name+contact->lname, contact);
		else if (which_value ==2) add(root, contact->fname+last_name, contact);

		if(node->contactVector.size()>1)
		{
			node->contactVector.erase(which_person-1);
		}
		else
		{
			updateflag = false;
			remove(getRoot(), removeKey);
		}

	}

	cout << "The contact record has been successfully updated!"<< endl;
	cout << "Do you want to edit another field? (Y/N) : ";
	cin >> choice;
	cin.clear();
	cin.ignore();

	if(choice == 'N' || choice == 'n')
	{
		break;
	}
	}
}

void ContactBST::remove(Node* ptr,string key)		//Delete a node with key from the tree/subtree with root
{
	int which_person;

	Node* node = searchFor(root, key);  			//search for node to be removed
	string tempName = key;							//save name of node to be removed for cout

	if(node == NULL)
	{
		cout << "contact not found" << endl;
		return;
	}

	if(node->contactVector.size() > 1)						//if the picked node has a vector sized bigger than 1, just delete one vector content
	{
	while(true)
	{
		cout << "Please select the record you want to remove: ";
		cin >> which_person;
		cin.clear();
		cin.ignore();
		if(which_person < 1 || which_person > node->contactVector.size())					//check for valid input between 1 and size of vector
			{cout << "pleae enter a valid number" << endl;
			continue;
		}
		break;
	}
	Contact* ct = node->contactVector.at(which_person-1);					//get name of the vector content about to be deleted
	string name = ct->fname+ " " + ct ->lname;
	node->contactVector.erase(which_person-1);								//delete vector
	cout << name << " has been successfully removed"<<endl;
	return;
	}

	//if the picked node has vector sized 1, remove the node

	if(node->left ==NULL && node ->right ==NULL)    //if node is an external node
	{
		if(node == root)						//if the node is root of the tree, assign root as null
		{
			root =NULL;
		}
		else
		{
			Node* parent = node->parent;		//find parent node and assign the child of the parent node as null
			if(node == parent -> left)
			{
				parent -> left = NULL;
			}
			else
			{
				parent -> right = NULL;
			}
		}
		delete node;
	}
	else if(node -> left == NULL || node -> right == NULL)    //if node has one child
	{
		Node* child;
		if(node->left ==NULL)    //find child node
		{
			child = node -> right;
		}
		else
		{
			child = node ->left;
		}

		if(node == root)     //check if node is root
		{
			root = child;
			child -> parent = NULL;
		}
		else   				//if node is not the root, find the parent node
		{
			Node* parent = node -> parent;      //find parent node, assign the child of the node to be deleted as the child of the parent node
			if(node == parent -> left)
			{
				parent -> left = child;
			}
			else
			{
				parent -> right = child;
			}
			child-> parent = parent;
		}
		delete node;
	}

	else     				//if node was two children
	{
		Node* minNode = findMin(node-> right);     //find minimum node in right subtree


		node->key = minNode -> key;							//swap values between the minimum node of the right subtree and the node to remove
		node -> contactVector = minNode -> contactVector;      


		if(minNode->parent->left == minNode)   //if the minimum node is a left child of its parent 
		{
			minNode->parent->left = minNode->right;   //connect minimum node's parent to the child of the minimum node
			if(minNode->right != NULL)
			{
				minNode->right->parent = minNode->parent;
			}
		}
		else									//if the minimum node is a right child of its parent
		{
			minNode->parent->right = minNode->right;   //connect minimum node's parent to the child of the minimum node
			if(minNode->right != NULL)
			{
				minNode->right->parent = minNode->parent;
			}
		}
		delete minNode;       //delete minimum node
	}

	if(updateflag==true)
	{
		cout << key << " has been successfully removed"<<endl;
	}
	updateflag =true;
}


Node* ContactBST::searchFor(Node* ptr,string key)		//Find and returns the node with key
{

	if(ptr == NULL)
	{
		cout << "Not found" << endl;
		return ptr;
	}

	if(ptr -> getKey() == key)			//if the tree is empty/the key is not found, return NULL or the node to search for is found, return ptr
	{
		if(updateflag==true)
		{ptr->print();}
		return ptr;
	}

	if(key < ptr -> getKey())							//if the key to search for is smaller than the key of the root, search left subtree
	{
		return searchFor(ptr->left, key);
	}
	else
	{
		return searchFor(ptr->right, key);				//if the key to search for is larger than the key of the root, search right subtree
	}
}

bool ContactBST::markFav(string key)  				//Mark a contact as favorite 
{
	Node* temp = searchFor(root, key);
	if(temp == NULL)
	{
		cout << "contact not found" << endl;
		return false;
	}
	
	int which_person;

	do {
	cout << "Please select the record you want to mark as favorite: ";
	cin >> which_person;
	cin.clear();
	cin.ignore();
	}while(which_person < 1 || which_person > temp -> contactVector.size());					//check for valid input between 1 and size of vector

	Contact* contact = temp -> contactVector.at(which_person-1);				//access data of valid person
	contact -> isFav = true;													//change isfav value

	cout << "Contact " << contact->fname << contact -> lname << " has successfully been marked as favorite" << endl;
	
	return true;
}


bool ContactBST::unmarkFav(string key)  //Unmark a contact as favorite 
{
	Node* temp = searchFor(root, key);
	if(temp == NULL)
	{
		cout << "contact not found" << endl;
		return false;
	}
	
	int which_person;

	do {
	cout << "Please select the record you want to unmark as favorite: ";
	cin >> which_person;
	cin.clear();
	cin.ignore();
	}while(which_person < 1 || which_person > temp -> contactVector.size());

	Contact* contact = temp -> contactVector.at(which_person-1);
	contact -> isFav = false;

	cout <<"Contact " << contact->fname << contact -> lname << " has successfully been unmarked as favorite" << endl;

	return true;
}

void ContactBST::printASC(Node* ptr)		//Recursive method that prints the data at nodes in an ascending order
{
	if(ptr == NULL)							//if the tree is emtpy, return
	{
		return;
	}

	printASC(ptr -> left);					//recursivley call function to move to the leftmost side of the tree, acessing the smallest node

	ptr -> print2(cout);

	printASC(ptr -> right);					//recursivley call function to move to the right, printing the keys in ascending order

}

void ContactBST::printDES(Node* ptr)		//Recursive method that prints the data at nodes in a descending order
{
	if(ptr == NULL)						//if tree is empty, return
	{
		return;
	}
	printDES(ptr ->right);		//recursivley call function to move to the rightmost side of the tree, acessing the largest node

	ptr->print2(cout);

	printDES(ptr->left);			//recursivley call function to move to the left, printing the keys in descending order

}

void ContactBST::printFav(Node* ptr)           //Print the favorite data at nodes in an ascending order
{
	if(ptr == NULL)							//return if tree is empty
	{
		return;
	}
        printFav(ptr->left);					//traverse to left subtree for acsending order


        for(int i = 0; i< ptr->contactVector.size(); i++)				//traverse through vector of node in case there are people with same names
        {
        	Contact* ct = ptr->contactVector.at(i);						//access data from each person

        	if (ct->isFav==true) 						//if isFav is marked as true, print content of person
        	{
          	  	cout<<" "<<". "<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->phone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
       		}
   		}

        printFav(ptr->right);					//traverse to right subtree for ascending order

}

int ContactBST::importCSV(string path) //Load all the contacts from the CSV file to the BST
{
	string key;
	ifstream fin(path);

	if(!fin){   					  //invalid path
		return -1;
	}

	int count =0;
	string line;

	while(getline(fin,line))					//traverse through each line of csv file
	{
		stringstream ss(line);						
		string fname, lname, email, phone, country, city, isfav;
		bool fav;
		getline(ss, fname, ',');					//store content of each line 
        getline(ss, lname, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');
        getline(ss, city, ',');
        getline(ss, country, ',');
        getline(ss, isfav, ',');

        fav = (stoi(isfav)==0) ? false : true;			//store boolean value of isfav

        Contact* newContact = new Contact(fname, lname, email, phone, city, country, fav);		//create new contact object
        key = fname + lname;

        add(getRoot(), key, newContact);							//add each line as a node inside the bst
        count ++;												//increment count

	}
	fin.close();
	return count;


}
int ContactBST::exportCSV(Node* ptr,ostream& file) //Export all the contacts from the BST to a CSV file in an ascending order
{
	int count = 0;

	if (ptr == NULL) {									//return 0 if bst is empty
        return 0;
    }
    
    count += exportCSV(ptr->left, file);				// recursively traverse to the left subtree for ascending order
   													 
    ptr -> print2(file);							// write contact information to file 	
    count++;										//increment count every time node is exported
    												
    count += exportCSV(ptr->right, file);			// recursively traverse to the right subtree
    
    return count+1;
}

Node* ContactBST::findMin(Node* ptr)
{
	while(ptr -> left != NULL)  	//move pointer to the left until the it reaches the leftmost node of the tree, accessing the minimum node 
	{
		ptr = ptr -> left;
	}
	return ptr;
}








