#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>

#define INVINP "Неправильный ввод!"
#define EXITHINT "Введите 0, чтобы выйти"
#define NOSTUDS "Нет студентов"
#define MAXSIZE 200


using namespace std;

string fheader = "\3\4\5\7";
bool fileBarMi() {
    FILE *file = nullptr;
    file = fopen("db.bin", "r");
    if (file) {
        fclose(file);
        return true;
    }
    else
        return false;
}
void writeF(string str, FILE* f) {
    fwrite(str.c_str(), 1, str.size(), f);
}

class Date{
public:
    int day = 0, mon = 0, year = 0;
    bool tuzMu(Date);
    Date();
    Date(int, int, int);
};
Date::Date() {
    this->day = 0;
    this->mon = 0;
    this->year = 0;
}

Date::Date(int _day, int _mon, int _year) {
    this->day = _day;
    this->mon = _mon;
    this->year = _year;
}
Date toDate(string sdate) {
    Date dt;
    sdate.append(" ");
    if (sdate.find_first_not_of("0123456789.") != sdate.size() - 1)
        return Date(-1, -1, -1);
    sdate = sdate.substr(0, sdate.size() - 1);
    char c_st[sdate.size() + 1];
    strncpy(c_st, sdate.c_str(), sdate.size() + 1);
    char *part;
    part = strtok(c_st, ".");
    int c = 0;
    while (part != NULL) {
        switch (c)
        {
            case 0:
                dt.day = stoi(part);
                break;
            case 1:
                dt.mon = stoi(part);
                break;
            case 2:
                dt.year = stoi(part);
                break;
        }
        part = strtok(NULL, ".");
        c++;
    }
    delete part;
    if (c != 3)
        return Date(-1, -1, -1);
    return dt;
}

bool Date::tuzMu(Date d) {
    return ((d.day > 0) && (d.day <= 31) && (d.mon > 0) && (d.mon <= 12) && (d.year >= 1900) && (d.year <= 2022));
}

string strToLow(string s) {
    int size = s.size();
    string r = s;
    for (int i = 0; i < size; i++) {
        r[i] = char(tolower(s[i]));
    }
    return r;
}

string dateToStr(Date d) {
    string ret = "";
    if (d.day > 0) {
        if (d.day < 10)
            ret.append("0");
        ret.append(to_string(d.day));
    }
    if (ret != "")
        ret.append(".");
    if (d.mon > 0) {
        if (d.mon < 10)
            ret.append("0");
        ret.append(to_string(d.mon));
    }
    if (ret != "")
        ret.append(".");
    if (d.year > 0)
        ret.append(to_string(d.year));
    return ret;
}

bool intMi(string num) {
    if (num == "" || num.length() > 9)
        return 0;
    num.append("a");
    if (num.find_first_not_of("0123456789") != num.length() - 1)
        return 0;
    return 1;
}

bool harpMi(string s) {
    s.append("$");
    s = strToLow(s);
    return (s.find_first_not_of("-abcdefghijklmnopqrstuvwxyzабвгдеёжзийклмнопрстуфхцчшщъыьэюяЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ") == s.length() - 1);
}

bool harpWaSanawMi(string name) {
    name.append("$");
    name = strToLow(name);
    return (name.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789.-абвгдеёжзийклмнопрстуфхцчшщъыьэюяЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ") == name.length() - 1);
}

string rmAra(string str) {
    if (str == "")
        return "";
    int rLen = str.size();
    char c = str[0];
    int count = 0;
    while (c == ' ') {
        count++;
        c = str[count];
    }
    str = str.substr(count, rLen - count);

    c = str[rLen - count - 1];
    while (c == ' ') {
        rLen--;
        c = str[rLen - count - 1];
    }
    str = str.substr(0, rLen - count);

    return str;
}


class Dars {
public:
    string darsName;
    int mark, indexDars;
    Dars(string, int);
    Dars();
};

Dars::Dars(string _darsName, int _mark) {
    darsName = rmAra(_darsName);
    mark = _mark;
}

Dars::Dars(){
    darsName = "";
    mark = 0;
}


class Adam {
protected:
    string sname, name, pname;
    Date bdate;
    string gender;
public:
    void xabarGet();
};

void Adam::xabarGet() {
    cout << "ФИО: " << this->sname << ' ' << this->name << ' ' << this->pname << endl;
    cout << "Пол: " << this->gender << endl << "Дата рождения: " << dateToStr(this->bdate) << endl;
}


class Semestr
{
    friend class Student;
    friend class Za4otka;
    friend class Workers;
    Dars* darslar[10];
public:
    int kolDars = 0;
    Semestr();
    int darsBarMi(string);
    Dars* getDarsName(string);
    int addDars(Dars*);
    float orta();
    void interfAddDars();
};

Semestr::Semestr() {
    kolDars = 0;
}
int Semestr::addDars(Dars* d) {
    if (kolDars == 10)
        return 0;
    if (!darsBarMi(d->darsName)) {
        darslar[kolDars] = d;
        kolDars++;
        return 1;
    }
    return 0;
}
float Semestr::orta()
{
    int sum = 0, count = 0;
    if (kolDars != 0)
        for (int i = 0; i < kolDars; i++) {
            if (abs(darslar[i]->mark) != 1)
                sum += darslar[i]->mark;
            count++;
        }
    return count == 0 ? -1 : sum * 1.0 / count;
}
int Semestr::darsBarMi(string darsName) {
    for (int i = 0; i < kolDars; i++) {
        if (rmAra(strToLow(darslar[i]->darsName)) == rmAra(strToLow(darsName)))
            return 1;
    }
    return 0;
}
Dars* Semestr::getDarsName(string darsName)
{
    for (int i = 0; i < kolDars; i++) {
        if (rmAra(darslar[i]->darsName) == rmAra(darsName)) {
            darslar[i]->indexDars = i;
            return darslar[i];
        }
    }
    return nullptr;
}

void Semestr::interfAddDars() {
    for (int j = 1; j <= 10;j++){
        string stitle, mark;
        tcheck:
        cout << "   Название " << j << "-ого предмета [0 - конец ввода предметов] > ";
        getline(cin, stitle);
        if (stitle == "0")
            break;
        if (this->darsBarMi(stitle) || stitle == "" || stitle == " " || stitle.size() > MAXSIZE) {
            cout << "Предмет с таким названием уже существует или неверно введено название!" << endl;
            goto tcheck;
        }
        mark_input:
        cout << "   Оценка (1 - пересдача, 2-5 - оценка) > ";
        getline(cin, mark);
        if (!intMi(mark) || (stoi(mark) < 1 || stoi(mark) > 5)) {
            cout << INVINP << endl;
            goto mark_input;
        }
        Dars* s = new Dars(stitle, stoi(mark));
        this->addDars(s);
    }
}


class Za4otka
{
    friend class Student;
    friend class Workers;
    string num;
    Semestr* semestrs[9];
    int kolSem = 0;
public:
    Za4otka(string);
    void showSems();
    ~Za4otka();
    int addSem(Semestr*);
    string za4ToStr();
};

Za4otka::Za4otka(string _num) {
    num = _num;
}
Za4otka::~Za4otka() {
    for (int i = 0; i < kolSem; i++) {
        delete semestrs[i];
    }
}
void Za4otka::showSems() {
    for (int i = 0; i < kolSem; i++) {
        if (semestrs[i]->kolDars == 0)
            continue;
        cout << "   " << (i + 1) << "-й семестр: " << endl;
        for (int j = 0; j < semestrs[i]->kolDars; j++)
            cout << setw(7) << " " << semestrs[i]->darslar[j]->darsName << ": " << (semestrs[i]->darslar[j]->mark == 1 ? "пересдача" : to_string(semestrs[i]->darslar[j]->mark)) << endl;
    }

}
string Za4otka::za4ToStr() {
    string result; 	string m = "\3", s = "\2", le = "\1";
    for (int i = 0;i < 9;i++) {
        for (int j = 0; j < semestrs[i]->kolDars; j++)
            result.append(semestrs[i]->darslar[j]->darsName + s + to_string(semestrs[i]->darslar[j]->mark) + m);
        result.append(le);
    }
    return result;
}
int Za4otka::addSem(Semestr* s) {
    if (kolSem < 9) {
        semestrs[kolSem] = s;
        kolSem++;
        return 1;
    }
    return 0;
}


class Student : public Adam {
    friend class Workers;
    Date idate;
    string group, fac, kaf;
    Za4otka* za4;
public:
    void xabarGet();
    Student(string, string, string, string, Date, string, string, string, Date, Za4otka*);
    Student(string);
    string dataForExport();
    ~Student();
};

Student::~Student() {
    delete za4;
}

Student::Student(string _sname, string _name, string _pname, string _gender, Date _bdate, string _group, string _fac, string _kaf, Date _idate, Za4otka* _za4){
    sname = _sname;
    name = _name;
    pname = _pname;
    gender = _gender;
    bdate = _bdate;
    fac = _fac;
    kaf = _kaf;
    idate = _idate;
    group = _group;
    za4 = _za4;
}
string Student::dataForExport() {
    string result; 	char s = '\1'; 	string el = "\2";
    result.append(this->sname + s + this->name + s + this->pname + s + this->gender + s);
    result.append(dateToStr(this->bdate) + s + dateToStr(this->idate) + s + this->fac + s);
    result.append(this->kaf + s + this->group + s + this->za4->num + el);
    result.append(za4->za4ToStr());
    result.append("\6");
    return result;
}
Student::Student(string data) {
    int ch = 0, i = 0;
    char c = '1';
    string _sname, _name, _pname,
            _gender, _birth, _idate,
            _fac, _kaf, _group, _zach_num;
    for (;i < data.length();i++) {
        c = data[i];
        if (c == '\1') {
            ch++;
            continue;
        }
        else if (c == '\2')
            break;
        switch (ch) {
            case 0:
                _sname += c;break;
            case 1:
                _name += c;break;
            case 2:
                _pname += c;break;
            case 3:
                _gender += c;break;
            case 4:
                _birth += c;break;
            case 5:
                _idate += c;break;
            case 6:
                _fac += c;break;
            case 7:
                _kaf += c;break;
            case 8:
                _group += c;break;
            case 9:
                _zach_num += c;break;
        }
    }
    sname = _sname;
    name = _name;
    pname = _pname;
    gender = _gender;
    bdate = toDate(_birth);
    fac = _fac;
    kaf = _kaf;
    idate.year = stoi(_idate);
    group = _group;
    Za4otka* zach = new Za4otka(_zach_num);
    c = data[++i];
    while (c != '\6') {
        Semestr* sem = new Semestr();
        while (c != '\1' && c != '\6') {
            string snameDars = "", smark = "";
            while (c != '\2' && c != '\1') {
                snameDars += c;
                c = data[++i];
            }
            c = data[++i];
            while (c != '\3' && c != '\1') {
                smark += c;
                c = data[++i];
            }
            c = data[++i];
            Dars* dars = new Dars(snameDars, stoi(smark));
            sem->addDars(dars);
        }
        zach->addSem(sem);
        c = data[++i];
    }
    za4 = zach;
}

void Student::xabarGet(){
    Adam::xabarGet();
    cout << "Номер зачётной книжки: " << this->za4->num << endl << "Год поступления: " << dateToStr(this->idate)
    << endl << "Группа: " << this->group << endl << "Факультет: " << this->fac << endl << "Кафедра: " << this->kaf << endl;
}

class Workers {
public:
    int N;
    Workers();
    void inizFile();
    void showStds();
    void rmStud(string);
    bool stdBarMi(string);
    void changeStudent(Student*, int);
    void showStdChangeLaqir(Student*);
    void writingChanges(string);
    void sortirovka(int, int, int);
};

Workers::Workers() {
    N = 0;
}

void Workers::showStdChangeLaqir(Student * s) {
    cout << "Длина фамилии, имени, отчества, группы, кафедры, факультета не должна первышать двухсот символов." << endl <<
    "Двойные имена, фамилии пишутся через тире." << endl;
    while(1) {
        cout << "Введите пунтк, которые хотите изменить:" << endl;
        cout << "1. Фамилия (" << s->sname << ")" << endl;
        cout << "2. Имя (" << s->name << ")" << endl;
        cout << "3. Отчество (" << s->pname << ")" << endl;
        cout << "4. Пол (" << s->gender << ")" << endl;
        cout << "5. День рождения (" << dateToStr(s->bdate) << ")" << endl;
        cout << "6. Год поступления (" << to_string(s->idate.year) << ")" << endl;
        cout << "7. Факультет (" << s->fac << ")" << endl;
        cout << "8. Кафедра (" << s->kaf << ")" << endl;
        cout << "9. Группа (" << s->group << ")" << endl;
        cout << "10.Номер зачётки (" << s->za4->num << ")" << endl;
        cout << "11.Семестр" << endl;
        cout << "0. Выход в главное меню" << endl;
        cout << "> ";
        n3g:
        string n;
        getline(cin, n);
        if (!intMi(n) || stoi(n) > 11 || stoi(n) < 0) {
            cout << INVINP << endl;
            goto n3g;
        }
        if (n == "0") {
            break;
        }
        changeStudent(s, stoi(n));
    }
}
void Workers::changeStudent(Student* t, int param) {
    string tmp;
    string zach_num = t->za4->num;
    switch (param)
    {
        case 1: {
            sne:
            cout << EXITHINT << endl;
            cout << "Фамилия (" << t->sname << ") > ";
            getline(cin, tmp);
            if(tmp=="0"){
                break;
            }
            if (!harpMi(tmp) || tmp == "" || tmp.size() > MAXSIZE) {
                cout << INVINP << endl;
                goto sne;
            }
            t->sname = tmp; break;
        }
        case 2: {
            fne:
            cout << EXITHINT << endl;
            cout << "Имя (" << t->name << ") > ";
            getline(cin, tmp);
            if(tmp=="0"){
                break;
            }
            if (!harpMi(tmp) || tmp == "" || tmp.size() > MAXSIZE) {
                cout << INVINP << endl;
                goto fne;
            }
            t->name = tmp; break;
        }
        case 3: {
            mne:
            cout << EXITHINT << endl;
            cout << "Отчество (" << t->pname << ") > ";
            getline(cin, tmp);
            if(tmp=="0"){
                break;
            }
            if (!harpMi(tmp) || tmp.size() > MAXSIZE) {
                cout << INVINP << endl;
                goto mne;
            }
            t->pname = tmp; break;
        }
        case 4: {
            gender_input:
            cout << "Пол [м,ж] (" << t->gender << ") > ";
            getline(cin, tmp);
            if(tmp=="0"){
                break;
            }
            if ((strToLow(tmp) != "м") && (strToLow(tmp) != "ж")) {
                cout << INVINP;
                goto gender_input;
            }
            t->gender = tmp; break;
        }
        case 5: {
            Date bday;
            bdate_input:
            cout << EXITHINT << endl;
            cout << "День рождения {дд.мм.гггг} (" << dateToStr(t->bdate = bday) << ") > ";
            getline(cin, tmp);
            if(tmp=="0"){
                break;
            }
            if (!bday.tuzMu(toDate(tmp)) || toDate(tmp).year >= t->idate.year || tmp == "") {
                cout << INVINP << " (Некорректный формат даты)" << endl;
                goto bdate_input;
            }
            bday = toDate(tmp);
            t->bdate = bday; break;
        }
        case 6: {
            Date jdate;
            jdate_input:
            cout << EXITHINT << endl;
            cout << "Год поступления {гггг} (" << to_string(t->idate.year) << ") > ";
            getline(cin, tmp);
            if(tmp=="0"){
                break;
            }
            if (!intMi(tmp) || stoi(tmp) < 1947 || stoi(tmp) > 2022 || stoi(tmp) <= t->bdate.year) {
                cout << INVINP << " (Некорректный формат года)" << endl;
                goto jdate_input;
            }
            jdate.year = stoi(tmp);
            t->idate = jdate; break;
        }
        case 7: {
            fk:
            cout << EXITHINT << endl;
            cout << "Факультет > ";
            getline(cin, tmp);
            if(tmp=="0"){
                break;
            }
            if (tmp.size() > MAXSIZE){
                cout << INVINP;
                goto fk;
            }
            tmp = rmAra(tmp);
            t->fac = tmp;
            break;
        }
        case 8: {
            kf:
            cout << "Кафедра > ";
            cout << EXITHINT << endl;
            getline(cin, tmp);
            if(tmp=="0"){
                break;
            }
            if (tmp.size() > MAXSIZE){
                cout << INVINP;
                goto kf;
            }
            tmp = rmAra(tmp);
            t->kaf = tmp;
            break;
        }
        case 9: {
            gri:
            cout << EXITHINT << endl;
            cout << "Группа > ";
            getline(cin, tmp);
            if(tmp=="0"){
                break;
            }
            if (!harpWaSanawMi(tmp) || tmp.size() > MAXSIZE) {
                cout << INVINP << endl;
                goto gri;
            }
            t->group = tmp;  break;
        }

        case 10: {
            zang:
            cout << EXITHINT << " Длина номера зачётки не превышает семи символов." << endl;
            cout << "Номер зачётки (" << t->za4->num << ") > ";
            getline(cin, tmp);
            if(tmp=="0"){
                break;
            }
            if (!harpWaSanawMi(tmp)){
                cout << "Номер зачётной книжки должен содержать буквы и цифры!" << endl;
                goto zang;
            }
            else if(tmp.size() > 7 || tmp == ""){
                cout << INVINP;
                goto zang;
            }
            else if (stdBarMi(tmp)) {
                cout << "Студент с таким номером зачётки уже имеется!" << endl;
                goto zang;
            }
            else
                t->za4->num = tmp;

            break;
        }

        case 11: {
            cout << EXITHINT << endl;
            t->za4->showSems();
            semnum:
            cout << "Номер семестра > ";
            getline(cin, tmp);
            if (tmp == "0") {
                break;
            }
            if (!intMi(tmp) || stoi(tmp) > 9 || stoi(tmp) < 1) {
                cout << INVINP << endl;
                goto semnum;
            }
            Semestr *tsem = t->za4->semestrs[stoi(tmp) - 1];
            if (tsem->kolDars == 0) {
                cout << "Добавление данных по новому семестру. Длина предмета не должна превышать двухсот символов." << endl;
                tsem->interfAddDars();
                break;
            }

            cout << "Введите предмет, который хотите заменить > ";
            getline(cin, tmp);
            if (tmp == "0") {
                break;
            }

            if (!tsem->darsBarMi(tmp)) {
                if (tsem->kolDars == 10) {
                    cout << "Количество предметов максимальное, не получиться добавить новый." << endl;
                    break;
                }
                string mark;
                cout << "Добавление предмета. Длина предмета не должна превышать двухсот символов." << endl;
                markinput:
                cout << "Оценка:  (1=пересдача, 2-5=оценка)" << endl;
                getline(cin, mark);
                if (!intMi(mark) || (stoi(mark) < 1 || stoi(mark) > 5)) {
                    cout << INVINP << endl;
                    goto markinput;
                }
                Dars *s = new Dars(tmp, stoi(mark));
                tsem->addDars(s);
                break;
            }

            Dars *tdars = tsem->getDarsName(tmp);
            darsmenu:
            cout << "Что хотите изменить: " << endl;
            cout << "1. Название" << endl;
            cout << "2. Оценка" << endl;
            cout << "3. Удалить" << endl;
            cout << "> ";
            getline(cin, tmp);
            if (tmp == "0") {
                break;
            }
            if (!intMi(tmp) || stoi(tmp) < 1 || stoi(tmp) > 3) {
                cout << INVINP << endl;
                goto darsmenu;
            }
            if (tmp == "1") {
                nstitle:
                cout << "Введите название, не превышающее двухсот, предмета > ";
                getline(cin, tmp);
                if (tmp == "0") {
                    break;
                }
                if (!tsem->darsBarMi(tmp) && tmp != "" && tmp.size() <= MAXSIZE) {
                    tdars->darsName = rmAra(tmp);
                } else {
                    cout << "Предмет в пределах одного семеcтра должен быть уникальным  и корректным!" << endl;
                    goto nstitle;
                }
            } else if (tmp == "2") {
                cstitle:
                cout << "Введите оценку (1=пересдача, 2-5=оценка) > ";
                getline(cin, tmp);
                if (tmp == "0") {
                    break;
                }
                if (!intMi(tmp) || stoi(tmp) < 1 || stoi(tmp) > 5) {
                    cout << INVINP << endl;
                    goto cstitle;
                } else {
                    tdars->mark = stoi(tmp);
                }
            }
            else{
                for (int i = tdars->indexDars; i < tsem->kolDars - 1; ++i)
                    tsem->darslar[i] = tsem->darslar[i + 1];
                tsem->kolDars--;
            }
            break;
        }
    }
}

void Workers::inizFile() {
    FILE *fn = nullptr;
    if (!fileBarMi()) {
        cout << "Данные о студентах будут содержится в файле db.bin" << endl;
        cout << "Для начала работы с программой необходимо сначала заполнить базу студентов. Для этого выберите первый пункт меню." << endl;
        fn = fopen("db.bin", "wb");
        for (int i = 0;i < 4;i++)
            fwrite(&fheader[i], 1, 1, fn);
        fclose(fn);
    }
    else{
        cout << "База данных о студентах загружена." << endl;
        fn = fopen("db.bin", "rb");
        string result = "";
        char c;
        fseek(fn, 0, 0);
        for (int i = 0;i < 4;i++) {
            fread(&c, 1, 1, fn);
            if (c != fheader[i]) {
                cout << "Файл базы данных студентов был повреждён! Придётся вам удалить db.bin файл..." << endl;
                exit(0);
            }
        }

        N = 0;
        while (!feof(fn)) {
            fread(&c, 1, 1, fn);
            if (c == '\6')
                N++;
        }
        if (N != 0)
            N--;
        fclose(fn);
    }
}

void Workers::showStds() {
    FILE *in = nullptr;
    in = fopen("db.bin", "rb");
    char c;

    fseek(in, 4, 0);
    string oneStud = "";
    int k = 0;
    while (k < N) {
        fread(&c, 1, 1, in);
        if (c == '\6' || feof(in)) {
            Student ns(oneStud + '\6');
            ns.xabarGet();
            ns.za4->showSems();
            cout << "------------------------------------------------------" << endl;
            oneStud = "";
            k++;
        } else
            oneStud += c;
    }
    fclose(in);
}

void Workers::rmStud(string nom) {
    FILE *fon;
    fon = fopen("db.bin", "rb");
    FILE *fin;
    fin = fopen("sp.bin", "wb");

    fseek(fon, 4, 0);
    int k = 0;
    char c;
    string oneStud = "";
    while (k < N) {
        fread(&c, 1, 1, fon);
        if (c == '\6' || feof(fon)) {
            Student ns(oneStud + '\6');
            if (ns.za4->num != nom) {
                oneStud += '\6';
                writeF(oneStud, fin);
            }
            oneStud = "";
            k++;
        } else
            oneStud += c;
    }
    N--;
    fclose(fon);
    fclose(fin);

    fon = fopen("sp.bin", "rb");
    fin = fopen("db.bin", "wb");
    fseek(fin, 0, 0);

    for (int i = 0; i < 4; i++)
        fwrite(&fheader[i], 1, 1, fin);
    k = 0;
    while (k < N){
        fread(&c, 1, 1, fon);
        fwrite(&c, 1, 1, fin);
        if (c == '\6' || feof(fon))
            k++;
    }
    fclose(fon);
    fclose(fin);

    FILE *file = fopen("sp.bin", "w");
    fclose(file);
}

bool Workers::stdBarMi(string _num) {
    FILE *fn;
    fn = fopen("db.bin", "rb");
    char c;
    string oneStud = "";
    int k = 0;
    while (k < N) {
        fread(&c, 1, 1, fn);
        if (c == '\6' || feof(fn)) {
            Student ns(oneStud + '\6');
            if (ns.za4->num == _num) {
                fclose(fn);
                return true;
            }
            oneStud = "";
            k++;
        }else
            oneStud += c;
    }
    fclose(fn);
    return false;
}

void Workers::writingChanges(string zach_num) {
    FILE *on;
    on = fopen("db.bin", "rb");
    FILE *in;
    in = fopen("sp.bin", "wb");
    fseek(on, 4, 0);
    Student *ns;
    int k = 0;
    char c;
    string oneStud = "";
    while (k < N) {
        fread(&c, 1, 1, on);
        if (c == '\6' || feof(on)) {
            ns = new Student(oneStud + '\6');
            if (ns->za4->num == zach_num)
                showStdChangeLaqir(ns);
            oneStud = ns->dataForExport();
            writeF(oneStud, in);
            oneStud = "";
            k++;
        } else
            oneStud += c;
    }
    fclose(on);
    fclose(in);
    FILE *on2;
    on2 = fopen("sp.bin", "rb");
    FILE *in2;
    in2 = fopen("db.bin", "wb");
    fseek(in2, 0, 0);
    for (int i = 0; i < 4; i++)
        fwrite(&fheader[i], 1, 1, in2);
    k = 0;
    while (k < N){
        fread(&c, 1, 1, on2);
        fwrite(&c, 1, 1, in2);
        if (c == '\6' || feof(on))
            k++;
    }
    fclose(on2);
    fclose(in2);
    FILE *file = fopen("sp.bin", "w");
    fclose(file);
}

void Workers::sortirovka(int semnun, int ySt, int yEnd) {
    FILE *fon;
    fon = fopen("db.bin", "rb");
    FILE *spf;
    spf = fopen("sp.bin", "wb+");

    fseek(fon, 4, 0);
    int k = 0, l;
    char c = '\0', d;
    fwrite(&c, 1, 1, spf);
    string nStud = "", spStud = "";
    while (k < N) {
        fread(&c, 1, 1, fon);
        if (c == '\6' || feof(fon)) {
            Student ns(nStud + '\6');
            if (ns.bdate.year >= ySt && ns.bdate.year <= yEnd && ns.za4->semestrs[semnun]->orta() != -1) {
                fseek(spf, 0, 0);
                fread(&d, 1, 1, spf);
                while (1) {
                    if (d == '\0') {
                        fseek(spf, -1, 2);
                        writeF(nStud + '\6' + '\0', spf);
                        break;
                    }
                    else if (d == '\6') {
                        Student spSt(spStud + '\6');
                        if (ns.za4->semestrs[semnun]->orta() > spSt.za4->semestrs[semnun]->orta()){
                            nStud += '\6';
                            spStud += '\6';
                            int l = spStud.size();
                            fseek(spf, -l, 1);
                            l = nStud.size();
                            spStud = "";
                            fread(&d, 1, 1, spf);
                            while (1) {
                                spStud += d;
                                if (d == '\0'){
                                    int sz = spStud.size();
                                    fseek(spf, -sz, 1);
                                    writeF(nStud + spStud, spf);
                                    break;
                                }
                                else if (spStud.size() == l) {
                                    fseek(spf, -l, 1);
                                    writeF(nStud, spf);
                                    nStud = spStud;
                                    spStud = "";
                                }
                                fread(&d, 1, 1, spf);
                            }
                            break;
                        }
                        spStud = "";
                    }
                    else
                        spStud += d;
                    fread(&d, 1, 1, spf);
                }
                spStud = "";
            }
            nStud = "";
            k++;
        } else
            nStud += c;
    }
    fclose(fon);
    fclose(spf);
    nStud = "";
    spf = fopen("sp.bin", "rb");
    fseek(spf, 0, 0);
    cout << semnun + 1 << "-й семестр: " << endl;
    fread(&c, 1, 1, spf);
    while (c != '\0'){
        if (c == '\6') {

            Student ns(nStud + '\6');
            cout << "   " << ns.sname << ' ' << ns.name << ' ' << ns.pname << ' ' << ns.za4->num << endl;
            nStud = "";
        } else
            nStud += c;
        fread(&c, 1, 1, spf);
    }
    fclose(spf);

    FILE *file = fopen("sp.bin", "w");
    fclose(file);
}

void input_data();
void menu();
Workers u;

int main()
{
    setlocale(LC_ALL, "Russian");
    while (1)
        menu();

    return 0;
}


void menu() {
    string n;
    menu_n:
    u.inizFile();
    cout << "Введите номер действия, которое хотите совершить: " << endl;
    cout << "1. Добавить студентов" << endl;
    cout << "2. Удалить студента" << endl;
    cout << "3. Показать всех студентов" << endl;
    cout << "4. Изменить информацию о студенте" << endl;
    cout << "5. Вывести студентов по успеваемости от лучшего к худшему" << endl;
    cout << "0. Выход из программы" << endl;
    cout << "> ";
    getline(cin, n);
    if (!intMi(n) || (stoi(n) > 5 || stoi(n) < -1)) {
        goto menu_n;
    }
    switch (stoi(n))
    {
        case 0:
            exit(0);
        case 1: {
            input_data();
            break;
        }
        case 2: {
            if (u.N == 0) {
                cout << NOSTUDS << endl;
                break;
            }
            string zach;
            zenter:
            cout << "Введите номер зачетной книжки студента, которого хотите удалить из университета: [0 - выход в меню] > ";
            getline(cin, zach);
            if (zach == "0") {break; }

            if (u.stdBarMi(zach)) {
                u.rmStud(zach);
                cout << "Информация о студенте успешно стёрта." << endl;
            }else {
                cout << "Такого студента нет." << endl;
                goto zenter;
            }
            break;
        }
        case 3: {
            if (u.N == 0) {
                cout << NOSTUDS << endl;
                break;
            }
            u.showStds();
            break;
        }
        case 4: {
            if (u.N == 0) {
                cout << NOSTUDS << endl;
                break;
            }
            string zn;
            cout << "Введите номер зачётной книжки студента, информацию о котором хоитите изменить > ";
            checkZn:
            getline(cin, zn);
            if (zn == "0") {
                break;
            }
            if (!u.stdBarMi(zn)) {
                cout << "Не найдено студентов с таким номером зачетки, попробуйте снова [0 - выход в меню] > ";
                goto checkZn;
            }
            u.writingChanges(zn);

            break;
        }
        case 5: {
            if (u.N == 0) {
                cout << NOSTUDS << endl;
                break;
            }

            semnum:
            string tmp;
            cout << "Введите 0, чтобы выйти." << endl;
            cout << "Введите номер семестра, по которому хотите отсортировать студентов. Введите '10' чтобы отсортировать по всем семестрам" << endl << "> ";
            getline(cin, tmp);
            if (tmp == "0")
                break;
            if (!intMi(tmp) || stoi(tmp) > 10 || stoi(tmp) < 1) {
                cout << INVINP << endl;
                goto semnum;
            }

            brthsSt:
            string yearSt, yearEnd;


            cout << "Укажите начальный интервал года рождения: ";
            getline(cin, yearSt);
            if (!intMi(yearSt) || stoi(yearSt) < 0 || stoi(yearSt) > 2022) {
                cout << INVINP << endl;
                goto brthsSt;
            }


            brthsEn:
            cout << "Укажите конечный интервал года рождения: ";
            getline(cin, yearEnd);
            if (!intMi(yearSt) || stoi(yearEnd) < stoi(yearSt)) {
                cout << INVINP << endl;
                goto brthsEn;
            }

            if (tmp == "10")
                for (int i = 0; i < 9; i++)
                    u.sortirovka(i, stoi(yearSt), stoi(yearEnd));
            else
                u.sortirovka(stoi(tmp) - 1, stoi(yearSt), stoi(yearEnd));

            break;
        }
    }
}
void input_data() {
    string scount;
    students_count_input:
    cout << "Введите количество студентов > ";
    getline(cin, scount);
    if (!intMi(scount)) {
        cout << INVINP << endl;
        goto students_count_input;
    }
    cout << "Длина фамилии, имени, отчества, группы, кафедры, факультета не должна первышать двухсот символов." << endl;
    for (int i = 1;i < stoi(scount) + 1;i++) {
        string sname, name, pname, group, zach_num, kaf, fac, bdate, y, gender, ksem;
        Date bday, jdate;
        cout << "   Студент [№" << i << "]:" << endl;
        sstart:
        cout << "Фамилия > ";
        getline(cin, sname);
        if (!harpMi(sname) || sname == "" && sname.size() > MAXSIZE){
            cout << INVINP << endl;
            goto sstart;
        }else
            sname = rmAra(sname);
        fstart:
        cout << "Имя > ";
        getline(cin, name);
        if (!harpMi(name) || name == "" && name.size() > MAXSIZE){
            cout << INVINP << endl;
            goto fstart;
        }else
            name = rmAra(name);
        mstart:
        cout << "Отчество > ";
        getline(cin, pname);
        if (!harpMi(pname) || pname.size() > MAXSIZE){
            cout << INVINP << endl;
            goto mstart;
        }else
            sname = rmAra(sname);

        gender_input:
        cout << "Пол {м,ж} > ";
        getline(cin, gender);
        if ((strToLow(gender) != "ж") && (strToLow(gender) != "м")) {
            cout << INVINP << endl;
            goto gender_input;
        }
        bdate_input:
        cout << "Дата рождения {дд.мм.ГГГГ}(не ранее 1900-ого года) > ";
        getline(cin, bdate);
        if (!bday.tuzMu(toDate(bdate))) {
            cout << INVINP << endl;
            goto bdate_input;
        }
        bday = toDate(bdate);
        jdate_input:
        cout << "Год поступления {ГГГГ}(не ранее 1947-ого года) > ";
        getline(cin, y);
        if (!intMi(y) || stoi(y) < 1947 || stoi(y) > 2022 || stoi(y) <= bday.year) {
            cout << INVINP << endl;
            goto jdate_input;
        }
        jdate.year = stoi(y);
        gri:
        cout << "Группа > ";
        getline(cin, group);
        if (!harpWaSanawMi(group) || group.size() > MAXSIZE) {
            cout << INVINP << endl;
            goto gri;
        }
        znum:
        cout << "Номер зачётной книжки (длина не должна превышать семи) > ";
        getline(cin, zach_num);
        if (!harpWaSanawMi(zach_num) || u.stdBarMi(zach_num) || zach_num == "" || zach_num.size() > 8) {
            cout << "Введённый номер зачётной книжки уже существует или содержит недопустимые символы!" << endl;
            goto znum;
        }
        kf:
        cout << "Кафедра > ";
        getline(cin, kaf);
        if (kaf.size() > MAXSIZE) {
            cout << INVINP << endl;
            goto kf;
        }
        kaf = rmAra(kaf);
        fk:
        cout << "Факультет > ";
        getline(cin, fac);
        if (fac.size() > MAXSIZE) {
            cout << INVINP << endl;
            goto fk;
        }
        fac = rmAra(fac);
        semes:
        cout << "Номер семестра, до которго будет вводиться инофрмация > ";
        getline(cin, ksem);
        if (!intMi(ksem) || stoi(ksem) < 1 || stoi(ksem) > 9){
            cout << INVINP << endl;
            goto semes;
        }
        int k;
        Za4otka *z = new Za4otka(zach_num);
        for (k = 1; k <= stoi(ksem); k++) {
            cout << "Можно ввести 9 сессий и по 10 предметов (их длина не должна превышать двухсот символов) для каждой из них:" << endl;
            cout << to_string(k) << "-й семестр" << endl;
            Semestr* sem = new Semestr();
            sem->interfAddDars();
            z->addSem(sem);
        }
        for (;k<=9;k++){
            Semestr* sem = new Semestr();
            z->addSem(sem);
        }
        Student std(sname, name, pname, gender, bday, group, fac, kaf, jdate, z);
        FILE *fn;
        fn = fopen("db.bin", "ab");
        writeF(std.dataForExport(), fn);
        fclose(fn);
        u.N++;
    }
}
