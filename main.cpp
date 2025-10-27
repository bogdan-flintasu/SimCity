#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Strada {
private:
    int ID{};
    std::string nume;
    double cost_construire{};
    double cost_intretinere{};
    bool trotuar{};
    bool sens_unic{};
    int numar_benzi{};
    double lungime{};

public:

    // Constructor de initializare
    explicit Strada(int id = 0, std::string  nume_ = "", int cost_c = 0, int cost_i = 0, bool trot = false, bool unic = false, int nr_benzi = 1, int lung = 14);

    // Constructor de copiere
    Strada(const Strada& other);

    // operator=
    Strada& operator=(const Strada& other);

    // Destructor
    ~Strada();

    // getters
    [[nodiscard]] int get_ID() const;
    [[nodiscard]] double get_cost_intretinere() const;
    [[nodiscard]] double get_cost_construire() const;
    [[nodiscard]] const std::string& get_nume() const;
    [[nodiscard]] bool get_trotuar() const;
    [[nodiscard]] bool get_sens_unic() const;
    [[nodiscard]] double get_lungime() const;
    [[nodiscard]] int get_numar_benzi() const;

    // setters
    void set_cost_intretinere(double cost_nou);

    // operator<<
    friend std::ostream& operator<<(std::ostream& os, const Strada& s);
};

Strada::Strada(int id, std::string  nume_, int cost_c, int cost_i, bool trot, bool unic, int nr_benzi, int lung) : ID(id), nume(std::move(nume_)), cost_construire(cost_c), cost_intretinere(cost_i),
                                                                                                            trotuar(trot), sens_unic(unic), numar_benzi(nr_benzi), lungime(lung) {
    std::cout << "Constructor initializare strada apelat\n";
}

Strada::Strada(const Strada& other): ID(other.ID), nume(other.nume), cost_construire(other.cost_construire),
                                    cost_intretinere(other.cost_intretinere), trotuar(other.trotuar), sens_unic(other.sens_unic), numar_benzi(other.numar_benzi), lungime(other.lungime) {}


Strada::~Strada() {
    std::cout << "Destructor strada apelat\n";
};

Strada& Strada::operator=(const Strada& other) {
    if (this != &other) {
        ID = other.ID;
        nume = other.nume;
        cost_construire = other.cost_construire;
        cost_intretinere = other.cost_intretinere;
        trotuar = other.trotuar;
        sens_unic = other.sens_unic;
        numar_benzi = other.numar_benzi;
        lungime = other.lungime;
    }
    return *this;
}

int Strada::get_ID() const { return ID; }
double Strada::get_cost_intretinere() const { return cost_intretinere; }
const std::string& Strada::get_nume() const { return nume; }
double Strada::get_cost_construire() const { return cost_construire; }
bool Strada::get_trotuar() const { return trotuar; }
bool Strada::get_sens_unic() const { return sens_unic; }
double Strada::get_lungime() const { return lungime; }
int Strada::get_numar_benzi() const { return numar_benzi; }

void Strada::set_cost_intretinere(double cost_nou) {
    if (cost_nou >= 0) cost_intretinere = cost_nou;
}

std::ostream& operator<<(std::ostream& os, const Strada& s) {
    os << " Strada" << s.nume << " (ID: " << s.ID << ")\n";
    os << " Cost C/I: " << s.cost_construire << "/" << s.cost_intretinere << " RON \n";
    os << " Detalii: " << s.lungime << "m, " << s.numar_benzi << " benzi, "<< (s.trotuar ? "Cu trotuar" : "Fara trotuar") << ", "<< (s.sens_unic ? "Sens unic" : "Sens dublu");
    return os;
}

enum class CladiriRezidentiale{
    CASA,
    BLOC
};

std::string reztostr(const CladiriRezidentiale tip) {
    switch (tip) {
        case CladiriRezidentiale::CASA: return "Casa";
        case CladiriRezidentiale::BLOC: return "Bloc";
        default: return "Necunoscut";
    }
}

class CladireRezidentiala {
private:
    int ID{};
    std::string nume;
    double cost_construire{};
    double cost_intretinere{};
    CladiriRezidentiale tip; // casa sau bloc
    double suprafata_utila{};
    int numar_etaje{};
    int numar_locuitori{};
public:

    explicit CladireRezidentiala(int id = 0, std::string  nume_ = "", int cost_c = 0, int cost_i = 0,
                                CladiriRezidentiale  tip_ = CladiriRezidentiale::CASA, int suprafata = 0, int etaje = 0 , int locatari = 0);

    CladireRezidentiala(const CladireRezidentiala& other);
    CladireRezidentiala& operator=(const CladireRezidentiala& other);
    ~CladireRezidentiala();

    [[nodiscard]] int get_ID() const;
    [[nodiscard]] double get_cost_construire() const;
    [[nodiscard]] double get_cost_intretinere() const;
    [[nodiscard]] const std::string& get_nume() const;
    [[nodiscard]] int get_numar_etaje() const;
    [[nodiscard]] CladiriRezidentiale get_tip() const;
    [[nodiscard]] double get_suprafata() const;
    [[nodiscard]] int get_numar_locuitori() const;

    void set_cost_intretinere(double cost_nou);

    friend std::ostream& operator<<(std::ostream& os, const CladireRezidentiala& cr);
};

CladireRezidentiala::CladireRezidentiala(int id, std::string nume_, int cost_c, int cost_i, CladiriRezidentiale  tip_, int suprafata, int etaje, int locatari) : ID(id), nume(std::move(nume_)), cost_construire(cost_c),
                                                                                                                                                    cost_intretinere(cost_i), tip(tip_), suprafata_utila(suprafata),
                                                                                                                                                    numar_etaje(etaje), numar_locuitori(locatari){}

CladireRezidentiala::CladireRezidentiala(const CladireRezidentiala &other): ID(other.ID), nume(other.nume), cost_construire(other.cost_construire),
                                                                        cost_intretinere(other.cost_intretinere), tip(other.tip),
                                                                        suprafata_utila(other.suprafata_utila), numar_etaje(other.numar_etaje), numar_locuitori(other.numar_locuitori) {}

CladireRezidentiala& CladireRezidentiala:: operator=(const CladireRezidentiala& other) {
    if (this != &other) {
        ID = other.ID;
        nume = other.nume;
        cost_construire = other.cost_construire;
        cost_intretinere = other.cost_intretinere;
        tip = other.tip;
        suprafata_utila = other.suprafata_utila;
        numar_etaje = other.numar_etaje;
        numar_locuitori = other.numar_locuitori;
    }
    return *this;
}

CladireRezidentiala::~CladireRezidentiala() {
    std::cout << "Destructor CladireRezidentiala apelat\n";
}

int CladireRezidentiala::get_ID() const { return ID; }
double CladireRezidentiala::get_cost_construire() const { return cost_construire; }
double CladireRezidentiala::get_cost_intretinere() const { return cost_intretinere; }
const std::string& CladireRezidentiala::get_nume() const { return nume; }
int CladireRezidentiala::get_numar_etaje() const { return numar_etaje; }
CladiriRezidentiale CladireRezidentiala::get_tip() const { return tip; }
double CladireRezidentiala::get_suprafata() const { return suprafata_utila; }
int CladireRezidentiala::get_numar_locuitori() const { return numar_locuitori; }

void CladireRezidentiala::set_cost_intretinere(double cost_nou) {
    if(cost_nou >= 0) cost_intretinere = cost_nou;
}

std::ostream& operator<<(std::ostream& os, const CladireRezidentiala& cr) {
    os << " Cladire rezidentiala: " << cr.nume << " (Tip: " << reztostr(cr.tip) << ")\n";
    os << " Cost C/I: " << cr.cost_construire << "/" << cr.cost_intretinere << " RON \n";
    os << "Detalii: " << cr.numar_etaje <<" etaje, " << cr.suprafata_utila << "m2 suprafata utila, " << cr.numar_locuitori << " locatari\n";
    return os;
}

enum class CladiriPublice {
    SCOALA,
    UNIVERSITATE,
    SPITAL,
    POLITIE,
    POMPIERI,
    SPATIU_COMERCIAL,
    CLADIRE_BIROURI,
    PARC,
    BISERICA,
    FABRICA
};

std::string pubtostr(CladiriPublice tip) {
    switch (tip) {
        case CladiriPublice::SCOALA: return "Scoala";
        case CladiriPublice::UNIVERSITATE: return "Universitate";
        case CladiriPublice::SPITAL: return "Spital";
        case CladiriPublice::POLITIE: return "Politie";
        case CladiriPublice::POMPIERI: return "Pompieri";
        case CladiriPublice::SPATIU_COMERCIAL: return "Spatiu Comercial";
        case CladiriPublice::CLADIRE_BIROURI: return "Cladire Birouri";
        case CladiriPublice::PARC: return "Parc";
        case CladiriPublice::BISERICA: return "Biserica";
        case CladiriPublice::FABRICA: return "Fabrica";
        default: return "Necunoscut";
    }
}

class CladirePublica {
private:
    int ID{};
    std::string nume;
    double cost_construire{};
    double cost_intretinere{};
    CladiriPublice tip;
    int capacitate_servicii{}; // nr elevi, nr paturi spital, suprafata m2 pentru parc etc.
    bool inchiriat;

public:
    explicit CladirePublica(int id = 0, std::string  n = "", int cost_c = 0, int cost_i = 0, CladiriPublice  tip_ = CladiriPublice::POMPIERI, int capacitate = 0, bool inchiriat_ = false);

    CladirePublica(const CladirePublica& other);
    CladirePublica& operator=(const CladirePublica& other);
    ~CladirePublica();

    [[nodiscard]] int get_ID() const;
    [[nodiscard]] double get_cost_intretinere() const;
    [[nodiscard]] double get_cost_construire() const;
    [[nodiscard]] const std::string& get_nume() const;
    [[nodiscard]] CladiriPublice get_tip() const;
    [[nodiscard]] int get_capacitate() const;
    [[nodiscard]] bool get_inchiriat() const;

    void set_cost_intretinere(double cost_nou);

    friend std::ostream& operator<<(std::ostream& os, const CladirePublica& cp);
};

CladirePublica::CladirePublica(int id, std::string  n, int cost_c, int cost_i, CladiriPublice tip_, int capacitate, bool inchiriat_): ID(id), nume(std::move(n)), cost_construire(cost_c), cost_intretinere(cost_i),
                                                                                                                tip(tip_), capacitate_servicii(capacitate), inchiriat(inchiriat_) {}

CladirePublica::CladirePublica(const CladirePublica &other): ID(other.ID), nume(other.nume), cost_construire(other.cost_construire),
                                                                        cost_intretinere(other.cost_intretinere), tip(other.tip),
                                                                        capacitate_servicii(other.capacitate_servicii), inchiriat(other.inchiriat) {}

CladirePublica& CladirePublica:: operator=(const CladirePublica& other) {
    if (this != &other) {
        ID = other.ID;
        nume = other.nume;
        cost_construire = other.cost_construire;
        cost_intretinere = other.cost_intretinere;
        tip = other.tip;
        capacitate_servicii = other.capacitate_servicii;
        inchiriat = other.inchiriat;
    }
    return *this;
}

CladirePublica::~CladirePublica() {
    std::cout << "Destructor CladirePublica apelat\n";
}

int CladirePublica::get_ID() const { return ID; }
double CladirePublica::get_cost_intretinere() const { return cost_intretinere; }
double CladirePublica::get_cost_construire() const { return cost_construire; }
const std::string& CladirePublica::get_nume() const { return nume; }
CladiriPublice CladirePublica::get_tip() const { return tip; }
int CladirePublica::get_capacitate() const { return capacitate_servicii; }
bool CladirePublica::get_inchiriat() const { return inchiriat; }

void CladirePublica::set_cost_intretinere(double cost_nou) {
    if(cost_nou >= 0) cost_intretinere = cost_nou;
}

std::ostream& operator<<(std::ostream& os, const CladirePublica& cp) {
    os << " Cladire Publica: " << cp.nume << " (Tip: " << pubtostr(cp.tip) <<")\n";
    os << " Cost C/I: " << cp.cost_construire << "/" << cp.cost_intretinere << " RON \n";
    os << " Detalii: " << cp.capacitate_servicii << ", iar cladirea " << (cp.inchiriat ? "este" : "nu este") << " inchiriata de primarie" <<"\n";
    return os;
}

enum class Proiecte {
    STRADA,
    REZIDENTIAL,
    PUBLIC
};

std::string prtostr(Proiecte p) {
    switch (p) {
        case Proiecte::STRADA: return "Strada";
        case Proiecte::REZIDENTIAL: return "Rezidential";
        case Proiecte::PUBLIC: return "Public";
        default: return "Proiect neidentificat";
    }
}

enum class Amanunte {
    IMBUNATATIRE,
    DEMOLARE,
    DE_LA_ZERO
};

std::string amtostr(Amanunte am) {
    switch (am) {
        case Amanunte::DE_LA_ZERO: return "De construit de la zero";
        case Amanunte::DEMOLARE: return "Demolare";
        case Amanunte::IMBUNATATIRE: return "Imbunatatire";
        default: return "Amanunte neidentificate";
    }
}

class Proiect {
private:
    std::string nume_proiect;
    Proiecte tip;
    Amanunte detalii;
    double cost_estimat;
public:
    explicit Proiect(std::string  nume = "", Proiecte tip_ = Proiecte::STRADA, Amanunte det = Amanunte::DE_LA_ZERO, int cost = 0);

    Proiect(const Proiect& other);
    Proiect& operator=(const Proiect& other);
    ~Proiect();

    [[nodiscard]] const std::string& get_nume() const;
    [[nodiscard]] Proiecte get_tip() const;
    [[nodiscard]] Amanunte get_detalii() const;
    [[nodiscard]] double get_cost_estimat() const;

    friend std::ostream& operator<<(std::ostream& os, const Proiect& p);
};

Proiect::Proiect(std::string  nume, Proiecte tip_, Amanunte det, int cost): nume_proiect(std::move(nume)), tip(tip_), detalii(det), cost_estimat(cost) {}

Proiect::Proiect(const Proiect &other): nume_proiect(other.nume_proiect), tip(other.tip), detalii(other.detalii), cost_estimat(other.cost_estimat) {}

Proiect& Proiect::operator=(const Proiect &other) {
    if (this != &other) {
        nume_proiect = other.nume_proiect;
        tip = other.tip;
        detalii = other.detalii;
        cost_estimat = other.cost_estimat;
    }
    return *this;
}

Proiect::~Proiect() {
    std::cout << "Destructor Proiect apelat\n";
}

const std::string& Proiect::get_nume() const { return nume_proiect; }
Proiecte Proiect::get_tip() const { return tip; }
Amanunte Proiect::get_detalii() const { return detalii; }
double Proiect::get_cost_estimat() const { return cost_estimat; }

std::ostream& operator<<(std::ostream& os, const Proiect& p) {
    os << " Proiect: " << p.nume_proiect << "( Cost estimat: " << p.cost_estimat << " RON )\n";
    os << " Detalii: " << "proiectul este destinat " << prtostr(p.tip) << ",iar acesta este de tipul "<< amtostr(p.detalii) <<"\n";
    return os;
}

class Zona {
private:
    std::string nume_zona;
    std::vector<Strada> strazi;
    std::vector<CladireRezidentiala> cladiri_rezidentiale;
    std::vector<CladirePublica> cladiri_publice;
public:
    explicit Zona(std::string  nume = "");

    Zona(const Zona& other);
    Zona& operator=(const Zona& other);
    ~Zona();

    void adauga_strada(const Strada& s);
    void adauga_cladire_rezidentiala(const CladireRezidentiala& cr);
    void adauga_cladire_publica(const CladirePublica& cp);

    // functie pentru calculul intretinerii platite de primarie pentru o zona
    [[nodiscard]] double calcul_cost_intretinere_zona() const;

    // functie pentru calculul masinilor dintr-o zona pentru a putea aplica taxele in functie de acest numar
    [[nodiscard]] int calcul_numar_masini_zona() const;

    // functie pentru calculul taxelor, impozitelor, chirii si orice tip de venit incasat de primarie
    [[nodiscard]] double calcul_incasari_zona() const;

    [[nodiscard]] const std::string& get_nume() const;
    [[nodiscard]] const std::vector<CladireRezidentiala>& get_cladiri_rezidentiale() const;

    std::vector<Strada>& get_strazi_modificabile();
    std::vector<CladireRezidentiala>& get_cladiri_rezidentiale_modificabile();
    std::vector<CladirePublica>& get_cladiri_publice_modificabile();

    friend std::ostream& operator<<(std::ostream& os, const Zona& z);
};

Zona::Zona(std::string  nume) : nume_zona(std::move(nume)) {}

Zona::Zona(const Zona& other): nume_zona(other.nume_zona), strazi(other.strazi), cladiri_rezidentiale(other.cladiri_rezidentiale), cladiri_publice(other.cladiri_publice) {}

Zona& Zona::operator=(const Zona& other) {
    if (this != &other) {
        nume_zona = other.nume_zona;
        strazi = other.strazi;
        cladiri_rezidentiale = other.cladiri_rezidentiale;
        cladiri_publice = other.cladiri_publice;
    }
    return *this;
}

Zona::~Zona() {
    std::cout << "Destructor Zona apelat\n";
}

void Zona::adauga_strada(const Strada& s) { strazi.push_back(s); }
void Zona::adauga_cladire_rezidentiala(const CladireRezidentiala& cr) { cladiri_rezidentiale.push_back(cr); }
void Zona::adauga_cladire_publica(const CladirePublica& cp) { cladiri_publice.push_back(cp); }

double Zona::calcul_cost_intretinere_zona() const {
    double total = 0;

    for (const Strada& s : strazi) {
        total += s.get_cost_intretinere();
    }

    for (const CladireRezidentiala& cr : cladiri_rezidentiale) {
        total += cr.get_cost_intretinere();
    }

    for (const CladirePublica& cp : cladiri_publice) {
        total += cp.get_cost_intretinere();
    }

    return total;
}

int Zona::calcul_numar_masini_zona() const {
    int nr_locuitori = 0;
    for (const CladireRezidentiala& cr : this -> cladiri_rezidentiale) {
        nr_locuitori += cr.get_numar_locuitori();
    }

    return nr_locuitori / 2;
}

double Zona::calcul_incasari_zona() const {
    double total = 0;

    for (const CladireRezidentiala& cr : cladiri_rezidentiale) {
        if (cr.get_tip() == CladiriRezidentiale::CASA) {
            total += cr.get_numar_locuitori() * 15;
        }
        else if (cr.get_tip() == CladiriRezidentiale::BLOC) {
            total += cr.get_numar_locuitori() * 10;
        }
    }

    for (const CladirePublica& cp : cladiri_publice) {
        if (cp.get_inchiriat()) {
            CladiriPublice tip_cladire = cp.get_tip();
            if (tip_cladire == CladiriPublice::SPATIU_COMERCIAL) {
                total += cp.get_capacitate() * 200;
            } else if (tip_cladire == CladiriPublice::CLADIRE_BIROURI) {
                total += cp.get_capacitate() * 300;
            } else if (tip_cladire == CladiriPublice::SCOALA || tip_cladire == CladiriPublice::SPITAL || tip_cladire == CladiriPublice::UNIVERSITATE) {
                total += cp.get_capacitate() * 25;
            }
            else {
                total += cp.get_capacitate() * 100;
            }
        }
    }

    for (const Strada& s : strazi) {
        double taxa = s.get_numar_benzi() * 7 * s.get_lungime() * 0.5;
        if (!s.get_sens_unic())
            taxa *= 2.0;
        total += taxa;
    }

    return total;
}

const std::string& Zona::get_nume() const { return nume_zona; }
const std::vector<CladireRezidentiala>& Zona::get_cladiri_rezidentiale() const {
    return cladiri_rezidentiale;
}
std::vector<Strada>& Zona::get_strazi_modificabile() { return strazi; }
std::vector<CladireRezidentiala>& Zona::get_cladiri_rezidentiale_modificabile() { return cladiri_rezidentiale; }
std::vector<CladirePublica>& Zona::get_cladiri_publice_modificabile() { return cladiri_publice; }

std::ostream& operator<<(std::ostream& os, const Zona& z) {
    os << " Zona: " << z.nume_zona << "\n\n";

    os << " Strazi (" << z.strazi.size() << "):\n";
    if (z.strazi.empty()) {
        os << "Nicio strada\n";
    } else {
        for (const Strada& s : z.strazi) {
            os << s << "\n";
        }
    }

    os << "  Cladiri Rezidentiale (" << z.cladiri_rezidentiale.size() << "):\n";
    if (z.cladiri_rezidentiale.empty()) {
        os << "Nicio cladire rezidentiala\n";
    } else {
        for (const CladireRezidentiala& cr : z.cladiri_rezidentiale) {
            os << cr << "\n";
        }
    }

    os << "  Cladiri Publice (" << z.cladiri_publice.size() << "):\n";
    if (z.cladiri_publice.empty()) {
        os << "Nicio cladire publica\n";
    } else {
        for (const CladirePublica& cp : z.cladiri_publice) {
            os << cp << "\n";
        }
    }

    return os;
}

class Oras {
private:
    std::string nume_oras;
    double buget_curent;
    double indice_fericire;
    std::vector<Zona> zone;

    Zona* cautare_zona(const std::string& nume);

    [[nodiscard]] const Zona* cautare_zona(const std::string& nume) const;

public:

    explicit Oras(std::string nume = "", double buget = 0.0, double fericire_init = 0.5);

    Oras(const Oras& other);
    Oras& operator=(const Oras& other);
    ~Oras();

    void adauga_zona(const Zona& z);

    [[nodiscard]] double calcul_cost_intretinere_total() const;
    [[nodiscard]] double calcul_incasari_totale() const;
    [[nodiscard]] int calcul_numar_total_masini() const;

    [[nodiscard]] bool implementare_proiect_stradal(const Proiect& p, const Strada& s, const std::string& nume_zona_proiect);
    [[nodiscard]] bool implementare_proiect_rezidential(const Proiect& p, const CladireRezidentiala& cr, const std::string& nume_zona_proiect);
    [[nodiscard]] bool implementare_proiect_public(const Proiect& p, const CladirePublica& cp, const std::string& nume_zona_proiect);



    void simulare_luna();

    [[nodiscard]] double get_buget() const;
    [[nodiscard]] double get_fericire() const;

    friend std::ostream& operator<<(std::ostream& os, const Oras& o);
};

Zona* Oras::cautare_zona(const std::string& nume) {
    for (Zona& z : zone) {
        if (z.get_nume() == nume) {
            return &z;
        }
    }
    return nullptr;
}

const Zona* Oras::cautare_zona(const std::string& nume) const{
    for (const Zona& z : zone) {
        if (z.get_nume() == nume) {
            return &z;
        }
    }
    return nullptr;
}

Oras::Oras(std::string nume, double buget, double fericire_init): nume_oras(std::move(nume)), buget_curent(buget), indice_fericire(fericire_init) {}

Oras::Oras(const Oras& other)
    : nume_oras(other.nume_oras), buget_curent(other.buget_curent),
      indice_fericire(other.indice_fericire), zone(other.zone) {}

Oras& Oras::operator=(const Oras& other) {
    if (this != &other) {
        nume_oras = other.nume_oras;
        buget_curent = other.buget_curent;
        indice_fericire = other.indice_fericire;
        zone = other.zone;
    }
    return *this;
}

Oras::~Oras() {
    std::cout << "Destructor Oras apelat\n";
}

void Oras::adauga_zona(const Zona& z) { zone.push_back(z); }

double Oras::calcul_cost_intretinere_total() const {
    double total = 0;
    for (const Zona& z : zone) {
        total += z.calcul_cost_intretinere_zona();
    }
    return total;
}

double Oras::calcul_incasari_totale() const {
    double total = 0;
    for (const Zona& z : zone) {
        total += z.calcul_incasari_zona();
    }
    return total;
}

int Oras::calcul_numar_total_masini() const {
    int total = 0;
    for (const Zona& z : zone) {
        total += z.calcul_numar_masini_zona();
    }
    return total;
}

double Oras::get_buget() const { return buget_curent; }
double Oras::get_fericire() const { return indice_fericire; }

[[nodiscard]] bool Oras::implementare_proiect_stradal(const Proiect& p, const Strada& s, const std::string& nume_zona_proiect) {
    if (p.get_tip() != Proiecte::STRADA) return false;
    if (buget_curent < p.get_cost_estimat()) return false;
    Zona* zona_tinta = cautare_zona(nume_zona_proiect);
    if (zona_tinta == nullptr) return false;
    buget_curent -= p.get_cost_estimat();
    zona_tinta -> adauga_strada(s);
    if (p.get_detalii() == Amanunte::DEMOLARE)
        indice_fericire = std::max(0.0, indice_fericire - 0.03);
    else if (p.get_detalii() == Amanunte::IMBUNATATIRE)
        indice_fericire = std::min(1.0, indice_fericire + 0.01);
    else indice_fericire = std::min(1.0, indice_fericire + 0.02);
    return true;
}

[[nodiscard]] bool Oras::implementare_proiect_rezidential(const Proiect& p, const CladireRezidentiala& cr, const std::string& nume_zona_proiect) {
    if (p.get_tip() != Proiecte::REZIDENTIAL) return false;
    if (buget_curent < p.get_cost_estimat()) return false;
    Zona* zona_tinta = cautare_zona(nume_zona_proiect);
    if (zona_tinta == nullptr) return false;
    buget_curent -= p.get_cost_estimat();
    zona_tinta->adauga_cladire_rezidentiala(cr);
    if (p.get_detalii() == Amanunte::DEMOLARE) {
        if (cr.get_tip() == CladiriRezidentiale::CASA)
            indice_fericire = std::max(0.0, indice_fericire - 0.01);
        else indice_fericire = std::max(0.0, indice_fericire - 0.05);
    }
    else if (p.get_detalii() == Amanunte::IMBUNATATIRE)
        indice_fericire = std::min(1.0, indice_fericire + 0.04);
    else indice_fericire = std::min(1.0, indice_fericire + 0.02);
    return true;
}

[[nodiscard]] bool Oras::implementare_proiect_public(const Proiect& p, const CladirePublica& cp, const std::string& nume_zona_proiect) {
    if (p.get_tip() != Proiecte::PUBLIC) return false;
    if (buget_curent < p.get_cost_estimat()) return false;
    Zona* zona_tinta = cautare_zona(nume_zona_proiect);
    if (zona_tinta == nullptr) return false;
    buget_curent -= p.get_cost_estimat();
    zona_tinta->adauga_cladire_publica(cp);
    if (p.get_detalii() == Amanunte::DEMOLARE) {
        if (cp.get_tip() == CladiriPublice::FABRICA)
            indice_fericire = std::min(0.0, indice_fericire + 0.04);
        else if (cp.get_tip() == CladiriPublice::BISERICA)
            indice_fericire = std::max(1.0, indice_fericire - 0.07);
        else if (cp.get_tip() == CladiriPublice::SPATIU_COMERCIAL)
            indice_fericire = std::max(1.0, indice_fericire - 0.1);
        else if (cp.get_tip() == CladiriPublice::PARC)
            indice_fericire = std::max(1.0, indice_fericire - 0.07);
        else if (cp.get_tip() == CladiriPublice::SPITAL)
            indice_fericire = std::max(1.0, indice_fericire - 0.08);
        else if (cp.get_tip() == CladiriPublice::CLADIRE_BIROURI)
            indice_fericire = std::max(1.0, indice_fericire - 0.04);
        else if (cp.get_tip() == CladiriPublice::POMPIERI)
            indice_fericire = std::max(1.0, indice_fericire - 0.02);
        else if (cp.get_tip() == CladiriPublice::POLITIE)
            indice_fericire = std::max(1.0, indice_fericire - 0.01);
        else if (cp.get_tip() == CladiriPublice::SCOALA)
            indice_fericire = std::max(1.0, indice_fericire - 0.04);
        else if (cp.get_tip() == CladiriPublice::UNIVERSITATE)
            indice_fericire = std::max(1.0, indice_fericire - 0.05);
    }
    else if (p.get_detalii() == Amanunte::IMBUNATATIRE) {
        if (cp.get_tip() == CladiriPublice::FABRICA)
            indice_fericire = std::min(0.0, indice_fericire + 0.02);
        else if (cp.get_tip() == CladiriPublice::BISERICA)
            indice_fericire = std::min(1.0, indice_fericire + 0.03);
        else if (cp.get_tip() == CladiriPublice::SPATIU_COMERCIAL)
            indice_fericire = std::min(1.0, indice_fericire + 0.05);
        else if (cp.get_tip() == CladiriPublice::PARC)
            indice_fericire = std::min(1.0, indice_fericire + 0.02);
        else if (cp.get_tip() == CladiriPublice::SPITAL)
            indice_fericire = std::min(1.0, indice_fericire + 0.06);
        else if (cp.get_tip() == CladiriPublice::CLADIRE_BIROURI)
            indice_fericire = std::min(1.0, indice_fericire + 0.01);
        else if (cp.get_tip() == CladiriPublice::POMPIERI)
            indice_fericire = std::min(1.0, indice_fericire + 0.03);
        else if (cp.get_tip() == CladiriPublice::POLITIE)
            indice_fericire = std::min(1.0, indice_fericire + 0.02);
        else if (cp.get_tip() == CladiriPublice::SCOALA)
            indice_fericire = std::min(1.0, indice_fericire + 0.02);
        else if (cp.get_tip() == CladiriPublice::UNIVERSITATE)
            indice_fericire = std::min(1.0, indice_fericire + 0.03);
    }
    else if (p.get_detalii() == Amanunte::DE_LA_ZERO) {
        if (cp.get_tip() == CladiriPublice::FABRICA)
            indice_fericire = std::max(0.0, indice_fericire - 0.03);
        else if (cp.get_tip() == CladiriPublice::BISERICA)
            indice_fericire = std::min(1.0, indice_fericire + 0.04);
        else if (cp.get_tip() == CladiriPublice::SPATIU_COMERCIAL)
            indice_fericire = std::min(1.0, indice_fericire + 0.08);
        else if (cp.get_tip() == CladiriPublice::PARC)
            indice_fericire = std::min(1.0, indice_fericire + 0.05);
        else if (cp.get_tip() == CladiriPublice::SPITAL)
            indice_fericire = std::min(1.0, indice_fericire + 0.07);
        else if (cp.get_tip() == CladiriPublice::CLADIRE_BIROURI)
            indice_fericire = std::min(1.0, indice_fericire + 0.02);
        else if (cp.get_tip() == CladiriPublice::POMPIERI)
            indice_fericire = std::min(1.0, indice_fericire + 0.03);
        else if (cp.get_tip() == CladiriPublice::POLITIE)
            indice_fericire = std::min(1.0, indice_fericire + 0.02);
        else if (cp.get_tip() == CladiriPublice::SCOALA)
            indice_fericire = std::min(1.0, indice_fericire + 0.02);
        else if (cp.get_tip() == CladiriPublice::UNIVERSITATE)
            indice_fericire = std::min(1.0, indice_fericire + 0.04);
    }
    return true;
}

void Oras::simulare_luna() {
    std::cout << "\n>>> SIMULARE LUNA... <<<\n";
    double cost_lunar = calcul_cost_intretinere_total();
    double venit_lunar = calcul_incasari_totale();
    std::cout << "Cost intretinere lunar: " << cost_lunar << " RON\n";
    std::cout << "Venit lunar (taxe+chirii): " << venit_lunar << " RON\n";
    double sold = venit_lunar - cost_lunar;
    buget_curent += sold;

    if (buget_curent < 0) indice_fericire = std::max(0.0, indice_fericire - 0.05);
    else if (sold < 0) indice_fericire = std::max(0.0, indice_fericire - 0.01);
    else indice_fericire = std::min(1.0, indice_fericire + 0.01);
    std::cout << "Sold lunar: " << sold << " RON.\nBuget nou: " << buget_curent << " RON.\nFericire noua: " << (indice_fericire*100) << "%\n";
}

std::ostream& operator<<(std::ostream& os, const Oras& o) {
    os << "========================================\n";
    os << "Raportul orasului: " << o.nume_oras << "\n";
    os << "========================================\n";
    os << "Buget Curent: " << o.buget_curent << " RON\n";
    os << "Indice Fericire: " << (o.indice_fericire * 100) << "%\n";
    os << "----------------------------------------\n";
    os << "Zone (" << o.zone.size() << "):\n\n";
    if (o.zone.empty()) {
        os << "(Orasul este gol)\n";
    } else {
        for (const Zona& z : o.zone) {
            os << z << "\n";
        }
    }
    os << "========================================\n";
    return os;
}

int main() {
std::cout << std::fixed << std::setprecision(2);

    std::cout << "--- Initializare Simulator Urban ---\n";

    // creare structuri initiale
    Strada str_principala(100, "Bd. Unirii", 50000.0, 1000.0, true, false, 4, 2500.0);
    CladireRezidentiala bloc_a1(200, "Bloc A1", 100000.0, 500.0, CladiriRezidentiale::BLOC, 70.0, 4, 120);
    CladirePublica spital_jud(300, "Spitalul Judetean", 300000.0, 8000.0, CladiriPublice::SPITAL, 250, true);
    CladirePublica parc_central(301, "Parcul Central", 80000.0, 500.0, CladiriPublice::PARC, 10000, false);

    // creare si populare zone ---
    Zona zona_centru("Centru");
    zona_centru.adauga_strada(str_principala);
    zona_centru.adauga_cladire_publica(spital_jud);
    zona_centru.adauga_cladire_publica(parc_central);

    Zona zona_rezidentiala("Cartier Sud");
    zona_rezidentiala.adauga_cladire_rezidentiala(bloc_a1);

    // creare oras si adaugare zone
    Oras simCity("SimCity Bucharest", 1000000.0, 0.75);
    simCity.adauga_zona(zona_centru);
    simCity.adauga_zona(zona_rezidentiala);

    // testare operator
    std::cout << "\n--- STAREA INITIALA ---\n";
    std::cout << simCity;

    // testare regula celor trei
    std::cout << "\n--- Testare Regula Celor Trei pentru Oras ---\n";
    Oras copie_oras = simCity;
    copie_oras.adauga_zona(Zona("Zona Copiata - TEST"));
    Oras oras_atribuit("oras vechi", 0.0, 0.0);
    oras_atribuit = simCity;
    std::cout << "Testare copiere si atribuire finalizata (obiectele vor fi afisate la final).\n";

    // testare funcții
    std::cout << "\n--- Testare Functii Netriviale ---\n";

    double cost_total_intretinere = simCity.calcul_cost_intretinere_total();
    std::cout << "COST TOTAL INTRETINERE: " << cost_total_intretinere << " RON\n";

    double incasari_totale = simCity.calcul_incasari_totale();
    std::cout << "INCASARI TOTALE: " << incasari_totale << " RON\n";

    int nr_masini = simCity.calcul_numar_total_masini();
    std::cout << "NETRIVIAL #3: Numar total masini estimate: " << nr_masini << "\n";

    simCity.simulare_luna(); // Bonus

    Proiect proiect_casa("Dezvoltare Casa Cartier Sud", Proiecte::REZIDENTIAL, Amanunte::DE_LA_ZERO, 80000.0);
    CladireRezidentiala casa_noua(201, "Casa Sfatului", 0.0, 300.0, CladiriRezidentiale::CASA, 120.0, 2, 5);

    std::cout << "\n>>>: Incercare implementare proiect casa...\n";
    bool succes_casa = simCity.implementare_proiect_rezidential(proiect_casa, casa_noua, "Cartier Sud");
    if(succes_casa) std::cout << "SUCCES: Proiectul casa a fost implementat.\n";
    else std::cout << "ESEC: Proiectul casa NU a fost implementat.\n";


    // afișare stare finală
    std::cout << "\n--- STAREA FINALA A ORASULUI ---\n";
    std::cout << simCity;

    // afisare copii
    std::cout << "\n--- STAREA ORASULUI COPIAT ---\n";
    std::cout << copie_oras;
    std::cout << "\n--- STAREA ORASULUI ATRIBUIT ---\n";
    std::cout << oras_atribuit;


    std::cout << "\nSimulare finalizata.\n";
    return 0;
}
