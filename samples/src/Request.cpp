#include "Request.hpp"
#include "Response.hpp"
#include <stdexcept>
#include <cassert>
#include <stdio.h>
#include <curl/curl.h>
#include <json/json.h>

Request::Request(const std::string& url) :
    m_handle(curl_easy_init()),
    m_headers(NULL),
    m_url(url),
    m_userAgent("Mozilla/4.0")
{
}

Request::~Request()
{
    curl_easy_cleanup(m_handle);
}

void Request::SetUserAgent(const std::string& userAgent)
{
    m_userAgent = userAgent;
}

void Request::SetHeaders(std::initializer_list<StringKeyValuePair> headers)
{

    for (auto &header : headers) {
        m_headers = curl_slist_append(m_headers, (header.first + ": " + header.second).c_str());
    }
    curl_easy_setopt(m_handle, CURLOPT_HTTPHEADER, m_headers);
}

void Request::SetParameters(std::initializer_list<StringKeyValuePair> parameters)
{
    assert(parameters.size() != 0);
    for (auto& param : parameters) {
        std::string escapedValue = curl_easy_escape(m_handle, param.second.c_str(), 0);
        std::string escapedKey = curl_easy_escape(m_handle, param.first.c_str(), 0);
        m_parameters += escapedKey + "=" + escapedValue + "&";
    }
}

void Request::SetOutputFile(const std::string& filePath)
{
    m_filePath = filePath;
}

void Request::SetBody(const std::string& body)
{
    curl_easy_setopt(m_handle, CURLOPT_POSTFIELDS, body.c_str());
}

Response Request::Get()
{
    FILE *fileHandle = NULL;
    if (not m_filePath.empty()) {
        fileHandle = fopen(m_filePath.c_str(), "wb");
        curl_easy_setopt(m_handle, CURLOPT_WRITEDATA, fileHandle);
    }

    Response resp;

    curl_easy_setopt(m_handle, CURLOPT_URL, (m_url + m_parameters).c_str());
    curl_easy_setopt(m_handle, CURLOPT_FOLLOWLOCATION, true);
    curl_easy_setopt(m_handle, CURLOPT_AUTOREFERER, true);
    curl_easy_setopt(m_handle, CURLOPT_DNS_CACHE_TIMEOUT, 360);
    curl_easy_setopt(m_handle, CURLOPT_TIMEOUT, 20);

    m_curlRes = curl_easy_perform(m_handle);

    if (m_curlRes != CURLE_OK) {
        throw std::runtime_error("Curl operation failed");
    }

    curl_easy_getinfo(m_handle, CURLINFO_RESPONSE_CODE, &m_responseCode);

    resp.m_statusCode = m_responseCode;

    if (fileHandle) {
        fclose(fileHandle);
    }

    return resp;
}

Response Request::Post()
{
    Response resp;
    FILE* fileHandle = NULL;
    if (not m_filePath.empty()) {
        fileHandle = fopen(m_filePath.c_str(), "wb");
        curl_easy_setopt(m_handle, CURLOPT_WRITEDATA, fileHandle);
    }

    curl_easy_setopt(m_handle, CURLOPT_USERAGENT, m_userAgent.c_str());
    curl_easy_setopt(m_handle, CURLOPT_URL, m_url.c_str());
    curl_easy_setopt(m_handle, CURLOPT_POST, true);

    m_curlRes = curl_easy_perform(m_handle);

    if (fileHandle) {
        fclose(fileHandle);
    }

    return resp;
}
