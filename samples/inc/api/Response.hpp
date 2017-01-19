#ifndef Response_H_
#define Response_H_ value

#include <vector>

/**
 * HTTP Response type
 */
class Response {
    friend class Request;

    public:
        Response();
        long StatusCode() const;

    private:
        long m_statusCode;
};

#endif /* ifndef Response_H_ */
