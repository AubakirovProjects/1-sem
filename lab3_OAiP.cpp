#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Product {
    std::string name;
    double price;
    int quantity;

    void display() const {
        std::cout << name << price << quantity << "\n";
    }
};

void appendToFile(const std::string& filename, const std::string& line) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << line << "\n";
    }
}


std::vector<Product> readProducts(const std::string& filename) {
    std::vector<Product> products;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string name;
        double price;
        int quantity;
        while (file >> name >> price >> quantity) {
            products.push_back({name, price, quantity});
        }
    }
    return products;
}

void writeProducts(const std::string& filename, const std::vector<Product>& products) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& product : products) {
            file << product.name << " " << product.price << " " << product.quantity << "\n";
        }
    }
}

void addProduct(const std::string& filename) {
    std::string name;
    double price;
    int quantity;

    std::cout << "Введите название продукта (пустая строка для завершения): ";
    std::getline(std::cin, name);
    while (!name.empty()) {
        std::cout << "Введите цену: ";
        std::cin >> price;
        std::cout << "Введите количество: ";
        std::cin >> quantity;
        std::cin.ignore(); 

        appendToFile(filename, name + " " + std::to_string(price) + " " + std::to_string(quantity));

        std::cout << "Введите название продукта (пустая строка для завершения): ";
        std::getline(std::cin, name);
    }
}

void findProduct(const std::string& filename) {
    std::string searchName;
    std::cout << "Введите название продукта для поиска: ";
    std::cin >> searchName;

    auto products = readProducts(filename);
    bool found = false;

    for (const auto& product : products) {
        if (product.name == searchName) {
            std::cout << "Найден продукт:\n";
            product.display();
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Продукт с таким названием не найден.\n";
    }
}

void sortProducts(const std::string& filename, const std::string& criteria) {
    auto products = readProducts(filename);

    if (criteria == "price") {
        std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
            return a.price < b.price;
        });
    } else if (criteria == "quantity") {
        std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
            return a.quantity < b.quantity;
        });
    }

    writeProducts(filename, products);

    std::cout << "Продукты отсортированы по " << criteria << ".\n";
}

void filterByPrice(const std::string& filename) {
    double maxPrice;
    std::cout << "Введите максимальную цену: ";
    std::cin >> maxPrice;

    auto products = readProducts(filename);

    std::cout << "Продукты с ценой не более " << maxPrice << ":\n";
    for (const auto& product : products) {
        if (product.price <= maxPrice) {
            product.display();
        }
    }
}

void menu(const std::string& inputFile, const std::string& outputFile) {
    while (true) {
        std::cout << "\nМеню:\n"
                  << "1. Добавить продукт\n"
                  << "2. Найти продукт\n"
                  << "3. Отсортировать продукты\n"
                  << "4. Фильтрация по цене\n"
                  << "5. Выход\n"
                  << "Выберите действие: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
        case 1:
            addProduct(inputFile);
            break;
        case 2:
            findProduct(inputFile);
            break;
        case 3: {
            std::string criteria;
            std::cout << "Введите критерий сортировки (price/quantity): ";
            std::cin >> criteria;
            sortProducts(inputFile, criteria);
            break;
        }
        case 4:
            filterByPrice(inputFile);
            break;
        case 5:
            std::cout << "Выход из программы.\n";
            return;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}

int main() {
    const std::string inputFile = "products.txt";
    const std::string outputFile = "outputLab3.txt";

    menu(inputFile, outputFile);

    return 0;
}