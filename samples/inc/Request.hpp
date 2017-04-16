/**
 * @file
 * Defines a Request type which adds a simple wrapper to libcurl.
 */
#ifndef REQUESTS_H_
#define REQUESTS_H_ value

#include <string>
#include <curl/curl.h>
#include <initializer_list>
#include <utility>

/*
 * TODO: Define a better way to define parameters for a request
 */

//TODO: Headers should accept string or number types

class Response;

/**
 * @class Simple libcurl Wrapper
 */
class Request {
    public:
        /**
         * Alias for a std::string pair.
         */
        using StringKeyValuePair = std::pair<std::string, std::string>;

        Request() = delete;

        /**
         * Construct a new request for a URL
         *
         * @param url  host to make the request to
         */
        Request(const std::string& url);


        /**
         * Destructor
         */
        ~Request();

        /**
         * Set request headers
         *
         * @param headers  a list of headers to add to the request
         */
        void SetHeaders(std::initializer_list<StringKeyValuePair> headers);

        /**
         * Set User Agent
         *
         * @param userAgent  set the User-Agent for the request
         */
        void SetUserAgent(const std::string& userAgent);

        /**
         * Set Request parameters
         *
         * @param parameters a list of parameters to add to the request
         */
        void SetParameters(std::initializer_list<StringKeyValuePair> parameters);

        void SetOutputFile(const std::string& filePath);

        /**
         * Set the request body.
         *
         * This only affects a POST request.
         *
         * @param body a string to set the body to
         */
        void SetBody(const std::string& body);

        /**
         * Send a GET request
         *
         * @return a response received by the request
         */
        Response Get();

        /**
         * Send a POST Request
         *
         * @return a response received by the request
         */
        Response Post();

        /**
         * Explicitly initialize curl with curl_global_init.
         * This should be called before using Request objects in
         * threads
         */
        static void InitializeGlobalCurl();

        /**
         * Explicitly cleanup curl with curl_global_cleanup.
         * This should be called before using Request objects in
         * threads
         */
        static void CleanupGlobalCurl();

    private:
        /**
         * Handle to curl easy interface
         */
        CURL *m_handle;
        CURLcode m_curlRes;
        struct curl_slist *m_headers;
        long m_responseCode;
        std::string m_url;
        std::string m_userAgent;
        std::string m_filePath;
        std::string m_parameters = "?";
};

#endif /* ifndef REQUESTS_H_ */
