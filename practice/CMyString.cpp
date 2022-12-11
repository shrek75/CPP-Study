#include <iostream>
#include "CMyString.h"


CMyString::CMyString():data_(nullptr),length_(0)
{
    
}
CMyString::~CMyString()
{

}
CMyString::CMyString(const CMyString & param)
{
    this->SetString(param.GetString());
}
CMyString & CMyString::operator=(const CMyString & param)
{
    this->SetString(param.GetString());
    return *this;
}
int CMyString::SetString(const char* param)
{
    
    int i = 0;
    if(param == NULL) return -1;
    while(true)
    {
        if(param[i] == '\0') break;
        i++;
    }
    if(i == 0) return -1;
    CMyString::data_ = new char[i+1];
    for(int j = 0; j<=i;j++)
    {
        data_[j] = param[j];
    }
    CMyString::length_ = i;

    return 0;
}
const char* CMyString::GetString() const
{
    
    if(data_ == nullptr) return "NULL";
    return data_;
}
int CMyString::Release()
{
    if(this->data_ != nullptr)
    delete [] this->data_;
   
    return 0;
}
CMyString::CMyString(const char * param)
{
    SetString(param);
}
int CMyString::GetLength() const
{
    return length_;
}
CMyString::operator const char *(void) const
{
    return GetString();
}
char& CMyString::operator[](int param)
{
    return data_[param];
}
char CMyString::operator[](int param) const
{
    return data_[param];
}