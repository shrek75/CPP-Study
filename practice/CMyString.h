#pragma once


class CMyString
{
    private:
    //문자열을 저장하기 위해 동적 할당한 메모리를 가리키는 포인터
    char *data_;
    //저장된 문자열의 길이
    int length_;

    public:
    CMyString();
    ~CMyString() ;
    CMyString(const CMyString& param);
    CMyString(const char* param);
    CMyString& operator=(const CMyString&);
    int SetString(const char* param);
    int SetString(int x) = delete;
    const char* GetString() const;
    int GetLength() const;
    operator const char* (void) const;
    char& operator [] (int);
    char operator[] (int) const;
    int operator++(); //전위식
    int operator++(int);//후위식
    int Release();
};
