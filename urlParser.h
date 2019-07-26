//
//  urlParser.h
//  DyMasServer
//
//  Created by  on 2018/6/29.
//  Copyright © 2018年 . All rights reserved.
//

#ifndef urlParser_h
#define urlParser_h

#include <string>
using namespace std;


class UrlParser
{
public:
    UrlParser(const char* url);
    const string GetScheme() const
    {
        return m_scheme;
    }
    const string GetHost() const
    {
        return m_host;
    }
    const string GetPort() const
    {
        return m_port;
    }
    const string GetPath() const
    {
        return m_path;
    }
    const string GetQuery() const
    {
        return m_query;
    }
    const string GetFragment() const
    {
        return m_fragment;
    }
    const string GetUserName() const
    {
        return m_username;
    }
    const string GetPassword() const
    {
        return m_password;
    }
private:
    bool Init(const char* url);
    bool IsSchemeChar(int c)
    {
        return (!isalpha(c) && '+' != c && '-' != c && '.' != c) ? 0 : 1;
    }
private:
    string m_scheme;               /* mandatory */
    string m_host;                 /* mandatory */
    string m_port;                 /* optional */
    string m_path;                 /* optional */
    string m_query;                /* optional */
    string m_fragment;             /* optional */
    string m_username;             /* optional */
    string m_password;             /* optional */
};


#endif /* urlParser_h */
