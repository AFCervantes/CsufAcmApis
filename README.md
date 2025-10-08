# CsufAcmApis
A brief introduction of Web APIs in C++

## Overview
This project demonstrates how to make HTTP requests to Web APIs using C++. The example program fetches real-time weather data from [WeatherAPI.com](https://www.weatherapi.com/) and displays it in a user-friendly format.

## What You'll Learn
- How to make HTTP GET requests in C++
- How to work with API responses (JSON format)
- Basic string parsing techniques
- Understanding API keys and endpoints

## Prerequisites
Before you can build and run this program, you need:

1. **A C++ compiler** (g++ recommended)
   - Linux/Mac: Usually pre-installed or available via package manager
   - Windows: Install MinGW or use WSL

2. **libcurl library** - For making HTTP requests
   - **Ubuntu/Debian**: `sudo apt-get install libcurl4-openssl-dev`
   - **Fedora/RHEL**: `sudo dnf install libcurl-devel`
   - **macOS**: `brew install curl`
   - **Windows**: Download from [curl.se](https://curl.se/download.html)

3. **A free API key from WeatherAPI.com**
   - Sign up at: https://www.weatherapi.com/signup.aspx
   - After signing up, copy your API key from the dashboard

## Setup Instructions

1. **Clone this repository**
   ```bash
   git clone https://github.com/AFCervantes/CsufAcmApis.git
   cd CsufAcmApis
   ```

2. **Add your API key**
   - Open `weather_api.cpp` in a text editor
   - Find the line: `string apiKey = "YOUR_API_KEY_HERE";`
   - Replace `YOUR_API_KEY_HERE` with your actual API key from WeatherAPI.com

3. **Build the program**
   ```bash
   make
   ```

4. **Run the program**
   ```bash
   ./weather_api
   ```

## How It Works

### 1. Making the API Request
The program uses libcurl to send an HTTP GET request to the WeatherAPI endpoint:
```
http://api.weatherapi.com/v1/current.json?key=YOUR_KEY&q=LOCATION
```

### 2. Receiving the Response
The API returns weather data in JSON format, which looks like:
```json
{
  "location": {
    "name": "Fullerton",
    "region": "California",
    "country": "USA"
  },
  "current": {
    "temp_c": 22.0,
    "temp_f": 71.6,
    "condition": {
      "text": "Sunny"
    }
  }
}
```

### 3. Parsing and Displaying
The program extracts specific values from the JSON response and displays them in a readable format.

## Customization

You can modify the program to:
- Check weather for different locations (change the `location` variable)
- Extract additional weather data (humidity, wind speed, etc.)
- Display the information in different formats

## Project Structure
```
CsufAcmApis/
├── weather_api.cpp    # Main program file
├── Makefile          # Build configuration
└── README.md         # This file
```

## Troubleshooting

**Error: "curl/curl.h: No such file or directory"**
- Install libcurl development package (see Prerequisites)

**Error: "No response received from API"**
- Check your internet connection
- Verify your API key is correct
- Ensure the API key is placed correctly in the code

**Build errors**
- Make sure g++ is installed: `g++ --version`
- Verify libcurl is installed: `curl-config --version`

## Learning Resources

- [WeatherAPI Documentation](https://www.weatherapi.com/docs/)
- [libcurl Tutorial](https://curl.se/libcurl/c/libcurl-tutorial.html)
- [Understanding REST APIs](https://restfulapi.net/)
- [JSON Format Basics](https://www.json.org/)

## License
This is an educational project for CSUF ACM students.

## Contributors
- CSUF ACM
