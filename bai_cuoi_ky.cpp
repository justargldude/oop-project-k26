#include <iostream>
#include <string>
using namespace std;

class Phong {
protected:
    string ma_p;
    string ten_p;
    double gia;
    int tt;
    static int sl_phong;

public:
    Phong() {
        ma_p="";
        ten_p="";
        gia=0;
        tt=0;
        sl_phong++;
    }
    virtual ~Phong() {
        sl_phong--;
    }
    static int get_sl() {return sl_phong;}
    string getma() {return ma_p;}
    string getten() {return ten_p;}
    int gettt() {return tt;}
    void settt(int x) {tt=x;}
    virtual double tinh_gia() = 0;
    bool operator==(Phong& p) {
        return ma_p==p.ma_p;
    }
    friend ostream& operator<<(ostream& os, Phong& p) {
        p.xuat();
        return os;
    }
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
int Phong::sl_phong = 0;

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