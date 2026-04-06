#include <iostream>
#include <string>
#include <cstdio>
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

int main()
{
    Phong* dsphong[50];
    int sophong = 0;
    Khach_hang dskh[50];
    int sokh = 0;
    Hoa_don dshd[50];
    int sohd = 0;
    int chon;

    while(true)
    {
        printf("\nQuan Ly Khac San\n");
        printf("1.them phong\n");
        printf("2.danh sach phong\n");
        printf("3.them khach hang\n");
        printf("4.dat phong\n");
        printf("5.xem hoa don\n");
        printf("6.tim phong\n");
        printf("0.thoat\n");
        printf("chon: ");
        cin >> chon;
        if(chon == 0) { printf("thoat chuong trinh\n"); break; }

        switch(chon)
        {
        case 1:
        {
            int loai;
            cout << "1:thuong 2:vip: "; cin >> loai;
            if(loai == 1) dsphong[sophong] = new Phong_thuong();
            else dsphong[sophong] = new Phong_vip();
            dsphong[sophong]->nhap();
            sophong++;
            cout << "them phong thanh cong roi dang co " << Phong::get_sl() << " phong\n";
            break;
        }
        case 2:
        {
            if(sophong == 0) { cout << "chua co phong nao het\n"; break; }
            cout << "danh sach phong hien tai:\n";
            for(int i = 0; i < sophong; i++)
            {
                cout << i+1 << ". ";
                cout << *dsphong[i];
            }
            break;
        }
        case 3:
        {
            dskh[sokh].nhap_kh();
            sokh++;
            cout << "da them khach hang moi\n";
            break;
        }
        case 4:
        {
            if(sophong == 0 || sokh == 0) { cout << "chua co phong hoac chua co khach\n"; break; }
            cout << "cac phong dang trong:\n";
            for(int i = 0; i < sophong; i++)
            {
                if(dsphong[i]->gettt() == 0)
                {
                    cout << i << ". ";
                    cout << *dsphong[i];
                }
            }
            int ichon, ikhach, nn;
            cout << "chon so thu tu phong:"; cin >> ichon;
            cout << "danh sach khach hang:\n";
            for(int i = 0; i < sokh; i++)
            {
                cout << i << ". ";
                dskh[i].xuat_kh();
            }
            cout << "chon so thu tu khach:"; cin >> ikhach;
            cout << "so ngay o:"; cin >> nn;

            string mahd;
            fflush(stdin);
            cout << "nhap ma hoa don:"; cin >> mahd;
            dshd[sohd].set_ma(mahd);
            dshd[sohd].set_khach(dskh[ikhach]);
            dshd[sohd].set_phong(dsphong[ichon]);
            dshd[sohd].set_ngay(nn);
            dsphong[ichon]->settt(1);

            double tien = dshd[sohd].tinh_tien();
            cout << "dat phong thanh cong tong tien la:" << tien << endl;
            double gg;
            cout << "giam gia % nhap 0 neu khong:"; cin >> gg;
            if(gg > 0)
            {
                cout << "tien sau khi giam gia con lai:" << tinh_giam(dshd[sohd], gg) << endl;
            }
            sohd++;
            break;
        }
        case 5:
        {
            if(sohd == 0) { cout << "chua co hoa don nao\n"; break; }
            cout << "tat ca hoa don:\n";
            for(int i = 0; i < sohd; i++)
            {
                cout << "hoa don thu " << i+1 << ":\n";
                dshd[i].xuat_hd();
            }
            break;
        }
        case 6:
        {
            string matim;
            cout << "nhap ma phong muon tim:"; cin >> matim;
            bool found = false;
            for(int i = 0; i < sophong; i++)
            {
                if(dsphong[i]->getma() == matim)
                {
                    cout << *dsphong[i];
                    found = true; break;
                }
            }
            if(!found) cout << "khong tim thay phong nay\n";
            break;
        }
        default: cout << "khong co lua chon nay\n";
        }

    }
    for(int i = 0; i < sophong; i++) delete dsphong[i];
    return 0;
}