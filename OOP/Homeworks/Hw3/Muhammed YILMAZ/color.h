/* HEADER : COLOR CODES
 * AUTHOR : Muhammed YILMAZ
 * DATE   : 13.05.2018
 * E-MAIL : yilmazmu15@itu.edu.tr
 */

#ifndef COLOR_H
#define COLOR_H

#ifdef __unix__

#define COLOR_FG_RED "\033[31m"
#define COLOR_FG_DEF "\033[39m"

#else   //not linux

#define COLOR_FG_RED ""
#define COLOR_FG_DEF ""

#endif  //linux
#endif //COLOR_H
