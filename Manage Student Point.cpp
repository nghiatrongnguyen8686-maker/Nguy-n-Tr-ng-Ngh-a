#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// ===================== PHẦN 1: QUẢN LÝ ĐIỂM SINH VIÊN =====================
struct Diem {
    float diem;
};

struct SinhVien {
    string maSV;
    string tenSV;
    Diem diemToan, diemVatLy, diemTiengAnh, diemCTDLGT;
    SinhVien* prev;
    SinhVien* next;
};

class DanhSachSinhVien {
private:
    SinhVien* head;

    void swapSinhVien(SinhVien* a, SinhVien* b) {
        swap(a->maSV, b->maSV);
        swap(a->tenSV, b->tenSV);
        swap(a->diemToan, b->diemToan);
        swap(a->diemVatLy, b->diemVatLy);
        swap(a->diemTiengAnh, b->diemTiengAnh);
        swap(a->diemCTDLGT, b->diemCTDLGT);
    }

public:
    DanhSachSinhVien() { head = nullptr; }

    void nhapSinhVien() {
        while (true) {
            SinhVien* sv = new SinhVien;
            cout << "\nNhap ma sinh vien (nhap $ de ket thuc): ";
            cin >> sv->maSV;
            if (sv->maSV == "$") { delete sv; break; }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nhap ten sinh vien: ";
            getline(cin, sv->tenSV);
            cout << "Nhap diem Toan: "; cin >> sv->diemToan.diem;
            cout << "Nhap diem Vat ly: "; cin >> sv->diemVatLy.diem;
            cout << "Nhap diem Tieng Anh: "; cin >> sv->diemTiengAnh.diem;
            cout << "Nhap diem CTDL&GT: "; cin >> sv->diemCTDLGT.diem;

            sv->prev = nullptr;
            sv->next = head;
            if (head != nullptr) head->prev = sv;
            head = sv;
        }
    }

    float tinhDiemTrungBinh(SinhVien* sv) {
        return (sv->diemToan.diem + sv->diemVatLy.diem +
                sv->diemTiengAnh.diem + sv->diemCTDLGT.diem) / 4.0;
    }

    void sapXepDiemToan() {
        for (SinhVien* i = head; i != nullptr; i = i->next) {
            for (SinhVien* j = i->next; j != nullptr; j = j->next) {
                if (i->diemToan.diem > j->diemToan.diem) swapSinhVien(i, j);
            }
        }
        cout << "Da sap xep sinh vien theo diem Toan tang dan.\n";
    }

    void sapXepDiemTrungBinh() {
        for (SinhVien* i = head; i != nullptr; i = i->next) {
            for (SinhVien* j = i->next; j != nullptr; j = j->next) {
                if (tinhDiemTrungBinh(i) > tinhDiemTrungBinh(j)) swapSinhVien(i, j);
            }
        }
        cout << "Da sap xep sinh vien theo diem trung binh tang dan.\n";
    }

    void timSinhVienMaxMin() {
        if (!head) return;
        SinhVien* maxSV = head;
        SinhVien* minSV = head;
        for (SinhVien* sv = head; sv != nullptr; sv = sv->next) {
            if (tinhDiemTrungBinh(sv) > tinhDiemTrungBinh(maxSV)) maxSV = sv;
            if (tinhDiemTrungBinh(sv) < tinhDiemTrungBinh(minSV)) minSV = sv;
        }
        cout << "Sinh vien diem trung binh cao nhat: " << maxSV->tenSV << endl;
        cout << "Sinh vien diem trung binh thap nhat: " << minSV->tenSV << endl;
    }

    void hienThiDiemTrungBinhTrongKhoang(float a, float b) {
        for (SinhVien* sv = head; sv != nullptr; sv = sv->next) {
            float diemTB = tinhDiemTrungBinh(sv);
            if (diemTB > a && diemTB < b) {
                cout << "Sinh vien: " << sv->tenSV << " - Diem TB: " << diemTB << endl;
            }
        }
    }
};

// ===================== PHẦN 2: QUẢN LÝ NHÂN SỰ =====================
struct CanBo {
    int maCB;
    string hoTen, phongBan, chucVu;
    float heSoLuong;
    CanBo* prev;
    CanBo* next;
};

class DanhSachCanBo {
private:
    CanBo* head;

public:
    DanhSachCanBo() { head = nullptr; }

    void nhapCanBo() {
        while (true) {
            CanBo* cb = new CanBo;
            cout << "\nNhap ma can bo (ma <= 0 de ket thuc): ";
            cin >> cb->maCB;
            if (cb->maCB <= 0) { delete cb; break; }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nhap ho ten: "; getline(cin, cb->hoTen);
            cout << "Nhap phong ban: "; getline(cin, cb->phongBan);
            cout << "Nhap chuc vu: "; getline(cin, cb->chucVu);
            cout << "Nhap he so luong: "; cin >> cb->heSoLuong;

            cb->prev = nullptr;
            cb->next = head;
            if (head != nullptr) head->prev = cb;
            head = cb;
        }
    }

    void themCanBo() {
        CanBo* cb = new CanBo;
        cout << "\nNhap ma can bo: "; cin >> cb->maCB;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nhap ho ten: "; getline(cin, cb->hoTen);
        cout << "Nhap phong ban: "; getline(cin, cb->phongBan);
        cout << "Nhap chuc vu: "; getline(cin, cb->chucVu);
        cout << "Nhap he so luong: "; cin >> cb->heSoLuong;

        cb->prev = nullptr;
        cb->next = head;
        if (head != nullptr) head->prev = cb;
        head = cb;
    }

    void tinhLuong() {
        cout << "\n===== DANH SACH LUONG CAN BO =====\n";
        CanBo* cb = head;
        while (cb != nullptr) {
            float luong = cb->heSoLuong * 1150000;
            cout << setw(25) << left << cb->hoTen
                 << " | Luong: " << fixed << setprecision(0) << luong << endl;
            cb = cb->next;
        }
    }

    void thongKeTheoPhongBan() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string phongBan;
        cout << "\nNhap phong ban: "; getline(cin, phongBan);

        bool found = false;
        for (CanBo* cb = head; cb != nullptr; cb = cb->next) {
            if (cb->phongBan == phongBan) {
                cout << cb->hoTen << " - " << cb->chucVu
                     << " (He so luong: " << cb->heSoLuong << ")\n";
                found = true;
            }
        }
        if (!found) cout << "Khong co can bo nao trong phong ban nay.\n";
    }

    void hienThiHeSoLuong() {
        bool found = false;
        for (CanBo* cb = head; cb != nullptr; cb = cb->next) {
            if (cb->heSoLuong >= 4.9) {
                cout << cb->hoTen << " - He so luong: " << cb->heSoLuong << endl;
                found = true;
            }
        }
        if (!found) cout << "Khong co can bo nao co he so luong >= 4.9\n";
    }

    void hienThiHeSoLuongTrongKhoang(float a, float b) {
        bool found = false;
        for (CanBo* cb = head; cb != nullptr; cb = cb->next) {
            if (cb->heSoLuong > a && cb->heSoLuong < b) {
                cout << cb->hoTen << " - He so luong: " << cb->heSoLuong << endl;
                found = true;
            }
        }
        if (!found) cout << "Khong co can bo nao trong khoang nay.\n";
    }
};

// ===================== MAIN =====================
int main() {
    DanhSachSinhVien dsSV;
    DanhSachCanBo dsCB;
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Quan ly diem sinh vien\n";
        cout << "2. Quan ly nhan su\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        if (choice == 1) {
            int svChoice;
            do {
                cout << "\n===== MENU SINH VIEN =====\n";
                cout << "1. Nhap danh sach sinh vien\n";
                cout << "2. Sap xep theo diem Toan\n";
                cout << "3. Sap xep theo diem trung binh\n";
                cout << "4. Tim sinh vien diem TB max/min\n";
                cout << "5. Hien thi sinh vien theo diem TB trong khoang\n";
                cout << "6. Quay lai\n";
                cout << "Nhap lua chon: ";
                cin >> svChoice;

                switch (svChoice) {
                    case 1: dsSV.nhapSinhVien(); break;
                    case 2: dsSV.sapXepDiemToan(); break;
                    case 3: dsSV.sapXepDiemTrungBinh(); break;
                    case 4: dsSV.timSinhVienMaxMin(); break;
                    case 5: {
                        float a, b;
                        cout << "Nhap khoang a, b: "; cin >> a >> b;
                        dsSV.hienThiDiemTrungBinhTrongKhoang(a, b);
                        break;
                    }
                    case 6: break;
                    default: cout << "Lua chon sai!\n"; break;
                }
            } while (svChoice != 6);

        } else if (choice == 2) {
            int nhanSuChoice;
            do {
                cout << "\n===== MENU NHAN SU =====\n";
                cout << "1. Nhap danh sach can bo\n";
                cout << "2. Them can bo\n";
                cout << "3. Tinh luong\n";
                cout << "4. Thong ke theo phong ban\n";
                cout << "5. Hien thi can bo he so luong >= 4.9\n";
                cout << "6. Hien thi can bo theo he so luong trong khoang\n";
                cout << "7. Quay lai\n";
                cout << "Nhap lua chon: ";
                cin >> nhanSuChoice;

                switch (nhanSuChoice) {
                    case 1: dsCB.nhapCanBo(); break;
                    case 2: dsCB.themCanBo(); break;
                    case 3: dsCB.tinhLuong(); break;
                    case 4: dsCB.thongKeTheoPhongBan(); break;
                    case 5: dsCB.hienThiHeSoLuong(); break;
                    case 6: {
                        float a, b;
                        cout << "Nhap khoang a, b: "; cin >> a >> b;
                        dsCB.hienThiHeSoLuongTrongKhoang(a, b);
                        break;
                    }
                    case 7: break;
                    default: cout << "Lua chon sai!\n"; break;
                }
            } while (nhanSuChoice != 7);
        }

    } while (choice != 0);

    cout << "\nCam on ban da su dung chuong trinh!\n";
    cout << "\n";
    return 0;
}
