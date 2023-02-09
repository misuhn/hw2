#include "mydatastore.h"
#include "util.h"
#include <iostream>
using namespace std;

MyDataStore::MyDataStore() {
	updated_ = true;
}

// Cleared up storage.
MyDataStore::~MyDataStore() {
	for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
		delete it->second;
	}
	for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
		delete *it;
	}
}

void MyDataStore::addUser(User* u) {
	users_.insert(make_pair(u->getName(), u));
}

void MyDataStore::addProduct(Product* p) {
	products_.insert(p);
	updated_ = false;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
	if (!updated_) {
		update();
	}
	set<Product*> final;
	for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it) {
		if (links_.find(*it) != links_.end()) {
			if (type == 0) {
				if (final.size()) {
					final = setIntersection(links_[*it], final);
				} else {
					final = links_[*it];
				}
			} else {
				final = setUnion(links_[*it], final);
			}
		}
	}
	vector<Product*> result(final.begin(), final.end());
	return result;
}

void MyDataStore::addToCart(string username, Product* p) {
	if (users_.find(username) != users_.end() && products_.find(p) != products_.end()) {
		if (carts_.find(username) != carts_.end()) {
			carts_[username].push_back(p);
		} else {
			vector<Product*> cart(1, p);
			carts_.insert(make_pair(username, cart));
		}
	} else {
		cout << "Invalid request" << endl;
	}
}

void MyDataStore::buyCart(string username) {
	if (carts_.find(username) != carts_.end()) {
		for (vector<Product*>::iterator item = carts_[username].begin(); item != carts_[username].end();) {
			if ((*item)->getQty() >= 1 && users_[username]->getBalance() >= (*item)->getPrice()) {
				(*item)->subtractQty(1);
				users_[username]->deductAmount((*item)->getPrice());
				carts_[username].erase(item);
			} else {
				++item;
			}
		}
	} else {
		cout << "Invalid username" << endl;
	}
}

void MyDataStore::viewCart(string username) {
	if (carts_.find(username) != carts_.end()) {
		int count = 1;
		for (vector<Product*>::iterator item = carts_[username].begin(); item != carts_[username].end(); ++item) {
			cout << "Item " << count++ << endl << (*item)->displayString() << endl;
		}
	} else {
		cout << "Invalid username" << endl;
	}
}

void MyDataStore::update() {
	for (set<Product*>::iterator it1 = products_.begin(); it1 != products_.end(); ++it1) {
		set<string>keyWords = (*it1)->keywords();
		for (set<string>::iterator it2 = keyWords.begin(); it2 != keyWords.end(); ++it2) {
			if (links_.find(*it2) != links_.end()) {
				links_[*it2].insert(*it1);
			} else {
				set<Product*> match;
				match.insert(*it1);
				links_.insert(make_pair(*it2, match));
			}
		}
	}
}

void MyDataStore::dump(ostream& ofile) {
	ofile << "<products>" << endl;
	for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
		(*it)->dump(ofile);
	}
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;
	for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
		it->second->dump(ofile);
	}
	ofile << "</users>";
}