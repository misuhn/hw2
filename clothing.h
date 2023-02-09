#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <set>
#include <string>
#include <vector>

class Clothing : public Product {
 public:
 //return new Clothing("clothing", prodName_, price_, qty_, brand_, size_);
  Clothing(const std::string category, const std::string name, double price,
           int qty, const std::string brand, const std::string size);
  std::set<std::string> keywords() const;
  std::string displayString() const;
  void dump(std::ostream& os) const;
 private:
  std::string brand_;
  std::string size_;
};
#endif
