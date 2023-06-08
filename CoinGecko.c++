#include <iostream>
#include <curl/curl.h>
#include <json/json.h>

int main() {
    // Initialize CURL
    CURL* curl = curl_easy_init();
    if (curl == NULL) {
        std::cerr << "Failed to initialize CURL." << std::endl;
        return 1;
    }

    // Set URL to CoinGecko API endpoint for Bitcoin price
    std::string url = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd";

    // Set up CURL options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Create a string to store the API response
    std::string response_string;

    // Write the response data to the string
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CURLOPT_WRITEFUNCTION);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    // Perform the CURL request
    CURLcode res = curl_easy_perform(curl);

    // Check if the request was successful
    if (res != CURLE_OK) {
        std::cerr << "Failed to fetch Bitcoin price from CoinGecko API: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        return 1;
    }

    // Parse the JSON response using the JsonCpp library
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errors;

    bool parsingSuccessful = Json::parseFromStream(builder, response_string, &root, &errors);
    if (!parsingSuccessful) {
        std::cerr << "Failed to parse Bitcoin price response from CoinGecko API: " << errors << std::endl;
        curl_easy_cleanup(curl);
        return 1;
    }

    // Extract the Bitcoin price from the response
    double bitcoin_price_usd = root["bitcoin"]["usd"].asDouble();
    std::cout << "The current price of Bitcoin is $" << bitcoin_price_usd << std::endl;

    // Clean up
    curl_easy_cleanup(curl);

    return 0;
}