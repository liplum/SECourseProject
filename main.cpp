#include <iostream>
#include <nlohmann/json.hpp>

int main() {
  // Create a JSON object
  nlohmann::json data;

  // Add key-value pairs to the JSON object
  data["name"] = "John Doe";
  data["age"] = 25;
  data["city"] = "New York";

  // Convert the JSON object to a string
  std::string jsonStr = data.dump();

  // Print the JSON string
  std::cout << "JSON Data: " << jsonStr << std::endl;

  // Parse a JSON string
  std::string jsonData = R"({"status": "success", "code": 200})";
  nlohmann::json parsedData = nlohmann::json::parse(jsonData);

  // Access values from the parsed JSON
  std::string status = parsedData["status"];
  int code = parsedData["code"];

  // Print the parsed values
  std::cout << "Status: " << status << std::endl;
  std::cout << "Code: " << code << std::endl;

  return 0;
}
