/*Tema 2. Clasa ”Fractie”
- membrii privati pentru numarator si numitor (int);
- constructori pentru initializare si copiere;
- destructor (în cazul alocarii statice, se seteaza dimensiunea vectorului la zero, iar în cazul alocarii
dinamice, se dezaloca zona de memorie utilizata);
- metode publice pentru setat/furnizat numaratorul si numitorul;
- metoda publica pentru simplificare;
- metoda publica de afisare (sub forma &quot;a&quot;, &quot;a/b&quot;, &quot;-a/b&quot;, dupa caz);
- metode publice pentru suma, diferența, produsul si împărțirea a doua numere raționale,
implementate prin supraincarcarea operatorilor +, -, *, /
- metode publice pentru inmultirea unui numar rațional cu un numar întreg, realizata prin
supraincarcarea operatorlui *.
Să se realizeze un program de rezolvare a unui sistem de doua ecuatii liniare cu doua
necunoscute si coeficienti rationali. */




#include <iostream>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
using namespace std;

class rational
{

// date membru protejate(private);
    int ns;//numarator
    int nj;//numitor
// functii membru neprotejate
public:
    int cmmdc(int a,int b);
// constructor folosit la initializare
    rational(int n1=0,int n2=0)
    {
        ns=n1;
        nj=n2;
    }// constructor de copiere
    rational(const rational& r)
    {
        ns=r.sus();
        nj=r.jos();
    }
    int sus() const
    {
        return ns;
    }
    int jos() const
    {
        return nj;
    }
    void setsus(int x)
    {
        ns=x;
    }
    void setjos(int y)
    {
        nj=y;
    }
    rational& operator+= (const rational& r);
    rational& operator-= (const rational& r);
    rational& operator*= (const rational& r);
    rational& operator/= (const rational& r);
    friend std::istream& operator>>(std::istream& is, rational& r);
    friend std::istream& operator<<(std::istream& is, rational& r);
    friend rational operator== (const rational& r1, const rational& r2);
    friend rational operator+ (const rational& r1, const rational& r2);
    friend rational operator- (const rational& r1, const rational& r2);
    friend rational operator* (const rational& r1, const rational& r2);
    friend rational operator/ (const rational& r1, const rational& r2);

    friend void simplifica(rational& r);
};
rational& rational::operator+=(const rational& r)
{
    int z;
    z = ns * r.jos() + nj * r.sus();
    nj= nj * r.jos();
    ns= z;
    return *this;
}
rational& rational::operator-=(const rational& r)
{
    int t=ns*r.jos()-nj*r.sus();
    nj=nj*r.jos();
    ns=t;
    return *this;
}
rational& rational::operator*=(const rational& r)
{
    ns*=r.sus();
    nj*=r.jos();
    return *this;
}
rational& rational::operator/=(const rational& r)
{
    ns/=r.sus();
    nj/=r.jos();
    return *this;
}
int rational::cmmdc(int a, int b)
{
    int r;
    do
    {
        r=a%b;
        a=b;
        b=r;
    }
    while(r);
    return a;
}
std::istream& operator>>(std::istream& is, rational& r)
{
    int x,y;
    is>>x>>y;
    r.setsus(x);
    r.setjos(y);
    return is;
}
std::ostream& operator<<(std::ostream& os, const rational& r)
{
    os<<r.sus()<<" / "<<r.jos();
    return os;
}
int operator==(rational& r1, rational& r2)
{
    simplifica(r1);
    simplifica(r2);
    return r1.sus() == r2.sus()  &&  r1.jos() == r2.jos();
}
rational operator+ (const rational & r1, const rational & r2)
{
    rational r(r1);
    r+=r2;
    return r;
}
rational operator- (const rational& r1, const rational& r2)
{
    rational r(r1);
    r-=r2;
    return r;
}
rational operator* (const rational& r1, const rational& r2)
{
    rational r(r1);
    r*=r2;
    return r;
}
rational operator/ (const rational& r1, const rational& r2)
{
    rational r(r1);
    r/=r2;
    return r;
}
void simplifica(rational& r)
{
    int s=r.sus();
    int j=r.jos();
    int c=r.cmmdc(s,j);
    s/=c;
    j/=c;
    r.setsus(s);
    r.setjos(j);
}
int main()
{

    rational suma,t;
    int n;
    // numarul de numere rationale
    cout<<"numar de termeni = ";
    cin>>n;
    cout<<"Introduceti fractiile cate una pe linie"<<endl;
//initial suma este egala doar cu primul nr. rational
    cin>>t;
    simplifica(t);
    suma=t;//citim si prelucram urmatoarele n-1 nr. rationale
    for(int i=1; i<n; i++)
    {
        cin>>t;
        simplifica(t);
        suma+=t;
        simplifica(suma);
    }
    cout<<suma<<endl;
    getch();
    return 0;
}
