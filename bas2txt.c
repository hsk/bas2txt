#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

unsigned char* fileread(const char* fpath);
int hextoi(const char* srcStr);
const char* scanTable(int srcCode);
typedef struct Rec {
  const char* name;
  int value;
} Rec;
const Rec wordTable[] = {
    {">",       0xEE  },{"CMD",    0xD7  },{"ERR",    0xE2  },{"LIST",    0x93  },
    {"PAINT",   0xBF  },{"SPRITE", 0xC7  },{"=",      0xEF  },{"COLOR",   0xBD  },
    {"ERROR",   0xA6  },{"LLIST",  0x9E  },{"PDL",    0xFFA4},{"SQR",     0xFF87},
    {"<",       0xF0  },{"CONT",   0x99  },{"EXP",    0xFF8B},{"LOAD",    0xB5  },
    {"PEEK",    0xFF97},{"STEP",   0xDC  },{"+",      0xF1  },{"COPY",    0xD6  },
    {"FIELD",   0xB1  },{"LOC",    0xFFAC},{"PLAY",   0xC1  },{"STICK",   0xFFA2},
    {"-",       0xF2  },{"COS",    0xFF8C},{"FILES",  0xB7  },{"LOCATE",  0xD8  },
    {"POINT",   0xED  },{"STOP",   0x90  },{"*",      0xF3  },{"CSAVE",   0x9A  },
    {"FIX",     0xFFA1},{"LOF",    0xFFAD},{"POKE",   0x98  },{"STR$",    0xFF93},
    {"/",       0xF4  },{"CSNG",   0xFF9F},{"FN",     0xDE  },{"LOG",     0xFF8A},
    {"POS",     0xFF91},{"STRIG",  0xFFA3},{"^",      0xF5  },{"CSRLIN",  0xE8  },
    {"FOR",     0x82  },{"LPOS",   0xFF9C},{"PRESET", 0xC3  },{"STRING$", 0xE3  },
    {"\\",      0xFC  },{"CVD",    0xFFAA},{"FPOS",   0xFFA7},{"LPRINT",  0x9D  },
    {"PRINT",   0x91  },{"SWAP",   0xA4  },{"ABS",    0xFF86},{"CVI",     0xFFA8},
    {"FRE",     0xFF8F},{"LSET",   0xB8  },{"PSET",   0xC2  },{"TAB(",    0xDB  },
    {"AND",     0xF6  },{"CVS",    0xFFA9},{"GET",    0xB2  },{"MAX",     0xCD  },
    {"PUT",     0xB3  },{"TAN",    0xFF8D},{"ASC",    0xFF95},{"DATA",    0x84  },
    {"GOSUB",   0x8D  },{"MERGE",  0xB6  },{"READ",   0x87  },{"THEN",    0xDA  },
    {"ATN",     0xFF8E},{"DEF",    0x97  },{"GOTO",   0x89  },{"MID$",    0xFF83},
    {"REM",     0x8F  },{"TIME",   0xCB  },{"ATTR$",  0xE9  },{"DEFDBL",  0xAE  },
    {"HEX$",    0xFF9B},{"MKD$",   0xFFB0},{"RENUM",  0xAA  },{"TO",      0xD9  },
    {"AUTO",    0xA9  },{"DEFINT", 0xAC  },{"IF",     0x8B  },{"MKI$",    0xFFAE},
    {"RESTORE", 0x8C  },{"TROFF",  0xA3  },{"BASE",   0xC9  },{"DEFSNG",  0xAD  },
    {"IMP",     0xFA  },{"MKS$",   0xFFAF},{"RESUME", 0xA7  },{"TRON",    0xA2  },
    {"BEEP",    0xC0  },{"DEFSTR", 0xAB  },{"INKEY$", 0xEC  },{"MOD",     0xFB  },
    {"RETURN",  0x8E  },{"USING",  0xE4  },{"BIN$",   0xFF9D},{"DELETE",  0xA8  },
    {"INP",     0xFF90},{"MOTOR",  0xCE  },{"RIGHT$", 0xFF82},{"USR",     0xDD  },
    {"BLOAD",   0xCF  },{"DIM",    0x86  },{"INPUT",  0x85  },{"NAME",    0xD3  },
    {"RND",     0xFF88},{"VAL",    0xFF94},{"BSAVE",  0xD0  },{"DRAW",    0xBE  },
    {"INSTR",   0xE5  },{"NEW",    0x94  },{"RSET",   0xB9  },{"VARPTR",  0xE7  },
    {"CALL",    0xCA  },{"DSKF",   0xFFA6},{"INT",    0xFF85},{"NEXT",    0x83  },
    {"RUN",     0x8A  },{"VDP",    0xC8  },{"CDBL",   0xFFA0},{"DSKI$",   0xEA  },
    {"IPL",     0xD5  },{"NOT",    0xE0  },{"SAVE",   0xBA  },{"VPEEK",   0xFF98},
    {"CHR$",    0xFF96},{"DSKO$",  0xD1  },{"KEY",    0xCC  },{"OCT$",    0xFF9A},
    {"SCREEN",  0xC5  },{"VPOKE",  0xC6  },{"CINT",   0xFF9E},{"ELSE",    0x3AA1},
    {"KILL",    0xD4  },{"OFF",    0xEB  },{"SET",    0xD2  },{"WAIT",    0x96  },
    {"CIRCLE",  0xBC  },{"END",    0x81  },{"LEFT$",  0xFF81},{"ON",      0x95  },
    {"SGN",     0xFF84},{"WIDTH",  0xA0  },{"CLEAR",  0x92  },{"EOF",     0xFFAB},
    {"LEN",     0xFF92},{"OPEN",   0xB0  },{"SIN",    0xFF89},{"XOR",     0xF8  },
    {"CLOAD",   0x9B  },{"EQV",    0xF9  },{"LET",    0x88  },{"OR",      0xF7  },
    {"SOUND",   0xC4  },{"CLOSE",  0xB4  },{"ERASE",  0xA5  },{"LFILES",  0xBB  },
    {"OUT",     0x9C  },{"SPACE$", 0xFF99},{"CLS",    0x9F  },{"ERL",     0xE1  },
    {"LINE",    0xAF  },{"PAD",    0xFFA5},{"SPC(",   0xDF  },{"",        0x00  }};
int dbg;
int main(int argc, const char* argv[]) {
  if (argc < 2) {
    printf("usage: bastxt [msxbasic.bas]\n");
    return (0);
  }
  dbg = 0;
  if (argc >= 3) {
    dbg = 1;
  }
  unsigned char* buff = fileread(argv[1]);
  if(dbg) printf("/*buff %p*/",buff);
  if(dbg) printf("/* head(%02x) */",buff[0]);
  int pos = 1;
  int ofs = 0x8000;
  if(dbg) printf("/* lp(%02x,%02x) lp=%02x%02x */",buff[pos],buff[pos+1],buff[pos+1],buff[pos]);
  int lp = (buff[pos + 1] << 8) | buff[pos]; pos += 2;
  while (lp != 0) {
    if (dbg) printf("/* line(%02x,%02x) */",buff[pos],buff[pos+1]);
    int lineNum = (buff[pos + 1] << 8) | buff[pos]; pos += 2;
    printf("%d ", lineNum);
    while (buff[pos]) {
      int scode = buff[pos++];
      switch (scode) {
        case 0xff:
          scode = (scode << 8) | buff[pos++];
          if(dbg) printf("/* 0xff scode=%d */",scode);
          printf("%s", scanTable(scode));
          break;
        case 0x3a:
          if (buff[pos] > 0x81) {
            scode = (scode << 8) | buff[pos++];
            if (buff[pos] == 0xe6) {
              if(dbg) printf("/* 0x3a ' scode 0x%x*/",scode);
              pos++;
              printf("'");
            } else {
              const char* itmp = scanTable(scode);
              if (itmp) {
                printf("%s", itmp);
              } else {
                pos--;
              }
            }
          } else {
            if(dbg) printf("/* 0x3a : */");
            printf(":");
          }
          break;
        case 0x0b: {  // oct num
          int ivalue = buff[pos] | (buff[pos + 1] << 8); pos += 2;
          printf("&O%O", ivalue);
          break;
        }
        case 0x0c: {  // hex num
          int ivalue = buff[pos] | (buff[pos + 1] << 8); pos += 2;
          printf("&H%X", ivalue);
          break;
        }
        case 0x0e: {  // line num(line)
          int ivalue = buff[pos] | (buff[pos + 1] << 8); pos += 2;
          printf("%X", ivalue);
          break;
        }
        case 0x0d: {  // line num(addr)
          int ivalue = buff[pos] | (buff[pos + 1] << 8); pos += 2;
          ivalue -= ofs;
          int linevalue = buff[ivalue] | (buff[ivalue + 1] << 8);
          printf("%d", linevalue);
          break;
        }
        case 0x0f: {  // num 10-255
          if (dbg) printf("/* num 10-255 0x%02x */",scode);
          int ivalue = buff[pos]; pos += 1;
          printf("%d", ivalue);
          break;
        }
        case 0x11:  // num 0
        case 0x12:  // num 1
        case 0x13:  // num 2
        case 0x14:  // num 3
        case 0x15:  // num 4
        case 0x16:  // num 5
        case 0x17:  // num 6
        case 0x18:  // num 7
        case 0x19:  // num 8
        case 0x1a:  // num 9
          if (dbg) printf("/* num 0x%02x */",scode);
          printf("%d", scode - 0x11);
          break;
        case 0x1c: {  // int num
          if (dbg) printf("/* int 2bytes 0x%02x */",scode);
          int16_t ivalue = buff[pos] | (buff[pos + 1] << 8); pos += 2;
          printf("%d", ivalue);
          break;
        }
        case 0x1d: {  // float num
          if (dbg) printf("/* float 0x%02x */",scode);
          if (buff[pos] & 0x80) printf("-");
          int exponent = buff[pos]& ~0x40; pos++;
          char str[7];
          str[6]=0;
          for(int i=0;i<3;i++) sprintf(&str[i*2],"%02X",buff[pos++]);
          if(dbg) printf("/*exponent = %d*/",exponent);
          if (exponent==0) {
            printf("0.%s",str);
          } else {
            for(int i=0;i<exponent;i++) printf("%c",str[i]);
            int r = 5;
            for(;r>=0;r--) if(str[r]!='0') break;
            if(r>0) printf("."); else printf("!");
            for(int i=exponent;i<=r;i++) printf("%c",str[i]);
          }
          break;
        }
        case 0x1e: {  // double num
          if (dbg) printf("/* double 0x%02x */",scode);
          if (buff[pos] & 0x80) printf("-");
          int exponent = buff[pos]& ~0x80; pos++;
          char str[15];
          str[14]=0;
          for(int i=0;i<7;i++) sprintf(&str[i*2],"%02X",buff[pos++]);
          if (exponent==0) {
            printf(str,"0.%s",str);
          } else {
            for(int i=0;i<exponent;i++) printf("%c",str[i]);
            printf(".");
            for(int i=exponent;i<14;i++) printf("%c",str[i]);
          }
          break;
        }
        default:
          if(dbg)printf("/* char 0x%02x */",scode);
          if (scode < 0x80) {
            char tmpc = scode;
            printf("%c", tmpc);
          } else {
            printf("%s", scanTable(scode));
          }
          break;
      }
    }
    if (dbg) printf("/* pos = %d 0x%04x buff=0x%02x */",pos,pos,buff[pos]);
    pos = lp - ofs;
    if(dbg)printf("/* lp(%02x,%02x),pos=%d lp=%02x %02x */", buff[pos],buff[pos+1],pos, buff[pos+1],buff[pos]);
    lp = (buff[pos + 1] << 8) | buff[pos]; pos += 2;
    printf("\n");
  }

  return 0;
}

int hextoi(const char* srcStr) {
  int value = 0;
  int cc, cb;
  int i = 0;

  while (srcStr[i]) {
    cc = srcStr[i++];
    cb = -1;
    if (cc >= '0' & cc <= '9') {
      cb = cc - '0';
    }
    if (cc >= 'A' & cc <= 'F') {
      cb = cc - 'A' + 10;
    }
    if (cc >= 'a' & cc <= 'f') {
      cb = cc - 'a' + 10;
    }
    if (cb == -1) {
      return value;
    }
    value = value << 4;
    value |= cb;
  }
  return value;
}

const char* scanTable(int srcCode) {
  for (int i = 0; wordTable[i].value; i++)
    if (wordTable[i].value == srcCode) return wordTable[i].name;
  return NULL;
}
// 全データ読み込み
unsigned char* fileread(const char* fpath) {
  FILE* fr = fopen(fpath, "rb");
  if (!fr) return NULL;
  fseek(fr, 0, SEEK_END);
  fpos_t sz = 0;
  fgetpos(fr, &sz);
  if(dbg)printf("/*file size = %lld 0x%04llx*/\n",sz,sz);
  fseek(fr, 0, SEEK_SET);
  if(dbg)printf("/*seek ok*/\n");
  if (sz > 0x10000) return NULL;
  if(dbg)printf("/*malloc %lld*/\n",sz);
  unsigned char* buf = (unsigned char*)malloc(sz+1);
  if(dbg)printf("/* malloc ok %p*/\n",buf);
  if(buf==0) {
    printf("/* malloc error %p */",buf);
    return NULL;
  }
  if(dbg)printf("/* fread %p*/\n",buf);
  size_t r = fread(buf, 1, sz, fr);
  if(dbg)printf("/* fread ok %p %ld*/\n",fr,r);
  fclose(fr);
  if(dbg)printf("/* fclose ok %p */",buf);
  return buf;
}