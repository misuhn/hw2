// book.cpp
#include "book.h"
#include "util.h"
#include <sstream>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, 
        const std::string ISBN, const std::string author)
    : Product(category, name, price, qty), ISBN_(ISBN), author_(author)
{
}

Book::~Book()
{
}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> result = parseStringToWords(convToLower(name_));
    result.insert(ISBN_);
		set<std::string> parsed = parseStringToWords(convToLower(author_));
		for (set<std::string>::iterator it = parsed.begin(); it != parsed.end(); ++it) {
			result.insert(*it);
		}
    return result;
}

std::string Book::displayString() const
{
    std::string result;
    result += name_ + "\n";
    result += "Author: " + author_ + " ISBN: " + ISBN_ + "\n";
    result += std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return result;
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" 
       << ISBN_ << "\n" << author_ << std::endl;
}
