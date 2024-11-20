#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class movie {
private:
    string name;      
    float ticket_price; 
    int show_times;     
    float rating;      

public:
    movie() {}
    movie(string name, float ticket_price, int show_times, float rating)
        : name(name), ticket_price(ticket_price), show_times(show_times), rating(rating) {}

    friend istream& operator>>(istream& in, movie& mv) {
        cout << "Nhap ten phim: ";
        in.ignore();
        getline(in, mv.name);
        cout << "Nhap gia ve: ";
        in >> mv.ticket_price;
        cout << "Nhap so luong suat chieu: ";
        in >> mv.show_times;
        cout << "Nhap diem danh gia: ";
        in >> mv.rating;
        return in;
    }

    friend ostream& operator<<(ostream& out, const movie& mv) {
        out << "Ten phim: " << mv.name
            << ", Gia ve: " << mv.ticket_price
            << ", So luong suat chieu: " << mv.show_times
            << ", Diem danh gia: " << mv.rating;
        return out;
    }

    // Getter cho các thu?c tính
    string get_name() const { return name; }
    float get_ticket_price() const { return ticket_price; }
    float get_rating() const { return rating; } // Thêm getter cho rating
};

class movie_list {
private:
    vector<movie> movies;

public:
    bool is_empty() const {
        return movies.empty();
    }

    // Thêm phim vào danh sách
    void add_movie() {
        int count;
        cout << "Nhap so luong phim can them: ";
        cin >> count;

        for (int i = 0; i < count; ++i) {
            cout << "\nNhap thong tin phim thu " << i + 1 << ":\n";
            movie mv;
            cin >> mv;
            movies.push_back(mv);
        }
    }

    void display_movies() const {
        for (const auto& mv : movies) {
            cout << mv << endl;
        }
    }

    void sort_movies() {
        sort(movies.begin(), movies.end(), [](const movie& a, const movie& b) {
            return a.get_rating() > b.get_rating(); // S? d?ng getter thay v? truy c?p tr?c ti?p
        });
        cout << "Danh sach phim da duoc sap xep theo diem danh gia (tu cao den thap):\n";
        display_movies();
    }

    movie find_most_expensive_movie() const {
        return *max_element(movies.begin(), movies.end(), [](const movie& a, const movie& b) {
            return a.get_ticket_price() < b.get_ticket_price();
        });
    }

    movie find_cheapest_movie() const {
        return *min_element(movies.begin(), movies.end(), [](const movie& a, const movie& b) {
            return a.get_ticket_price() < b.get_ticket_price();
        });
    }

    movie* find_movie_by_name(const string& name) {
        for (auto& mv : movies) {
            if (mv.get_name() == name) return &mv;
        }
        return nullptr;
    }

    void delete_movie_by_name(const string& name) {
        movies.erase(remove_if(movies.begin(), movies.end(), [name](const movie& mv) {
            return mv.get_name() == name;
        }), movies.end());
    }
};

class app {
private:
    movie_list mv_list;

public:
    void menu() {
        int choice;
        do {
            cout << "\n=== Menu Quan Ly Phim ===\n";
            cout << "1. Them phim\n";
            cout << "2. Hien thi danh sach phim\n";
            cout << "3. Sap xep phim theo diem danh gia\n";
            cout << "4. Tim phim co gia ve cao nhat\n";
            cout << "5. Tim phim co gia ve thap nhat\n";
            cout << "6. Tim phim theo ten\n";
            cout << "7. Xoa phim theo ten\n";
            cout << "0. Thoat\n";
            cout << "Lua chon cua ban: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    mv_list.add_movie();
                    break;
                case 2:
                    mv_list.display_movies();
                    break;
                case 3:
                    mv_list.sort_movies();
                    break;
                case 4: {
                    if (!mv_list.is_empty()) {
                        movie most_expensive = mv_list.find_most_expensive_movie();
                        cout << "Phim co gia ve cao nhat: " << most_expensive << endl;
                    } else {
                        cout << "Danh sach phim trong.\n";
                    }
                    break;
                }
                case 5: {
                    if (!mv_list.is_empty()) {
                        movie cheapest = mv_list.find_cheapest_movie();
                        cout << "Phim co gia ve thap nhat: " << cheapest << endl;
                    } else {
                        cout << "Danh sach phim trong.\n";
                    }
                    break;
                }
                case 6: {
                    string name;
                    cout << "Nhap ten phim can tim: ";
                    cin.ignore();
                    getline(cin, name);
                    movie* mv = mv_list.find_movie_by_name(name);
                    if (mv != nullptr)
                        cout << "Thong tin phim: " << *mv << endl;
                    else
                        cout << "Khong tim thay phim co ten " << name << endl;
                    break;
                }
                case 7: {
                    string name;
                    cout << "Nhap ten phim can xoa: ";
                    cin.ignore();
                    getline(cin, name);
                    mv_list.delete_movie_by_name(name);
                    cout << "Da xoa phim co ten " << name << endl;
                    break;
                }
                case 0:
                    cout << "Thoat chuong trinh.\n";
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long chon lai.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    app application;
    application.menu();
    return 0;
}

