
#include "amici/symbolic_functions.h"
#include "amici/defines.h" //realtype definition
typedef amici::realtype realtype;
#include <cmath> 

void xBdot_model_jakstat_adjoint_o2(realtype *xBdot, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *xB, const realtype *w, const realtype *dwdx) {
  xBdot[0] = -p[0]*w[0]*xB[1]+k[0]*p[0]*w[0]*w[2]*xB[0];
  xBdot[1] = p[1]*xB[1]*dwdx[0]*2.0-p[1]*xB[2]*dwdx[0];
  xBdot[2] = p[2]*xB[2]-k[0]*p[2]*w[3]*xB[3];
  xBdot[3] = -p[3]*xB[4]*dwdx[1]+k[1]*p[3]*w[3]*xB[3];
  xBdot[4] = p[3]*xB[4]-p[3]*xB[5];
  xBdot[5] = p[3]*xB[5]-p[3]*xB[6];
  xBdot[6] = p[3]*xB[6]-p[3]*xB[7];
  xBdot[7] = p[3]*xB[7]-p[3]*xB[8];
  xBdot[8] = p[3]*xB[8]-k[1]*p[3]*w[2]*xB[0];
  xBdot[9] = w[0]*xB[0]-w[0]*xB[1]+p[0]*w[0]*xB[9]-p[0]*w[0]*xB[10];
  xBdot[10] = p[1]*x[1]*xB[10]*4.0+p[1]*x[10]*xB[1]*4.0-p[1]*x[1]*xB[11]*2.0-p[1]*x[10]*xB[2]*2.0;
  xBdot[11] = p[2]*xB[11]-k[0]*p[2]*w[3]*xB[12];
  xBdot[12] = p[3]*xB[12]-p[3]*xB[13]*2.0;
  xBdot[13] = p[3]*xB[13]-p[3]*xB[14];
  xBdot[14] = p[3]*xB[14]-p[3]*xB[15];
  xBdot[15] = p[3]*xB[15]-p[3]*xB[16];
  xBdot[16] = p[3]*xB[16]-p[3]*xB[17];
  xBdot[17] = p[3]*xB[17]-k[1]*p[3]*w[2]*xB[9];
  xBdot[18] = p[0]*w[0]*xB[18]-p[0]*w[0]*xB[19];
  xBdot[19] = xB[1]*(dwdx[0]*2.0+p[1]*x[19]*4.0)-xB[2]*(dwdx[0]+p[1]*x[19]*2.0)+p[1]*x[1]*xB[19]*4.0-p[1]*x[1]*xB[20]*2.0;
  xBdot[20] = p[2]*xB[20]-k[0]*p[2]*w[3]*xB[21];
  xBdot[21] = p[3]*xB[21]-p[3]*xB[22]*2.0;
  xBdot[22] = p[3]*xB[22]-p[3]*xB[23];
  xBdot[23] = p[3]*xB[23]-p[3]*xB[24];
  xBdot[24] = p[3]*xB[24]-p[3]*xB[25];
  xBdot[25] = p[3]*xB[25]-p[3]*xB[26];
  xBdot[26] = p[3]*xB[26]-k[1]*p[3]*w[2]*xB[18];
  xBdot[27] = p[0]*w[0]*xB[27]-p[0]*w[0]*xB[28];
  xBdot[28] = p[1]*x[1]*xB[28]*4.0+p[1]*x[28]*xB[1]*4.0-p[1]*x[1]*xB[29]*2.0-p[1]*x[28]*xB[2]*2.0;
  xBdot[29] = xB[2]+p[2]*xB[29]-k[0]*w[3]*xB[3]-k[0]*p[2]*w[3]*xB[30];
  xBdot[30] = p[3]*xB[30]-p[3]*xB[31]*2.0;
  xBdot[31] = p[3]*xB[31]-p[3]*xB[32];
  xBdot[32] = p[3]*xB[32]-p[3]*xB[33];
  xBdot[33] = p[3]*xB[33]-p[3]*xB[34];
  xBdot[34] = p[3]*xB[34]-p[3]*xB[35];
  xBdot[35] = p[3]*xB[35]-k[1]*p[3]*w[2]*xB[27];
  xBdot[36] = p[0]*w[0]*xB[36]-p[0]*w[0]*xB[37];
  xBdot[37] = p[1]*x[1]*xB[37]*4.0+p[1]*x[37]*xB[1]*4.0-p[1]*x[1]*xB[38]*2.0-p[1]*x[37]*xB[2]*2.0;
  xBdot[38] = p[2]*xB[38]-k[0]*p[2]*w[3]*xB[39];
  xBdot[39] = xB[3]+p[3]*xB[39]-p[3]*xB[40]*2.0-xB[4]*dwdx[1];
  xBdot[40] = xB[4]-xB[5]+p[3]*xB[40]-p[3]*xB[41];
  xBdot[41] = xB[5]-xB[6]+p[3]*xB[41]-p[3]*xB[42];
  xBdot[42] = xB[6]-xB[7]+p[3]*xB[42]-p[3]*xB[43];
  xBdot[43] = xB[7]-xB[8]+p[3]*xB[43]-p[3]*xB[44];
  xBdot[44] = xB[8]+p[3]*xB[44]-k[1]*w[2]*xB[0]-k[1]*p[3]*w[2]*xB[36];
  xBdot[45] = p[0]*w[0]*xB[45]-p[0]*w[0]*xB[46];
  xBdot[46] = p[1]*x[1]*xB[46]*4.0+p[1]*x[46]*xB[1]*4.0-p[1]*x[1]*xB[47]*2.0-p[1]*x[46]*xB[2]*2.0;
  xBdot[47] = p[2]*xB[47]-k[0]*p[2]*w[3]*xB[48];
  xBdot[48] = p[3]*xB[48]-p[3]*xB[49]*2.0;
  xBdot[49] = p[3]*xB[49]-p[3]*xB[50];
  xBdot[50] = p[3]*xB[50]-p[3]*xB[51];
  xBdot[51] = p[3]*xB[51]-p[3]*xB[52];
  xBdot[52] = p[3]*xB[52]-p[3]*xB[53];
  xBdot[53] = p[3]*xB[53]-k[1]*p[3]*w[2]*xB[45];
  xBdot[54] = p[0]*w[5]*xB[0]-p[0]*w[5]*xB[1]+p[0]*w[0]*xB[54]-p[0]*w[0]*xB[55];
  xBdot[55] = p[1]*x[1]*xB[55]*4.0+p[1]*x[55]*xB[1]*4.0-p[1]*x[1]*xB[56]*2.0-p[1]*x[55]*xB[2]*2.0;
  xBdot[56] = p[2]*xB[56]-k[0]*p[2]*w[3]*xB[57];
  xBdot[57] = p[3]*xB[57]-p[3]*xB[58]*2.0;
  xBdot[58] = p[3]*xB[58]-p[3]*xB[59];
  xBdot[59] = p[3]*xB[59]-p[3]*xB[60];
  xBdot[60] = p[3]*xB[60]-p[3]*xB[61];
  xBdot[61] = p[3]*xB[61]-p[3]*xB[62];
  xBdot[62] = p[3]*xB[62]-k[1]*p[3]*w[2]*xB[54];
  xBdot[63] = p[0]*w[6]*xB[0]-p[0]*w[6]*xB[1]+p[0]*w[0]*xB[63]-p[0]*w[0]*xB[64];
  xBdot[64] = p[1]*x[1]*xB[64]*4.0+p[1]*x[64]*xB[1]*4.0-p[1]*x[1]*xB[65]*2.0-p[1]*x[64]*xB[2]*2.0;
  xBdot[65] = p[2]*xB[65]-k[0]*p[2]*w[3]*xB[66];
  xBdot[66] = p[3]*xB[66]-p[3]*xB[67]*2.0;
  xBdot[67] = p[3]*xB[67]-p[3]*xB[68];
  xBdot[68] = p[3]*xB[68]-p[3]*xB[69];
  xBdot[69] = p[3]*xB[69]-p[3]*xB[70];
  xBdot[70] = p[3]*xB[70]-p[3]*xB[71];
  xBdot[71] = p[3]*xB[71]-k[1]*p[3]*w[2]*xB[63];
  xBdot[72] = p[0]*w[7]*xB[0]-p[0]*w[7]*xB[1]+p[0]*w[0]*xB[72]-p[0]*w[0]*xB[73];
  xBdot[73] = p[1]*x[1]*xB[73]*4.0+p[1]*xB[1]*x[73]*4.0-p[1]*x[1]*xB[74]*2.0-p[1]*xB[2]*x[73]*2.0;
  xBdot[74] = p[2]*xB[74]-k[0]*p[2]*w[3]*xB[75];
  xBdot[75] = p[3]*xB[75]-p[3]*xB[76]*2.0;
  xBdot[76] = p[3]*xB[76]-p[3]*xB[77];
  xBdot[77] = p[3]*xB[77]-p[3]*xB[78];
  xBdot[78] = p[3]*xB[78]-p[3]*xB[79];
  xBdot[79] = p[3]*xB[79]-p[3]*xB[80];
  xBdot[80] = p[3]*xB[80]-k[1]*p[3]*w[2]*xB[72];
  xBdot[81] = p[0]*w[8]*xB[0]-p[0]*w[8]*xB[1]+p[0]*w[0]*xB[81]-p[0]*w[0]*xB[82];
  xBdot[82] = p[1]*x[1]*xB[82]*4.0+p[1]*xB[1]*x[82]*4.0-p[1]*x[1]*xB[83]*2.0-p[1]*xB[2]*x[82]*2.0;
  xBdot[83] = p[2]*xB[83]-k[0]*p[2]*w[3]*xB[84];
  xBdot[84] = p[3]*xB[84]-p[3]*xB[85]*2.0;
  xBdot[85] = p[3]*xB[85]-p[3]*xB[86];
  xBdot[86] = p[3]*xB[86]-p[3]*xB[87];
  xBdot[87] = p[3]*xB[87]-p[3]*xB[88];
  xBdot[88] = p[3]*xB[88]-p[3]*xB[89];
  xBdot[89] = p[3]*xB[89]-k[1]*p[3]*w[2]*xB[81];
  xBdot[90] = p[0]*w[9]*xB[0]-p[0]*w[9]*xB[1]+p[0]*w[0]*xB[90]-p[0]*w[0]*xB[91];
  xBdot[91] = p[1]*x[1]*xB[91]*4.0+p[1]*xB[1]*x[91]*4.0-p[1]*x[1]*xB[92]*2.0-p[1]*xB[2]*x[91]*2.0;
  xBdot[92] = p[2]*xB[92]-k[0]*p[2]*w[3]*xB[93];
  xBdot[93] = p[3]*xB[93]-p[3]*xB[94]*2.0;
  xBdot[94] = p[3]*xB[94]-p[3]*xB[95];
  xBdot[95] = p[3]*xB[95]-p[3]*xB[96];
  xBdot[96] = p[3]*xB[96]-p[3]*xB[97];
  xBdot[97] = p[3]*xB[97]-p[3]*xB[98];
  xBdot[98] = p[3]*xB[98]-k[1]*p[3]*w[2]*xB[90];
  xBdot[99] = p[0]*w[0]*xB[99]-p[0]*w[0]*xB[100];
  xBdot[100] = p[1]*x[1]*xB[100]*4.0+p[1]*xB[1]*x[100]*4.0-p[1]*x[1]*xB[101]*2.0-p[1]*xB[2]*x[100]*2.0;
  xBdot[101] = p[2]*xB[101]-k[0]*p[2]*w[3]*xB[102];
  xBdot[102] = p[3]*xB[102]-p[3]*xB[103]*2.0;
  xBdot[103] = p[3]*xB[103]-p[3]*xB[104];
  xBdot[104] = p[3]*xB[104]-p[3]*xB[105];
  xBdot[105] = p[3]*xB[105]-p[3]*xB[106];
  xBdot[106] = p[3]*xB[106]-p[3]*xB[107];
  xBdot[107] = p[3]*xB[107]-k[1]*p[3]*w[2]*xB[99];
  xBdot[108] = p[0]*w[0]*xB[108]-p[0]*w[0]*xB[109];
  xBdot[109] = p[1]*x[1]*xB[109]*4.0+p[1]*xB[1]*x[109]*4.0-p[1]*x[1]*xB[110]*2.0-p[1]*xB[2]*x[109]*2.0;
  xBdot[110] = p[2]*xB[110]-k[0]*p[2]*w[3]*xB[111];
  xBdot[111] = p[3]*xB[111]-p[3]*xB[112]*2.0;
  xBdot[112] = p[3]*xB[112]-p[3]*xB[113];
  xBdot[113] = p[3]*xB[113]-p[3]*xB[114];
  xBdot[114] = p[3]*xB[114]-p[3]*xB[115];
  xBdot[115] = p[3]*xB[115]-p[3]*xB[116];
  xBdot[116] = p[3]*xB[116]-k[1]*p[3]*w[2]*xB[108];
  xBdot[117] = p[0]*w[0]*xB[117]-p[0]*w[0]*xB[118];
  xBdot[118] = p[1]*x[1]*xB[118]*4.0+p[1]*xB[1]*x[118]*4.0-p[1]*x[1]*xB[119]*2.0-p[1]*xB[2]*x[118]*2.0;
  xBdot[119] = p[2]*xB[119]-k[0]*p[2]*w[3]*xB[120];
  xBdot[120] = p[3]*xB[120]-p[3]*xB[121]*2.0;
  xBdot[121] = p[3]*xB[121]-p[3]*xB[122];
  xBdot[122] = p[3]*xB[122]-p[3]*xB[123];
  xBdot[123] = p[3]*xB[123]-p[3]*xB[124];
  xBdot[124] = p[3]*xB[124]-p[3]*xB[125];
  xBdot[125] = p[3]*xB[125]-k[1]*p[3]*w[2]*xB[117];
  xBdot[126] = p[0]*w[0]*xB[126]-p[0]*w[0]*xB[127];
  xBdot[127] = p[1]*x[1]*xB[127]*4.0+p[1]*xB[1]*x[127]*4.0-p[1]*x[1]*xB[128]*2.0-p[1]*xB[2]*x[127]*2.0;
  xBdot[128] = p[2]*xB[128]-k[0]*p[2]*w[3]*xB[129];
  xBdot[129] = p[3]*xB[129]-p[3]*xB[130]*2.0;
  xBdot[130] = p[3]*xB[130]-p[3]*xB[131];
  xBdot[131] = p[3]*xB[131]-p[3]*xB[132];
  xBdot[132] = p[3]*xB[132]-p[3]*xB[133];
  xBdot[133] = p[3]*xB[133]-p[3]*xB[134];
  xBdot[134] = p[3]*xB[134]-k[1]*p[3]*w[2]*xB[126];
  xBdot[135] = p[0]*w[0]*xB[135]-p[0]*w[0]*xB[136];
  xBdot[136] = p[1]*x[1]*xB[136]*4.0+p[1]*xB[1]*x[136]*4.0-p[1]*x[1]*xB[137]*2.0-p[1]*xB[2]*x[136]*2.0;
  xBdot[137] = p[2]*xB[137]-k[0]*p[2]*w[3]*xB[138];
  xBdot[138] = p[3]*xB[138]-p[3]*xB[139]*2.0;
  xBdot[139] = p[3]*xB[139]-p[3]*xB[140];
  xBdot[140] = p[3]*xB[140]-p[3]*xB[141];
  xBdot[141] = p[3]*xB[141]-p[3]*xB[142];
  xBdot[142] = p[3]*xB[142]-p[3]*xB[143];
  xBdot[143] = p[3]*xB[143]-k[1]*p[3]*w[2]*xB[135];
  xBdot[144] = p[0]*w[0]*xB[144]-p[0]*w[0]*xB[145];
  xBdot[145] = p[1]*x[1]*xB[145]*4.0+p[1]*xB[1]*x[145]*4.0-p[1]*x[1]*xB[146]*2.0-p[1]*xB[2]*x[145]*2.0;
  xBdot[146] = p[2]*xB[146]-k[0]*p[2]*w[3]*xB[147];
  xBdot[147] = p[3]*xB[147]-p[3]*xB[148]*2.0;
  xBdot[148] = p[3]*xB[148]-p[3]*xB[149];
  xBdot[149] = p[3]*xB[149]-p[3]*xB[150];
  xBdot[150] = p[3]*xB[150]-p[3]*xB[151];
  xBdot[151] = p[3]*xB[151]-p[3]*xB[152];
  xBdot[152] = p[3]*xB[152]-k[1]*p[3]*w[2]*xB[144];
  xBdot[153] = p[0]*w[0]*xB[153]-p[0]*w[0]*xB[154];
  xBdot[154] = p[1]*x[1]*xB[154]*4.0+p[1]*xB[1]*x[154]*4.0-p[1]*x[1]*xB[155]*2.0-p[1]*xB[2]*x[154]*2.0;
  xBdot[155] = p[2]*xB[155]-k[0]*p[2]*w[3]*xB[156];
  xBdot[156] = p[3]*xB[156]-p[3]*xB[157]*2.0;
  xBdot[157] = p[3]*xB[157]-p[3]*xB[158];
  xBdot[158] = p[3]*xB[158]-p[3]*xB[159];
  xBdot[159] = p[3]*xB[159]-p[3]*xB[160];
  xBdot[160] = p[3]*xB[160]-p[3]*xB[161];
  xBdot[161] = p[3]*xB[161]-k[1]*p[3]*w[2]*xB[153];
}

