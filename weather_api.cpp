/*
 * Introduction to APIs in C++
 * 
 * This program demonstrates how to make HTTP requests to a Web API
 * and process the response. We'll use weatherapi.com to get current
 * weather information for a specific location.
 * 
 * Concepts covered:
 * - Making HTTP GET requests
 * - Working with JSON responses
 * - String manipulation and parsing
 * 
 * Note: This is a simplified example for educational purposes.
 * For production code, you would want more robust error handling
 * and JSON parsing using a library like nlohmann/json.
 */

#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

// This callback function gets called by libcurl when data is received
// It appends the received data to our string buffer
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) {
    // Calculate total size of the received data
    size_t totalSize = size * nmemb;
    
    // Append the received data to our string
    userp->append((char*)contents, totalSize);
    
    // Return the number of bytes processed
    return totalSize;
}

// Function to make an API request and return the response
string makeAPIRequest(const string& url) {
    CURL* curl;
    CURLcode res;
    string response;
    
    // Initialize libcurl
    curl = curl_easy_init();
    
    if(curl) {
        // Set the URL for the request
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        // Set the callback function to handle received data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        
        // Pass our string to the callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        // Follow redirects if any
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        
        // Perform the request
        res = curl_easy_perform(curl);
        
        // Check for errors
        if(res != CURLE_OK) {
            cerr << "Error: " << curl_easy_strerror(res) << endl;
        }
        
        // Clean up
        curl_easy_cleanup(curl);
    }
    
    return response;
}

// Simple function to extract a value from JSON response
// Note: This is a basic implementation. In real projects, use a proper JSON library
string extractJSONValue(const string& json, const string& key) {
    // Find the key in the JSON string
    string searchKey = "\"" + key + "\":";
    size_t keyPos = json.find(searchKey);
    
    if (keyPos == string::npos) {
        return "Not found";
    }
    
    // Find the start of the value (after the colon and any spaces)
    size_t valueStart = json.find_first_not_of(" ", keyPos + searchKey.length());
    
    // Determine if the value is a string (starts with quote) or number
    char firstChar = json[valueStart];
    size_t valueEnd;
    
    if (firstChar == '"') {
        // String value - find the closing quote
        valueStart++; // Move past the opening quote
        valueEnd = json.find('"', valueStart);
    } else {
        // Number value - find the next comma, closing brace, or closing bracket
        valueEnd = json.find_first_of(",}]", valueStart);
    }
    
    return json.substr(valueStart, valueEnd - valueStart);
}

int main() {
    cout << "=== Weather API Demo ===" << endl;
    cout << "This program demonstrates how to use Web APIs in C++" << endl << endl;
    
    // API Configuration (hardcoded for simplicity)
    // Note: In a real application, you should protect your API key
    // Get a free API key from: https://www.weatherapi.com/
    string apiKey = "YOUR_API_KEY_HERE";  // Replace with your actual API key
    string location = "Fullerton";        // Location to check weather for
    
    // Construct the API URL
    // The API endpoint format: http://api.weatherapi.com/v1/current.json?key=KEY&q=LOCATION
    string apiUrl = "http://api.weatherapi.com/v1/current.json?key=" + apiKey + "&q=" + location;
    
    cout << "Requesting weather data for: " << location << endl;
    cout << "Please wait..." << endl << endl;
    
    // Make the API request
    string jsonResponse = makeAPIRequest(apiUrl);
    
    // Check if we got a response
    if (jsonResponse.empty()) {
        cerr << "Error: No response received from API" << endl;
        return 1;
    }
    
    // Display the raw JSON response (helpful for learning)
    cout << "Raw API Response:" << endl;
    cout << "-------------------" << endl;
    cout << jsonResponse << endl << endl;
    
    // Extract and display specific weather information
    cout << "Parsed Weather Information:" << endl;
    cout << "-------------------" << endl;
    
    // Extract location information
    string locationName = extractJSONValue(jsonResponse, "name");
    string region = extractJSONValue(jsonResponse, "region");
    string country = extractJSONValue(jsonResponse, "country");
    
    // Extract weather data
    string tempC = extractJSONValue(jsonResponse, "temp_c");
    string tempF = extractJSONValue(jsonResponse, "temp_f");
    string condition = extractJSONValue(jsonResponse, "text");
    string humidity = extractJSONValue(jsonResponse, "humidity");
    string windKph = extractJSONValue(jsonResponse, "wind_kph");
    
    // Display the extracted information
    cout << "Location: " << locationName << ", " << region << ", " << country << endl;
    cout << "Temperature: " << tempC << "°C (" << tempF << "°F)" << endl;
    cout << "Conditions: " << condition << endl;
    cout << "Humidity: " << humidity << "%" << endl;
    cout << "Wind Speed: " << windKph << " km/h" << endl;
    
    cout << endl << "=== End of Demo ===" << endl;
    
    return 0;
}
