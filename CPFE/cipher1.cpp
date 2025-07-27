#include <iostream>


// Begin the Obsfucation from here
#include <string>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cctype>

namespace magic {
    // XOR key for encryption
    const char XOR_KEY = 0x42;  // Simple XOR key
    const int NUM_GROUPS = 5;   // Number of groups (adjustable)
    
    // Helper class to handle both print and return
    class PoofResult {
        std::string value;
        int group;
    public:
        PoofResult(const std::string& v, int g) : value(v), group(g) {
            std::cout << "Poof:" << value << std::endl;
            std::cout << "You are Group " << group << std::endl;
        }
        operator std::string() const { return value; }
    };
    
    // Function to get current datetime in "1-July-2025-6:54-pm" format
    std::string getDateTime() {
        time_t now = time(0);           // Get current time
        tm* ltm = localtime(&now);      // Convert to local time struct
        
        // Month names array
        const char* months[] = {"January","February","March","April","May","June",
                               "July","August","September","October","November","December"};
        
        // Format hour for 12-hour clock
        int hour = ltm->tm_hour;
        std::string ampm = (hour >= 12) ? "pm" : "am";
        if (hour > 12) hour -= 12;
        if (hour == 0) hour = 12;
        
        // Build datetime string
        std::stringstream ss;
        ss << ltm->tm_mday << "-" << months[ltm->tm_mon] << "-" 
           << (1900 + ltm->tm_year) << "-" << hour << ":" 
           << std::setfill('0') << std::setw(2) << ltm->tm_min 
           << "-" << ampm;
        
        return ss.str();
    }
    
    // XOR encryption function
    std::string xorEncrypt(const std::string& str) {
        std::string encrypted = str;
        for (size_t i = 0; i < encrypted.length(); i++) {
            encrypted[i] = encrypted[i] ^ XOR_KEY;
        }
        return encrypted;
    }
    
    // Main function: combines, reverses, then encrypts with XOR
    PoofResult poof(const std::string& n) {
        // Extract last digit from input string
        int lastDigit = 0;
        for (int i = n.length() - 1; i >= 0; i--) {
            if (isdigit(n[i])) {
                lastDigit = n[i] - '0';  // Convert char to int
                break;
            }
        }
        
        // Calculate group number (1-indexed)
        int group = (lastDigit % NUM_GROUPS) + 1;
        
        std::string dt = getDateTime();                     // Get current datetime
        std::string combined = n + "$" + dt;                // Combine with $ separator
        std::reverse(combined.begin(), combined.end());     // Invert all characters
        std::string encrypted = xorEncrypt(combined);       // XOR encrypt
        return PoofResult(encrypted, group);                // Return result (prints automatically)
    }
}
// End the Obsfucation from here


int main() {
    magic::poof("ly1165");
    return 0;
}