// CPFE - C++ Assignment Template
// ACADEMIC INTEGRITY NOTICE: Modifying the sealed section below will result
// in automatic detection and academic consequences.
// ============================================================================
// BEGIN SEALED SECTION - DO NOT MODIFY
#include <iostream>
#include<string>
#include<ctime>
#include<algorithm>
#include<sstream>
#include<iomanip>
#include<cctype>
namespace m{const char X=66,G=5;class P{std::string v;int g;public:P(const std::string&a,int b):v(a),g(b){char p[]={80,111,111,102,58,0},y[]={89,111,117,32,97,114,101,32,71,114,111,117,112,32,0};std::cout<<p<<v<<"\n"<<y<<g<<"\n";}operator std::string()const{return v;}};std::string D(){time_t n=time(0);tm*l=localtime(&n);char m[][4]={{74,97,110,0},{70,101,98,0},{77,97,114,0},{65,112,114,0},{77,97,121,0},{74,117,110,0},{74,117,108,0},{65,117,103,0},{83,101,112,0},{79,99,116,0},{78,111,118,0},{68,101,99,0}};int h=l->tm_hour;char p[]={112,109,0},a[]={97,109,0};std::string z=(h>=12)?p:a;if(h>12)h-=12;if(h==0)h=12;std::stringstream s;s<<l->tm_mday<<char(45)<<m[l->tm_mon]<<char(45)<<(1900+l->tm_year)<<char(45)<<h<<char(58)<<std::setfill(char(48))<<std::setw(2)<<l->tm_min<<char(45)<<z;return s.str();}std::string E(const std::string&s){std::string e=s;for(size_t i=0;i<e.length();i++)e[i]=e[i]^X;return e;}P p(const std::string&n){int d=0;for(int i=n.length()-1;i>=0;i--)if(isdigit(n[i])){d=n[i]-48;break;}int g=(d%G)+1;std::string t=D(),c=n+char(36)+t;std::reverse(c.begin(),c.end());std::string e=E(c);return P(e,g);}}
// END SEALED SECTION

// ============================================================================
// YOUR ASSIGNMENT BEGINS HERE
// Follow the instructions provided assignment pdf. Leave the line m::p("mae8");
// ============================================================================


int main() {
    m::p("mae8");  // <-- REPLACE mae8 with your NetID (e.g., "abc123")

   


    return 0;
}