//
// Created by Liplum on 6/12/2023.
//

#include <iostream>
#include "ui.h"
#include "auth.h"
#include "../../shared/utils.h"

namespace ui {
    void inputBook(Book &p) {
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
    void addBook(DataSet<Book> &books) {
        // Get input for the new product details
        Book p;
        inputBook(p);

        // Add the new product to the DataSet<Book>
        books.addRow(p.name, p.price, p.discount, p.premiumPrice);
        cout << "Book added successfully!" << endl;
    }

// Function to delete a product
    bool deleteBook(DataSet<Book> &books) {
        // Get the ID of the product to delete
        cout << "Enter the product ID to delete: ";
        auto id = inputInt();

        auto product = books.findById(id);
        if (!product.has_value()) {
            cout << "Book not found." << endl;
            return false;
        }

        cout << "Ensure to delete product " << product->name << "? ";
        bool ensure = inputInt();
        if (!ensure) {
            return false;
        }

        // Attempt to remove the product by ID
        if (books.removeById(id)) {
            cout << "Book deleted successfully!" << endl;
            return true;
        } else {
            cout << "Failed to delete product." << endl;
            return false;
        }
    }

// Function to modify a product
    bool modifyBook(DataSet<Book> &books) {
        // Get the ID of the product to modify
        cout << "Enter the product ID to modify: ";
        auto id = inputInt();

        // Find the product by ID
        auto product = books.findById(id);

        // Check if the product exists
        if (!product.has_value()) {
            cout << "Book not found." << endl;
            return false;
        }
        // Get input for the updated product details
        inputBook(*product);
        if (books.update(*product)) {
            cout << "Book modified successfully!" << endl;
            return true;
        } else {
            cout << "Failed to delete product." << endl;
            return false;
        }
    }

    void printBookDetails(const Book &product) {
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
    void searchBook(DataSet<Book> &books) {
        cout << "Enter the product name or ID to search: ";
        auto searchQuery = inputString();

        // Search by name
        auto found = books.findByName(searchQuery);

        // Search by ID
        auto productId = tryStoi(searchQuery);
        if (productId.has_value()) {
            auto productById = books.findById(*productId);
            if (productById.has_value()) {
                found.push_back(*productById);
            }
        }
        if (!found.empty()) {
            // Books found by name
            cout << "Found " << found.size() << " product(s) by name:" << endl;
            for (const auto &product: found) {
                printBookDetails(product);
            }
        } else {
            // No books found
            cout << "Book not found." << endl;
        }
    }
}