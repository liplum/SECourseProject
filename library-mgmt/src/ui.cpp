//
// Created by Liplum on 6/12/2023.
//

#include <iostream>
#include "ui.h"
#include "auth.h"
#include "../../shared/utils.h"

namespace ui {
    void inputProduct(Product &p) {
        cout << "Enter the name: ";
        p.name = inputString();

        // Input and validate price
        while (true) {
            cout << "Enter the price: ";
            p.price = inputDouble();
            if (p.price >= 0) {
                break;
            } else {
                cout << "Invalid price. Please enter a non-negative value." << endl;
            }
        }

        // Input and validate discount
        while (true) {
            cout << "Enter the discount: ";
            p.discount = inputDouble();
            if (p.discount >= 0 && p.discount <= 1) {
                break;
            } else {
                cout << "Invalid discount. Please enter a value between 0 and 1." << endl;
            }
        }

        // Input and validate premium price
        while (true) {
            cout << "Enter the premium price: ";
            p.premiumPrice = inputDouble();
            if (p.premiumPrice >= 0) {
                break;
            } else {
                cout << "Invalid premium price. Please enter a non-negative value." << endl;
            }
        }
    }


    // Function to add a new product
    void addProduct(DataSet<Product> &products) {
        // Get input for the new product details
        Product p;
        inputProduct(p);

        // Add the new product to the DataSet<Product>
        products.addProduct(p.name, p.price, p.discount, p.premiumPrice);
        cout << "Product added successfully!" << endl;
    }

// Function to delete a product
    bool deleteProduct(DataSet<Product> &products) {
        // Get the ID of the product to delete
        cout << "Enter the product ID to delete: ";
        auto id = inputInt();

        auto product = products.findById(id);
        if (!product.has_value()) {
            cout << "Product not found." << endl;
            return false;
        }

        cout << "Ensure to delete product " << product->name << "? ";
        bool ensure = inputInt();
        if (!ensure) {
            return false;
        }

        // Attempt to remove the product by ID
        if (products.removeProductById(id)) {
            cout << "Product deleted successfully!" << endl;
            return true;
        } else {
            cout << "Failed to delete product." << endl;
            return false;
        }
    }

// Function to modify a product
    bool modifyProduct(DataSet<Product> &products) {
        // Get the ID of the product to modify
        cout << "Enter the product ID to modify: ";
        auto id = inputInt();

        // Find the product by ID
        auto product = products.findById(id);

        // Check if the product exists
        if (!product.has_value()) {
            cout << "Product not found." << endl;
            return false;
        }
        // Get input for the updated product details
        inputProduct(*product);
        if (products.updateProduct(*product)) {
            cout << "Product modified successfully!" << endl;
            return true;
        } else {
            cout << "Failed to delete product." << endl;
            return false;
        }
    }

    void printProductDetails(const Product &product) {
        cout << "ID: " << product.id << ", Name: " << product.name
             << ", Price: " << product.price << ", Discount: " << product.discount
             << ", Premium Price: " << product.premiumPrice << endl;
    }

    optional<int> tryStoi(const std::string &input) {
        try {
            return std::stoi(input);
        } catch (const std::invalid_argument &) {
            // Conversion failed due to invalid argument
            return std::nullopt;
        } catch (const std::out_of_range &) {
            // Conversion failed due to out of range
            return std::nullopt;
        }
    }

// Function to search for a product by name or ID
    void searchProduct(DataSet<Product> &products) {
        cout << "Enter the product name or ID to search: ";
        auto searchQuery = inputString();

        // Search by name
        auto found = products.findByName(searchQuery);

        // Search by ID
        auto productId = tryStoi(searchQuery);
        if (productId.has_value()) {
            auto productById = products.findById(*productId);
            if (productById.has_value()) {
                found.push_back(*productById);
            }
        }
        if (!found.empty()) {
            // Products found by name
            cout << "Found " << found.size() << " product(s) by name:" << endl;
            for (const auto &product: found) {
                printProductDetails(product);
            }
        } else {
            // No products found
            cout << "Product not found." << endl;
        }
    }

// Function to display product rankings based on discount price
    void showProductRankings(DataSet<Product> &products) {
        cout << R"(Enter "+" to sort by ascending, "-" by descending, "+" by default: )";
        auto sortType = inputString();

        vector<Product> sorted = products.getProducts();
        sort(sorted.begin(), sorted.end(),
             sortType == "-" ?
             [](const Product &p1, const Product &p2) {
                 return p1.price > p2.price;
             } :
             [](const Product &p1, const Product &p2) {
                 return p1.price < p2.price;
             }
        );

        cout << "Product Rankings (based on price):" << endl;
        for (const auto &product: sorted) {
            printProductDetails(product);
        }
    }
}