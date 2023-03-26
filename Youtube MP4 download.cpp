#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    ofstream* file = static_cast<ofstream*>(userdata);
    file->write(ptr, size * nmemb);
    return size * nmemb;
}

int main() {
    // Set the YouTube video ID and the output file name
    string video_id = "VIDEO_ID_HERE";
    string file_name = "OUTPUT_FILE_NAME_HERE.mp4";
    
    // Construct the YouTube video URL
    string url = "https://www.youtube.com/watch?v=" + video_id;

    // Initialize curl
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    if (curl) {
        // Set the options
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
        
        // Send the request and retrieve the response
        curl_easy_perform(curl);
        
        // Get the final URL after the redirection
        char* final_url;
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &final_url);
        
        // Construct the download URL
        url = final_url;
        url = url.substr(0, url.find("&")) + "&format=mp4&quality=hd720";
        
        // Set the output file stream
        ofstream file(file_name, ios::binary);
        if (!file) {
            cerr << "Failed to open output file" << endl;
            return 1;
        }
        
        // Set the options
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
        
        // Send the request and retrieve the response
        CURLcode res = curl_easy_perform(curl);
        
        // Clean up
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        
        if (res != CURLE_OK) {
            cerr << "Failed to download video" << endl;
            return 1;
        }
        
        cout << "Video downloaded successfully" << endl;
        return 0;
    }
}
