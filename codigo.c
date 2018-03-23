//#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct atuadores{
//iniciam-se em zero
int temperatura;
int humidade;
int luz;
int infravermelho;

} atuadores;

struct atuadores sala, cozinha, quarto1, quarto2; //mote: 1,2,3 e 4 respetivamente

int checker(char input[])
{
int result = 1;


if ((input[0]!='7') || (input[1]!='E') ){
	result=0;}

     return result;
}

long moteID(char *a, char *b) {

int mote;
mote = strtol(a,NULL,16)*256;
mote = mote + strtol(b,NULL,16);

return mote;
}
long volts(char *a, char *b) {

float volt;
volt = strtol(a,NULL,16)*256;
volt = volt + strtol(b,NULL,16);
volt = volt*1.5*2/4096;

return volt;
}
long luz(char *a, char *b) {

float luz;
luz = strtol(a,NULL,16)*256;
luz = luz + strtol(b,NULL,16);
luz = luz*2.2888;

return luz;
}
long ired(char *a, char *b) {

float inf;
inf = strtol(a,NULL,16)*256;
inf = inf + strtol(b,NULL,16);
inf = inf*0.28162;

return inf;
}
long tempe(char *a, char *b) {

float temp;
temp = strtol(a,NULL,16)*256;
temp = temp + strtol(b,NULL,16);
temp = temp*0.01-39.6;

return temp;
}
long humi(char *a, char *b, long temp) {

long hum, hum2, humreal;
hum = strtol(a,NULL,16)*256;
hum = hum + strtol(b,NULL,16);
hum2 = -2.0468 + 0.0367 * (float)hum - 0.0000015955 * (float)hum*(float)hum;
humreal = ((float)temp - 25) * (0.01 + 0.00008*hum) + hum2;

return humreal;
}

int main()
{
FILE *f;

char input[100];
char *token, *aux1, *aux2;
long mote, volt,light,infra,temp,hum;
float v_arm[4], l_arm[4], i_arm[4], t_arm[4], h_arm[4];


while(1)
{
	int i = 0;
	if (fgets(input,100,stdin) == NULL)
	{
		printf("Falha\n");
		break;
	}

	if(checker(input) == 0){
			printf("Mensagem Inválida\n");
			;}

	token=strtok(input," ");

	while(token!=NULL){

		if (i == 5)
		{
		aux1 = token;
		printf("Teste\n");
		}
		if (i == 6)
		{
			//durante a execução do programa vai-se assumir que 1<=mote<=5;
			aux2 = token;
			mote = moteID(aux1, aux2);
			printf("%ld é o mote; ", mote);
		}
		if(i == 10)
		{
			aux1 = token;
		}
		if(i == 11)
		{
			aux2 = token;
			volt = volts(aux1, aux2);
			printf("volts =%.2ld; ", volt);
		}
		if (i == 12)
		{
			aux1 = token;
		}
		if (i == 13)
		{
			aux2 = token;
			light = luz(aux1, aux2);
			printf("luz = %.2ld; ", light);
		}
		if (i == 14)
		{
			aux1 = token;
		}
		if (i == 15)
		{
			aux2 = token;
			infra = ired(aux1, aux2);
			printf("infravermelhos = %.2ld; ", infra);
		}
		if(i == 16)
		{
			aux1 = token;
		}
		if(i == 17)
		{
			aux2 = token;
			temp=tempe(aux1, aux2);
			printf("Temperatura = %.2ld; ", temp);
		}
		if(i == 1)
		{
			aux1 = token;
		}
		if(i == 19)
		{
			aux2 = token;
			hum=humi(aux1, aux2, temp);
			printf("Humidade = %.2ld%%\n", hum);
		}
		i++;
		token=strtok(NULL," ");
		}

	int valor = 0;

	//<<Sensores>>

	if(mote>=1 && mote<=5)
	{
	v_arm[mote-1] = volt;
	l_arm[mote-1] = light;
	i_arm[mote-1] = infra;
	t_arm[mote-1] = temp;
	h_arm[mote-1] = hum;
	}

	//lum min:  300lux
	//temp min: 20ºC   temp max: 28ºC
	//hum min:  40%    hum max:  55%

	//<<Atuadores>>

	if(l_arm[mote-1] < 300 )
	{
		if(mote == 1)
			sala.luz = 1;
		if(mote == 2)
			cozinha.luz = 1;
		if(mote == 3)
			quarto1.luz = 1;
		if(mote == 4)
			quarto2.luz = 1;
	}

	/*if (l_arm[mote-1] >= 300 )
	{
		if(mote == 1)
			sala.luz = 0;
		if(mote == 2)
			cozinha.luz = 0;
		if(mote == 3)
			casab.luz = 0;
		if(mote == 4)
			quarto1.luz = 0;
		if(mote == 5)
			quarto2.luz = 0;
	}*/



	if(t_arm[mote-1] < 20 || t_arm[mote-1] > 2
	{
		if(mote == 1)
			sala.temperatura = 1;
		if(mote == 2)
			cozinha.temperatura = 1;
		if(mote == 3)
			quarto1.temperatura = 1;
		if(mote == 4)
			quarto2.temperatura = 1;
	}

	if(t_arm[mote-1] >= 20 && t_arm[mote-1] <= 2
	{
		if(mote == 1)
			sala.temperatura = 0;
		if(mote == 2)
			cozinha.temperatura = 0;
		if(mote == 3)
			quarto1.temperatura = 0;
		if(mote == 4)
			quarto2.temperatura = 0;

	}

	if(h_arm[mote-1] < 40 || h_arm[mote-1] > 55)
	{
		if(mote == 1)
			sala.humidade = 1;
		if(mote == 2)
			cozinha.humidade = 1;
		if(mote == 3)
			quarto1.humidade = 1;
		if(mote == 4)
			quarto2.humidade = 1;
	}

	if(h_arm[mote-1] >= 40 && h_arm[mote-1] <= 55)
	{
		if(mote == 1)
			sala.humidade = 0;
		if(mote == 2)
			cozinha.humidade = 0;
		if(mote == 3)
			quarto1.humidade = 0;
		if(mote == 4)
			quarto2.humidade = 0;
	}



f = fopen("matriz.txt","w");

printf("%d %d %d %d\n", cozinha.temperatura, cozinha.humidade, cozinha.luz, cozinha.infravermelho);

//<<Impressão da matriz>>
fprintf(f,"[[%d,%d,%d],[%d,%d,%d],[%d,%d,%d],[%d,%d,%d],", 255,255-255*sala.temperatura,255-255*sala.temperatura,    255-190*sala.humidade, 255-150*sala.humidade,255-30*sala.humidade,      255,255,255-255*sala.luz,      255-127*sala.infravermelho,255-255*sala.infravermelho,255-255*sala.infravermelho);

fprintf(f,"[%d,%d,%d],[%d,%d,%d],[%d,%d,%d],[%d,%d,%d],", 255,255-255*cozinha.temperatura,255-255*cozinha.temperatura,    255-190*cozinha.humidade, 255-150*cozinha.humidade,255-30*cozinha.humidade,      255,255,255-255*cozinha.luz,      255-127*cozinha.infravermelho,255-255*cozinha.infravermelho,255-255*cozinha.infravermelho);

 fprintf(f,"[%d,%d,%d],[%d,%d,%d],[%d,%d,%d],[%d,%d,%d], ", 255,255-255*sala.temperatura,255-255*sala.temperatura,    255-190*quarto1.humidade, 255-150*quarto1.humidade,255-30*quarto1.humidade,      255,255,255-255*quarto1.luz,      255-127*quarto1.infravermelho,255-255*quarto1.infravermelho,255-255*quarto1.infravermelho);

 fprintf(f,"[%d,%d,%d],[%d,%d,%d],[%d,%d,%d],[%d,%d,%d]]", 255,255-255*quarto2.temperatura,255-255*quarto2.temperatura,    255-190*quarto2.humidade, 255-150*quarto2.humidade,255-30*quarto2.humidade,      255,255,255-255*quarto2.luz,      255-127*quarto2.infravermelho,255-255*quarto2.infravermelho,255-255*quarto2.infravermelho);


fclose(f);

}

}
