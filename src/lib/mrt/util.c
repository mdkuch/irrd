/*
 * $Id: util.c,v 1.3 2001/07/13 18:02:46 ljb Exp $
 */

#include <mrt.h>

/* r_inet_ntoa
 * A thread safe (and IPNG) version of inet_ntoa
 * takes allocated buffer and buffer size
 */
char *r_inet_ntoa (char *buf, int n, u_char *l, int len)
{
  memset (buf, 0, n);

  /*ASSERT ( (len >= 0) && (len < 255));*/

   if (len > 24)
      sprintf(buf, "%d.%d.%d.%d/%d", l[0], l[1], l[2], l[3], len);
   else if (len > 16)
      sprintf(buf, "%d.%d.%d/%d", l[0], l[1], l[2], len);
   else if (len > 8)
      sprintf(buf, "%d.%d/%d", l[0], l[1], len);
   else 
      sprintf(buf, "%d/%d", l[0], len);

   return (buf);
}

/* 
 * A thread safe (and IPNG) version of inet_ntoa
 * takes allocated buffer and buffer size
 * this doesn't append /length
 */
char *r_inet_ntoa2 (char *buf, int n, u_char *l)
{
   sprintf(buf, "%d.%d.%d.%d", l[0], l[1], l[2], l[3]);
   return (buf);
}

/* r_inet_ntoa
 * A thread safe (and IPNG) version of inet_ntoa
 * takes allocated buffer and buffer size
 */
char *rinet_ntoa (char *buf, int n, prefix_t *prefix)
{
  int len = prefix->bitlen;
  u_char *l = (u_char *) prefix_tochar (prefix);
  memset (buf, 0, n);

  /*ASSERT ( (len >= 0) && (len < 255));*/

   if (len > 24)
      sprintf(buf, "%d.%d.%d.%d/%d", l[0], l[1], l[2], l[3], len);
   else if (len > 16)
      sprintf(buf, "%d.%d.%d/%d", l[0], l[1], l[2], len);
   else if (len > 8)
      sprintf(buf, "%d.%d/%d", l[0], l[1], len);
   else 
      sprintf(buf, "%d/%d", l[0], len);

   return (buf);
}

/*-----------------------------------------------------------
 *  Name: 	my_strftime
 *  Created:	Mon Dec 19 14:15:42 1994
 *  Author: 	Craig Labovitz   <labovit@snoopy.merit.net>
 *  DESCR:  	Given a time long and format, return string. 
 *		If time <=0, use current time of day
 */

char *my_strftime(long in_time, char *fmt)
{
   char *tmp = NewArray (char, BUFSIZE);
   long t;
   struct tm *tm;

   if (in_time <= 0)
      t = time (NULL);
   else
      t = in_time;

   tm = localtime(&t);

   strftime (tmp, BUFSIZE, fmt, tm);
   return (tmp);
}


/*
 * returns pointer to a token
 * line, a pointer of pointer to the string will be updated to the next position
 * word is a strage for the token
 * if word == NULL, it will be dynamically allocated by malloc
 */

char *
uii_parse_line2 (char **line, char *word)
{
    char *cp = *line, *start;
    int len;

    int in_quote = 0;	/* used for grouping everything within a """" into a single token */

    /* skip spaces */
    while (*cp && isspace (*cp))
	cp++;

    start = cp;
    while ((in_quote || !isspace (*cp)) && (*cp != '\0') && (*cp != '\n')) {
      if (*cp == '\"') {
	if (in_quote == 0) 
	  in_quote = 1;
	else
	  in_quote = 0;
      }
      cp++;
    }

    if ((len = cp - start) > 0) {
	if (word == NULL) {
	    word = NewArray (char, len + 1);
	    assert (word);
	}
	memcpy (word, start, len);
	word[len] = '\0';
	*line = cp;
	return (word);
    }

    return (NULL);
}
