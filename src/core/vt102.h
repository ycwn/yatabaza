

#ifndef __CORE_VT102_H
#define __CORE_VT102_H


#define VT102_ESC  "\033"
#define VT102_CSI  VT102_ESC "["

#define VT102_RIS  VT102_ESC "c"    // Reset
#define VT102_IND  VT102_ESC "D"    // Linefeed
#define VT102_NEL  VT102_ESC "E"    // Newline
#define VT102_HTS  VT102_ESC "H"    // Set tab stop at current column.
#define VT102_RI   VT102_ESC "M"    // Reverse linefeed

#define VT102_DECID  VT102_ESC "Z"    // DEC private identification.
#define VT102_DECSC  VT102_ESC "7"    // Save current state
#define VT102_DECRC  VT102_ESC "8"    // Restore state most recently saved

#define VT102_CHR_ISO   VT102_ESC "%@"   // Select default (ISO 646 / ISO 8859-1)
#define VT102_CHR_UTF8  VT102_ESC "%G"   // Select UTF-8

#define VT102_SCS_G0_UK       VT102_ESC "(A"   // Select G0 UK character set
#define VT102_SCS_G0_US       VT102_ESC "(B"   // Select G0 US character set
#define VT102_SCS_G0_SPEC     VT102_ESC "(0"   // Select G0 special characters and line drawing
#define VT102_SCS_G0_ALTROM   VT102_ESC "(1"   // Select G0 alternate ROM
#define VT102_SCS_G0_ALTSPEC  VT102_ESC "(2"   // Select G0 alternate ROM and special characters

#define VT102_SCS_G1_UK       VT102_ESC ")A"   // Select G1 UK character set
#define VT102_SCS_G1_US       VT102_ESC ")B"   // Select G1 US character set
#define VT102_SCS_G1_SPEC     VT102_ESC ")0"   // Select G1 special characters and line drawing
#define VT102_SCS_G1_ALTROM   VT102_ESC ")1"   // Select G1 alternate ROM
#define VT102_SCS_G1_ALTSPEC  VT102_ESC ")2"   // Select G1 alternate ROM and special characters

#define VT102_DECPNM  VT102_ESC ">"    // Set numeric keypad mode
#define VT102_DECPAM  VT102_ESC "="    // Set application keypad mode

#define VT102_ICH(n)  VT102_CSI #n "@"    // Insert the indicated # of blank characters.

#define VT102_CUU(n)  VT102_CSI #n "A"    // Move cursor up the indicated # of rows.
#define VT102_CUD(n)  VT102_CSI #n "B"    // Move cursor down the indicated # of rows.
#define VT102_CUF(n)  VT102_CSI #n "C"    // Move cursor right the indicated # of columns.
#define VT102_CUB(n)  VT102_CSI #n "D"    // Move cursor left the indicated # of columns.

#define VT102_CNL(n)    VT102_CSI #n "E"           // Move cursor down the indicated # of rows, to column 1.
#define VT102_CPL(n)    VT102_CSI #n "F"           // Move cursor up the indicated # of rows, to column 1.
#define VT102_CHA(n)    VT102_CSI #n "G"           // Move cursor to indicated column in current row.
#define VT102_CUP(r,c)  VT102_CSI #r ";" #c "H"    // Move cursor to the indicated row, column

#define VT102_ED_E   VT102_CSI  "J"    // Erase display: from cursor to end of display
#define VT102_ED_S   VT102_CSI "1J"    // Erase display: from start to cursor
#define VT102_ED_A   VT102_CSI "2J"    // Erase display: whole display
#define VT102_ED_AB  VT102_CSI "3J"    // Erase display: whole display including scroll-back buffer

#define VT102_EL_E   VT102_CSI  "K"    // Erase line: from cursor to end of line
#define VT102_EL_S   VT102_CSI  "1K"   // Erase line: from start of line to cursor
#define VT102_EL_A   VT102_CSI  "2K"   // Erase line: whole line

#define VT102_IL(n)  VT102_CSI #n "L"    // Insert the indicated # of blank lines.
#define VT102_DL(n)  VT102_CSI #n "N"    // Delete the indicated # of lines.

#define VT102_DCH(n)  VT102_CSI #n "P"   // Delete the indicated # of characters on current line.
#define VT102_ECH(n)  VT102_CSI #n "X"   // Erase the indicated # of characters on current line.

#define VT102_HPR(n)  VT102_CSI #n "a"   // Move cursor right the indicated # of columns.
#define VT102_VPR(n)  VT102_CSI #n "e"   // Move cursor down the indicated # of rows.


#define VT102_SGR_RESET  VT102_CSI "0m"

#define VT102_SGR_BOLD_ON        VT102_CSI "1m"
#define VT102_SGR_HALFBRIGHT_ON  VT102_CSI "2m"
#define VT102_SGR_UNDERSCORE_ON  VT102_CSI "4m"
#define VT102_SGR_BLINK_ON       VT102_CSI "5m"
#define VT102_SGR_REVERSE_ON     VT102_CSI "7m"

#define VT102_SGR_BOLD_OFF        VT102_CSI "21m"
#define VT102_SGR_HALFBRIGHT_OFF  VT102_CSI "22m"
#define VT102_SGR_UNDERLINE_OFF   VT102_CSI "24m"
#define VT102_SGR_BLINK_OFF       VT102_CSI "25m"
#define VT102_SGR_REVERSE_OFF     VT102_CSI "27m"

#define VT102_SGR_COLOR_FG_BLACK         VT102_CSI "30m"
#define VT102_SGR_COLOR_FG_DARK_RED      VT102_CSI "31m"
#define VT102_SGR_COLOR_FG_DARK_GREEN    VT102_CSI "32m"
#define VT102_SGR_COLOR_FG_BROWN         VT102_CSI "33m"
#define VT102_SGR_COLOR_FG_DARK_BLUE     VT102_CSI "34m"
#define VT102_SGR_COLOR_FG_DARK_MAGENTA  VT102_CSI "35m"
#define VT102_SGR_COLOR_FG_DARK_CYAN     VT102_CSI "36m"
#define VT102_SGR_COLOR_FG_DARK_GRAY     VT102_CSI "37m"

#define VT102_SGR_COLOR_FG_BRIGHT_GRAY     VT102_CSI "90m"
#define VT102_SGR_COLOR_FG_BRIGHT_RED      VT102_CSI "91m"
#define VT102_SGR_COLOR_FG_BRIGHT_GREEN    VT102_CSI "92m"
#define VT102_SGR_COLOR_FG_YELLOW          VT102_CSI "93m"
#define VT102_SGR_COLOR_FG_BRIGHT_BLUE     VT102_CSI "94m"
#define VT102_SGR_COLOR_FG_BRIGHT_MAGENTA  VT102_CSI "95m"
#define VT102_SGR_COLOR_FG_BRIGHT_CYAN     VT102_CSI "96m"
#define VT102_SGR_COLOR_FG_WHITE           VT102_CSI "97m"

#define VT102_SGR_COLOR_BG_BLACK         VT102_CSI "40m"
#define VT102_SGR_COLOR_BG_DARK_RED      VT102_CSI "41m"
#define VT102_SGR_COLOR_BG_DARK_GREEN    VT102_CSI "42m"
#define VT102_SGR_COLOR_BG_BROWN         VT102_CSI "43m"
#define VT102_SGR_COLOR_BG_DARK_BLUE     VT102_CSI "44m"
#define VT102_SGR_COLOR_BG_DARK_MAGENTA  VT102_CSI "45m"
#define VT102_SGR_COLOR_BG_DARK_CYAN     VT102_CSI "46m"
#define VT102_SGR_COLOR_BG_DARK_GRAY     VT102_CSI "47m"

#define VT102_SGR_COLOR_BG_BRIGHT_GRAY     VT102_CSI "100m"
#define VT102_SGR_COLOR_BG_BRIGHT_RED      VT102_CSI "101m"
#define VT102_SGR_COLOR_BG_BRIGHT_GREEN    VT102_CSI "102m"
#define VT102_SGR_COLOR_BG_YELLOW          VT102_CSI "103m"
#define VT102_SGR_COLOR_BG_BRIGHT_BLUE     VT102_CSI "104m"
#define VT102_SGR_COLOR_BG_BRIGHT_MAGENTA  VT102_CSI "105m"
#define VT102_SGR_COLOR_BG_BRIGHT_CYAN     VT102_CSI "106m"
#define VT102_SGR_COLOR_BG_WHITE           VT102_CSI "107m"


#endif

