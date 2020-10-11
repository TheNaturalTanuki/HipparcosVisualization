#include "HipparcosExtraction.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using std::cout;
using std::string;

int writeJson(CatalogueRaw* catalogue);
string charArrayToString(char charArray[], int len);
void compute3Dcoordinates(char plxChar[], char raChar[], char deChar[], float* dly, float* xly, float* yly, float* zly);

int main() {
   string line;
   std::ifstream infile("../../../1.HipparcosData/I_311_hip2.dat.gz.fits.gz");

   if (infile.is_open())
   {
      while (getline(infile, line))
      {
         struct CatalogueRaw * catalogue;
         catalogue = (CatalogueRaw*)(&line[28800]);

         writeJson(catalogue);
      }

      infile.close();
   }

   else cout << "Unable to open infile";

   return 0;
}

int writeJson(CatalogueRaw* catalogue)
{
   std::ofstream outfile("../../../1.HipparcosData/Hipparcos.json");
   if (outfile.is_open())
   {
      outfile << "{\"Stars\": [\n";

      float *dlyp, *xlyp, *ylyp, *zlyp;
      float dly, xly, yly, zly;
      dlyp = &dly;
      xlyp = &xly;
      ylyp = &yly;
      zlyp = &zly;

      outfile << std::fixed;
      outfile << std::setprecision(2);

      for (int i = 0; i < 117955; i++)
      {
         compute3Dcoordinates(catalogue->Stars[i].Plx, catalogue->Stars[i].Rarad, catalogue->Stars[i].Derad, dlyp, xlyp, ylyp, zlyp);

         outfile
            << "   {"
            << "\"Hip\": "    << charArrayToString(catalogue->Stars[i].Hip    , 6)  << ", "
         // << "\"Sn\": "     << charArrayToString(catalogue->Stars[i].Sn     , 4)  << ", "
         // << "\"So\": "     << charArrayToString(catalogue->Stars[i].So     , 2)  << ", "
            << "\"Nc\": "     << charArrayToString(catalogue->Stars[i].Nc     , 2)  << ", "
            << "\"Rarad\": "  << charArrayToString(catalogue->Stars[i].Rarad  , 14) << ", "
            << "\"Derad\": "  << charArrayToString(catalogue->Stars[i].Derad  , 14) << ", "
            << "\"Plx\": "    << charArrayToString(catalogue->Stars[i].Plx    , 8)  << ", "
         // << "\"Pmra\": "   << charArrayToString(catalogue->Stars[i].Pmra   , 9)  << ", "
         // << "\"Pmde\": "   << charArrayToString(catalogue->Stars[i].Pmde   , 9)  << ", "
         // << "\"E1\": "     << charArrayToString(catalogue->Stars[i].E1     , 7)  << ", "
         // << "\"E2\": "     << charArrayToString(catalogue->Stars[i].E2     , 7)  << ", "
         // << "\"E3\": "     << charArrayToString(catalogue->Stars[i].E3     , 7)  << ", "
         // << "\"E4\": "     << charArrayToString(catalogue->Stars[i].E4     , 7)  << ", "
         // << "\"E5\": "     << charArrayToString(catalogue->Stars[i].E5     , 7)  << ", "
         // << "\"Ntr\": "    << charArrayToString(catalogue->Stars[i].Ntr    , 4)  << ", "
         // << "\"F2\": "     << charArrayToString(catalogue->Stars[i].F2     , 6)  << ", "
         // << "\"F1\": "     << charArrayToString(catalogue->Stars[i].F1     , 3)  << ", "
         // << "\"Var\": "    << charArrayToString(catalogue->Stars[i].Var    , 7)  << ", "
         // << "\"Ic\": "     << charArrayToString(catalogue->Stars[i].Ic     , 5)  << ", "
         // << "\"Hpmag\": "  << charArrayToString(catalogue->Stars[i].Hpmag  , 8)  << ", "
         // << "\"E6\": "     << charArrayToString(catalogue->Stars[i].E6     , 7)  << ", "
         // << "\"Shp\": "    << charArrayToString(catalogue->Stars[i].Shp    , 6)  << ", "
         // << "\"Va\": "     << charArrayToString(catalogue->Stars[i].Va     , 2)  << ", "
            << "\"Bv\": "     << charArrayToString(catalogue->Stars[i].Bv     , 7)  << ", "
         // << "\"E7\": "     << charArrayToString(catalogue->Stars[i].E7     , 6)  << ", "
         // << "\"Vi\": "     << charArrayToString(catalogue->Stars[i].Vi     , 7)  << ", "
         // << "\"Uw01\": "   << charArrayToString(catalogue->Stars[i].Uw01   , 7)  << ", "
         // << "\"Uw02\": "   << charArrayToString(catalogue->Stars[i].Uw02   , 7)  << ", "
         // << "\"Uw03\": "   << charArrayToString(catalogue->Stars[i].Uw03   , 7)  << ", "
         // << "\"Uw04\": "   << charArrayToString(catalogue->Stars[i].Uw04   , 7)  << ", "
         // << "\"Uw05\": "   << charArrayToString(catalogue->Stars[i].Uw05   , 7)  << ", "
         // << "\"Uw06\": "   << charArrayToString(catalogue->Stars[i].Uw06   , 7)  << ", "
         // << "\"Uw07\": "   << charArrayToString(catalogue->Stars[i].Uw07   , 7)  << ", "
         // << "\"Uw08\": "   << charArrayToString(catalogue->Stars[i].Uw08   , 7)  << ", "
         // << "\"Uw09\": "   << charArrayToString(catalogue->Stars[i].Uw09   , 7)  << ", "
         // << "\"Uw10\": "   << charArrayToString(catalogue->Stars[i].Uw10   , 7)  << ", "
         // << "\"Uw11\": "   << charArrayToString(catalogue->Stars[i].Uw11   , 7)  << ", "
         // << "\"Uw12\": "   << charArrayToString(catalogue->Stars[i].Uw12   , 7)  << ", "
         // << "\"Uw13\": "   << charArrayToString(catalogue->Stars[i].Uw13   , 7)  << ", "
         // << "\"Uw14\": "   << charArrayToString(catalogue->Stars[i].Uw14   , 7)  << ", "
         // << "\"Uw15\": "   << charArrayToString(catalogue->Stars[i].Uw15   , 7)  << ", "
            << "\"Dly\": " << dly << ", "
            << "\"Xly\": " << xly << ", "
            << "\"Yly\": " << yly << ", "
            << "\"Zly\": " << zly << "},\n";
      }

      outfile << "]}\n";

      outfile.close();
   }

   else cout << "Unable to open outfile";

   return 0;
}

string charArrayToString(char charArray[], int len)
{
   string result = "";

   int i = 0;
   while (charArray[i] == ' ') { i++; }

   for (; i < len; i++)
   {
      result += charArray[i];
   }

   return result;
}

void compute3Dcoordinates(char plxChar[], char raChar[], char deChar[], float* dlyp, float* xlyp, float* ylyp, float* zlyp)
{
   float plx = atof(plxChar);
   float ra = atof(raChar);
   float de = atof(deChar);

   if (plx != 0)
   {
      float dly = 3261.56 / plx;

      *dlyp = dly;

      *xlyp = dly * cos(ra) * cos(de);
      *ylyp = dly * sin(ra) * cos(de);
      *zlyp = dly * sin(de);
   }
}
