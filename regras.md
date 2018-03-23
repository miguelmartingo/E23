Regras:

<<Modos>>

automatico: automatico = 1;
manual: automatico = 0;

<<Sensores>>

voltagem: volt;
luminusidade: lum;
infra-vermelhos: infra;
temperatura: temp;
humidade: hum;

<<Atuadores>>

iluminação: atuador_lum;
ar condicionado: atuador_temp;
controlador de humidade: atuador_hum;

Assume-se que os atuadores estão sempre em estado 0, 
com exceção nas seguintes condições

Se (lum < 300 || luz_manual == 1)
	atuador_luz = 1;

Se (temp < 20 || temp > 28 || temp_manual == 1)
	atuador_temp = 1;

Se (temp >=20 && temp <= 28)
	atuador_temp = 0;

Se (hum < 40 || hum > 55 || hum_manual == 1)
	atuador_hum = 1;

Se (hum >= 40 && hum <= 55)
	atuador_hum = 0;
