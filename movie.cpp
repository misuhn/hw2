// movie.cpp
#include "movie.h"
#include "util.h"
#include <sstream>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, 
        const std::string genre, const std::string rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating)
{
}

Movie::~Movie()
{

}

set<string> Movie::keywords() const {
	set<string> keyWords = parseStringToWords(convToLower(name_));
	keyWords.insert(convToLower(genre_));
	return keyWords;
}

string Movie::displayString() const {
    std::string result;
    result += name_ + "\n";
    result += "Genre: " + genre_ + " Rating: " + rating_ + "\n";
    result += std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return result;
}

void Movie::dump(ostream& os) const {
	Product::dump(os);
	os << genre_ << "\n" << rating_ << endl;
}