// Comsc 210 Lab 28 Algrothims || Akashdeep Singh
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

//Function prototypes
int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);

void sort_goats(list<Goat>&);           //milestone 1 Sort
void reverse_goats(list<Goat>&);        //milestone 2 Reverse list
void find_goat(list<Goat>);             //milestone 3 Find goat
void count_color(list<Goat>);           //milestone 4 Count color
void unique_goats(list<Goat>&);         //milestone 5 Unique goats
void oldest_goat(list<Goat>);           //milestone 6 Oldest goat
void youngest_goat(list<Goat>);         //milestone 7 Youngest goat

int main_menu();

int main() {
    srand(time(0));
    bool again;

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
    while (sel != 5) {  // milestone 1 quit option change
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
            case 4:                         //milestone 1
                sort_goats(trip);
                break;
           case 5:                          //milestone 2
                reverse_goats(trip);
                break;
            case 6:                         //milestone 3
                find_goat(trip);
                break;
            case 7:                         //milestone 4
                count_color(trip);
                break;
            case 8:                         //milsetone 5
                unique_goats(trip);
                break;
            case 9:                         //milsetone 6
                oldest_goat(trip);
                break;
            case 10:                        //milsetone 7
                youngest_goat(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}
// --------Menu--------
int main_menu() {
    cout << "\n*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort goats\n";                             //milestone 1
    cout << "[5] Reverse list\n";                           //milestone 2
    cout << "[6] Find goat by name\n";                      //milestone 3
    cout << "[7] Count goats by color\n";                   //milestone 4
    cout << "[8] Remove duplicates\n";                      //milestone 5        
    cout << "[9] Oldest goat\n";                            //milsetone 6    
    cout << "[10] Youngest goat\n";                         //milsetone 7
    //cout << "[8] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {  //changed choice > 5 instead of choice > 4 || changed to choice > 6 (milestone2 going to repeat without adding comment)
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}
// Delete Goat
void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}
//Add Goat
void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}
//Display trip
void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}
/*Select Goat
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
   */
//Sort Goat: Milestone 1
void sort_goats(list<Goat>& trip) {
    trip.sort();
    cout << "Sorted goats. \n";

}

//Reverse Goat: Milestone 2
void reverse_goats(list<Goat>& trip) {
    trip.reverse();
    cout << "List reversed.\n";
}

//Find goat: Milestone 3
void find_goat(list<Goat> trip) {
    string name;
    cout << "Enter name: ";
    cin >> name;

    bool found = false;

    for (auto g : trip) {
        if (g.get_name() == name) {
            cout << "Found: "
                 << g.get_name()
                 << " (" << g.get_age()
                 << ", " << g.get_color() << ")\n";
            found = true;
        }
    }

    if (!found)
        cout << "Goat not found.\n";
}

//Count by color: Milestone 4
void count_color(list<Goat> trip) {
    string color;
    cout << "Enter color: ";
    cin >> color;

    int count = 0;

    for (auto g : trip) {
        if (g.get_color() == color)
            count++;
    }

    cout << "Total goats with color " << color << ": " << count << endl;
}

//Unique goats: Milestone 5
void unique_goats(list<Goat>& trip) {
    trip.sort();
    trip.unique();
    cout << "Duplicates removed.\n";
}

// OLDEST GOAT: MILESTONE 6 
void oldest_goat(list<Goat> trip) {
    Goat oldest = *trip.begin();

    for (auto g : trip) {
        if (g.get_age() > oldest.get_age())
            oldest = g;
    }

    cout << "Oldest: "
         << oldest.get_name()
         << " (" << oldest.get_age()
         << ", " << oldest.get_color() << ")\n";
}

// YOUNGEST Goat: Milestone 7
void youngest_goat(list<Goat> trip) {
    Goat youngest = *trip.begin();

    for (auto g : trip) {
        if (g.get_age() < youngest.get_age())
            youngest = g;
    }

    cout << "Youngest: "
         << youngest.get_name()
         << " (" << youngest.get_age()
         << ", " << youngest.get_color() << ")\n";
}





