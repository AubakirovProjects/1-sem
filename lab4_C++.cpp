#include <iostream>
#include <pqxx/pqxx>
#include <fstream>
#include <string>


class Category {
public:
    static void addCategory(pqxx::connection& conn, const std::string& category_name) {
        try {
            pqxx::work txn(conn);
            txn.exec("INSERT INTO categories_new (category_name) VALUES (" + txn.quote(category_name) + ")");
            txn.commit();
            logOperation("Added category: " + category_name);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    static void logOperation(const std::string& message) {
        std::ofstream log("log.txt", std::ios_base::app);
        log << message << std::endl;
    }
};


class Product {
public:
    static void addProduct(pqxx::connection& conn, const std::string& name, double price, int quantity, int category_id) {
        try {
            pqxx::work txn(conn);
            txn.exec("INSERT INTO products_new (name, price, quantity, category_id) VALUES ("
                     + txn.quote(name) + ", " + txn.quote(price) + ", " + txn.quote(quantity) + ", " + txn.quote(category_id) + ")");
            txn.commit();
            Category::logOperation("Added product: " + name);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
};


class Sale {
public:
    static void addSale(pqxx::connection& conn, int product_id, const std::string& sale_date, int quantity_sold) {
        try {
            pqxx::work txn(conn);
            txn.exec("INSERT INTO sales_new (product_id, sale_date, quantity_sold) VALUES ("
                     + txn.quote(product_id) + ", " + txn.quote(sale_date) + ", " + txn.quote(quantity_sold) + ")");
            txn.commit();
            Category::logOperation("Added sale for product ID: " + std::to_string(product_id));
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
};

void getTopSellingProducts(pqxx::connection& conn) {
    try {
        pqxx::work txn(conn);
        pqxx::result res = txn.exec("SELECT name, SUM(quantity_sold) AS total_sold "
                                    "FROM products_new JOIN sales_new ON products.id = sales.product_id "
                                    "GROUP BY name ORDER BY total_sold DESC LIMIT 5");

        std::cout << "Top 5 Selling Products:\n";
        for (const auto& row : res) {
            std::cout << "Product: " << row["name"].c_str()
                      << ", Sold: " << row["total_sold"].as<int>() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void menu(pqxx::connection& conn) {
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Category\n";
        std::cout << "2. Add Product\n";
        std::cout << "3. Add Sale\n";
        std::cout << "4. View Top Selling Products\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string category_name;
            std::cout << "Enter category name: ";
            std::cin.ignore();
            std::getline(std::cin, category_name);
            Category::addCategory(conn, category_name);
            break;
        }
        case 2: {
            std::string name;
            double price;
            int quantity, category_id;
            std::cout << "Enter product name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter price: ";
            std::cin >> price;
            std::cout << "Enter quantity: ";
            std::cin >> quantity;
            std::cout << "Enter category ID: ";
            std::cin >> category_id;
            Product::addProduct(conn, name, price, quantity, category_id);
            break;
        }
        case 3: {
            int product_id, quantity_sold;
            std::string sale_date;
            std::cout << "Enter product ID: ";
            std::cin >> product_id;
            std::cout << "Enter sale date (YYYY-MM-DD): ";
            std::cin >> sale_date;
            std::cout << "Enter quantity sold: ";
            std::cin >> quantity_sold;
            Sale::addSale(conn, product_id, sale_date, quantity_sold);
            break;
        }
        case 4:
            getTopSellingProducts(conn);
            break;
        case 0:
            return;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}

// Функция main
int main() {
    try {
        std::string connection_string = "dbname=products_new user=ser password=1420 host=localhost port=5432";
        pqxx::connection conn(connection_string);

        if (conn.is_open()) {
            std::cout << "Connected to database.\n";
            menu(conn);
        } else {
            std::cerr << "Failed to connect to database.\n";
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
