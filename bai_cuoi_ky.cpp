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

//khach hang
class Khach_hang {
private:
    string ma_khach;
    string ten_khach;
    string so_dt;

public:
    Khach_hang() {
        ma_khach = "";
        ten_khach = "";
        so_dt = "";
    }

    string get_ma() {return ma_khach;}
    string get_ten() {return ten_khach;}

    void nhap_kh() {
        cout<<"ma KH: ";
        cin>>ma_khach;
        cin.ignore();
        cout<<"ten: ";
        getline(cin, ten_khach);
        cout<<"sdt: ";
        cin>>so_dt;
    }

    void xuat_kh() {
        cout<<ma_khach<<" | "<<ten_khach<<" | "<<so_dt<<endl;
    }
};

//hoa don dat phong
class Hoa_don {
private:
    string ma_hd;
    Khach_hang khach;
    Phong* phong_dat;
    int so_ngay;

public:
    Hoa_don() {
        ma_hd = "";
        phong_dat = NULL;
        so_ngay = 0;
    }

    void set_ma(string ma) {ma_hd = ma;}
    void set_khach(Khach_hang k) {khach = k;}
    void set_phong(Phong* p) {phong_dat = p;}
    void set_ngay(int n) {so_ngay = n;}
    string get_ma() {return ma_hd;}

    double tinh_tien() {
        if(phong_dat != NULL)
            return phong_dat->tinh_gia() * so_ngay;
        return 0;
    }

    friend double tinh_giam(Hoa_don& hd, double gg) {
        double tien = hd.tinh_tien();
        return tien - tien * (gg / 100);
    }

    void xuat_hd() {
        cout<<"ma HD: "<<ma_hd<<endl;
        cout<<"khach: "; khach.xuat_kh();
        cout<<"phong: ";
        if(phong_dat != NULL) cout<<phong_dat->getma();
        cout<<endl;
        cout<<"so ngay: "<<so_ngay<<endl;
        cout<<"tong tien: "<<tinh_tien()<<endl;
    }
};

int main() {
    return 0;
}