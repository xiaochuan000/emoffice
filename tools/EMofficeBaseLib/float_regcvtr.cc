#include "float_regcvtr.h"

regcvtr::regcvtr()
{
  n = 0;
  field = 0;
}

ifstream &operator>> (ifstream &inputFile, regcvtr &reg)
{
  int i;
  
  for (i = 0; i < reg.n; i ++) {
    double re, im;
    inputFile >> re >> im;
    reg.field[i].x = Complex (re, im);

    inputFile >> re >> im;
    reg.field[i].y = Complex (re, im);

    inputFile >> re >> im;
    reg.field[i].z = Complex (re, im);
  }

  return inputFile;
}

ofstream &operator<< (ofstream &outputFile, const regcvtr &reg)
{
  int i;

  for (i = 0; i < reg.n; i ++) {
    outputFile << reg.field[i].x.real() << " " << reg.field[i].x.imag() << endl;
    outputFile << reg.field[i].y.real() << " " << reg.field[i].y.imag() << endl;
    outputFile << reg.field[i].z.real() << " " << reg.field[i].z.imag() << endl;
  }
  outputFile << endl;

  return outputFile;
}

void regcvtr::SetField(int id, cVtr cv)
{
  if (id < 0 || id >= n) return;

  field[id] = cv;
}

cVtr regcvtr::GetField(int id) 
{
  cVtr cv;

  if (id < 0 || id >= n) return cv;

  return field[id]; 
}

void regcvtr::init(int dim) 
{
  n = dim;
  field = new cVtr[n];
}

void ReadRegcvtr(char *regName, int nT, regcvtr *reg)
{
  ifstream fin(regName, ios::in);
  int i;
  char buffer[360];

  //  fin >> buffer;

  for (i = 0; i < nT; i ++)
    fin >> (reg[i]);

  fin.close();
}

cVtr GetField(regcvtr reg, double z0, double z1, double z2)
{
  double zeta[3];
  cVtr cv;
  
  zeta[0] = z0; zeta[1] = z1; zeta[2] = z2;
  
  int i, i1, i2;
  if (reg.n == 6) {
    for (i = 0; i < 3; i ++) 
      cv = cv + reg.GetField(i) * (2.0 * zeta[i] * (zeta[i] - 0.5));
    for (i = 0; i < 3; i ++) {
      i1 = (i + 1) % 3;
      i2 = (i + 2) % 3;
    
      cv = cv + reg.GetField(i + 3) * (4.0 * zeta[i1] * zeta[i2]);
    }
  }
  if (reg.n == 3) {
    for (i = 0; i < 3; i ++) 
      cv = cv + reg.GetField(i) * zeta[i];
  }

  return cv;
}



