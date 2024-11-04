/*********************************************

COMSC 210 | Lab 28 | Skylar Robinson | IDE Used: Eclipse

**********************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
void delete_by_name(list<Goat> &trip);
void search_for_goat(list<Goat> trip);
void avg_age(list<Goat> trip);
void increase_ages(list<Goat> &trip);
void sort_trip(list<Goat> &trip);
void sort_rm_dups(list<Goat> &trip);
void reverse(list<Goat> &trip);
int main_menu();

int main() {
    srand(time(0));

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
            	cout << "Removing a goat by name.\n";
            	delete_by_name(trip);
            	break;
            case 5:
            	cout << "Searching for a goat.\n";
            	search_for_goat(trip);
            	break;
            case 6:
            	cout << "Getting average age.\n";
            	avg_age(trip);
            	break;
            case 7:
            	cout << "Increasing ages by 1.\n";
            	increase_ages(trip);
            	break;
            case 8:
            	cout << "Sorting goats alphabetically by name.\n";
				sort_trip(trip);
            	break;
            case 9:
            	cout << "Sorting and deleting duplicates by name.\n";
            	sort_rm_dups(trip);
            	break;
            case 10:
            	cout << "Reversing the order of goats.\n";
            	reverse(trip);
            	break;
            case 11:
            	cout << "Shuffling the order of goats.\n";
				//shuffle(trip);
            	break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Delete goat by name\n";
    cout << "[5] Search for goat\n";
    cout << "[6] Get average age\n";
    cout << "[7] Increase goat ages\n";
    cout << "[8] Sort goats alphabetically\n";
    cout << "[9] Sort goats and remove duplicate names\n";
    cout << "[10] Reverse goat order\n";
    cout << "[11] Shuffle goat order\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    cin.ignore();
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
        cin.ignore();
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void delete_by_name(list<Goat> &trip) {
    string input;
    cout << "Select a name:\n";
    display_trip(trip);
    cout << "Choice --> ";
    getline(cin, input);
    auto it = find(trip.begin(), trip.end(), input);
    if (it == trip.end()) {
    	cout << input << " not found.\n";
    	return;
    }
	trip.erase(remove(trip.begin(), trip.end(), input), trip.end());
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void search_for_goat(list<Goat> trip) {
	string input;
	cout << "Name to search for: ";
	getline(cin, input);
	auto it = find(trip.begin(), trip.end(), input);
	if (it == trip.end()) {
		cout << input << " not found.\n";
	} else {
	    cout << "Displaying " << input << ":\n"
	    	 << it->get_name() << " ("
			 << it->get_age() << ", "
			 << it->get_color() << ")\n";
	}
}

void avg_age(list<Goat> trip) {
	int sum = accumulate(trip.begin(), trip.end(), 0, [](int sum, const Goat& g){ return sum + g.get_age(); });
	cout << "Average age: " << fixed << setprecision(0) << sum / trip.size() << endl;
}

void increase_ages(list<Goat> &trip) {
	for_each(trip.begin(), trip.end(), [](Goat& g){ g.set_age(g.get_age() + 1); });
	cout << "\nAges increased.\n";
}

void sort_trip(list<Goat> &trip) {
	sort(trip.begin(), trip.end(), 0);
	cout << "\nTrip sorted.\n";
}

void sort_rm_dups(list<Goat> &trip) {
//	sort(trip.begin(), trip.end());
//	trip.erase(unique(trip.begin(), trip.end()), trip.end());
	cout << "\nSorting and deletion complete.\n";
}

void reverse(list<Goat> &trip) {
	reverse(trip.begin(), trip.end());
	cout << "\nTrip reversed.\n";
}

void shuffle(list<Goat> &trip) {
//	shuffle(trip.begin(), trip.end(), default_random_engine());
	cout << "\nTrip shuffled.\n";
}
