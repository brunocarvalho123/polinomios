typedef struct list Poli;

struct frac {
	int numerador;
	int denominador;
};

struct list {
  int con;
  char *var;
  int exp;
  struct frac *Frac;
  Poli *next;
};

Poli *newitem(int conTemp, char varTemp, int expTemp);

Poli *newMon(Poli *poli, Poli *temp);

Poli *append (Poli *poli1, Poli *poli2, Poli *original);

void delete(Poli *poli);

void printPoli(Poli *poli);

Poli *polToList(char poli[20]);
