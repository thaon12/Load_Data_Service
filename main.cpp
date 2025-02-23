#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

// File path constants
const string REQUEST_FILE = "request.txt";
const string RESPONSE_FILE = "response.txt";
const string DEFAULT_DATA_FILE = "default_data.txt";
const string USER_DATA_FILE = "user_data.txt";

void processRequest() {
    while (true) {
        this_thread::sleep_for(chrono::seconds(1));
        ifstream requestFile(REQUEST_FILE);
        if (!requestFile) {
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }

        string requestType;
        getline(requestFile, requestType);
        requestFile.close();

        if (requestType.empty()) {  // No new request
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }

        string responseData;
        if (requestType == "default") {
            ifstream defaultFile(DEFAULT_DATA_FILE);
            if (defaultFile) {
                getline(defaultFile, responseData);
                defaultFile.close();
            }
            else {
                responseData = "Error: Default data file missing.";
            }
        }
        else if (requestType == "user") {
            ifstream userFile(USER_DATA_FILE);
            if (userFile) {
                getline(userFile, responseData);
                userFile.close();
            }
            else {
                responseData = "Warning: User data missing. Returning default values.";
                ifstream defaultFile(DEFAULT_DATA_FILE);
                if (defaultFile) {
                    getline(defaultFile, responseData);
                    defaultFile.close();
                }
                else {
                    responseData = "Error: Default data file missing.";
                }
            }
        }
        else {
            responseData = "Invalid request type.";
        }

        // Write response to response.txt
        ofstream responseFile(RESPONSE_FILE);
        if (responseFile) {
            responseFile << responseData;
            responseFile.close();
        }

        // **Reset the request file** after processing
        ofstream resetRequest(REQUEST_FILE, ofstream::trunc);  // Truncate file to clear content
        resetRequest.close();

        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    cout << "Microservice is running. Waiting for requests...\n";
    processRequest();
    return 0;
}
