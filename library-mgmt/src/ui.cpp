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
        auto $int = nonNegativeInputBox(inputInt);
        p.collection = $int.getInput("collection");
        p.rest = $int.getInput("rest");
    }


    // Function to add a new product
    void addBook(DataSet <Book> &books) {
        // Get input for the new product details
        Book p;
        inputBook(p);

        // Add the new product to the DataSet<Book>
        books.addRow(p);
        cout << "Book added successfully!" << endl;
    }

// Function to delete a product
    bool deleteBook(DataSet <Book> &books) {
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
    bool modifyBook(DataSet <Book> &books) {
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

    void printBookDetails(const Book &book) {
        cout << "ID: " << book.id << ", Name: " << book.name
             << ", Collection: " << book.rest << "/" << book.collection << endl;
    }

    // Function to search for a product by name or ID
    void searchBook(DataSet <Book> &books) {
        cout << "Enter the book name or ID to search: ";
        auto searchQuery = inputString();

        // Search by name
        auto found = findByName(books, searchQuery);

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
            cout << "Found " << found.size() << " book(s) by name:" << endl;
            for (const auto &book: found) {
                printBookDetails(book);
            }
        } else {
            // No books found
            cout << "Book not found." << endl;
        }
    }
}