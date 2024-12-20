#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;


class Animal {
protected:
    string name;
    string species;
public:
    Animal(const string& name, const string& species)
        : name(name), species(species) {}

    virtual ~Animal() = default;

    virtual void display() const {
        cout << "Name: " << name << ", Species: " << species << endl;
    }

    virtual void modify(const string& newName, const string& newSpecies) {
        name = newName;
        species = newSpecies;
    }
};

class Bird : public Animal {
    double wingSpan; 
public:
    Bird(const string& name, const string& species, double wingSpan)
        : Animal(name, species), wingSpan(wingSpan) {}

    void display() const override {
        cout << "Bird - Name: " << name << ", Species: " << species
                  << ", Wing Span: " << wingSpan << endl;
    }

    void modify(const string& newName, const string& newSpecies, double newWingSpan) {
        Animal::modify(newName, newSpecies);
        wingSpan = newWingSpan;
    }
};

class Mammal : public Animal {
    string furType;
public:
    Mammal(const string& name, const string& species, const string& furType)
        : Animal(name, species), furType(furType) {}

    void display() const override {
        cout << "Mammal - Name: " << name << ", Species: " << species
                  << ", Fur Type: " << furType << endl;
    }

    void modify(const string& newName, const string& newSpecies, const string& newFurType) {
        Animal::modify(newName, newSpecies);
        furType = newFurType;
    }
};

void modifyAnimal(Animal* animal, const string& newName, const string& newSpecies) {
    animal->modify(newName, newSpecies);
}

int main() {
    vector<shared_ptr<Animal>> animals;

    animals.push_back(make_shared<Bird>("Chaika", "Morskaya Chaika", 1.6));
    animals.push_back(make_shared<Bird>("Orel", "Ispanskiy mogilnik", 2.4));
    animals.push_back(make_shared<Mammal>("Medved", "Belyi medved", "Short"));
    animals.push_back(make_shared<Mammal>("Tiger", "Amurskyi tiger", "Short"));

    cout << "Animal list:\n";
    for (const auto& animal : animals) {
        animal->display();
    }

    cout << "\nModifying the first animal...\n";
    modifyAnimal(animals[0].get(), "Flamingo", "Rozovyi flamingo");

    cout << "\nAnimal list after modification:\n";
    for (const auto& animal : animals) {
        animal->display();
    }

    return 0;
}