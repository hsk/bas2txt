#include <stdio.h>
#include <string.h>
 #include <ctype.h>
typedef struct Rec {
  const char* name;
  int value;
} Rec;
const Rec wordTable[] = {
    {">",       0xEE  },{"CMD",    0xD7  },{"ERROR",  0xA6  },{"LIST",    0x93  },
    {"PAINT",   0xBF  },{"SPRITE", 0xC7  },{"=",      0xEF  },{"COLOR",   0xBD  },
    {"ERR",    0xE2   },{"LLIST",  0x9E  },{"PDL",    0xFFA4},{"SQR",     0xFF87},
    {"<",       0xF0  },{"CONT",   0x99  },{"EXP",    0xFF8B},{"LOAD",    0xB5  },
    {"PEEK",    0xFF97},{"STEP",   0xDC  },{"+",      0xF1  },{"COPY",    0xD6  },
    {"FIELD",   0xB1  },{"LOCATE", 0xD8  },{"PLAY",   0xC1  },{"STICK",   0xFFA2},
    {"-",       0xF2  },{"COS",    0xFF8C},{"FILES",  0xB7  },{"LOC",     0xFFAC},
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
    {"ATN",     0xFF8E},{"DEFSTR", 0xAB  },{"GOTO",   0x89  },{"MID$",    0xFF83},
    {"REM",     0x8F  },{"TIME",   0xCB  },{"ATTR$",  0xE9  },{"DEFDBL",  0xAE  },
    {"HEX$",    0xFF9B},{"MKD$",   0xFFB0},{"RENUM",  0xAA  },{"TO",      0xD9  },
    {"AUTO",    0xA9  },{"DEFINT", 0xAC  },{"IF",     0x8B  },{"MKI$",    0xFFAE},
    {"RESTORE", 0x8C  },{"TROFF",  0xA3  },{"BASE",   0xC9  },{"DEFSNG",  0xAD  },
    {"IMP",     0xFA  },{"MKS$",   0xFFAF},{"RESUME", 0xA7  },{"TRON",    0xA2  },
    {"BEEP",    0xC0  },{"DEF",    0x97  },{"INKEY$", 0xEC  },{"MOD",     0xFB  },
    {"RETURN",  0x8E  },{"USING",  0xE4  },{"BIN$",   0xFF9D},{"DELETE",  0xA8  },
    {"INPUT",   0x85  },{"MOTOR",  0xCE  },{"RIGHT$", 0xFF82},{"USR",     0xDD  },
    {"BLOAD",   0xCF  },{"DIM",    0x86  },{"INP",    0xFF90},{"NAME",    0xD3  },
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

unsigned char buf[48 * 1024];
unsigned char head[] = {255};

Rec* search_keyword(char *str) {
  int i;
  char tmp[256];
  int slen = strlen(str);
  printf("slen=%d\n",slen);
  for(int l=0;l<slen && l < 8;l++) tmp[l]=toupper(str[l]);
  tmp[8]=0;tmp[slen]=0;
  Rec* rec = wordTable;
  for (; rec->value; rec++) {
    int len = strlen(rec->name);
    printf("%d len=%d %s %s\n",i,len,tmp,rec->name);
    if(slen < len) continue;
    if (memcmp(rec->name, tmp, len) == 0) {
      printf("ok=%d\n",i);
      return rec;
    }
  }
  printf("ng\n");
  return rec;
}

int main(int argc, char *argv[]) {
  unsigned int car, number, end, lastptr, adr;
  int j;
  FILE *in, *out;
  if (argc != 3) {
    printf("Usage : txt2bas txtfile <Oric-BASIC-file>\n");
    return 1;
  }
  in = fopen(argv[1], "r");
  if (in == NULL) {
    printf("Can't open input file\n");
    return 1;
  }
  out = fopen(argv[2], "wb");
  if (out == NULL) {
    printf("Can't open file for writing\n");
    return 1;
  }

  unsigned int i = 0;
  while (1) {
    int addr = i;
    buf[i++] = 0;
    buf[i++] = 0;
    printf("read lineNo\n");
    if (fscanf(in, "%u", &number) <= 0) break;
    buf[i++] = number & 0xFF;
    buf[i++] = number >> 8;
    j = 0;
    unsigned char ligne[256];
    printf("read line datas\n");
    while ((ligne[j] = getc(in)) != '\n') {
      j++;
    }
    if(j>0&&ligne[j-1]=='\r')j--;
    printf("read line datas ok\n");
    ligne[j] = 0;
    int ptr = 0;
    enum {REM=1,STRING,DATA};
    int mode = 0;
    if (ligne[ptr] == ' ') ptr++;
    while (ligne[ptr]) {
      switch(mode){
        case REM: buf[i++] = ligne[ptr++]; continue;
        case STRING:
          if (ligne[ptr] == '"') mode = 0;
          buf[i++] = ligne[ptr++];
          continue;
        case DATA:
          if (ligne[ptr] == ':') mode = 0;
          buf[i++] = ligne[ptr++];
          continue;
      }
      Rec* keyw = search_keyword(ligne + ptr);
      printf("value=%x\n",keyw->value);
      if (keyw->value > 0) {
        if (keyw->value == 0x84 || keyw->value == 0xCA) mode = DATA;//or CALL
        else if (keyw->value == 0x8F) mode = REM;
        if(keyw->value>=0x100) {
          buf[i++] = (keyw->value >> 8) & 0xff;
          buf[i++] = keyw->value & 0xff;
        } else buf[i++] = keyw->value;
        ptr += strlen(keyw->name);
      } else {
        if (ligne[ptr] == '\'') mode = REM;
        else if (ligne[ptr] == '"') mode = STRING;
        if (ligne[ptr] >= '0' && ligne[ptr] <= '9') {
          int start=ptr;
          while(ligne[ptr] >= '0' && ligne[ptr] <= '9') ptr++;
          unsigned int j;
          printf("sscanf %d\n",start);
          sscanf(&ligne[start],"%d",&j);
          printf("j=%d\n",j);
          if (j < 10) {
            buf[i++] = 0x11+j;
            continue;
          }
          if (j < 256) {
            buf[i++] = 0x0f;
            buf[i++] = j;
            continue;
          }
          if (j < 32768) {
            buf[i++] = 0x1c;
            buf[i++] = j & 255;
            buf[i++] = (j >> 8) & 255;
            continue;
          }
          ptr = start;
        }
        buf[i++] = ligne[ptr++];
      }
    }
    buf[i++] = 0;
    int ofs = i + 0x8001;
    buf[addr] = ofs & 0xff;
    buf[addr+1] = (ofs >> 8) & 0xff;
  }
  printf("read files ok\n");
  fwrite(head, 1, 1, out);
  fwrite(buf, 1, i, out);
  fclose(out);
}
