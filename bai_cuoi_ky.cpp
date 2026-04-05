#include <iostream>
#include <string>
using namespace std;

class Phong {
protected:
    string ma_p;
    string ten_p;
    double gia;
    int tt;

public:
    Phong() {
        ma_p="";
        ten_p="";
        gia=0;
        tt=0;
    }
    ~Phong() {}
    string getma() {return ma_p;}
    string getten() {return ten_p;}
    int gettt() {return tt;}
    void settt(int x) {tt=x;}
    virtual double tinh_gia() = 0;
    virtual void nhap() {
        cout<<"ma phong: "; cin>>ma_p;
        cin.ignore();
        cout<<"ten phong: "; getline(cin,ten_p);
        cout<<"gia: "; cin>>gia;
        while(gia<0) {cout<<"nhap lai: "; cin>>gia;}
    }
    virtual void xuat() {
        cout<<ma_p<<" | "<<ten_p<<" | "<<tinh_gia()
            <<" | "<<(tt==0 ? "Trong" : "Co khach")<<endl;
    }
};

class Phong_thuong : public Phong {
public:
    Phong_thuong() : Phong() {}
    double tinh_gia() {return gia;}
    void nhap() {
        cout<<"phong thuong\n";
        Phong::nhap();
    }
};

class Phong_vip : public Phong {
private:
    double phu_thu;
public:
    Phong_vip() : Phong() {phu_thu=0;}
    double tinh_gia() {return gia+phu_thu;}
    void nhap() {
        cout<<"phong vip\n";
        Phong::nhap();
        cout<<"phu thu: "; cin>>phu_thu;
        while(phu_thu<0) {cout<<"nhap lai: "; cin>>phu_thu;}
    }
};

int main() {
    return 0;
}