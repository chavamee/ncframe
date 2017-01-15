#include "api/Response.hpp"

Response::Response()
{
}

long Response::StatusCode() const
{
    return m_statusCode;
}
