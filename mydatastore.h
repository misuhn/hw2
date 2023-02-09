#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <map>

class MyDataStore : public DataStore {
	public:
	MyDataStore();
	~MyDataStore();
	void addUser(User* u);
	void addProduct(Product* p);
	std::vector<Product*> search (std::vector<std::string>& terms, int type);
	void addToCart(std::string username, Product* p);
	void buyCart(std::string username);
	void viewCart(std::string username);
	void dump(std::ostream& ofile);
	protected:
	void update();
	private:
	bool updated_;
	std::map<std::string, User*> users_;
	std::set<Product*> products_;
	std::map<std::string, std::vector<Product*>> carts_;
	std::map<std::string, std::set<Product*>> links_;
};

#endif