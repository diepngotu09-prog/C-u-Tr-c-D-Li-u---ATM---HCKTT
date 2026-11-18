#include "QuanLyTaiKhoan.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include <filesystem>

using namespace std;

bool QuanLyTaiKhoan::docFile(string ID, TaiKhoan& tk) {

    // Ham xoa khoang trang dau va cuoi chuoi
    auto xoaKhoangTrang = [](string& str) {
        size_t dau = str.find_first_not_of(" \t\r\n");

        if (dau == string::npos) {
            str.clear();
            return;
        }

        size_t cuoi = str.find_last_not_of(" \t\r\n");
        str = str.substr(dau, cuoi - dau + 1);
    };

    // Chuan hoa ID
    xoaKhoangTrang(ID);

    string tenFile = "data/" + ID + ".txt";
    ifstream file(tenFile);

    if (!file.is_open()) {
        return false;
    }

    string dong;
    size_t viTri;

    // Doc ID
    if (!getline(file, dong)) return false;

    viTri = dong.find(':');
    if (viTri == string::npos) return false;

    string id = dong.substr(viTri + 1);
    xoaKhoangTrang(id);
    tk.setID(id);

    // Doc ten tai khoan
    if (!getline(file, dong)) return false;

    viTri = dong.find(':');
    if (viTri == string::npos) return false;

    string ten = dong.substr(viTri + 1);
    xoaKhoangTrang(ten);
    tk.setTenChuTaiKhoan(ten);

    // Doc so du
    if (!getline(file, dong)) return false;

    viTri = dong.find(':');
    if (viTri == string::npos) return false;

    string soDu = dong.substr(viTri + 1);
    xoaKhoangTrang(soDu);

    try {
        size_t viTriCuoi;
        double tien = stod(soDu, &viTriCuoi);

        if (viTriCuoi != soDu.size() || tien < 0) {
            return false;
        }

        tk.setSoDu(tien);
    }
    catch (...) {
        return false;
    }

    // Doc don vi tien te
    if (!getline(file, dong)) return false;

    viTri = dong.find(':');
    if (viTri == string::npos) return false;

    string loaiTien = dong.substr(viTri + 1);
    xoaKhoangTrang(loaiTien);
    tk.setLoaiTienTe(loaiTien);

    file.close();
    return true;
}

bool QuanLyTaiKhoan::ghiFile(const TaiKhoan& tk) {
    string tenFile = "data/" + tk.getID() + ".txt";

    ofstream file(tenFile);

    if (!file.is_open()) {
        cout << "Khong mo duoc file: " << tenFile << endl;
        return false;
    }

    file << fixed << setprecision(0);

    file << "ID: " << tk.getID() << endl;
    file << "Ten tai khoan: " << tk.getTenChuTaiKhoan() << endl;
    file << "So du tai khoan: " << tk.getSoDu() << endl;
    file << "Don vi: " << tk.getLoaiTienTe() << endl;

    file.close();

    return !file.fail();
}
void QuanLyTaiKhoan::xuatThongTin(const TaiKhoan& tk) {
    cout << fixed << setprecision(0);

    cout << "ID: " << tk.getID() << endl;
    cout << "Ten tai khoan: " << tk.getTenChuTaiKhoan() << endl;
    cout << "So du tai khoan: "
         << tk.getSoDu() << " " << tk.getLoaiTienTe() << endl;
    cout << "Don vi: " << tk.getLoaiTienTe() << endl;
}

vector<string> QuanLyTaiKhoan::docDanhSachID() {
    vector<string> dsID;
    ifstream file("data/DanhSachID.txt");

    string ID;
    while (getline(file, ID)) {
        if (!ID.empty())
            dsID.push_back(ID);
    }

    file.close();
    return dsID;
}

bool QuanLyTaiKhoan::kiemTraTrungID(string ID) {
    vector<string> dsID = docDanhSachID();

    for (const string& id : dsID) {
        if (id == ID) {
            return true; // ID đã tồn tại
        }
    }

    return false; // ID chưa tồn tại
}
