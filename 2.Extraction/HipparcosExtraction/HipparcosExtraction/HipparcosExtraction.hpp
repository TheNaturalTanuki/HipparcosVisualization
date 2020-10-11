#pragma once

struct StarRaw
{
   char Hip[6];
   char Sn[4];
   char So[2];
   char Nc[2];
   char Rarad[14];
   char Derad[14];
   char Plx[8];
   char Pmra[9];
   char Pmde[9];
   char E1[7];
   char E2[7];
   char E3[7];
   char E4[7];
   char E5[7];
   char Ntr[4];
   char F2[6];
   char F1[3];
   char Var[7];
   char Ic[5];
   char Hpmag[8];
   char E6[7];
   char Shp[6];
   char Va[2];
   char Bv[7];
   char E7[6];
   char Vi[7];
   char Uw01[7];
   char Uw02[7];
   char Uw03[7];
   char Uw04[7];
   char Uw05[7];
   char Uw06[7];
   char Uw07[7];
   char Uw08[7];
   char Uw09[7];
   char Uw10[7];
   char Uw11[7];
   char Uw12[7];
   char Uw13[7];
   char Uw14[7];
   char Uw15[7];
};

struct CatalogueRaw {
   StarRaw Stars[117955];
};
