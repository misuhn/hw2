#include "clothing.h"
#include "util.h"
#include <sstream>

Clothing::Clothing(const std::string category, const std::string name,
                   double price, int qty, const std::string brand,
                   const std::string size)
    : Product(category, name, price, qty),
      brand_(brand),
      size_(size) {}

std::set<std::string> Clothing::keywords() const {
  std::set<std::string> keywords;
  keywords = parseStringToWords(convToLower(getName()));
  std::set<std::string> brand_keywords = parseStringToWords(convToLower(brand_));
  keywords.insert(brand_keywords.begin(), brand_keywords.end());
  return keywords;
}

std::string Clothing::displayString() const {
	std::string result;
    result += name_ + "\n";
    result += "Size: " + size_ + " Brand: " + brand_ + "\n";
    result += std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return result;
}

void Clothing::dump(std::ostream& os) const {
  Product::dump(os);
	os << size_ << "\n" << brand_ << std::endl;
}
