#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Class Question
class Question {
private:
    string questionText;
    string options[4];
    int correctAnswer;
    int currentOrder[4];

public:
    Question() {
        for (int i = 0; i < 4; ++i) {
            currentOrder[i] = i;
        }
    }
    
    Question(const string& text, const string options_[4], int correct) {
        questionText = text;
        for (int i = 0; i < 4; ++i) {
            options[i] = options_[i];
            currentOrder[i] = i;
        }
        correctAnswer = correct;
    }
    
    void shuffleOptions() {
        for (int i = 3; i > 0; --i) {
            int j = rand() % (i + 1);
            int temp = currentOrder[i];
            currentOrder[i] = currentOrder[j];
            currentOrder[j] = temp;
        }
    }
    
    void display() const {
        cout << questionText << "\n\n";
        for (int i = 0; i < 4; ++i) {
            cout << (i + 1) << ". " << options[currentOrder[i]] << "\n";
        }
    }
    
    bool checkAnswer(int userAnswer) const {
        return currentOrder[userAnswer - 1] == correctAnswer;
    }
};

// Class Vector
template<typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t size_;

public:
    Vector() : data(NULL), capacity(0), size_(0) {}
    
    ~Vector() {
        delete[] data;
    }
    
    void push_back(const T& value) {
        if (size_ == capacity) {
            size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[newCapacity];
            for (size_t i = 0; i < size_; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        data[size_++] = value;
    }
    
    T& operator[](size_t index) {
        return data[index];
    }
    
    size_t size() const {
        return size_;
    }
    
    void shuffle() {
        for (size_t i = size_ - 1; i > 0; --i) {
            size_t j = rand() % (i + 1);
            T temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
};

// Class Exam
class Exam {
private:
    Vector<Question> questions;
    Vector<Question> examQuestions;
    
public:
    void loadQuestionsFromFile(const string& filename) {
        ifstream file(filename.c_str());
        if (!file.is_open()) {
            cout << "Khong the mo file: " << filename << endl;
            return;
        }
        
        string line;
        while (getline(file, line)) {
            string questionText;
            string options[4];
            int correctAnswer;
            
            questionText = line;
            
            for (int i = 0; i < 4; ++i) {
                getline(file, options[i]);
            }
            
            string correct;
            getline(file, correct);
            correctAnswer = atoi(correct.c_str());
            
            questions.push_back(Question(questionText, options, correctAnswer));
            
            if (!file.eof()) {
                getline(file, line);
            }
        }
        
        file.close();
    }
    
    void createExam(int k) {
        if (questions.size() == 0) {
            cout << "Khong co cau hoi trong ngan hang!" << endl;
            return;
        }

        examQuestions = Vector<Question>(); 

        if (k > static_cast<int>(questions.size())) {
            k = questions.size(); 
        }

        Vector<size_t> indices;
        for (size_t i = 0; i < questions.size(); ++i) {
            indices.push_back(i);
        }
        indices.shuffle(); 
        
        for (int i = 0; i < k; ++i) {
            examQuestions.push_back(questions[indices[i]]);
        }
    }
    
    void takeExam() {
        if (examQuestions.size() == 0) {
            cout << "Chua tao de thi!" << endl;
            return;
        }
        
        int score = 0;
        
        for (size_t i = 0; i < examQuestions.size(); ++i) {
            cout << "\nCau " << (i + 1) << ":\n";
            examQuestions[i].shuffleOptions();
            examQuestions[i].display();
            
            int answer;
            do {
                cout << "\nNhap cau tra loi (1-4): ";
                cin >> answer;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    answer = 0;
                }
            } while (answer < 1 || answer > 4);
            
            if (examQuestions[i].checkAnswer(answer)) {
                score++;
            }
        }
        
        cout << "\nDiem cua ban: " << score << "/" << examQuestions.size() << "\n";
        double percentage = (static_cast<double>(score) / examQuestions.size()) * 10;
        cout << "Diem theo thang diem 10: " << percentage << "\n";
    }
};

int main() {
    srand(static_cast<unsigned>(time(NULL)));
    
    Exam exam;
    
    exam.loadQuestionsFromFile("questions.txt");
    
    int numQuestions;
    cout << "Nhap so luong cau hoi cho de thi: ";
    cin >> numQuestions;
    
    exam.createExam(numQuestions);
    
    cout << "\n=== BAT DAU THI ===\n\n";
    exam.takeExam();
    
    return 0;
}

