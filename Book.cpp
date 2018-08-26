#include "Book.h"
#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include"GeneralBookFunctions.h"

void Book::setAuthor(string author) {
	this->author = author;
}

void Book::setEdition(int edition) {
	this->edition = edition;
}

void Book::setISBN(string ISBN) {
	this->ISBN = ISBN;
}

void Book::setlibraryID(string libraryID) {
	this->libraryID = libraryID;
}

void Book::setPrice(float price) {
	this->price = price;
}

void Book::setPublisher(string publisher) {
	this->publisher = publisher;
}

void Book::setTitle(string title) {
	this->title = title;
}

string Book::getAuthor() const {
	return author;
}

string Book::getPublisher() const {
	return publisher;
}

bool Book::isBookIssued() const {
	return isIssued;
}

string Book::getISBN() const {
	return ISBN;
}

string Book::getlibraryID() const {
	return libraryID;
}

int Book::getEdition() const {
	return edition;
}

string Book::getTitle() const {
	return title;
}

float Book::getPrice() const {
	return price;
}

void Book::setBookAttributes(string title, string author, string publisher, string ISBN, string libraryID, int edition, float price) {
	setAuthor(author);
	setTitle(title);
	setPublisher(publisher);
	setISBN(ISBN);
	setlibraryID(libraryID);
	setEdition(edition);
	setPrice(price);
}

void Book::getAllAttributes() const {
	cout << "Title: " << title << "\n";
	cout << "Author: " << author << "\n";
	cout << "Edition: " << edition << "\n";
	cout << "Publisher: " << publisher << "\n";
	cout << "Issue State: ";
	if (isIssued == true)
		cout << "Issued\n";
	else
		cout << "Not Issued\n";
	cout << "ISBN: " << ISBN << "\n";
	cout << "Library ID: " << libraryID << "\n";
	cout << "Price: " << price << "\n\n";
}

void Book::getItemsFromUser() {
	string publisher, author, title, ISBN, libraryID;
	int edition;
	float price;
	cout << "Enter the title: ";
	cin >> ws;
	getline(cin, title);
	cout << "Enter the Author: ";
	cin >> ws;
	getline(cin, author);
	cout << "Enter the edition number: ";
	edition = checkInput();
	cout << "Enter the publisher name: ";
	cin >> ws;
	getline(cin, publisher);
	cout << "Enter the ISBN number: ";
	ISBN = ISBNChecker();
	cout << "Enter the library ID: ";
	cin >> libraryID;
	cout << "Enter the price: ";
	cin >> price;
	cout << "\n";
	setBookAttributes(title, author, publisher, ISBN, libraryID, edition, price);
	fstream f;
	f.open("Books.dat", ios::app | ios::binary | ios::out);
	f.write((char*)this, sizeof(*this));
	f.close();
}

void Book::setIssue(bool isIssued) {
	this->isIssued = isIssued;
}

Book Book::searchBookByAuthor() {
	string author;
	cout << "Enter the author's name: ";
	cin >> ws;
	getline(cin, author);
	fstream f;
	Book temp, temp1;
	vector<Book> results;
	f.open("Books.dat", ios::binary | ios::in);
	while (f.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if(temp1.getAuthor() == author)
			results.push_back(temp);
	}
	f.close();
	modifyPrint(results);
	return resultChecker(results);

}

Book Book::searchBookByISBN() {
	string ISBN;
	cout << "Enter the ISBN: ";
	cin >> ws;
	getline(cin, ISBN);
	fstream f;
	Book temp, temp1;
	vector<Book> results;
	f.open("Books.dat", ios::binary | ios::in);
	while (f.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if (temp1.getISBN() == ISBN)
			results.push_back(temp);
	}
	f.close();
	modifyPrint(results);
	return resultChecker(results);

}

Book Book::searchBookByLibraryID() {
	string libraryID;
	cout << "Enter the library ID: ";
	cin >> ws;
	getline(cin, libraryID);
	fstream f;
	Book temp, temp1;
	vector<Book> results;
	f.open("Books.dat", ios::binary | ios::in);
	while (f.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if (temp1.getlibraryID() == libraryID)
			results.push_back(temp);
	}
	f.close();
	modifyPrint(results);
	return resultChecker(results);

}

Book Book::searchBookByPublisher() {
	string publisher;
	cout << "Enter the publisher's name: ";
	cin >> ws;
	getline(cin, publisher);
	fstream f;
	Book temp, temp1;
	vector<Book> results;
	f.open("Books.dat", ios::binary | ios::in);
	while (f.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if (temp1.getPublisher() == publisher)
			results.push_back(temp);
	}
	f.close();
	modifyPrint(results);
	return resultChecker(results);

}

Book Book::searchBookByTitle() {
	string title;
	cout << "Enter the title: ";
	cin >> ws;
	getline(cin, title);
	fstream f;
	Book temp, temp1;
	vector<Book> results;
	f.open("Books.dat", ios::binary | ios::in);
	while (f.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if (temp1.getTitle() == title)
			results.push_back(temp);
	}
	f.close();
	modifyPrint(results);
	return resultChecker(results);

}

void Book::editBook() {
	cout << "Search book by?\n1.Title\n2.Author\n3.Publisher\n4.ISBN\n5.Library ID\nEnter the option: ";
	Book result;
	int option;
	char ch;
	do {
		cin >> option;
		switch (option) {
		case 1:
			result = searchBookByTitle();
			if(result.getlibraryID() != "")
				bookEdit(result);
			break;
		case 2:
			result = searchBookByAuthor();
			if (result.getlibraryID() != "")
				bookEdit(result);
			break;
		case 3:
			result = searchBookByPublisher();
			if (result.getlibraryID() != "")
				bookEdit(result);
			break;
		case 4:
			result = searchBookByISBN();
			if (result.getlibraryID() != "")
				bookEdit(result);
			break;
		case 5:
			result = searchBookByLibraryID();
			if (result.getlibraryID() != "")
				bookEdit(result);
			break;
		default:
			cout << "Wrong Option!\n";
			cout << "Press F to try again or press any other key to go back!";
			ch = getchar();
		}
	} while (ch == 'F' || ch == 'f');
}

void Book::bookEdit(Book book) {
	fstream fin, fout;
	fin.open("Books.dat", ios::in | ios::binary);
	fout.open("Temp.dat", ios::out | ios::trunc | ios::binary);
	Book temp, temp1;
	while (fin.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if (temp1.getlibraryID() == book.getlibraryID())
			fout.write((char*)&book, sizeof(book));
		else
			fout.write((char*)&temp1, sizeof(temp1));
	}
	fin.close();
	fout.close();
	remove("Books.dat");
	rename("Temp.dat", "Books.dat");
}

void Book::deleteBookByLibraryID(Book book) {
	fstream fin, fout;
	fin.open("Books.dat", ios::in | ios::binary);
	fout.open("Temp.dat", ios::out | ios::trunc | ios::binary);
	Book temp, temp1;
	while (fin.read((char*)&temp, sizeof(temp))) {
		temp1 = temp;
		if (temp1.getlibraryID() != book.getlibraryID())
			fout.write((char*)&temp1, sizeof(temp1));
	}
	fin.close();
	fout.close();
	remove("Books.dat");
	rename("Temp.dat", "Books.dat");
}

void Book::getAllBooks() {
	fstream f;
	f.open("Books.dat", ios::in | ios::binary);
	Book temp;
	while (f.read((char*)&temp, sizeof(temp))) 
		temp.getAllAttributes();
	f.close();
}

Book::~Book()
{
}
