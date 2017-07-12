/*
	* tcl: tranformation des chiffres en lettres
	* (C) 2006 by Richard NIAMKE (niamke_r <at> hotmail <dot> com)
	*
	***************************************************************************
	* This program is free software; you can redistribute it and/or modify it *
	* under the terms of the GNU General Public License as published  by  the *
	* Free Software Foundation; either version 2 of the License, or (at  your *
	* option) any later version.                                              *
	*                                                                         *
	* This program is distributed in the hope that it  will  be  useful,  but *
	* WITHOUT ANY WARRANTY; without the implied warranty  of  MERCHANTABILITY *
	* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License *
	* for more details.                                                       *
	*                                                                         *
	* You should have received a copy of the GNU General Public License along *
	* with this program; if not, write to the Free Software Foundation, Inc., *
	* 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA                   *
	***************************************************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <getopt.h>



char* u1(char u)
{
	switch (u)
	{
		case '0' :
		return("zéro") ;
		case '1' :
		return("un") ;
		case '2' :
		return("deux") ;
		case '3' :
		return("trois") ;
		case '4' :
		return("quatre") ;
		case '5' :
		return("cinq") ;
		case '6' :
		return("six") ;
		case '7' :
		return("sept") ;
		case '8' :
		return("huit") ;
		case '9' :
		return("neuf") ;
	}
}

char* d1(char d)
{
	switch (d)
	{
		case '0' :
		return("dix") ;
		case '1' :
		return("onze") ;
		case '2' :
		return("douze") ;
		case '3' :
		return("treize") ;
		case '4' :
		return("quatorze") ;
		case '5' :
		return("quize") ;
		case '6' :
		return("seize") ;
		case '7' :
		return("dix-sept") ;
		case '8' :
		return("dix-huit") ;
		case '9' :
		return("dix-neuf") ;
	}
}


char* d2(char d)
{
	switch (d)
	{
		case '2' :
		return("vingt") ;
		case '3' :
		return("trente") ;
		case '4' :
		return("quarante") ;
		case '5' :
		return("cinquante") ;
		case '6' :
		case '7' :
		return("soixante") ;
		case '8' :
		case '9' :
		return("quatre-vingt") ;
	}
}


int main(int argc, char *argv[])
{
	
	char *nombre ;
	char lettres[256]="", interm[256]="" ;
	const int lmax = 15 ;
	int lg ; /* longueur de la chaine (nombre) passée en argument */
	int i, j=0 ; /* indices */
	
	int c ;
	
	char mil[4] ; /* Découpage en milliers */
	
	
	
	if (argc != 2)
	{
		printf("nombre d'argument incorrect !") ;
		return 1 ;
	}
	
	opterr = 0 ;
	while ((c = getopt (argc, argv, "hv")) != -1)
    switch (c)
    {
		case 'h':
		printf("Utilisaton : tcl  -h | -v | <nombre-a-transformer>.") ;
		return 0 ;
		case 'v':
		printf("tcl - version 0.1 (alpha).") ;
		return 0 ;
		case '?':
		printf("Option invalide : %c", optopt) ;
		return 1 ;
		default:
		abort () ;
	}
	
	
	
	lg = (int)strlen(argv[1]) ;
	
	if (lg > lmax)
	{
		printf ("Argument invalide : valeur numerique trop grande.") ;
		return 1 ;
	}
	
	for(i=0 ; i < lg ; i++)
	{
		if ( ! isdigit(argv[1][i]) )
		{
			printf ("Le caractère en position %d n'est pas numerique.", i+1) ;
			return 1 ;
		}
	}
	
	/* Cleaning leading 0 */
	for(i=0 ; i < lg ; i++)
	{
		j = i ;
		if (argv[1][i] != '0') break ;
	}
	
	nombre = &argv[1][j] ;
	lg = (int)strlen(nombre) ; /* longueur (réelle) sans les zéros avant */
	
	
	
	/* do the job... */
	i=lg-1 ;
	do
	{
		
		if ( (fmod(lg-i,3) == 3) || (fmod(lg-i,3) == 1) )
		{
			if (i >= 1)
			{
				switch (nombre[i-1])
				{
					case '0' :
						if (nombre[i] == '0')
							break ;
						sprintf(lettres,"%s %s", u1(nombre[i]), interm) ;
						strcpy(interm, lettres) ;
						break ;
					case '1' :
						sprintf(lettres,"%s %s", d1(nombre[i]), interm) ;
						strcpy(interm, lettres) ;
						break ;
					case '7' :
					case '9' :
						sprintf(lettres,"%s %s %s", d2(nombre[i-1]), d1(nombre[i]), interm) ;
						strcpy(interm, lettres) ;
						break ;
					default :
						if (nombre[i] == '0')
							sprintf(lettres,"%s %s", d2(nombre[i-1]), interm) ;
						else
						{
							sprintf(lettres,"%s %s %s", d2(nombre[i-1]), u1(nombre[i]), interm) ;
							strcpy(interm, lettres) ;
						}

				}
				i-- ;
			}
			else
			{
				sprintf(lettres,"%s %s", u1(nombre[i]), interm) ;
				strcpy(interm, lettres) ;
			}
		}
		
		if (fmod(lg-i,3) == 0)
		{
			switch (nombre[i])
			{
				case '0' :
					break ;
				case '1' :
					sprintf(lettres,"cent %s", interm) ;
					strcpy(interm, lettres) ;
					break ;
				default :
					sprintf(lettres,"%s cent %s", u1(nombre[i]), interm) ;
					strcpy(interm, lettres) ;
			}
			
			if (lg > 3 && lg-i == 3)
			{
				if (lg >= 6)
				{
					sscanf (&nombre[lg-6], "%3c", &mil) ;
					mil[3] = '\0' ;
				}
				else
				if (lg == 5)
				{
					sscanf (nombre, "%2c", &mil) ;
					mil[2] = '\0' ;
				}
				else
				if (lg == 4)
				{
					sscanf (nombre, "%c", &mil) ;
					mil[1] = '\0' ;
				}
				
				if (atoi(mil) > 0) sprintf(lettres,"mille %s", interm) ;
				if (atoi(mil) == 1) i=i-2 ;
				
				strcpy(interm, lettres) ;
			}
			else
			if (lg > 6 && lg-i == 6)
			{
				if (lg >= 9)
				{
					sscanf (&nombre[lg-9], "%3c", &mil) ;
					mil[3] = '\0' ;
				}
				else
				if (lg == 8)
				{
					sscanf (nombre, "%2c", &mil) ;
					mil[2] = '\0' ;
				}
				else
				if (lg == 7)
				{
					sscanf (nombre, "%c", &mil) ;
					mil[1] = '\0' ;
				}
				
				if (atoi(mil) == 1) sprintf(lettres,"million %s", interm) ;
				if (atoi(mil) > 1) sprintf(lettres,"millions %s", interm) ;
				
				strcpy(interm, lettres) ;
			}
			else
			if (lg > 9 && lg-i == 9)
			{
				if (lg >= 12)
				{
					sscanf (&nombre[lg-12], "%3c", &mil) ;
					mil[3] = '\0' ;
				}
				else
				if (lg == 11)
				{
					sscanf (nombre, "%2c", &mil) ;
					mil[2] = '\0' ;
				}
				else
                if (lg == 10)
                {
					sscanf (nombre, "%c", &mil) ;
					mil[1] = '\0' ;
				}
				
				if (atoi(mil) == 1) sprintf(lettres,"milliard %s", interm) ;
				if (atoi(mil) > 1) sprintf(lettres,"milliards %s", interm) ;
				
				strcpy(interm, lettres) ;
			}
			else
            if (lg > 12 && lg-i == 12)
            {
				if (lg == 15)
				{
					sscanf (nombre, "%3c", &mil) ;
					mil[3] = '\0' ;
				}
				else
                if (lg == 14)
                {
					sscanf (nombre, "%2c", &mil) ;
					mil[2] = '\0' ;
				}
                else
				if (lg == 13)
				{
                    sscanf (nombre, "%c", &mil) ;
                    mil[1] = '\0' ;
				}
				
				if (atoi(mil) > 0) sprintf(lettres,"mille %s", interm) ;
				if (atoi(mil) == 1) i=i-2 ;
				
				strcpy(interm, lettres) ;
			}
			
		}
		
		i-- ;
	}
	while (i >= 0) ;
	
	
	printf("\n%s en toute lettre : %s\n",nombre,lettres) ;
	
	return 0 ;
	
}
