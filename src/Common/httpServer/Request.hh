#pragma once

#include <ostream>
#include <iostream>

#include <boost/algorithm/string.hpp>

namespace deadend {
namespace httpServer {

class Request {

/**
HTTP Request format - https://www.w3.org/Protocols/rfc2616/rfc2616.html
Request Line (Method Request-URI HTTP-Version CRLF)
GET www.reddit.com HTTP/1.1

Request       = Request-Line              ; Section 5.1
                *(( general-header        ; Section 4.5
                 | request-header         ; Section 5.3
                 | entity-header ) CRLF)  ; Section 7.1
                 CRLF
                [ message-body ]          ; Section 4.3

general-header = Cache-Control            ; Section 14.9
               | Connection               ; Section 14.10
               | Date                     ; Section 14.18
               | Pragma                   ; Section 14.32
               | Trailer                  ; Section 14.40
               | Transfer-Encoding        ; Section 14.41
               | Upgrade                  ; Section 14.42
               | Via                      ; Section 14.45
               | Warning                  ; Section 14.46

request-header = Accept                   ; Section 14.1
               | Accept-Charset           ; Section 14.2
               | Accept-Encoding          ; Section 14.3
               | Accept-Language          ; Section 14.4
               | Authorization            ; Section 14.8
               | Expect                   ; Section 14.20
               | From                     ; Section 14.22
               | Host                     ; Section 14.23
               | If-Match                 ; Section 14.24
               | If-Modified-Since        ; Section 14.25
               | If-None-Match            ; Section 14.26
               | If-Range                 ; Section 14.27
               | If-Unmodified-Since      ; Section 14.28
               | Max-Forwards             ; Section 14.31
               | Proxy-Authorization      ; Section 14.34
               | Range                    ; Section 14.35
               | Referer                  ; Section 14.36
               | TE                       ; Section 14.39
               | User-Agent               ; Section 14.43

entity-header  = Allow                    ; Section 14.7
               | Content-Encoding         ; Section 14.11
               | Content-Language         ; Section 14.12
               | Content-Length           ; Section 14.13
               | Content-Location         ; Section 14.14
               | Content-MD5              ; Section 14.15
               | Content-Range            ; Section 14.16
               | Content-Type             ; Section 14.17
               | Expires                  ; Section 14.21
               | Last-Modified            ; Section 14.29
**/
public:
struct eHttpMethod {
  enum type {
    OPTIONS = 0,
    GET     = 1,  
    HEAD    = 2,
    POST    = 3,
    PUT     = 4,
    DELETE  = 5,
    TRACE   = 6,
    CONNECT = 7,
    NONE    = 8};

  friend std::ostream &operator<<(std::ostream &out, const eHttpMethod::type value) {
    switch (value) {
      case eHttpMethod::OPTIONS: {
        return out << "OPTIONS";
      }
      case eHttpMethod::GET: {
        return out << "GET";
      }
      case eHttpMethod::HEAD: {
        return out << "HEAD";
      }
      case eHttpMethod::POST: {
        return out << "POST";
      }
      case eHttpMethod::PUT: {
        return out << "PUT";
      }
      case eHttpMethod::DELETE: {
        return out << "DELETE";
      }
      case eHttpMethod::TRACE: {
        return out << "TRACE";
      }
      case eHttpMethod::CONNECT: {
        return out << "CONNECT";
      }
      default: {
        return out << "*unknown* [value=" << int(value) << ']';
      }
    }
  }  
};

struct eHttpEntityHeader {
  enum type {
    Allow           = 0,
    ContentEncoding = 1,
    ContentLanguage = 2,
    ContentLength   = 3,
    ContentLocation = 4,
    ContentMD5      = 5,
    ContentRange    = 6,
    ContentType     = 7,
    Expires         = 8,
    LastModified    = 9,
    NONE            = 10};

  friend std::ostream &operator<<(std::ostream &out, const eHttpEntityHeader::type value) {
    switch (value) {
      case eHttpEntityHeader::Allow: {
        return out << "Allow";
      }
      case eHttpEntityHeader::ContentEncoding: {
        return out << "Content-Encoding";
      }
      case eHttpEntityHeader::ContentLanguage: {
        return out << "Content-Language";
      }
      case eHttpEntityHeader::ContentLength: {
        return out << "Content-Length";
      }
      case eHttpEntityHeader::ContentLocation: {
        return out << "Content-Location";
      }
      case eHttpEntityHeader::ContentMD5: {
        return out << "Content-MD5";
      }
      case eHttpEntityHeader::ContentRange: {
        return out << "Content-Range";
      }
      case eHttpEntityHeader::ContentType: {
        return out << "Content-Type";
      }
      case eHttpEntityHeader::Expires: {
        return out << "Expires";
      }
      case eHttpEntityHeader::LastModified: {
        return out << "Last-Modified";
      }
      default: {
        return out << "*unknown* [value=" << int(value) << ']';
      }
    }
  }
};

struct eHttpGeneralHeader {
  enum type {
    CacheControl     = 0,
    Connection       = 1,
    Date             = 2,
    Pragma           = 3,
    Trailer          = 4,
    TransferEncoding = 5,
    Upgrade          = 6,
    Via              = 7,
    Warning          = 8,
    NONE             = 9};

  friend std::ostream &operator<<(std::ostream &out, const eHttpGeneralHeader::type value) {
    switch (value) {
      case eHttpGeneralHeader::CacheControl: {
        return out << "Cache-Control";
      }
      case eHttpGeneralHeader::Connection: {
        return out << "Connection";
      }
      case eHttpGeneralHeader::Date: {
        return out << "Date";
      }
      case eHttpGeneralHeader::Pragma: {
        return out << "Pragma";
      }
      case eHttpGeneralHeader::Trailer: {
        return out << "Trailer";
      }
      case eHttpGeneralHeader::TransferEncoding: {
        return out << "Transfer-Encoding";
      }
      case eHttpGeneralHeader::Upgrade: {
        return out << "Upgrade";
      }
      case eHttpGeneralHeader::Via: {
        return out << "Via";
      }
      case eHttpGeneralHeader::Warning: {
        return out << "Warning";
      }
      default: {
        return out << "*unknown* [value=" << int(value) << ']';
      }
    }
  }  
};

struct eHttpRequestHeader {
  enum type {
    Accept             = 0,
    AcceptCharset      = 1,
    AcceptEncoding     = 2,
    AcceptLanguage     = 3,
    Authorization      = 4,
    Expect             = 5,
    From               = 6,
    Host               = 7,
    IfMatch            = 8,
    IfModifiedSince    = 9,
    IfNoneMatch        = 10,
    IfRange            = 11,
    IfUnmodifiedSince  = 12,
    MaxForwards        = 13,
    ProxyAuthorization = 14,
    Range              = 15,
    Referer            = 16,
    TE                 = 17,
    UserAgent          = 18,
    NONE               = 19};

  friend std::ostream &operator<<(std::ostream &out, const eHttpRequestHeader::type value) {
      switch (value) {
        case eHttpRequestHeader::Accept: {
          return out << "Accept";
        }
        case eHttpRequestHeader::AcceptCharset: {
          return out << "Accept-Charset";
        }
        case eHttpRequestHeader::AcceptEncoding: {
          return out << "Accept-Encoding";
        }
        case eHttpRequestHeader::AcceptLanguage: {
          return out << "Accept-Language";
        }
        case eHttpRequestHeader::Authorization: {
          return out << "Authorization";
        }
        case eHttpRequestHeader::Expect: {
          return out << "Expect";
        }
        case eHttpRequestHeader::From: {
          return out << "From";
        }
        case eHttpRequestHeader::Host: {
          return out << "Host";
        }
        case eHttpRequestHeader::IfMatch: {
          return out << "If-Match";
        }
        case eHttpRequestHeader::IfModifiedSince: {
          return out << "If-Modified-Since";
        }
        case eHttpRequestHeader::IfNoneMatch: {
          return out << "If-None-Match";
        }
        case eHttpRequestHeader::IfRange: {
          return out << "If-Range";
        }
        case eHttpRequestHeader::IfUnmodifiedSince: {
          return out << "If-Unmodified-Since";
        }
        case eHttpRequestHeader::MaxForwards: {
          return out << "Max-Forwards";
        }
        case eHttpRequestHeader::ProxyAuthorization: {
          return out << "Proxy-Authorization";
        }
        case eHttpRequestHeader::Range: {
          return out << "Range";
        }
        case eHttpRequestHeader::Referer: {
          return out << "Referer";
        }
        case eHttpRequestHeader::TE: {
          return out << "TE";
        }
        case eHttpRequestHeader::UserAgent: {
          return out << "UserAgent";
        }

        default: {
          return out << "*unknown* [value=" << int(value) << ']';
        }
      }
  }
};


public:
  Request() :
  m_method(eHttpMethod::NONE){}
  ~Request() {}

  void dumpRequest() {
    std::cout << *this << ":"                 << std::endl
              << "==========================" << std::endl
              << m_version                    << std::endl
              << "==========================" << std::endl
              << "METHOD[" << m_method << "]" << std::endl
              << "PATH["   << m_path   << "]" << std::endl
              << "ENTITY HEADERS["            << std::endl;
    for (auto entityIterator = m_entityHeaders.begin();
         entityIterator != m_entityHeaders.end();
         ++entityIterator) {
      std::cout << entityIterator->first << ": " << entityIterator->second << std::endl;
    }
    std::cout << "]" << std::endl
              << "GENERAL HEADERS["           << std::endl;
    for (auto generalIterator = m_generalHeaders.begin();
         generalIterator != m_generalHeaders.end();
         ++generalIterator) {
      std::cout << generalIterator->first << ": " << generalIterator->second << std::endl;
    }
    std::cout << "]" << std::endl
              << "REQUEST HEADERS["           << std::endl;
    for (auto requestIterator = m_requestHeaders.begin();
         requestIterator != m_requestHeaders.end();
         ++requestIterator) {
      std::cout << requestIterator->first << ": " << requestIterator->second << std::endl;
    }
    std::cout << "]" << std::endl;

  }
  // METHOD
  eHttpMethod::type getMethod() {
    return m_method;
  }

  bool setMethod(std::string method) {
    if (method == "OPTIONS") {
      m_method = eHttpMethod::OPTIONS;
      return true;
    }
    else if (method == "GET") {
      m_method = eHttpMethod::GET;
      return true;
    }
    else if (method == "HEAD") {
      m_method = eHttpMethod::HEAD;
      return true;
    }
    else if (method == "POST") {
      m_method = eHttpMethod::POST;
      return true;
    }
    else if (method == "PUT") {
      m_method = eHttpMethod::PUT;
      return true;
    }
    else if (method == "DELETE") {
      m_method = eHttpMethod::DELETE;
      return true;
    }
    else if (method == "TRACE") {
      m_method = eHttpMethod::TRACE;
      return true;
    }
    else if (method == "CONNECT") {
      m_method = eHttpMethod::CONNECT;
      return true;
    }

    std::cout << *this << ": Invalid HTTP METHOD[" << method << "]" << std::endl;
    return false;
  }

  // PATH
  std::string getPath() {
    return m_path;
  }
  void setPath(std::string path) {
    m_path = path;
  }

  // VERS
  std::string getVersion() {
    return m_version;
  }
  void setVersion(std::string version) {
    m_version = version;
  }

  void setHeader(std::string line) {
    // Should be of the format [field: value]
    std::vector<std::string> items;

    std::string header = line.substr(0, line.find(":"));

    // Just an empty line
    if (header.size() == 0) {
      return;
    }

    // Remove the ': '
    line.erase(0, line.find(":")+2);
    std::string value = line;


    // Entity Headers
    if (header == "Allow") {
      m_entityHeaders.insert(std::pair<eHttpEntityHeader::type, std::string>(eHttpEntityHeader::Allow, value));
    }
    else if (header == "Content-Encoding") {
      m_entityHeaders.insert(std::pair<eHttpEntityHeader::type, std::string>(eHttpEntityHeader::ContentEncoding, value));
    }
    else if (header == "Content-Language") {
      m_entityHeaders.insert(std::pair<eHttpEntityHeader::type, std::string>(eHttpEntityHeader::ContentLanguage, value));
    }
    else if (header == "Content-Length") {
      m_entityHeaders.insert(std::pair<eHttpEntityHeader::type, std::string>(eHttpEntityHeader::ContentLength, value));
    }
    else if (header == "Content-Location") {
      m_entityHeaders.insert(std::pair<eHttpEntityHeader::type, std::string>(eHttpEntityHeader::ContentLocation, value));
    }
    else if (header == "Content-MD5") {
      m_entityHeaders.insert(std::pair<eHttpEntityHeader::type, std::string>(eHttpEntityHeader::ContentMD5, value));
    }
    else if (header == "Content-Range") {
      m_entityHeaders.insert(std::pair<eHttpEntityHeader::type, std::string>(eHttpEntityHeader::ContentRange, value));
    }
    else if (header == "Content-Type") {
      m_entityHeaders.insert(std::pair<eHttpEntityHeader::type, std::string>(eHttpEntityHeader::ContentType, value));
    }
    else if (header == "Expires") {
      m_entityHeaders.insert(std::pair<eHttpEntityHeader::type, std::string>(eHttpEntityHeader::Expires, value));
    }
    else if (header == "Last-Modified") {
      m_entityHeaders.insert(std::pair<eHttpEntityHeader::type, std::string>(eHttpEntityHeader::LastModified, value));
    }
    // General Headers
    else if (header == "Cache-Control") {
      m_generalHeaders.insert(std::pair<eHttpGeneralHeader::type, std::string>(eHttpGeneralHeader::CacheControl, value));
    }
    else if (header == "Connection") {
      m_generalHeaders.insert(std::pair<eHttpGeneralHeader::type, std::string>(eHttpGeneralHeader::Connection, value));
    }
    else if (header == "Date") {
      m_generalHeaders.insert(std::pair<eHttpGeneralHeader::type, std::string>(eHttpGeneralHeader::Date, value));
    }
    else if (header == "Pragma") {
      m_generalHeaders.insert(std::pair<eHttpGeneralHeader::type, std::string>(eHttpGeneralHeader::Pragma, value));
    }
    else if (header == "Trailer") {
      m_generalHeaders.insert(std::pair<eHttpGeneralHeader::type, std::string>(eHttpGeneralHeader::Trailer, value));
    }
    else if (header == "Transfer-Encoding") {
      m_generalHeaders.insert(std::pair<eHttpGeneralHeader::type, std::string>(eHttpGeneralHeader::TransferEncoding, value));
    }
    else if (header == "Upgrade") {
      m_generalHeaders.insert(std::pair<eHttpGeneralHeader::type, std::string>(eHttpGeneralHeader::Upgrade, value));
    }
    else if (header == "Via") {
      m_generalHeaders.insert(std::pair<eHttpGeneralHeader::type, std::string>(eHttpGeneralHeader::Via, value));
    }
    else if (header == "Warning") {
      m_generalHeaders.insert(std::pair<eHttpGeneralHeader::type, std::string>(eHttpGeneralHeader::Warning, value));
    }
    // Request Headers
    else if (header == "Accept") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::Accept, value));
    }
    else if (header == "Accept-Charset") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::AcceptCharset, value));
    }
    else if (header == "Accept-Encoding") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::AcceptEncoding, value));
    }
    else if (header == "Accept-Language") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::AcceptLanguage, value));
    }
    else if (header == "Authorization") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::Authorization, value));
    }
    else if (header == "Expect") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::Expect, value));
    }
    else if (header == "From") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::From, value));
    }
    else if (header == "Host") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::Host, value));
    }
    else if (header == "If-Match") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::IfMatch, value));
    }
    else if (header == "If-Modified-Since") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::IfModifiedSince, value));
    }
    else if (header == "If-None-Match") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::IfNoneMatch, value));
    }
    else if (header == "If-Range") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::IfRange, value));
    }
    else if (header == "If-Unmodified-Since") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::IfUnmodifiedSince, value));
    }
    else if (header == "Max-Forwards") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::MaxForwards, value));
    }
    else if (header == "Proxy-Authorization") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::ProxyAuthorization, value));
    }
    else if (header == "Range") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::Range, value));
    }
    else if (header == "Referer") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::Referer, value));
    }
    else if (header == "TE") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::TE, value));
    }
    else if (header == "UserAgent") {
      m_requestHeaders.insert(std::pair<eHttpRequestHeader::type, std::string>(eHttpRequestHeader::UserAgent, value));
    }
    else {
      std::cout << *this << ": Unknown header[" << header << "]" << std::endl;
    }
  }
private:
  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const Request &) {
    return out << "Request";
  }
  eHttpMethod::type m_method;
  std::string m_path;
  std::string m_version;
  std::map<eHttpEntityHeader::type,  std::string> m_entityHeaders;
  std::map<eHttpGeneralHeader::type, std::string> m_generalHeaders;
  std::map<eHttpRequestHeader::type, std::string> m_requestHeaders;
};

}
}
