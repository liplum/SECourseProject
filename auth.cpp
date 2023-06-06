//
// Created by Liplum on 6/6/23.
//

#include "auth.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// Function to save user information to JSON file
void saveUsersToFile(const std::vector<User>& users, const std::string& filename) {
  json jsonData;
  for (const auto& user : users) {
    json userData;
    userData["username"] = user.username;
    userData["password"] = user.password;
    userData["userType"] = (user.userType == UserType(true, true, true)) ? "admin" : "regular";
    jsonData.push_back(userData);
  }

  std::ofstream file(filename);
  if (file.is_open()) {
    file << jsonData.dump(4) << std::endl;
    std::cout << "User data saved to " << filename << std::endl;
  } else {
    std::cerr << "Unable to save user data to file." << std::endl;
  }
  file.close();
}

// Function to load user information from JSON file
std::vector<User> loadUsersFromFile(const std::string& filename) {
  std::vector<User> users;
  std::ifstream file(filename);
  if (file.is_open()) {
    json jsonData;
    file >> jsonData;
    for (const auto& userData : jsonData) {
      User user;
      user.username = userData["username"];
      user.password = userData["password"];
      std::string userType = userData["userType"];
      if (userType == "admin") {
        user.userType = UserType(true, true, true);
      } else {
        user.userType = UserType(true, false, false);
      }
      users.push_back(user);
    }
    std::cout << "User data loaded from " << filename << std::endl;
  } else {
    std::cerr << "Unable to load user data from file." << std::endl;
  }
  file.close();
  return users;
}

// Function to find a user by username
User* findUserByUsername(std::vector<User>& users, const std::string& username) {
  auto it = std::find_if(users.begin(), users.end(), [username](const User& user) {
    return user.username == username;
  });

  if (it != users.end()) {
    return &(*it);
  } else {
    return nullptr;
  }
}

// Function to authenticate user login
bool userLogin(std::vector<User>& users) {
  std::string username, password;
  int attempts = 0;

  while (attempts < 3) {
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    User* user = findUserByUsername(users, username);

    if (user != nullptr && user->password == password) {
      std::cout << "Login successful." << std::endl;
      return true;
    } else {
      std::cout << "Invalid username or password. Please try again." << std::endl;
      attempts++;
    }
  }

  std::cout << "Maximum login attempts exceeded. Exiting program." << std::endl;
  return false;
}

int main() {
  std::vector<User> users = loadUsersFromFile("user_data.json");
  bool loggedIn = false;

  while (true) {
    if (!loggedIn) {
      if (!userLogin(users)) {
        break;
      }
      loggedIn = true;
    }

    // Your main menu and other functions here

    break; // Placeholder to exit the loop for demonstration
  }

  saveUsersToFile(users, "user_data.json");
  return 0;
}
