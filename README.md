# Communication Contract
1. Communication will take place over Discord.
2. Respond to teammates within 24 hours.
3. A back-up plan for microservices will take effect if a team member has become unresponsive for over 72 hours.
4. Establish clear deadlines and stick to them.
5. Ask for help when needed and provide help when able.

# How to Request data from the Microservice
You must first start the microservice, which will then continuously check the file "request.txt".

In order to request data from the Microservice, you must write keywords "user" or "default" into file "request.txt". 

## Pseudocode Example
        1. Get user input to determine whether the microservice should return default values or previous ones.
        2. Open the request.txt file for writing.
        3. Write "user" or "default" based on input.
        4. Close request.txt file.

## C++ Code Example
        cout << "Select an option (1: New Session, 2: Load Previous Session): ";
        string user_input;
        cin >> user_input;

        ofstream requestFile(request.txt);

        if (user_input == "1") {
            requestFile << "default";
        }
        else if (user_input == "2") {
            requestFile << "user";
        }
        else {
            cout << "Invalid selection. Exiting.\n";
            return 0;
        }

        requestFile.close();


# How to Receive data from the Microservice
Upon receiving the request, the Microservice will determine what kind of a request it is and based on this evaluation use appropriate file to copy into "response.txt":
1. If "request.txt" contains the keyword **user**, it will use values from "user_data.txt"
2. If "request.txt" contains the keyword **default**, it will use values from "default_data.txt"

If "user_data.txt" or "default_data.txt" files are needed but are missing, an error message will be printed in "response.txt" notifying the user that the files are missing.

After the service has copied the data to "response.txt", it will clear the file "request.txt" and continue to listen for more requests.

Once the microservice completed the task, the main program can retrieve the requested data from the file "response.txt" - the formatting will be the same as the one in source files ("user_data.txt" / "default_data.txt").

## Pseudocode Example
        1. Open the response.txt file for reading.
        2. Parse each line (and display/store in variables etc).
        3. Close response.txt file.


## C++ Code Example
    ifstream responseFile(response.txt);
    string line;

    while (getline(responseFile, line)) {
        // Process each line (for example, printing it)
        cout << "Parsed Line: " << line << endl;
    }
    
    // Close file
    responseFile.close();

# UML Diagram
![Sequence Diagram](https://github.com/user-attachments/assets/50873903-f8da-41a0-b468-b655357ae7c4)
